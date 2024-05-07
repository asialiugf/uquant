#include "Bars.h"

#include <cjson/cJSON.h>
#include <float.h>
#include <limits.h>
#include <string.h>

#include <iostream>
#include <map>

#include "base/error_log.h"
#include "base/timestamp.h"
#include "file.h"
// #include "FuList.h"
#include "global.h"
#include "libdeflate.h"
#include "zlib.h"

namespace uBEE {

uint64_t before;
uint64_t latency;

static sData *nData = new sData(); // Data for send !!
static sTick *nTick = new sTick(); // Data for send !!

Segment::Segment() {
    see_memzero(cB, 9);
    see_memzero(cE, 9);
    iB = -1;
    iE = -1;
    iI = -1;   // 和前一个 segment之间的间隔。如果是第一个segment， iI = 0;
    mark = -1; // 0 表示 seg 包含 bar。 // 1.2.3. 表示 一个bar 包含多个 seg。
    sn = -1;
    see_memzero(barB, 9);
    see_memzero(barE, 9);
    bariB = -1;
    bariE = -1;
    barBx = -1; // 记录 起始barB所在的 seg[]的 index .
    barEx = -1; // 记录 结束barE所在的 seg[]的 index .
}

// ---------------------------------------------------------
/*
 init Time Block.
 TT:member 成员变量
 M_TimeType: defined in Bars.h , there are 7 types of trading time.
 从 M_TimeType 取内容，初始化 TT这个数组，TT的每个时间类型，都包括了time
 segments.
*/
TimeBlock::TimeBlock() {
    uBEE::ErrLog(1000, " enter into TimeBlock()!", 1, 0, 0);
    cJSON *jRoot;
    cJSON *jTime;
    cJSON *jTemp;
    char ca_h[3];
    char ca_m[3];
    int ih;
    int im;
    int i, n;
    const std::map<int, std::string> *MP;
    MP = &M_TimeType;

    for (auto it = (*MP).begin(); it != (*MP).end(); ++it) {
        TT[it->first].iType = it->first;
        for (i = 0; i < SGM_NUM; i++) {
            TT[it->first].aSgms[i].iB = -1;
            TT[it->first].aSgms[i].iE = -1;
            TT[it->first].aSgms[i].iI = -1;
        }

        jRoot = cJSON_Parse(it->second.c_str());
        jTime = cJSON_GetObjectItem(jRoot, "time");
        n = cJSON_GetArraySize(jTime);

        TT[it->first].iSegNum = n;
        // std::cout << TT[it->first].iSegNum << "pppppppppppppppppppppp" <<
        // std::endl;
        for (i = 0; i < n; i++) {
            jTemp = cJSON_GetArrayItem(jTime, i);

            std::cout << jTemp->valuestring << std::endl;
            see_memzero(TT[it->first].aSgms[i].cB, 9);
            see_memzero(TT[it->first].aSgms[i].cE, 9);

            memcpy(TT[it->first].aSgms[i].cB, jTemp->valuestring, 5);
            memcpy(TT[it->first].aSgms[i].cB + 5, ":00", 3);
            memcpy(TT[it->first].aSgms[i].cE, jTemp->valuestring + 6, 5);
            memcpy(TT[it->first].aSgms[i].cE + 5, ":00", 3);
            std::cout << "cE: " << TT[it->first].aSgms[i].cE << std::endl;

            see_memzero(ca_h, 3);
            see_memzero(ca_m, 3);
            memcpy(ca_h, TT[it->first].aSgms[i].cB, 2);
            memcpy(ca_m, TT[it->first].aSgms[i].cB + 3, 2);
            ih = atoi(ca_h);
            im = atoi(ca_m);
            TT[it->first].aSgms[i].iB = ih * 3600 + im * 60;

            see_memzero(ca_h, 3);
            see_memzero(ca_m, 3);
            memcpy(ca_h, TT[it->first].aSgms[i].cE, 2);
            memcpy(ca_m, TT[it->first].aSgms[i].cE + 3, 2);
            ih = atoi(ca_h);
            im = atoi(ca_m);
            TT[it->first].aSgms[i].iE = ih * 3600 + im * 60;

            if (i == 0) {
                TT[it->first].aSgms[i].iI = 0;
            } else {
                if (TT[it->first].aSgms[i].iB >= TT[it->first].aSgms[i - 1].iE) {
                    TT[it->first].aSgms[i].iI = TT[it->first].aSgms[i].iB - TT[it->first].aSgms[i - 1].iE;
                } else {
                    TT[it->first].aSgms[i].iI = TT[it->first].aSgms[i].iB - TT[it->first].aSgms[i - 1].iE + 86400;
                }
            }
        }
        // std::cout << "mmmm " << jTemp->valuestring << std::endl;
    }
    cJSON_Delete(jRoot);
}

int TimeBlock::Init(stTimeType TT[]) { return 0; }

/*
  // 初始化 bar block(BarBlock) !!! ，每个 future block (FutureBlock) 有 50个 BarBlock ;
  // 每个future的交易时间类型不一样 每个 FutureBlock 有一个不同的pTimeType
  // 根据period + pTimeType， 初始化 BarBlock的 （Segment     *seg[100] ;）
  // new BarBlock("5F",300,pt);
*/
BarBlock::BarBlock(const char *pF, int period_value, stTimeType *pTimeType) {
    char cB[9];
    char cE[9];

    char cT[9];
    int iT;
    int idxT;

    char cTmp[9];
    int iB;
    int iE;
    int iI;
    int mark;

    for (int i = 0; i < 100; i++) {
        seg[i] = nullptr;
    }

    // ------------  tick ---------------------
    if (period_value == 0) {
        period_value_ = 0;
        iH = 0;
        iM = 0;
        iS = 0;
        memcpy(cF, pF, strlen(pF));

        for (int i = 0; i < pTimeType->iSegNum; i++) {
            iB = pTimeType->aSgms[i].iB;
            iE = pTimeType->aSgms[i].iE;
            seg[i] = new Segment();
            memcpy(seg[i]->cB, pTimeType->aSgms[i].cB, 9);
            memcpy(seg[i]->cE, pTimeType->aSgms[i].cE, 9);
            seg[i]->iB = iB;
            seg[i]->iE = iE;
            seg[i]->mark = 0;
        }

        iSegNum = pTimeType->iSegNum;
        curiX = 0;
        see_memzero(curB, 9); // 当第一次调用DealBar()时，判断tick一定不在这个区间，于是走到
                              // （MARK<0）这个流程中去.
        see_memzero(curE, 9);

        return;
    }

    // 成员变量 ----------------
    period_value_ = period_value;
    iH = period_value / 3600;
    iM = (period_value - iH * 3600) / 60;
    iS = period_value % 60;
    memcpy(cF, pF, strlen(pF));

    int last = 0; // 一个bar跨seg，在后面一个seg还差的时间数量
    int idx = 0;
    for (int i = 0; i < pTimeType->iSegNum; i++) {
        iB = pTimeType->aSgms[i].iB;
        iE = pTimeType->aSgms[i].iE;

        if (T________) {
            sprintf(ca_errmsg, "------ i:%d iSegNum:%d iB:%d  iE:%d last:%d ", i, pTimeType->iSegNum, iB, iE, last);
            uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
            sprintf(ca_errmsg, "------ pTimeType->aSgms[i].cB:%s .cE:%s", pTimeType->aSgms[i].cB, pTimeType->aSgms[i].cE);
            uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
        }

        if (last > 0) {
            if (iB + last <= iE) {
                // seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
                seg[idx] = new Segment();

                seg[idx]->iB = iB;
                seg[idx]->iE = iB + last;

                mark++;
                seg[idx]->mark = mark;

                MakeTime(seg[idx]->cB, seg[idx]->iB);
                MakeTime(seg[idx]->cE, seg[idx]->iE);

                if (T________) {
                    sprintf(ca_errmsg,
                            "2222--- idx:%d mark:%d seg[idx]->cB:%s "
                            "seg[idx]->cE:%s",
                            idx, mark, seg[idx]->cB, seg[idx]->cE);
                    uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
                }

                memcpy(seg[idx]->barB, cT, 9);
                seg[idx]->bariB = iT;
                seg[idx]->barBx = idxT;
                for (int j = 0; j < mark; j++) {
                    int k = idx - j;
                    memcpy(seg[k]->barE, seg[idx]->cE, 9);
                    seg[k]->bariE = seg[idx]->iE;
                    seg[k]->barEx = idx;

                    if (T________) {
                        sprintf(ca_errmsg,
                                "3333--- idx:%d mark:%d seg[idx]->barB:%s "
                                "seg[idx]->barE:%s",
                                idx, seg[k]->mark, seg[k]->barB, seg[k]->barE);
                        uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
                    }
                }

                mark = 0;
                idx++;
            } else if (iB + last > iE) {
                // seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
                seg[idx] = new Segment();

                seg[idx]->iB = iB;
                seg[idx]->iE = iE;

                mark++;
                seg[idx]->mark = mark;

                MakeTime(seg[idx]->cB, seg[idx]->iB);
                MakeTime(seg[idx]->cE, seg[idx]->iE);

                if (T________) {
                    sprintf(ca_errmsg,
                            "4444--- idx:%d mark:%d seg[idx]->cB:%s "
                            "seg[idx]->cE:%s",
                            idx, mark, seg[idx]->cB, seg[idx]->cE);
                    uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
                }

                memcpy(seg[idx]->barB, cT, 9);
                seg[idx]->bariB = iT;
                seg[idx]->barBx = idxT;
                if (i == pTimeType->iSegNum - 1) {
                    for (int j = 0; j < mark; j++) { // 【A】
                        int k = idx - j;
                        memcpy(seg[k]->barE, seg[idx]->cE, 9);
                        seg[k]->bariE = seg[idx]->iE;
                        seg[k]->barEx = idx;

                        if (T________) {
                            sprintf(ca_errmsg,
                                    "5555--- idx:%d mark:%d segBE:%s--%s  "
                                    "barBE:%s--%s",
                                    idx, seg[k]->mark, seg[k]->cB, seg[k]->cE, seg[k]->barB, seg[k]->barE);
                            uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
                        }
                    }
                    idx++;
                    break;
                }

                last = last + iB - iE;
                idx++;
                continue;
            }
        }

        iB = iB + last;
        int len = iE - iB;
        int num = len / period_value_;
        int mo = len % period_value_;

        if (len == 0) {
            last = 0;
            continue;
        }

        if (mo > 0) {
            last = period_value_ - mo;
        } else {
            last = 0;
        }

        if (T________) {
            sprintf(ca_errmsg, "6666--- idx:%d iB:%d len:%d num:%d mo:%d last:%d", idx, iB, len, num, mo, last);
            uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
        }

        if (num > 0) {
            // seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
            seg[idx] = new Segment();
            seg[idx]->iB = iB;
            seg[idx]->iE = iE - mo;
            mark = 0;
            seg[idx]->mark = 0;

            MakeTime(seg[idx]->cB, seg[idx]->iB);
            MakeTime(seg[idx]->cE, seg[idx]->iE);

            if (T________) {
                sprintf(ca_errmsg, "7777--- idx:%d mark:%d seg B:%s seg E:%s", idx, mark, seg[idx]->cB, seg[idx]->cE);
                uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
            }

            idx++;
        }

        if (mo > 0) {
            // seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
            seg[idx] = new Segment();
            seg[idx]->iB = iE - mo;
            seg[idx]->iE = iE;
            mark = 1;
            seg[idx]->mark = mark;

            MakeTime(seg[idx]->cB, seg[idx]->iB);
            MakeTime(seg[idx]->cE, seg[idx]->iE);

            if (T________) {
                sprintf(ca_errmsg, "8888--- idx:%d mark:%d mo:%d seg B:%s seg E:%s", idx, mark, mo, seg[idx]->cB, seg[idx]->cE);
                uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
            }

            memcpy(seg[idx]->barB, seg[idx]->cB, 9);
            seg[idx]->bariB = seg[idx]->iB;
            seg[idx]->barBx = idx;
            if (i == pTimeType->iSegNum - 1) {
                memcpy(seg[idx]->barE, seg[idx]->cE, 9);
                seg[idx]->bariE = seg[idx]->iE;
                seg[idx]->barEx = idx;
                if (T________) {
                    sprintf(ca_errmsg,
                            "9999--- idx:%d mark:%d seg[idx]->barB:%s "
                            "seg[idx]->barE:%s",
                            idx, seg[idx]->mark, seg[idx]->barB, seg[idx]->barE);
                    uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
                }
            }
            memcpy(cT, seg[idx]->cB, 9);
            iT = seg[idx]->iB;
            idxT = idx;
            idx++;
        }
    } // --- end for

    iSegNum = idx;
    if (T________) {
        sprintf(ca_errmsg, "-------------------iSegNum:%d", iSegNum);
        uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
    }

    // ------- 最后多申请一个 seg. -- 用于最开始第一个Kbar处理。 ------
    curiX = iSegNum;
    // seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
    seg[idx] = new Segment();
    seg[idx]->sn = 0;
    see_memzero(seg[idx]->cB, 9);
    see_memzero(seg[idx]->cE, 9);
    see_memzero(seg[idx]->barB, 9);
    see_memzero(seg[idx]->barE, 9);
    seg[idx]->iB = 0;
    seg[idx]->iE = 0;
    seg[idx]->bariB = 0;
    seg[idx]->bariE = 0;
    seg[idx]->mark = -1; // MARK < 0
    // 当第一次调用DealBar()时，判断tick一定不在这个区间，于是走到
    // （MARK<0）这个流程中去.

    see_memzero(curB, 9);
    see_memzero(curE, 9);

    // ---------------------------- 初始化  bar0 bar1 ----------------
    //  seg->sn 表示当前段和下一段之间是否连续。
    for (int i = 0; i < iSegNum; i++) {
        seg[i]->sn = 0;
        if (i < iSegNum - 1) {
            if (memcmp(seg[i]->cE, seg[i + 1]->cB, 8) != 0) {
                seg[i]->sn = 1;
                if (memcmp(seg[i]->cE, "24:00:00", 8) == 0 && memcmp(seg[i + 1]->cB, "00:00:00", 8) == 0) {
                    seg[i]->sn = 0;
                }
            }
        } else {
            seg[i]->sn = 1;
        }
    }

    // ----- 如果两个seg连续，则将前一个seg->iE 减1。 比如：24:00:00
    // 00:00:00连续，则前一个seg结束改成 23:59:59
    for (int i = 0; i < iSegNum; i++) {
        if (seg[i]->sn == 0) {
            seg[i]->iE -= 1;
            MakeTime(seg[i]->cE, seg[i]->iE);
        }
    }

    for (int i = 0; i < iSegNum; i++) {
        if (seg[i]->mark != 0) {
            int e = seg[i]->barEx;
            memcpy(seg[i]->barE, seg[e]->cE, 9);
            seg[i]->bariE = seg[e]->iE;
        }
    }

    // -----------------------------------------------------------------

    b1 = &bar1;

    stBar tmpBar;
    see_memzero(tmpBar.cB, 9);
    see_memzero(tmpBar.cE, 9);
    tmpBar.h = DBL_MIN;
    tmpBar.o = SEE_NAN;
    tmpBar.c = SEE_NAN;
    tmpBar.l = DBL_MAX;
    tmpBar.v = 0;
    tmpBar.vsum = 0; // 开始的第一个bar 的 v 值 可能会有问题！！
    tmpBar.vold = 0; // 开始的第一个bar 的 v 值 可能会有问题！！
    tmpBar.sent = 0;

    memcpy((char *)b1, &tmpBar, sizeof(stBar));

    if (T________) {
        sprintf(ca_errmsg, "--------------------------------------out BarBlock\n\n");
        uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
    }
}

/*
  Future Block !
  char *caFuture : future name
  uBEE::TimeBlock *tmbo : 时间块
*/

// FutureBlock::FutureBlock(char *caFuture, uBEE::TimeBlock *tmbo, uWS::Group<uWS::SERVER> *sg) {
FutureBlock::FutureBlock(const char *caFuture, uBEE::TimeBlock *tmbo) {
    if (T________) {
        uBEE::ErrLog(1000, " FutureBlock::FutureBlock():enter!", 1, 0, 0);
    }

    // SG = sg;

    iTickValid = -1;
    iChange = 0;

    see_memzero(InstrumentID, 81);
    see_memzero(UpdateTime, 9);

    memcpy(InstrumentID, caFuture, strlen(caFuture));

    // charmi-- 从 ag1803 取合约 "ag"
    char fn[3];
    // see_memzero(fn, 3);
    fn[2] = 0;
    memcpy(fn, caFuture, 2);
    if (fn[1] <= '9' && fn[1] >= '0') {
        fn[1] = 0;
    }

    // 初始化 pTimeType [stTimeType  *pTimeType]
    std::map<std::string, int>::const_iterator it;
    it = M_FuTime.find(fn);
    if (it == M_FuTime.end()) {
        sprintf(ca_errmsg, "FutureBlock::FutureBlock() :M_FuTime error:not defined: %s %s", InstrumentID, fn);
        uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
        return;
    } else {
        sprintf(ca_errmsg, "FutureBlock::FutureBlock(): future:%s %s timetype:%d, TimeType:", InstrumentID, fn, it->second);
        uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
        pTimeType = &tmbo->TT[it->second];
    }

    // -- 初始化 BarBlock[50] ;  BarBlock ----------------------------------------
    /*
    // 不同的周期，相当于不同的 frequency : fr     fr= 1 表示周期为1秒     fr= 60 表示周期为60秒
    //  默认周期有以下30个：
    //  0  1  2  3  4  5   6   7   8   9  10 11 12 13  14  15  16  17 18 19 20 21 22 23 24  25  26
    27 28 29 30
    //  T  1S 2S 3S 5S 10S 15S 20S 30S 1F 2F 3F 5F 10F 15F 20F 30F 1H 2H 3H 4H 5H 6H 8H 10H 12H 1D
    1W 1M 1J 1Y
    //
    //  用户自定义周期，可以有19个。
    // pBarBlock[50] : pBarBlock[0-30] pBarBlock[30-49]
    */
    // 默认的周期
    // 初始化--------------------------------------------------------- 每个 FutureBlock
    // --> future block 有 50个不同的周期 每个周期一个 BarBlock ( bar block )
    if (T________) {
        uBEE::ErrLog(1000, "FutureBlock::FutureBlock():kkkkk!!\n\n", 1, 0, 0);
    }

    int i = 0;
    for (i = 0; i < 50; i++) {
        pBarBlock[i] = nullptr;
    }

    i = 0;
    for (auto it = M_FF.begin(); it != M_FF.end(); ++it) {
        if (it->second >= 0) { // 在M_FF中定义.
            sprintf(ca_errmsg, "FutureBlock::FutureBlock(): idx:%d  %s: %d", i, it->first.c_str(), it->second);
            uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);

            pBarBlock[i] = new BarBlock(it->first.c_str() + 4, it->second, pTimeType); // +4:去掉前面100_ 101_
        }
        i++;
        if (i >= 50) {
            break;
        }
    }

