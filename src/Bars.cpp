#include "Bars.h"
#include "ErrLog.h"
#include "FuList.h"
#include "File.h"
#include "Global.h"
#include <cjson/cJSON.h>
#include <iostream>
#include <string.h>
#include <map>
#include <float.h>
#include <limits.h>

namespace uBEE
{

static sData  *nData = new sData() ;   // Data for send !!
static sTick  *nTick = new sTick() ;   // Data for send !!

Segment::Segment()
{
  see_memzero(cB,9);
  see_memzero(cE,9);
  iB=-1 ;
  iE=-1 ;
  iI=-1 ;  //和前一个 segment之间的间隔。如果是第一个segment， iI = 0;
  mark=-1 ; // 0 表示 seg 包含 bar。 // 1.2.3. 表示 一个bar 包含多个 seg。
  sn=-1 ;
  see_memzero(barB,9);
  see_memzero(barE,9);
  bariB=-1;
  bariE=-1;
  barBx=-1;  //记录 起始barB所在的 seg[]的 index .
  barEx=-1;  //记录 结束barE所在的 seg[]的 index .
}


// ---------------------------------------------------------
TmBo::TmBo()
{
  uBEE::ErrLog(1000," enter into TmBo()!",1,0,0);
  cJSON   *jRoot ;
  cJSON   *jTime ;
  cJSON   *jTemp ;
  char ca_h[3];
  char ca_m[3];
  int  ih;
  int  im;
  int    i, n ;
  const std::map<int,std::string> *MP ;
  MP = &M_TimeType ;

  for(auto it = (*MP).begin(); it != (*MP).end(); ++it) {
    TT[it->first].iType = it->first ;
    for(i=0; i<SGM_NUM; i++) {
      TT[it->first].aSgms[i].iB = -1;
      TT[it->first].aSgms[i].iE = -1;
      TT[it->first].aSgms[i].iI = -1;
    }

    jRoot = cJSON_Parse(it->second.c_str());
    jTime = cJSON_GetObjectItem(jRoot, "time");
    n = cJSON_GetArraySize(jTime);

    TT[it->first].iSegNum = n;
    //std::cout << TT[it->first].iSegNum << "pppppppppppppppppppppp" << std::endl;
    for(i=0; i<n; i++) {
      jTemp = cJSON_GetArrayItem(jTime,i);

      std::cout << jTemp->valuestring << std::endl;
      see_memzero(TT[it->first].aSgms[i].cB,9);
      see_memzero(TT[it->first].aSgms[i].cE,9);

      memcpy(TT[it->first].aSgms[i].cB,jTemp->valuestring,5);
      memcpy(TT[it->first].aSgms[i].cB+5,":00",3);
      memcpy(TT[it->first].aSgms[i].cE,jTemp->valuestring+6,5);
      memcpy(TT[it->first].aSgms[i].cE+5,":00",3);
      std::cout << "cE: " << TT[it->first].aSgms[i].cE << std::endl;

      see_memzero(ca_h,3);
      see_memzero(ca_m,3);
      memcpy(ca_h,TT[it->first].aSgms[i].cB,  2);
      memcpy(ca_m,TT[it->first].aSgms[i].cB+3,2);
      ih = atoi(ca_h);
      im = atoi(ca_m);
      TT[it->first].aSgms[i].iB = ih*3600 + im*60 ;

      see_memzero(ca_h,3);
      see_memzero(ca_m,3);
      memcpy(ca_h,TT[it->first].aSgms[i].cE,  2);
      memcpy(ca_m,TT[it->first].aSgms[i].cE+3,2);
      ih = atoi(ca_h);
      im = atoi(ca_m);
      TT[it->first].aSgms[i].iE = ih*3600 + im*60 ;

      if(i == 0) {
        TT[it->first].aSgms[i].iI = 0;
      } else {
        if(TT[it->first].aSgms[i].iB >= TT[it->first].aSgms[i-1].iE) {
          TT[it->first].aSgms[i].iI =
            TT[it->first].aSgms[i].iB - TT[it->first].aSgms[i-1].iE;
        } else {
          TT[it->first].aSgms[i].iI =
            TT[it->first].aSgms[i].iB - TT[it->first].aSgms[i-1].iE + 86400;
        }
      }

    }
    //std::cout << "mmmm " << jTemp->valuestring << std::endl;
  }
  cJSON_Delete(jRoot);
}


int TmBo::Init(stTimeType TT[])
{
}


int BaBo::MakeTime(char *caT, int T)
{
  int h,m,s;
  char cTmp[9];
  h = T / 3600;
  m =(T - h*3600) / 60;
  s = T % 60;
  see_memzero(cTmp,9);
  sprintf(cTmp,"%02d:%02d:%02d",h,m,s);
  memcpy(caT, cTmp, 9);
  return 0;
}

/*
  // 初始化 bar block(BaBo) !!! ，每个 future block (FuBo) 有 50个 BaBo ;
  // 每个future的交易时间类型不一样 每个 FuBo 有一个不同的pTimeType
  // 根据frequency + pTimeType， 初始化 BaBo的 （Segment     *seg[100] ;）
  // new BaBo("5F",300,pt);
*/
BaBo::BaBo(const char * pF, int iFr, stTimeType  *pTimeType)
{
  char cB[9];
  char cE[9];

  char cT[9];
  int  iT ;
  int  idxT ;

  char cTmp[9];
  int  iB ;
  int  iE ;
  int  iI ;
  int  mark ;

  if(T________) {
    sprintf(ca_errmsg,"--------------------------------------in BaBo: pF: %s  iFr:%d ",pF,iFr) ;
    uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
  }

  // ------------  tick ---------------------
  if(iFr == 0) {
    iF = 0;
    iH = 0;
    iM = 0;
    iS = 0;
    memcpy(cF,pF,strlen(pF));

    for(int i=0; i<100; i++) {
      seg[i] = nullptr;
    }

    for(int i=0; i<pTimeType->iSegNum; i++) {
      iB = pTimeType->aSgms[i].iB ;
      iE = pTimeType->aSgms[i].iE ;
      seg[i] = new Segment() ;
      memcpy(seg[i]->cB,pTimeType->aSgms[i].cB,9);
      memcpy(seg[i]->cE,pTimeType->aSgms[i].cE,9);
      seg[i]->iB = iB ;
      seg[i]->iE = iE ;
      seg[i]->mark = 0;
    }

    iSegNum = pTimeType->iSegNum ;
    curiX = 0;
    see_memzero(curB,9);    // 当第一次调用DealBar()时，判断tick一定不在这个区间，于是走到 （MARK<0）这个流程中去.
    see_memzero(curE,9);

    return;
  }

  // 成员变量 ----------------
  iF = iFr ;
  iH = iFr/3600;
  iM = (iFr-iH*3600)/60;
  iS = iFr%60;
  memcpy(cF,pF,strlen(pF));

  for(int i=0; i<100; i++) {
    seg[i] = nullptr;
  }

  int last = 0;   // 一个bar跨seg，在后面一个seg还差的时间数量
  int idx  = 0;
  for(int i=0; i<pTimeType->iSegNum; i++) {
    iB = pTimeType->aSgms[i].iB ;
    iE = pTimeType->aSgms[i].iE ;

    if(T________) {
      sprintf(ca_errmsg,"------ i:%d iSegNum:%d iB:%d  iE:%d last:%d ",i,pTimeType->iSegNum,iB,iE,last) ;
      uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
      sprintf(ca_errmsg,"------ pTimeType->aSgms[i].cB:%s .cE:%s",pTimeType->aSgms[i].cB,pTimeType->aSgms[i].cE) ;
      uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
    }

    if(last>0) {
      if(iB + last <= iE) {
        //seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
        seg[idx] = new Segment() ;

        seg[idx]->iB = iB ;
        seg[idx]->iE = iB + last ;

        mark ++ ;
        seg[idx]->mark = mark;

        MakeTime(seg[idx]->cB,seg[idx]->iB) ;
        MakeTime(seg[idx]->cE,seg[idx]->iE) ;

        if(T________) {
          sprintf(ca_errmsg,"2222--- idx:%d mark:%d seg[idx]->cB:%s seg[idx]->cE:%s",idx,mark,seg[idx]->cB,seg[idx]->cE) ;
          uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
        }

        memcpy(seg[idx]->barB,cT , 9);
        seg[idx]->bariB = iT ;
        seg[idx]->barBx = idxT ;
        for(int j =0; j<mark; j++) {
          int k = idx-j ;
          memcpy(seg[k]->barE,seg[idx]->cE , 9);
          seg[k]->bariE = seg[idx]->iE ;
          seg[k]->barEx = idx ;

          if(T________) {
            sprintf(ca_errmsg,"3333--- idx:%d mark:%d seg[idx]->barB:%s seg[idx]->barE:%s",idx,seg[k]->mark,seg[k]->barB,seg[k]->barE) ;
            uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
          }
        }

        mark = 0;
        idx++ ;

      } else if(iB + last > iE) {
        //seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
        seg[idx] = new Segment() ;

        seg[idx]->iB = iB ;
        seg[idx]->iE = iE ;

        mark ++;
        seg[idx]->mark = mark ;

        MakeTime(seg[idx]->cB,seg[idx]->iB) ;
        MakeTime(seg[idx]->cE,seg[idx]->iE) ;

        if(T________) {
          sprintf(ca_errmsg,"4444--- idx:%d mark:%d seg[idx]->cB:%s seg[idx]->cE:%s",idx,mark,seg[idx]->cB,seg[idx]->cE) ;
          uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
        }

        memcpy(seg[idx]->barB,cT , 9);
        seg[idx]->bariB = iT ;
        seg[idx]->barBx = idxT ;
        if(i == pTimeType->iSegNum-1) {
          for(int j =0; j<mark; j++) {    // 【A】
            int k = idx-j ;
            memcpy(seg[k]->barE,seg[idx]->cE , 9);
            seg[k]->bariE = seg[idx]->iE ;
            seg[k]->barEx = idx ;

            if(T________) {
              sprintf(ca_errmsg,"5555--- idx:%d mark:%d segBE:%s--%s  barBE:%s--%s",idx,
                      seg[k]->mark,
                      seg[k]->cB,  seg[k]->cE,
                      seg[k]->barB,seg[k]->barE) ;
              uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
            }
          }
          idx++;
          break;
        }

        last =  last + iB - iE ;
        idx++;
        continue ;
      }
    }

    iB = iB + last ;
    int len =  iE - iB ;
    int num = len / iF ;
    int mo  = len % iF ;

    if(len ==0) {
      last = 0;
      continue ;
    }

    if(mo>0) {
      last = iF-mo;
    } else {
      last = 0 ;
    }

    if(T________) {
      sprintf(ca_errmsg,"6666--- idx:%d iB:%d len:%d num:%d mo:%d last:%d",idx,iB,len,num,mo,last) ;
      uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
    }

    if(num > 0) {
      //seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
      seg[idx] = new Segment() ;
      seg[idx]->iB = iB ;
      seg[idx]->iE = iE-mo ;
      mark =0;
      seg[idx]->mark =0 ;

      MakeTime(seg[idx]->cB,seg[idx]->iB) ;
      MakeTime(seg[idx]->cE,seg[idx]->iE) ;

      if(T________) {
        sprintf(ca_errmsg,"7777--- idx:%d mark:%d seg B:%s seg E:%s",idx,mark,seg[idx]->cB,seg[idx]->cE) ;
        uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
      }


      idx++;
    }

    if(mo > 0) {
      //seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
      seg[idx] = new Segment() ;
      seg[idx]->iB = iE-mo ;
      seg[idx]->iE = iE ;
      mark = 1;
      seg[idx]->mark = mark;

      MakeTime(seg[idx]->cB,seg[idx]->iB) ;
      MakeTime(seg[idx]->cE,seg[idx]->iE) ;

      if(T________) {
        sprintf(ca_errmsg,"8888--- idx:%d mark:%d mo:%d seg B:%s seg E:%s",idx,mark,mo,seg[idx]->cB,seg[idx]->cE) ;
        uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
      }

      memcpy(seg[idx]->barB,seg[idx]->cB , 9);
      seg[idx]->bariB = seg[idx]->iB ;
      seg[idx]->barBx = idx ;
      if(i == pTimeType->iSegNum-1) {
        memcpy(seg[idx]->barE,seg[idx]->cE,9);
        seg[idx]->bariE = seg[idx]->iE ;
        seg[idx]->barEx = idx ;
        if(T________) {
          sprintf(ca_errmsg,"9999--- idx:%d mark:%d seg[idx]->barB:%s seg[idx]->barE:%s",idx,seg[idx]->mark,seg[idx]->barB,seg[idx]->barE) ;
          uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
        }
      }
      memcpy(cT,seg[idx]->cB , 9);
      iT = seg[idx]->iB ;
      idxT = idx ;
      idx++ ;
    }
  } // --- end for

  iSegNum = idx;
  if(T________) {
    sprintf(ca_errmsg,"-------------------iSegNum:%d",iSegNum) ;
    uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
  }

  // ------- 最后多申请一个 seg. -- 用于最开始第一个Kbar处理。 ------
  curiX = iSegNum ;
  //seg[idx] = (Segment *)malloc(sizeof(Segment)) ;
  seg[idx] = new Segment() ;
  seg[idx]->sn = 0 ;
  see_memzero(seg[idx]->cB,9);
  see_memzero(seg[idx]->cE,9);
  see_memzero(seg[idx]->barB,9);
  see_memzero(seg[idx]->barE,9);
  seg[idx]->iB =0;
  seg[idx]->iE =0;
  seg[idx]->bariB =0;
  seg[idx]->bariE =0;
  seg[idx]->mark = -1;    // MARK < 0

  see_memzero(curB,9);    // 当第一次调用DealBar()时，判断tick一定不在这个区间，于是走到 （MARK<0）这个流程中去.
  see_memzero(curE,9);

  // ---------------------------- 初始化  bar0 bar1 ----------------
  //  seg->sn 表示当前段和下一段之间是否连续。
  for(int i=0; i<iSegNum; i++) {
    seg[i]->sn = 0 ;
    if(i < iSegNum-1) {
      if(memcmp(seg[i]->cE,seg[i+1]->cB,8) != 0) {
        seg[i]->sn = 1 ;
        if(memcmp(seg[i]->cE,"24:00:00",8)==0 && memcmp(seg[i+1]->cB,"00:00:00",8)==0) {
          seg[i]->sn = 0 ;
        }
      }
    } else {
      seg[i]->sn = 1 ;
    }
  }

  // ----- 如果两个seg连续，则将前一个seg->iE 减1。 比如：24:00:00 00:00:00连续，则前一个seg结束改成 23:59:59
  for(int i=0; i<iSegNum; i++) {
    if(seg[i]->sn==0) {
      seg[i]->iE -= 1;
      MakeTime(seg[i]->cE,seg[i]->iE) ;
    }
  }

  for(int i=0; i<iSegNum; i++) {
    if(seg[i]->mark!=0) {
      int e = seg[i]->barEx ;
      memcpy(seg[i]->barE,seg[e]->cE,9);
      seg[i]->bariE = seg[e]->iE ;
    }
  }

  // -----------------------------------------------------------------

  b1 = &bar1 ;

  stBar tmpBar ;
  see_memzero(tmpBar.TradingDay,9);
  see_memzero(tmpBar.ActionDay,9);
  see_memzero(tmpBar.cB,9);
  see_memzero(tmpBar.cE,9);
  tmpBar.h = DBL_MIN;
  tmpBar.o = SEE_NULL;
  tmpBar.c = SEE_NULL;
  tmpBar.l = DBL_MAX;
  tmpBar.v = 0;
  tmpBar.vsum = 0;   // 开始的第一个bar 的 v 值 可能会有问题！！
  tmpBar.vold = 0;   // 开始的第一个bar 的 v 值 可能会有问题！！
  tmpBar.sent = 0;

  memcpy((char *)b1,&tmpBar,sizeof(stBar)) ;


  if(T________) {
    sprintf(ca_errmsg,"--------------------------------------out BaBo\n\n") ;
    uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
  }
}

/*
  Future Block !
*/

FuBo::FuBo(char *caFuture, uBEE::TmBo *tmbo, uWS::Group<uWS::SERVER> *sg)
{
  if(T________) {
    uBEE::ErrLog(1000," FuBo::FuBo():enter!",1,0,0) ;
  }

  SG = sg;

  iTickValid = -1;
  iChange = 0;

  see_memzero(InstrumentID,31);
  see_memzero(UpdateTime,9);

  memcpy(InstrumentID,caFuture,strlen(caFuture));

  // charmi-- 从 ag1803 取合约 "ag"
  char fn[3] ;
  see_memzero(fn,3);
  memcpy(fn,caFuture,2) ;
  if(fn[1] <= '9' && fn[1] >= '0') {
    fn[1] = '\0';
  }

  // 初始化 pTimeType [stTimeType  *pTimeType]
  std::map<std::string,int>::const_iterator it;
  it = M_FuTime.find(fn);
  if(it==M_FuTime.end()) {
    sprintf(ca_errmsg,"FuBo::FuBo() :M_FuTime error:not defined: %s %s",InstrumentID,fn) ;
    uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
  } else {
    sprintf(ca_errmsg,"FuBo::FuBo(): future:%s %s timetype:%d, TimeType:",InstrumentID,fn,it->second) ;
    uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
    pTimeType = &tmbo->TT[it->second] ;
  }

  // -- 初始化 BaBo[50] ; ----------------------------------------
  /*
   不同的周期，相当于不同的 frequency : fr
   fr= 1 表示周期为1秒
   fr= 60 表示周期为60秒

   默认周期有以下30个：
   0  1 2 3 4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29
   1S 2 3 5 10 15 20 30 1F 2F 3F 5F 10 15 20 30 1H 2H 3H 4H 5H 6H 8H 10 12 1D 1W 1M 1J 1Y
   用户自定义周期，可以有20个。
   pBaBo[50] :
   pBaBo[0-29]
   pBaBo[30-49]
   ------------------------
   0  1 2 3 4  5  6  7  8  9   10  11  12  13  14   15   16   17   18    19    20    21 22 23 24 25 26 27 28 29
   0S 1S 2 3 5 10 15 20 30 1F 2F  3F  5F  10  15  20   30   1H   2H   3H    4H    5H    6H 8H 10 12 1D 1W 1M 1J 1Y
   0, 1, 2,3,5,10,15,20,30,60,120,180,300,600,900,1200,1800,3600,7200,10800,14400,18000, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   0S是tick。
  */
  // 默认的周期 初始化---------------------------------------------------------
  // 每个 FuBo --> future block 有 50个不同的周期 每个周期一个 BaBo ( bar block )
  int i = 0;
  for(i=0; i<50; i++) {
    pBaBo[i] = nullptr;
  }

  i = 0;
  for(auto it = M_FF.begin(); it != M_FF.end(); ++it) {
    if(it->second >=0) {                              // 在M_FF中定义.
      sprintf(ca_errmsg,"FuBo::FuBo(): idx:%d  %s: %d",i, it->first.c_str(), it->second) ;
      uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;

      pBaBo[i] = new BaBo(it->first.c_str()+4,it->second, pTimeType); // +4:去掉前面100_ 101_
    }
    i++;
    if(i>=50) {
      break;
    }
  }


  if(T________) {
    uBEE::ErrLog(1000,"FuBo::FuBo():out!!\n\n",1,0,0) ;
  }
}

// ---------------------------------------------------------
/*
  下面的period，是指在 fubo->aBarBo[]数组的下标
*/
//int DealBar(see_fut_block_t *p_block, TICK *tick,int period)
int DealBar(uBEE::FuBo *fubo, TICK *tick,int period)
{
  stBar   *b1 = fubo->pBaBo[period]->b1 ;

  char * curB = fubo->pBaBo[period]->curB ;
  char * curE = fubo->pBaBo[period]->curE ;
  int &curiB = fubo->pBaBo[period]->curiB ;
  int &curiE = fubo->pBaBo[period]->curiE ;
  int &curiX = fubo->pBaBo[period]->curiX ;

  char * barB = b1->cB ;
  char * barE = b1->cE ;
  int x = 0;
  int i = 0;
  int fr = fubo->pBaBo[period]->iF ;

  BaBo * babo = fubo->pBaBo[period] ;

#define SEGB fubo->pBaBo[period]->seg[curiX]->cB
#define SEGE fubo->pBaBo[period]->seg[curiX]->cE
#define MARK babo->seg[curiX]->mark
#define ticK tick->UpdateTime


  //Display(fubo,tick,period,"eeee:enter:");

  // 只要tick落在 curB---curE之间，即UPDATE。 -----------------------
  // ticK == BarE，在这里就return了。
  // 只有ticK 在bar外，才可能新开一个bar,所以先在这里返回，等新的ticK到来。
  // 对于不跨段的情况 。。。bar在段内
  // 跨段，一个bar跨多个段，有可能前一个ticK在前一段中，现在这个tick已经是 barE了。
  // 这种情况，也在这里直接处理，并返回。
  if(memcmp(ticK,barE,8)==0) {  // >=500 在 Markbar()已经update
    if(tick->UpdateMillisec < 500) {
      UPDATE_B1;
      //Display(fubo,tick,period,"eeee:uuu---");
    }
    fubo->iTickValid = 1;
    return 0;
  }

  if(memcmp(ticK,curB,8)>=0 && memcmp(ticK,curE,8)<=0) {
    UPDATE_B1;
    //Display(fubo,tick,period,"eeee:uuu---");
    fubo->iTickValid = 1;
    return 0;
  }

  // 程序走到这里来 this tick is out of curB--curE
  // next curB--curE should be set !
  //--nnnnnn--------------------------------------------------------
  // here bars in one seg:
  if(MARK == 0) {
    // 【A】 barE < ticK <= segE
    // situation 1: tick still in same segB--segE, but out of  barB--barE(same curB--curE)
    if(memcmp(barE,ticK,8)<0 && memcmp(ticK,SEGE,8)<=0) {
      goto aaaa;
    }
    // -----
    // 【C】：barE<=segE <tick   外   ==>  e
    // 【D】：tick <barE<=segE   外   ==>  e  24:00:00
    // situation 2: tick is out of  segB--segE, out of  barB--barE
    if(memcmp(SEGE,ticK,8)<0 || memcmp(ticK,barE,8)<0) {
      //Display(fubo,tick,period,"eeee:1:E,F---");
      goto bbbb;
    } //------- E F
  }  // MARK ==0

  // --------------------------------------------------------------------
  // here a bar has lots of segs:
  if(MARK > 0) {
    // 【A】：segE < tick < barE    内  ==>  n
    // 【1】：tick > segE > barE    内  ==>  c    tick befor 00:00:00           图中seg2
    // 【2】：segE > barE > tick    内  ==>  c    tick after 00:00:00           图中seg3 4 5
    //  situation 1:  ticK is out of segB--segE(same curB--curE), but still in same barB--barE
    if((memcmp(SEGE,ticK,8)<0 && memcmp(ticK,barE,8)<0) ||
       (memcmp(ticK,SEGE,8)>0 && memcmp(SEGE,barE,8)>0) ||
       (memcmp(SEGE,barE,8)>0 && memcmp(barE,ticK,8)>0)) {
      int i = curiX;    // do while ==> keep curiX not changing .because maybe this tick is invalid.
      do {
        i++;
      } while((memcmp(barE,babo->seg[i]->barE,8)==0) &&
              (memcmp(ticK,babo->seg[i]->cB,8)<0 || memcmp(ticK,babo->seg[i]->cE,8)>0));
      if(memcmp(barE,babo->seg[i]->barE,8)!=0) {   // invalid tick
        fubo->iTickValid = -1;
        return 0;
      }

      UPDATE_B1;
      curiX=i;
      curiB = babo->seg[i]->iB ;
      curiE = babo->seg[i]->iE ;
      memcpy(curB,babo->seg[i]->cB,9);
      memcpy(curE,babo->seg[i]->cE,9);

      /*   ticK == barE 这种情况 在一开始就被处理了
      if(memcmp(ticK,barE,8)==0) {
        goto rrr;
      }
      */

      fubo->iTickValid = 1;
      return 0;
    }  // A 1 2 ------------

    // 【E】：segE<=barE< tick    外  ==>  e     00:00:00  -- barB segB -- segE barE -- tick  -- 00:00:00
    // 【F】：tick <segE<=barE    外  ==>  e     barB segB -- segE barE -- 00:00:00  -- tick
    // 【3】：segE >tick> barE    外  ==>  e     barB segB -- segE -- 00:00:00 -- barE -- tick
    //  situation 2: tick is out of bar !!
    if((memcmp(SEGE,barE,8)<=0 && (memcmp(barE,ticK,8)<0 || memcmp(ticK,SEGE,8)<0)) ||
       (memcmp(SEGE,ticK,8)> 0 && memcmp(ticK,barE,8)>0)) {

bbbb:
      if(curiX < babo->iSegNum-1) {
        if(memcmp(ticK,"20:50:00",8) >=0) {
          i = 0 ;                    // i always be 0 !!! no bug!
        } else {
          i = curiX+1;               // 如果最后一个段没有任何数据过来， bug!!! here
        }
      } else {                       //一天结束，从头开始
        i = 0;
        //b1->vold = 0;
        //b1->vsum = 0;                // 对于 "20:50:0x" 其它的周期走到这里
      }

      // one tick should be DealBar() many times for differient period.
      // 20:50:0x tick comming ==> first DealBar() will changed to 21:00:00
      // next period , the programe will be going to  bbbb:(above)
      // if i = curiX+1; problem coming, because this tick will not be found
      // from curiX+1 to the end : babo->iSegNum-1 !!!!!!
      // ===> same problem for the coming ticks after 21:00:00 !!!!!!
      // so i must be 0 always !! that is correct!!

      while(memcmp(ticK,babo->seg[i]->cB,8)<0 || memcmp(ticK,babo->seg[i]->cE,8)>0) {
        i++;
        if(i >= babo->iSegNum) {
          if(memcmp(ticK,"20:59:",6)==0) {
            memcpy(fubo->UpdateTime,ticK,9);      // save tick->UpdateTime "20:59:??" ...
            fubo->iChange = 1;
            memcpy(ticK,"21:00:00",8);            // 对于 "20:50:0x" 第一个周期走到这里
            i = 0;
            //b1->vold = 0;
            //b1->vsum = 0;
            break;
          } else {
            fubo->iTickValid = -1;
            return 0;
          }
        }
      }  // 找到 tick 在哪个段中
      curiX = i ;  // tick所在的段
      if(curiX == 0) {
        b1->vold = 0;
        b1->vsum = 0;
      }

      if(MARK==0) {
        curiE = babo->seg[curiX]->iB-1 ;   //for do while below!!
aaaa:
        if(memcmp(ticK,SEGE,8)<=0) {   // ---------
          do {
            curiB = curiE+1 ;
            curiE += fr ;
            if(curiE == babo->seg[curiX]->iE-1) {
              curiE = babo->seg[curiX]->iE ;
            }
            uBEE::MakeTime(curB,curiB);
            uBEE::MakeTime(curE,curiE);
          } while(memcmp(ticK,curE,8)>0);

          NEW_B1;
          memcpy(barB,curB,9);
          memcpy(barE,curE,9);
          //Display(fubo,tick,period,"eeee:011---");

          goto rrr;
          //return 0; //虽然没有用，但还是留着。
        } // (memcmp(ticK,SEGE,8)<0)
        fubo->iTickValid = 1;
        return 0;
      }

      if(MARK > 0) {
        NEW_B1;
        curiB = babo->seg[curiX]->iB ;
        curiE = babo->seg[curiX]->iE ;
        memcpy(curB,babo->seg[curiX]->cB,9);
        memcpy(curE,babo->seg[curiX]->cE,9);
        memcpy(barB,babo->seg[curiX]->barB,9);
        memcpy(barE,babo->seg[curiX]->barE,9);
        //Display(fubo,tick,period,"eeee:012---");
rrr:
        if(memcmp(ticK,barE,8)==0) {
          if(tick->UpdateMillisec >= 500) {
            //Display(fubo,tick,period,"eeee:goo---0");
            MarkBar(fubo,tick,period);
            SendBar(fubo,tick,period);
          }
        }
        fubo->iTickValid = 1;
        return 0;
      }
      fubo->iTickValid = 1;
      return 0;
    } // ----------------------------
    fubo->iTickValid = -1;
    return 0;
  } // MARK > 0
  // --------------------------------------------------------------------
  if(MARK < 0) {
    curiX = babo->iSegNum;
    goto bbbb;
  } // MARK < 0

  /*
    curB--curE
    barB--barE
    segB--segE
    mark ==> 每个seg的类型, 0:表示这个seg包含多个bar。 1：2：3：表示 此seg属于某个bar。
    idx  ==> seg 数组下标
  */
  return 0;
}


int MakeTime(char *caT, int T)
{
  int h,m,s;
  char cTmp[9];
  h = T / 3600;
  m =(T - h*3600) / 60;
  s = T % 60;
  see_memzero(cTmp,9);
  sprintf(cTmp,"%02d:%02d:%02d",h,m,s);
  memcpy(caT, cTmp, 9);
  return 0;
}


int SendTick(uBEE::FuBo *fubo, TICK *tick)
{
  char  *curB = fubo->pBaBo[0]->curB ;
  char  *curE = fubo->pBaBo[0]->curE ;
  int  &curiX = fubo->pBaBo[0]->curiX ;
  BaBo  *babo = fubo->pBaBo[0] ;
#define ticK tick->UpdateTime
  int i = 0;
  if(memcmp(ticK,curB,8)>=0 && memcmp(ticK,curE,8)<=0) {
    goto valid;
  } else {
    if(curiX < babo->iSegNum-1) {
      if(memcmp(ticK,"20:50:00",8) >=0) {
        i = 0 ;                    // i always be 0 !!! no bug!
      } else {
        i = curiX+1;               // 如果最后一个段没有任何数据过来， bug!!! here
      }
    } else {                       //一天结束，从头开始
      i = 0;
    }
    while(memcmp(ticK,babo->seg[i]->cB,8)<0 || memcmp(ticK,babo->seg[i]->cE,8)>0) {
      i++;
      if(i >= babo->iSegNum) {
        if(memcmp(ticK,"20:59:",6)==0) {
          i = 0;
          goto valid;
        } else {
          fubo->iTickValid = -1;
          return 0;
        }
      }
    }  // 找到 tick 在哪个段中
    curiX = i ;
    memcpy(curB,babo->seg[i]->cB,9);
    memcpy(curE,babo->seg[i]->cE,9);

valid:
    nTick->iType = T_TICK;
    snprintf(nTick->InstrumentID,31,"%s",fubo->InstrumentID);
    snprintf(nTick->TradingDay,9,"%s",tick->TradingDay);
    snprintf(nTick->ActionDay,9,"%s",tick->ActionDay);
    memcpy(nTick->UpdateTime,tick->UpdateTime,9) ;
    nTick->OpenPrice       = tick->OpenPrice;
    nTick->HighestPrice    = tick->HighestPrice;
    nTick->LowestPrice     = tick->LowestPrice;
    nTick->LastPrice       = tick->LastPrice;
    nTick->OpenInterest    = tick->OpenInterest;
    nTick->UpdateMillisec  = tick->UpdateMillisec;
    nTick->BidPrice1       = tick->BidPrice1;
    nTick->BidVolume1      = tick->BidVolume1;
    nTick->AskPrice1       = tick->AskPrice1;
    nTick->AskVolume1      = tick->AskVolume1;
    nTick->Volume          = tick->Volume;
    fubo->SG->broadcast((const char*)nTick, tLen, uWS::OpCode::BINARY);

    fubo->iTickValid = 1;
  }
  return 0;
}


int SaveTick(uBEE::FuBo *fubo, TICK *tick)
{
  char f[512] ;

  if(fubo->iChange ==1) {
    memcpy(tick->UpdateTime,fubo->UpdateTime,9);      // save tick->UpdateTime "20:59:??" ...
    fubo->iChange = 0 ;
  }

  snprintf(f,512,"../data/tick/%s.%s.tick.bin",tick->InstrumentID,tick->TradingDay);
  SaveBin(f,(const char *)tick,sizeof(TICK)) ;

  snprintf(f,512,"../data/tick/%s.%s.tick.txt",tick->InstrumentID,tick->TradingDay);
  snprintf(ca_errmsg,ERR_MSG_LEN,"T:%s %s %06d S:%d A:%s H:%g L:%g LP:%g AP:%g AV:%d BP:%g BV:%d OI:%g V:%d",
           tick->TradingDay,      tick->UpdateTime,
           tick->UpdateMillisec*1000, 0,            tick->ActionDay,
           tick->HighestPrice, tick->LowestPrice,   tick->LastPrice,
           tick->AskPrice1,    tick->AskVolume1,
           tick->BidPrice1,    tick->BidVolume1,
           tick->OpenInterest, tick->Volume);
  SaveLine(f,ca_errmsg) ;
}

int HandleTick(uBEE::FuBo *fubo, TICK *tick)
{
  int i = 0;
  int k = 0;
  int x = 0;
  stBar *b1;

  snprintf(nData->InstrumentID,31,"%s",fubo->InstrumentID);
  snprintf(nData->TradingDay,9,"%s",tick->TradingDay);
  snprintf(nData->ActionDay,9,"%s",tick->ActionDay);

  nData->iType = T_BARS;

// ----------  period   idx from 1 to 49 ---------------
  x=0;
  for(i=1; i<50; ++i) {
    if(fubo->pBaBo[i] != nullptr) {
      b1 = fubo->pBaBo[i]->b1 ;
      MarkBar(fubo,tick,i) ;
      if(b1->sent == 1) {
        b1->sent = 2;

        nData->KK[x].iX = i;
        nData->KK[x].iF = fubo->pBaBo[i]->iF;
        memcpy(nData->KK[x].cB,b1->cB,9);
        memcpy(nData->KK[x].cE,b1->cE,9);
        nData->KK[x].o = b1->o ;
        nData->KK[x].h = b1->h ;
        nData->KK[x].l = b1->l ;
        nData->KK[x].c = b1->c ;
        nData->KK[x].v = b1->v ;
        nData->KK[x].vsum = b1->vsum ;
        ++x ;
      }
    }
  } // for --
  nData->iN = x ;
  if(x>0) {
    fubo->SG->broadcast((const char*)nData, hLen+bLen*x, uWS::OpCode::BINARY);
  }

//  ---------  saving Klines Kbars !!!
//下面两个for必须分开写，因为DealBar中会改写 KBuf
  char f[512];
  for(k=0; k<nData->iN; ++k) {
    x = nData->KK[k].iX ;
    fubo->pBaBo[x]->b1->sent = 2 ;   // 如果已经send过，在下面的 DealBar中，可能会再次MarkBar() SendBar()
    snprintf(f,512,"../data/%s_%02d_%02d_%02d.%d.%di",nData->InstrumentID,
             fubo->pBaBo[x]->iH, fubo->pBaBo[x]->iM,
             fubo->pBaBo[x]->iS, fubo->pBaBo[x]->iF, x);

    snprintf(ca_errmsg,ERR_MSG_LEN,"%s T:%s A:%s %s--%s O:%g H:%g L:%g C:%g V:%d vsam:%d",
             nData->InstrumentID,
             nData->TradingDay,
             nData->ActionDay,
             nData->KK[k].cB,nData->KK[k].cE,
             nData->KK[k].o, nData->KK[k].h, nData->KK[k].l, nData->KK[k].c,
             nData->KK[k].v, nData->KK[k].vsum) ;
    //SaveLine(f,ca_errmsg) ;
  }

//-------------  update or new  bar!!!
  for(i=1; i<50; ++i) {
    if(fubo->pBaBo[i] != nullptr) {
      DealBar(fubo,tick,i) ;
    }
  }

  // ---------- send other updating bars : bar not end !!  ---------------
  if(fubo->iTickValid ==1) {

    nData->iType = T_UPDATE;

    x=0;
    for(i=1; i<50; ++i) {
      if(fubo->pBaBo[i] != nullptr) {
        if(b1->sent == 0) {

          nData->KK[x].iX = i;
          nData->KK[x].iF = fubo->pBaBo[i]->iF;
          memcpy(nData->KK[x].cB,b1->cB,9);
          memcpy(nData->KK[x].cE,b1->cE,9);
          nData->KK[x].o = b1->o ;
          nData->KK[x].h = b1->h ;
          nData->KK[x].l = b1->l ;
          nData->KK[x].c = b1->c ;
          nData->KK[x].v = b1->v ;
          nData->KK[x].vsum = b1->vsum ;

          ++x ;
        }
      }
    } // for --
    nData->iN = x ;
    fubo->SG->broadcast((const char*)nData, hLen+bLen*x, uWS::OpCode::BINARY);
  }

  return 0;
}

// period 是指数组下标
int SendBar(uBEE::FuBo *fubo, TICK *tick,int period)
{
  BaBo * babo = fubo->pBaBo[period] ;
  stBar *b1 = babo->b1 ;
  char f[512] ;

  //snprintf(nData->InstrumentID,31,"%s",fubo->InstrumentID);
  //snprintf(nData->TradingDay,9,"%s",tick->TradingDay);
  //snprintf(nData->ActionDay,9,"%s",tick->ActionDay);

  if(b1->sent==1) {   // 这里有 sent=2的情况，表示前面已经send过了。
    b1->sent =2 ;

    nData->iType = T_BARS ;

    nData->KK[0].iX = period;
    nData->KK[0].iF = fubo->pBaBo[period]->iF;
    memcpy(nData->KK[0].cB,b1->cB,9);
    memcpy(nData->KK[0].cE,b1->cE,9);
    nData->KK[0].o = b1->o ;
    nData->KK[0].h = b1->h ;
    nData->KK[0].l = b1->l ;
    nData->KK[0].c = b1->c ;
    nData->KK[0].v = b1->v ;
    nData->KK[0].vsum = b1->vsum ;
    nData->iN = 1;

    fubo->SG->broadcast((const char*)nData, oLen, uWS::OpCode::BINARY);

    snprintf(f,512,"../data/%s_%02d_%02d_%02d.%d.%di",nData->InstrumentID,babo->iH,babo->iM,babo->iS,babo->iF,period);
    snprintf(ca_errmsg,ERR_MSG_LEN,"%s T:%s A:%s %s--%s O:%g H:%g L:%g C:%g V:%d vsam:%d",
             nData->InstrumentID,
             nData->TradingDay,
             nData->ActionDay,
             nData->KK[0].cB,nData->KK[0].cE,
             nData->KK[0].o, nData->KK[0].h, nData->KK[0].l, nData->KK[0].c,
             nData->KK[0].v, nData->KK[0].vsum) ;
    //SaveLine(f,ca_errmsg) ;
  }
  return 0;
}

// period 是指数组下标
int SaveBar(uBEE::FuBo *fubo, TICK *tick,int period)
{
}

// period 是指数组下标
int MarkBar(uBEE::FuBo *fubo, TICK *tick,int period)
{
  stBar   *b1 = fubo->pBaBo[period]->b1 ;
  char * curB = fubo->pBaBo[period]->curB ;
  char * curE = fubo->pBaBo[period]->curE ;
  int  &curiX = fubo->pBaBo[period]->curiX ;

  char * barB = b1->cB ;
  char * barE = b1->cE ;

  BaBo * babo = fubo->pBaBo[period] ;

#define SEGB fubo->pBaBo[period]->seg[curiX]->cB
#define SEGE fubo->pBaBo[period]->seg[curiX]->cE
#define MARK babo->seg[curiX]->mark
#define ticK tick->UpdateTime

  //---------------------------------------------
  if(memcmp(barE,ticK,8)==0) {
    if(tick->UpdateMillisec >= 500) {
      UPDATE_B1;
      b1->sent = 1;
      return 0;
    }
  }

  if(memcmp(ticK,curB,8)>=0 &&
     memcmp(ticK,curE,8)<=0) { // 在当前的 curB curE 这个segment内
    return 0;
  }

  if(MARK == 0) {
    if(b1->sent == 0) {
      b1->sent = 1;
    }
    return 0;
  }

  if(MARK > 0) {
    if((memcmp(SEGE,barE,8)<=0 && (memcmp(barE,ticK,8)<0 || memcmp(ticK,SEGE,8)<0)) ||
       (memcmp(SEGE,ticK,8)>0 && memcmp(ticK,barE,8)>0)) {
      if(b1->sent == 0) {
        b1->sent = 1;
      }
    }
    return 0;
  }

  if(MARK < 0) {
    return 0;
  }

  return 0;
}

int Display(uBEE::FuBo *fubo, TICK *tick,int period,const char*msg)
{
  BaBo * babo = fubo->pBaBo[period] ;
  stBar *b1 = babo->b1 ;

  char * curB = babo->curB ;
  char * curE = babo->curE ;
  int &curiB = babo->curiB ;
  int &curiE = babo->curiE ;
  int &curiX = babo->curiX ;
  int fr = babo->iF ;

  char * barB = b1->cB ;
  char * barE = b1->cE ;
  char * tik = tick->UpdateTime ;

  char * segB = babo->seg[curiX]->cB;
  char * segE = babo->seg[curiX]->cE;
  int  &mark  = babo->seg[curiX]->mark;


  if(T________) {
    sprintf(ca_errmsg,"%s p:%d fr:%d tick:%s ms:%d crBE:%s-%s brBE:%s-%s sgBE:%s-%s curiX:%d",
            msg,
            period,fr,tick->UpdateTime,tick->UpdateMillisec, curB,curE, barB,barE, SEGB,SEGE, curiX) ;
    uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
  }
  return 0;
}

int DispBar(uBEE::FuBo *fubo, TICK *tick,int period,const char*msg)
{
  BaBo * babo = fubo->pBaBo[period] ;
  stBar *b1 = babo->b1 ;

  if(T________) {
    sprintf(ca_errmsg,"%s fr:%d  T:%s A:%s B:%s--%s H:%lf O:%lf C:%lf L:%lf V:%d vsam:%d",
            msg, babo->iF,b1->TradingDay, b1->ActionDay,
            b1->cB, b1->cE,
            b1->h, b1->o, b1->c, b1->l,
            b1->v, b1->vsum) ;
    uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
  }
}

} //namespace
