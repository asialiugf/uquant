#include "uBEE.h"
#include <thread>
#include <unistd.h>
#include <iostream>

using namespace uBEE;
int main()
{

  struct  timeval start;
  struct  timeval end;

  uBEE::Base *BB = new uBEE::Base();

  //标准周期
  //  0   1   2   3   4   5    6    7    8    9    10    11    12    13    14    15     16
  //  0S  1S  2S  3S  5S  10S  15S  20S  30S  1F   2F    3F    5F    10F   15F   20F    30F
  //  0,  1,  2,  3,  5,  10,  15,  20,  30,  60,  120,  180,  300,  600,  900,  1200,  1800
  //  0S是tick。
  //  17    18    19     20     21      22   23   24   25   26   27   28   29  30
  //  1H    2H    3H     4H     5H      6H   8H   10   12   1D   1W   1M   1J  1Y
  //  3600, 7200, 10800, 14400, 18000,  0,   0,   0,   0,   0,   0,   0,   0,  0};

  // 用户自定义 交易周期 不能超过20个 不能和已有的周期重复！
  //31  32   33   34   35
  const int fr[5] = {19,14401,9900,350,6600};

  std::map<std::string,std::vector<int>> M_futures ;
  M_futures["xu1801"] = {0,60,300,3600};
  M_futures["ru1805"] = {5,60,300,3600};
  M_futures["xu1807"] = {60,19,300,3600};
  M_futures["zz1805"] = {5,15,30,60,300,3600,14401};
  M_futures["ag1809"] = {5,15,30,60,300,3600,14401};

  //-------------------- 变量定义 -----------------------------------
  BB->Mode = 4;
  BB->FuInit(&M_futures,&fr[0],5);

  //exit(0);

  //-------------------- 变量定义 -----------------------------------


  gettimeofday(&start,NULL);
  for(int i=0; i<100; i++) {
    BB->getFutureTick("20170101", "20180101");
  }
  gettimeofday(&end,NULL);
  unsigned  long diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
  diff = diff/10000;
  printf("thedifference is %ld\n",diff);
  //uBEE::ErrLog(1000,"kkkk",1,(const char*)&diff,sizeof(unsigned  long));
  //uBEE::ErrLog(1000,"notttttttttttttt",1,0,0);

  std::cout << " end getTick() !!\n";

  int aa = 1009;

  //-------------------- 变量定义 -----------------------------------
  BB->onTick([&aa,&BB](sTick *tick) {
    //sTick * tick = (sTick *)data ;
    if(tick->iX == 0) {
      snprintf(ca_errmsg,1000,"T:%s %s %06d S:%d A:%s H:%g L:%g LP:%g AP:%g AV:%d BP:%g BV:%d OI:%g V:%d\n",
               BB->TradingDay,   tick->UpdateTime,
               tick->UpdateMillisec*1000, 0,            BB->ActionDay,
               tick->HighestPrice, tick->LowestPrice,   tick->LastPrice,
               tick->AskPrice1,    tick->AskVolume1,
               tick->BidPrice1,    tick->BidVolume1,
               tick->OpenInterest, tick->Volume);
      std::cout << ca_errmsg ;
    }
    /*
     for(int i = 0; i< KBuf->iN ; ++i) {
       std::cout << KBuf->KK[i].cK << std::endl;
     }
     */
    // usleep(1000000);
    //std::cout << aa << std::endl;
    //aa = 5990;
    //std::cout << aa << std::endl;
  });

  BB->onBars([&aa,&BB](sKbar * bar[], int len) {
    //sKbar * bar = (sKbar *)data ;
    //printf("%s %s %s\n",b->InstrumentID,b->TradingDay,b->ActionDay);
    for(int i=0; i<len; ++i) {
      if(bar[i]->iF != 0) {
        snprintf(ca_errmsg,ERR_MSG_LEN,"%s T:%s A:%s %s--%s O:%g H:%g L:%g C:%g V:%d vsam:%d\n",
                 BB->InstrumentID, BB->TradingDay, BB->ActionDay,
                 bar[i]->cB, bar[i]->cE,
                 bar[i]->o, bar[i]->h, bar[i]->l, bar[i]->c,
                 bar[i]->v, bar[i]->vsum) ;
        std::cout << ca_errmsg ;
      }
    }
    //usleep(1000000);

    //message[len] = 0;
    //std::cout<<" I am in onBars !"<<std::endl;
    //std::cout<<message<<std::endl;
    //std::cout << aa << std::endl;
    //aa = 5990;
    //std::cout << aa << std::endl;
  });

  BB->Run();
  std::cout << " game over ! " << std::endl;

  while(1) {
    // b.cs[0]->send("------------------------from main -----------");
    usleep(1000000);
  }
  usleep(8000000);


}