    if (T________) {
        uBEE::ErrLog(1000, "FutureBlock::FutureBlock():out!!\n\n", 1, 0, 0);
    }
}

// ---------------------------------------------------------
/*
  下面的period，是指在 future_block->aBarBo[]数组的下标
*/
int DealBar(uBEE::FutureBlock *future_block, TICK *tick, int period_index, int flag) {
    stBar *b1 = future_block->pBarBlock[period_index]->b1;

    char *curB = future_block->pBarBlock[period_index]->curB;
    char *curE = future_block->pBarBlock[period_index]->curE;
    int &curiB = future_block->pBarBlock[period_index]->curiB;
    int &curiE = future_block->pBarBlock[period_index]->curiE;
    int &curiX = future_block->pBarBlock[period_index]->curiX;

    char *barB = b1->cB;
    char *barE = b1->cE;
    int x = 0;
    int i = 0;
    int fr = future_block->pBarBlock[period_index]->period_value_;

    BarBlock *babo = future_block->pBarBlock[period_index];

#define SEGB future_block->pBarBlock[period_index]->seg[curiX]->cB
#define SEGE future_block->pBarBlock[period_index]->seg[curiX]->cE
#define MARK babo->seg[curiX]->mark
#define ticK tick->UpdateTime

    // Display(future_block,tick,period_index,"eeee:enter:");

    // 只要tick落在 curB---curE之间，即UPDATE。 -----------------------
    // ticK == BarE，在这里就return了。
    // 只有ticK 在bar外，才可能新开一个bar,所以先在这里返回，等新的ticK到来。
    // 对于不跨段的情况 。。。bar在段内
    // 跨段，一个bar跨多个段，有可能前一个ticK在前一段中，现在这个tick已经是
    // barE了。 这种情况，也在这里直接处理，并返回。
    if (memcmp(ticK, barE, 8) == 0) { // >=500 在 Markbar()已经update
        if (tick->UpdateMillisec < 500) {
            UPDATE_B1;
            // Display(future_block,tick,period_index,"eeee:uuu---");
        }
        future_block->iTickValid = 1;
        return 0;
    }

    if (memcmp(ticK, curB, 8) >= 0 && memcmp(ticK, curE, 8) <= 0) {
        UPDATE_B1;
        // Display(future_block,tick,period_index,"eeee:uuu---");
        future_block->iTickValid = 1;
        return 0;
    }

    // 程序走到这里来 this tick is out of curB--curE
    // next curB--curE should be set !
    //--nnnnnn--------------------------------------------------------
    // here bars in one seg:
    if (MARK == 0) {
        // 【A】 barE < ticK <= segE
        // situation 1: tick still in same segB--segE, but out of
        // barB--barE(same curB--curE)
        if (memcmp(barE, ticK, 8) < 0 && memcmp(ticK, SEGE, 8) <= 0) {
            goto aaaa;
        }
        // -----
        // 【C】：barE<=segE <tick   外   ==>  e
        // 【D】：tick <barE<=segE   外   ==>  e  24:00:00
        // situation 2: tick is out of  segB--segE, out of  barB--barE
        if (memcmp(SEGE, ticK, 8) < 0 || memcmp(ticK, barE, 8) < 0) {
            // Display(future_block,tick,period_index,"eeee:1:E,F---");
            goto bbbb;
        } //------- E F
    }     // MARK ==0

    // --------------------------------------------------------------------
    // here a bar has lots of segs:
    if (MARK > 0) {
        // 【A】：segE < tick < barE    内  ==>  n
        // 【1】：tick > segE > barE    内  ==>  c    tick befor 00:00:00
        // 图中seg2 【2】：segE > barE > tick    内  ==>  c    tick after
        // 00:00:00           图中seg3 4 5
        //  situation 1:  ticK is out of segB--segE(same curB--curE), but still
        //  in same barB--barE
        if ((memcmp(SEGE, ticK, 8) < 0 && memcmp(ticK, barE, 8) < 0) || (memcmp(ticK, SEGE, 8) > 0 && memcmp(SEGE, barE, 8) > 0) || (memcmp(SEGE, barE, 8) > 0 && memcmp(barE, ticK, 8) > 0)) {
            int i = curiX; // do while ==> keep curiX not changing .because
                           // maybe this tick is invalid.
            do {
                i++;
            } while ((memcmp(barE, babo->seg[i]->barE, 8) == 0) && (memcmp(ticK, babo->seg[i]->cB, 8) < 0 || memcmp(ticK, babo->seg[i]->cE, 8) > 0));
            if (memcmp(barE, babo->seg[i]->barE, 8) != 0) { // invalid tick
                future_block->iTickValid = -1;
                return 0;
            }

            UPDATE_B1;
            curiX = i;
            curiB = babo->seg[i]->iB;
            curiE = babo->seg[i]->iE;
            memcpy(curB, babo->seg[i]->cB, 9);
            memcpy(curE, babo->seg[i]->cE, 9);

            /*   ticK == barE 这种情况 在一开始就被处理了
            if(memcmp(ticK,barE,8)==0) {
              goto rrr;
            }
            */

            future_block->iTickValid = 1;
            return 0;
        } // A 1 2 ------------

        // 【E】：segE<=barE< tick    外  ==>  e     00:00:00  -- barB segB --
        // segE barE -- tick  -- 00:00:00 【F】：tick <segE<=barE    外  ==>  e
        // barB segB -- segE barE -- 00:00:00  -- tick 【3】：segE >tick> barE
        // 外  ==>  e     barB segB -- segE -- 00:00:00 -- barE -- tick
        //  situation 2: tick is out of bar !!
        if ((memcmp(SEGE, barE, 8) <= 0 && (memcmp(barE, ticK, 8) < 0 || memcmp(ticK, SEGE, 8) < 0)) || (memcmp(SEGE, ticK, 8) > 0 && memcmp(ticK, barE, 8) > 0)) {
        bbbb:
            if (curiX < babo->iSegNum - 1) {
                if (memcmp(ticK, "20:50:00", 8) >= 0) {
                    i = 0; // i always be 0 !!! no bug!
                } else {
                    i = curiX + 1; // 如果最后一个段没有任何数据过来， bug!!! here
                }
            } else { // 一天结束，从头开始
                i = 0;
                // b1->vold = 0;
                // b1->vsum = 0;                // 对于 "20:50:0x"
                // 其它的周期走到这里
            }

            // one tick should be DealBar() many times for differient period_index.
            // 20:50:0x tick comming ==> first DealBar() will changed to
            // 21:00:00 next period_index , the programe will be going to bbbb:(above)
            // if i = curiX+1; problem coming, because this tick will not be
            // found from curiX+1 to the end : babo->iSegNum-1 !!!!!!
            // ===> same problem for the coming ticks after 21:00:00 !!!!!!
            // so i must be 0 always !! that is correct!!
        for8:
            while (memcmp(ticK, babo->seg[i]->cB, 8) < 0 || memcmp(ticK, babo->seg[i]->cE, 8) > 0) {
                i++;
                if (i >= babo->iSegNum) {
                    //-----------------------
                    if (memcmp(ticK, "20:59:", 6) == 0) {
                        memcpy(future_block->UpdateTime, ticK,
                               9); // save tick->UpdateTime "20:59:??" ...
                        future_block->iChange = 1;
                        memcpy(ticK, "21:00:00",
                               8); // 对于 "20:50:0x" 第一个周期走到这里
                        i = 0;
                        break;
                    } else if (memcmp(ticK, "08:59:", 6) == 0) {
                        memcpy(future_block->UpdateTime, ticK,
                               9); // save tick->UpdateTime "20:59:??" ...
                        future_block->iChange = 1;
                        memcpy(ticK, "09:00:00",
                               8); // 对于 "20:50:0x" 第一个周期走到这里
                        i = 0;
                        goto for8;
                    } else {
                        future_block->iTickValid = -1;
                        return 0;
                    }
                    //-----------------------
                }
            }          // 找到 tick 在哪个段中
            curiX = i; // tick所在的段
            if (curiX == 0) {
                b1->vold = 0;
                b1->vsum = 0;
            }
            snprintf(future_block->ActionDay, 9, "%s", tick->ActionDay);
            snprintf(future_block->TradingDay, 9, "%s", tick->TradingDay);

            if (MARK == 0) {
                curiE = babo->seg[curiX]->iB - 1; // for do while below!!
            aaaa:
                if (memcmp(ticK, SEGE, 8) <= 0) { // ---------
                    do {
                        curiB = curiE + 1;
                        curiE += fr;
                        if (curiE == babo->seg[curiX]->iE - 1) {
                            curiE = babo->seg[curiX]->iE;
                        }
                        // before = rdtsc();
                        uBEE::MakeTime(curB, curiB);
                        uBEE::MakeTime(curE, curiE);
                        // latency = rdtsc() - before;
                        // std::cout << "\n latency ----MakeTime---------- Dealar::  " << latency
                        //           << std::endl;
                    } while (memcmp(ticK, curE, 8) > 0);

                    NEW_B1;
                    memcpy(barB, curB, 9);
                    memcpy(barE, curE, 9);
                    // Display(future_block,tick,period_index,"eeee:011---");

                    goto rrr;
                    // return 0; //虽然没有用，但还是留着。
                } // (memcmp(ticK,SEGE,8)<0)
                future_block->iTickValid = 1;
                return 0;
            }

            if (MARK > 0) {
                NEW_B1;
                curiB = babo->seg[curiX]->iB;
                curiE = babo->seg[curiX]->iE;
                memcpy(curB, babo->seg[curiX]->cB, 9);
                memcpy(curE, babo->seg[curiX]->cE, 9);
                memcpy(barB, babo->seg[curiX]->barB, 9);
                memcpy(barE, babo->seg[curiX]->barE, 9);
                // Display(future_block,tick,period_index,"eeee:012---");
            rrr:
                if (memcmp(ticK, barE, 8) == 0) {
                    if (tick->UpdateMillisec >= 500) {
                        // Display(future_block, tick, period_index, "eeee:goo---0");
                        MarkBar(future_block, tick, period_index);
                        SendBar(future_block, period_index, flag);
                    }
                }
                future_block->iTickValid = 1;
                return 0;
            }
            future_block->iTickValid = 1;
            return 0;
        } // ----------------------------
        future_block->iTickValid = -1;
        return 0;
    } // MARK > 0
    // --------------------------------------------------------------------
    if (MARK < 0) {
        curiX = babo->iSegNum;
        goto bbbb;
    } // MARK < 0

    /*
      curB--curE
      barB--barE
      segB--segE
      mark ==> 每个seg的类型, 0:表示这个seg包含多个bar。 1：2：3：表示
      此seg属于某个bar。 idx  ==> seg 数组下标
    */
    return 0;
}

// todo
// 目前测试，下面这个方法是最快的 -O3
int HhmmssToSec(const char *str) {
    /*
    int s = 0;
    const char *hh = str;
    const char *mm = str + 3;
    const char *ss = str + 6;
    int h1 = *hh - '0';
    int h2 = *(++hh) - '0';
    int m1 = *mm - '0';
    int m2 = *(++mm) - '0';
    int s1 = *ss - '0';
    int s2 = *(++ss) - '0';
    */
    int h1 = str[0] - '0';
    int h2 = str[1] - '0';
    int m1 = str[3] - '0';
    int m2 = str[4] - '0';
    int s1 = str[6] - '0';
    int s2 = str[7] - '0';

    return (h1 * 10 + h2) * 3600 + (m1 * 10 + m2) * 60 + s1 * 10 + s2;
    // return s;
}

// https://blog.51cto.com/waleon/5671078
// 目前发现效率最高！！
#define PRINTF_2D_WITH_TWO_DIGIT(buff, num)                                                                                                                                                                                                                                            \
    {                                                                                                                                                                                                                                                                                  \
        int32_t tmp2 = (num) / 10;                                                                                                                                                                                                                                                     \
        int32_t tmp = (num)-tmp2 * 10;                                                                                                                                                                                                                                                 \
        *buff++ = (char)('0' + tmp2);                                                                                                                                                                                                                                                  \
        *buff++ = (char)('0' + tmp);                                                                                                                                                                                                                                                   \
    }

// 要注意，小时不能超过24吧？ T的值不能大于某个数
int MakeTime(char *caT, int T) {
    int h, m, s;
    h = T / 3600;
    m = (T - h * 3600) / 60;
    s = T % 60;
    char *hh = caT;
    char *mm = caT + 3;
    char *ss = caT + 6;
    // see_memzero(caT, 9);
    // snprintf(caT, 9, "%02d:%02d:%02d", h, m, s);
    PRINTF_2D_WITH_TWO_DIGIT(hh, h);
    PRINTF_2D_WITH_TWO_DIGIT(mm, m);
    PRINTF_2D_WITH_TWO_DIGIT(ss, s);
    caT[2] = ':';
    caT[5] = ':';
    caT[8] = 0;
    return 0;
}

int SendTick(uBEE::FutureBlock *future_block, TICK *tick) {
    char *curB = future_block->pBarBlock[0]->curB;
    char *curE = future_block->pBarBlock[0]->curE;
    int &curiX = future_block->pBarBlock[0]->curiX;
    BarBlock *babo = future_block->pBarBlock[0];
#define ticK tick->UpdateTime
    int i = 0;
    if (memcmp(ticK, curB, 8) >= 0 && memcmp(ticK, curE, 8) <= 0) {
        goto valid;
    } else {
        if (curiX < babo->iSegNum - 1) {
            if (memcmp(ticK, "20:50:00", 8) >= 0) {
                i = 0; // i always be 0 !!! no bug!
            } else {
                i = curiX + 1; // 如果最后一个段没有任何数据过来， bug!!! here
            }
        } else { // 一天结束，从头开始
            i = 0;
        }

        while (memcmp(ticK, babo->seg[i]->cB, 8) < 0 || memcmp(ticK, babo->seg[i]->cE, 8) > 0) {
            i++;
            if (i >= babo->iSegNum) {
                if (memcmp(ticK, "20:59:", 6) == 0) {
                    goto valid;
                }
                if (memcmp(ticK, "08:59:", 6) == 0) {
                    goto valid;
                }
                return 0;
            }
        }

    valid:
        nTick->iType = T_TICK;
        snprintf(nTick->InstrumentID, 81, "%s", tick->InstrumentID);
        snprintf(nTick->TradingDay, 9, "%s", tick->TradingDay);
        snprintf(nTick->ActionDay, 9, "%s", tick->ActionDay);
        memcpy(nTick->UpdateTime, tick->UpdateTime, 9);
        nTick->OpenPrice = tick->OpenPrice;
        nTick->HighestPrice = tick->HighestPrice;
        nTick->LowestPrice = tick->LowestPrice;
        nTick->LastPrice = tick->LastPrice;
        nTick->OpenInterest = tick->OpenInterest;
        nTick->UpdateMillisec = tick->UpdateMillisec;
        nTick->BidPrice1 = tick->BidPrice1;
        nTick->BidVolume1 = tick->BidVolume1;
        nTick->AskPrice1 = tick->AskPrice1;
        nTick->AskVolume1 = tick->AskVolume1;
        nTick->Volume = tick->Volume;
        // todo broadcast
        // future_block->SG->broadcast((const char *)nTick, tLen, uWS::OpCode::BINARY);
    }
    return 0;
}

int ReadTick(const char *file_name) {
    // before = rdtsc();
    // latency = rdtsc() - before;
    // std::cout << file_name << std::endl;
    // std::cout << "\n latency ----filename-------------::    " << latency << std::endl;

    // struct libdeflate_compressor *compressor1;
    ofstream fout;

    // std::ifstream input("inputdata.dta", std::ios::binary);
    // std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    // const int originalDataSize = buffer.size();

    // Compress
    char indata[1000];
    char outdata[2048];
    // compressor = libdeflate_alloc_compressor(6);  // compression level = 9
    // std::vector<unsigned char> outdata;
    // outdata.resize(1000);

    // LOG("Compressing...");
    // int cmpsize = libdeflate_deflate_compress(compressor, buffer.data(), originalDataSize,
    // outdata.data(), originalDataSize);

    // snprintf(file_name, 512, "../data/tick/%s.%s.%s.tick.bin1", tick->InstrumentID,
    // tick->TradingDay, tick->ActionDay); SaveBin(file_name, (const char *)tick, TICK_LEN);

    // libdeflate_free_compressor(compressor);

    // Decompress

    struct libdeflate_decompressor *decompressor;
    decompressor = libdeflate_alloc_decompressor();
    size_t decsize;

    int iRc = 0;
    int fd;
    int retry;

    retry = 0;
    while ((fd = open(file_name, O_RDONLY, 0660)) == -1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if ((retry++) > 10) {
            printf("File.cpp:  file_name:  %s\n", file_name);
            printf("File.cpp: fatal error occured !!! error_no is %d\n", errno);
            iRc = -1;
        }
    }

    char ca_errmsg1[8192];

    int16_t len;
    while (read(fd, &len, sizeof(int16_t))) {
        int in_len = read(fd, outdata, len);
        libdeflate_deflate_decompress(decompressor, indata, in_len, outdata, 2048, &decsize);
        CThostFtdcDepthMarketDataField *tick = (CThostFtdcDepthMarketDataField *)outdata;

        snprintf(ca_errmsg1, 8192, "A:%s %s %s T:%s O:%g H:%g L:%g C:%g V:%d \n", tick->ActionDay, tick->InstrumentID, tick->TradingDay, tick->UpdateTime, tick->LastPrice, tick->AskPrice1, tick->BidPrice1, tick->AskPrice2, tick->Volume);
        std::cout << ca_errmsg1 << std::endl;
    }

    close(fd);

    libdeflate_free_decompressor(decompressor);

    return 0;
}

int SaveTick(TICK *tick) {
    char file_name[512];
    int iRc = 0;
    int fd;
    int retry;

    // before = rdtsc();
    // 这里的文件名，是否要保存在内存里？每次要生成一次。
    snprintf(file_name, 512, "../data/tick/%s.%s.%s.tick.zzz", tick->InstrumentID, tick->TradingDay, tick->ActionDay);
    // latency = rdtsc() - before;
    // std::cout << file_name << std::endl;
    // std::cout << "\n latency ----filename-------------::    " << latency << std::endl;

    // ofstream fout;

    // Compress
    char outdata[5000];
    // compressor = libdeflate_alloc_compressor(6);  // compression level = 9
    // compressor 在主程序里初始化了。 全局一个。没有必要每次 free!!

    before = rdtsc();
    int16_t cmpsize = libdeflate_deflate_compress(g_compressor, tick, TICK_LEN, outdata, TICK_LEN);
    latency = rdtsc() - before;
    std::cout << "\n latency ---- compressor -------------::    " << latency << std::endl;
    /*
    fout.open(file_name, ios::binary | ios::out | ios::app);
    fout.write((char *)&cmpsize, sizeof(int16_t));
    fout.write((char *)outdata, cmpsize);
    fout.close();
    */

    retry = 0;
    while ((fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0660)) == -1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if ((retry++) > 10) {
            printf("File.cpp:  file_name:  %s\n", file_name);
            printf("File.cpp: fatal error occured !!! error_no is %d\n", errno);
            return -1;
        }
    }
    retry = 0;
    while (lockf(fd, F_LOCK, 0) == -1) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if ((retry++) > 10) {
            printf("File.cpp:  file_name:  %s\n", file_name);
            printf("File.cpp: fatal error occured !!! error_no is %d\n", errno);
            return -1;
        }
    }

    iRc = write(fd, (char *)&cmpsize, sizeof(int16_t));
    iRc = write(fd, (char *)outdata, cmpsize);
    close(fd);

    // snprintf(file_name, 512, "../data/tick/%s.%s.%s.tick.bin1", tick->InstrumentID,
    // tick->TradingDay, tick->ActionDay); SaveBin(file_name, (const char *)tick, TICK_LEN);

    // libdeflate_free_compressor(compressor);

    // Decompress
    /* 下面这一段代码是可以执行的。
    size_t dec_size;
    std::vector<unsigned char> dec_outdata;
    char str_out[5001];
    struct libdeflate_decompressor *decompressor;
    decompressor = libdeflate_alloc_decompressor();
    // libdeflate_deflate_decompress(decompressor, outdata.data(), cmpsize, dec_outdata.data(),
    originalDataSize, &dec_size); libdeflate_deflate_decompress(decompressor, outdata, cmpsize,
    str_out, 5000, &dec_size); CThostFtdcDepthMarketDataField *tttt =
    (CThostFtdcDepthMarketDataField *)str_out; snprintf(ca_errmsg, 8192, "A:%s %s %s T:%s O:%g H:%g
    L:%g C:%g V:%d \n", tttt->ActionDay, tttt->InstrumentID, tttt->TradingDay, tttt->UpdateTime,
    tttt->LastPrice, tttt->AskPrice1, tttt->BidPrice1, tttt->AskPrice2, tttt->Volume); std::cout <<
    ca_errmsg << "------?? " << std::endl; libdeflate_free_decompressor(decompressor);
    */

    return 0;
}

int SaveTick(uBEE::FutureBlock *future_block, TICK *tick) {
    char f[512];

    if (future_block->iChange == 1) {
        memcpy(tick->UpdateTime, future_block->UpdateTime,
               9); // save tick->UpdateTime "20:59:??" ...
        future_block->iChange = 0;
    }

    snprintf(f, 512, "../data/tick/%s.%s.tick.bin", tick->InstrumentID, tick->ActionDay);
    SaveBin(f, (const char *)tick, TICK_LEN);

    snprintf(f, 512, "../data/tick/%s.%s.tick.txt", tick->InstrumentID, tick->ActionDay);
    snprintf(ca_errmsg, ERR_MSG_LEN,
             "A:%s %s %06d S:%d T:%s H:%g L:%g LP:%g AP:%g AV:%d BP:%g BV:%d "
             "OI:%g V:%d",
             tick->ActionDay, tick->UpdateTime, tick->UpdateMillisec * 1000, 0, tick->TradingDay, tick->HighestPrice, tick->LowestPrice, tick->LastPrice, tick->AskPrice1, tick->AskVolume1, tick->BidPrice1, tick->BidVolume1, tick->OpenInterest, tick->Volume);
    SaveLine(f, ca_errmsg);
    return 0;
}

/*
  1. 调用 MarkBar() 标记那些已经结束的 bar !
  2. 将这些 bar 先送给 策略进程进行处理。
  3. 调用 DealBar() 处理相应的bar, 新生成 bar
  4. 调用 SG->broadcast() 将bars ticks 传给 策略程序  ~/uquant/t/main.cpp
  5. flag == SEND_ALL || flag == SEND_BAR || flag == SEND_SAVE_ALL || flag == SEND_SAVE_BAR)
*/
int HandleTick(uBEE::FutureBlock *future_block, TICK *tick, int flag) {
    // test begin ------------------------------------------
    /*
    int xxxx;
    bool ttf;
    before = rdtsc();
    xxxx = HhmmssToSec(tick->UpdateTime);  // latency 14
    latency = rdtsc() - before;
    constexpr int len = sizeof(TICK);
    std::cout << "\n latency ----Hhmmss---------- Dealar::  " << xxxx << "    " << latency
              << "  len tick:" << len << std::endl;

    char cabuf[2000];
    before = rdtsc();
    memcpy(cabuf, tick, len);  // latency 34
    latency = rdtsc() - before;
    std::cout << "\n latency ----memcpy tick ---------- Dealar::  " << len << "    " << latency
              << std::endl;

    before = rdtsc();
    ttf = memcmp(ticK, "08:59:", 5); // latency 10
    latency = rdtsc() - before;
    std::cout << "\n latency -----memcmp--------- Dealar::  " << xxxx << "    " << latency
              << std::endl;

    char ca_hh[3];
    char ca_mm[3];
    int ihh;
    int imm;
    int iss;
    see_memzero(ca_hh, 3);
    see_memzero(ca_mm, 3);
    memcpy(ca_hh, tick->UpdateTime, 2);
    memcpy(ca_mm, tick->UpdateTime + 3, 2);
    before = rdtsc();
    ihh = atoi(ca_hh);
    latency = rdtsc() - before;
    imm = atoi(ca_mm);
    iss = atoi(tick->UpdateTime + 6);  //latency 1256
    xxxx = ihh * 3600 + imm * 60 + iss;
    std::cout << "\n latency -----atoi--------- Dealar::  " << xxxx << "    " << latency
              << std::endl;

    */
    // test end ------------------------------------------

    int i = 0;
    int k = 0;
    int x = 0;
    stBar *b1;

    /*
    snprintf(nData->InstrumentID,81,"%s",future_block->InstrumentID);
    snprintf(nData->ActionDay,9,"%s",future_block->ActionDay);
    snprintf(nData->TradingDay,9,"%s",future_block->TradingDay);
    */
    memcpy(nData->InstrumentID, future_block->InstrumentID, 49);
    nData->iType = T_BARS;

    // ----------  period   idx from 1 to 49 ---------------
    x = 0;
    for (i = 1; i < 50; ++i) {
        if (future_block->pBarBlock[i] != nullptr) {
            b1 = future_block->pBarBlock[i]->b1;
            MarkBar(future_block, tick, i); //---------
            if (b1->sent == 1) {
                b1->sent = 2; // 如果已经send过，在下面的
                              // DealBar中，可能会再次MarkBar() SendBar()
                memcpy((char *)&(nData->KK[x]), (char *)b1, bLen);
                ++x;
            }
        }
    } // for --

    nData->iN = x;
    if (flag == SEND_ALL || flag == SEND_BAR || flag == SEND_SAVE_ALL || flag == SEND_SAVE_BAR) {
        if (x > 0) {
            // todo
            //  future_block->SG->broadcast((const char *)nData, hLen + bLen * x, uWS::OpCode::BINARY);
        }
    }

    //-------------  saving Klines Kbars !!!
    if (flag == SAVE_ALL || flag == SAVE_BAR || flag == SEND_SAVE_ALL || flag == SEND_SAVE_BAR) {
        for (k = 0; k < nData->iN; ++k) {
            SaveBar(future_block, &nData->KK[k], nData->KK[k].iX);
        }
    }

    //-------------  update or new  bar!!!
    for (i = 1; i < 50; ++i) {
        if (future_block->pBarBlock[i] != nullptr) {
            // todo
            DealBar(future_block, tick, i, flag); // latency 80 -- 284
        }
    }

    // ---------- send other updating bars : bar not end !!  ---------------
    if (flag == SEND_ALL || flag == SEND_BAR || flag == SEND_SAVE_ALL || flag == SEND_SAVE_BAR) {
        if (future_block->iTickValid == 1) {
            nData->iType = T_UPDATE;
            x = 0;
            for (i = 1; i < 50; ++i) {
                if (future_block->pBarBlock[i] != nullptr) {
                    if (b1->sent == 0) {
                        memcpy((char *)&(nData->KK[x]), (char *)b1, bLen);
                        ++x;
                    }
                }
            } // for --
            nData->iN = x;
            // todo
            // future_block->SG->broadcast((const char *)nData, hLen + bLen * x, uWS::OpCode::BINARY);
        }
    }

    if (flag == SEND_ALL || flag == SEND_TICK || flag == SEND_SAVE_ALL || flag == SEND_SAVE_TICK) {
        if (future_block->iTickValid == 1) {
            nTick->iType = T_TICK;
            snprintf(nTick->InstrumentID, 81, "%s", tick->InstrumentID);
            snprintf(nTick->TradingDay, 9, "%s", tick->TradingDay);
            snprintf(nTick->ActionDay, 9, "%s", tick->ActionDay);
            memcpy(nTick->UpdateTime, tick->UpdateTime, 9);
            nTick->OpenPrice = tick->OpenPrice;
            nTick->HighestPrice = tick->HighestPrice;
            nTick->LowestPrice = tick->LowestPrice;
            nTick->LastPrice = tick->LastPrice;
            nTick->OpenInterest = tick->OpenInterest;
            nTick->UpdateMillisec = tick->UpdateMillisec;
            nTick->BidPrice1 = tick->BidPrice1;
            nTick->BidVolume1 = tick->BidVolume1;
            nTick->AskPrice1 = tick->AskPrice1;
            nTick->AskVolume1 = tick->AskVolume1;
            nTick->Volume = tick->Volume;
            // todo
            // future_block->SG->broadcast((const char *)nTick, tLen, uWS::OpCode::BINARY);
        }
    }

    if (flag == SAVE_ALL || flag == SAVE_TICK || flag == SEND_SAVE_ALL || flag == SEND_SAVE_TICK) {
        SaveTick(future_block, tick);
    }

    return 0;
}

/*
  SendBar 用于 DealBar()内。
  当一个tick到来时，它可能终结前一个bar,同时这个tick又是新一个bar。
  DealBar()就会新生成这个bar,==> 但这个bar有可能也结束了，所以需要再 送给
  策略进程。
*/
// period 是指数组下标
int SendBar(uBEE::FutureBlock *future_block, int period, int flag) {
    stBar *b1 = future_block->pBarBlock[period]->b1;

    // snprintf(nData->InstrumentID,81,"%s",future_block->InstrumentID);
    // snprintf(nData->TradingDay,9,"%s",tick->TradingDay);
    // snprintf(nData->ActionDay,9,"%s",tick->ActionDay);

    if (b1->sent == 1) { // 这里有 sent=2的情况，表示前面已经send过了。
        b1->sent = 2;

        nData->iType = T_BARS;
        memcpy((char *)&(nData->KK[0]), (char *)b1, bLen);
        nData->iN = 1;

        if (flag == SEND_BAR || flag == SEND_ALL || flag == SEND_SAVE_BAR || flag == SEND_SAVE_ALL) {
            // todo
            // future_block->SG->broadcast((const char *)nData, oLen, uWS::OpCode::BINARY);
        }

        if (flag == SAVE_BAR || flag == SAVE_ALL || flag == SEND_SAVE_BAR || flag == SEND_SAVE_ALL) {
            // todo
            // std::cout << "\n not here ?? \n" << std::endl;
            SaveBar(future_block, &nData->KK[0], period);
        }
    }
    return 0;
}

// period 是指数组下标
int SaveBar(uBEE::FutureBlock *future_block, sKbar *KK, int period) {
    char f[512];
    BarBlock *babo = future_block->pBarBlock[period];

    snprintf(f, 512, "../data/%s_%02d_%02d_%02d.%d.%di", future_block->InstrumentID, babo->iH, babo->iM, babo->iS, babo->period_value_, period);
    snprintf(ca_errmsg, ERR_MSG_LEN, "%s A:%s T:%s %s--%s O:%g H:%g L:%g C:%g V:%d vsam:%d", future_block->InstrumentID, future_block->ActionDay, future_block->TradingDay, KK->cB, KK->cE, KK->o, KK->h, KK->l, KK->c, KK->v, KK->vsum);
    SaveLine(f, ca_errmsg);
    return 0;
}

// period 是指数组下标
int MarkBar(uBEE::FutureBlock *future_block, TICK *tick, int period_index) {
    stBar *b1 = future_block->pBarBlock[period_index]->b1;
    char *curB = future_block->pBarBlock[period_index]->curB;
    char *curE = future_block->pBarBlock[period_index]->curE;
    int &curiX = future_block->pBarBlock[period_index]->curiX;

    char *barB = b1->cB;
    char *barE = b1->cE;

    BarBlock *babo = future_block->pBarBlock[period_index];

#define SEGB future_block->pBarBlock[period_index]->seg[curiX]->cB
#define SEGE future_block->pBarBlock[period_index]->seg[curiX]->cE
#define MARK babo->seg[curiX]->mark
#define ticK tick->UpdateTime

    //---------------------------------------------
    if (memcmp(barE, ticK, 8) == 0) {
        if (tick->UpdateMillisec >= 500) {
            UPDATE_B1;
            b1->sent = 1;
            return 0;
        }
    }

    if (memcmp(ticK, curB, 8) >= 0 && memcmp(ticK, curE, 8) <= 0) { // 在当前的 curB curE 这个segment内
        return 0;
    }

    if (MARK == 0) {
        if (b1->sent == 0) {
            b1->sent = 1;
        }
        return 0;
    }

    if (MARK > 0) {
        if ((memcmp(SEGE, barE, 8) <= 0 && (memcmp(barE, ticK, 8) < 0 || memcmp(ticK, SEGE, 8) < 0)) || (memcmp(SEGE, ticK, 8) > 0 && memcmp(ticK, barE, 8) > 0)) {
            if (b1->sent == 0) {
                b1->sent = 1;
            }
        }
        return 0;
    }

    if (MARK < 0) {
        return 0;
    }

    return 0;
}

int Display(uBEE::FutureBlock *future_block, TICK *tick, int period_index, const char *msg) {
    BarBlock *babo = future_block->pBarBlock[period_index];
    stBar *b1 = babo->b1;

    char *curB = babo->curB;
    char *curE = babo->curE;
    int &curiB = babo->curiB;
    int &curiE = babo->curiE;
    int &curiX = babo->curiX;
    int fr = babo->period_value_;

    char *barB = b1->cB;
    char *barE = b1->cE;
    char *tik = tick->UpdateTime;

    char *segB = babo->seg[curiX]->cB;
    char *segE = babo->seg[curiX]->cE;
    int &mark = babo->seg[curiX]->mark;

    if (T________) {
        sprintf(ca_errmsg,
                "%s p:%d fr:%d tick:%s ms:%d crBE:%s-%s brBE:%s-%s sgBE:%s-%s "
                "curiX:%d",
                msg, period_index, fr, tick->UpdateTime, tick->UpdateMillisec, curB, curE, barB, barE, SEGB, SEGE, curiX);
        uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
    }
    return 0;
}

int DispBar(uBEE::FutureBlock *future_block, TICK *tick, int period_index, const char *msg) {
    BarBlock *babo = future_block->pBarBlock[period_index];
    stBar *b1 = babo->b1;

    if (T________) {
        sprintf(ca_errmsg, "%s fr:%d  T:%s A:%s B:%s--%s H:%lf O:%lf C:%lf L:%lf V:%d vsam:%d", msg, babo->period_value_, future_block->TradingDay, future_block->ActionDay, b1->cB, b1->cE, b1->h, b1->o, b1->c, b1->l, b1->v, b1->vsum);
        uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
    }
    std::cout << ca_errmsg << std::endl;
    return 0;
}

int DispKbar(const char *InstrumentID, const char *TradingDay, const char *ActionDay, sKbar *bar) {
    snprintf(ca_errmsg, ERR_MSG_LEN, "%s T:%s A:%s %s--%s O:%g H:%g L:%g C:%g V:%d vsam:%d", InstrumentID, TradingDay, ActionDay, bar->cB, bar->cE, bar->o, bar->h, bar->l, bar->c, bar->v, bar->vsum);
    std::cout << ca_errmsg << std::endl;
    uBEE::ErrLog(1000, ca_errmsg, 1, 0, 0);
    return 0;
}

//----------------------------------------
int GetFrequencyIdx(int f) {
    int i = 0;
    std::map<std::string, int>::const_iterator itt;
    for (itt = M_FF.begin(); itt != M_FF.end(); ++itt) { // all periods defined in M_FF <bars.h>
        if (f == itt->second) {
            break;
        }
        i++;
    }
    if (itt == M_FF.end()) {
        return -1;
    }
    return i;
}

//--------------------------------------------

/*
X_OHLC::X_OHLC() : O(100000, SEE_NULL), H(100000, SEE_NULL), L(100000, SEE_NULL), C(100000,
SEE_NULL), V(100000, SEE_NULL) { memset(cB, '\0', 9); memset(cE, '\0', 9); u = 0;  //
表示当前的bar是已经结束了的bar。每个bar只有最后一个tick过来时，才会结束，中间的tick会update这个bar。
    x = -1;
    iCall = 0;
    for (size_t i = 0; i < 256; ++i) {
        callbacks[i] = nullptr;
    }
}
*/

/*
 x: index !
*/
int X_OHLC::Insert(sKbar *bar) {
    if (u == 0) {
        x++;
    }
    O[x] = bar->o;
    H[x] = bar->h;
    L[x] = bar->l;
    C[x] = bar->c;
    V[x] = bar->v;
    memcpy(cB, bar->cB, 9);
    memcpy(cE, bar->cE, 9);
    u = 0;
    return 0;
}

int X_OHLC::Update(sKbar *bar) {
    if (u == 0) {
        x++;
        u = 1;
    }
    O[x] = bar->o;
    H[x] = bar->h;
    L[x] = bar->l;
    C[x] = bar->c;
    V[x] = bar->v;
    memcpy(cB, bar->cB, 9);
    memcpy(cE, bar->cE, 9);
    return 0;
}

} // namespace uBEE
