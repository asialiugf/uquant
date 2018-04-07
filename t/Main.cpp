#include "uBEE.h"
#include "Index.h"
#include <thread>
#include <unistd.h>
#include <iostream>
#include <vector>

using namespace uBEE;
int main()
{

  struct  timeval start;
  struct  timeval end;


  //------------------ 定义合约 及操作周期 --------------------------
  //31  32   33   34   35
  //const int fr[5] = {19,14401,9900,350,6600};

  std::map< std::string, std::vector<int> > fuMap ;
  fuMap["xu1801"] = {0,60,300,3600};
  fuMap["ru1805"] = {5,60,300,3600};
  fuMap["xu1807"] = {60,19,300,3600};
  fuMap["zz1805"] = {5,15,30,60,300,3600,14401};
  fuMap["ag1809"] = {5,15,30,60,300,3600,14401};

  //-------------------- 变量定义 -----------------------------------
  uBEE::Base *BB = new uBEE::Base();
  BB->Mode = 4;
  BB->FuInit(&fuMap);

  D_OHLC s5S ;
  D_OHLC s1F ;
  D_OHLC s5F ;
  //int x;
  //-------------------- 变量定义 -----------------------------------
  D_KDJ s5S_1 ;
  D_KDJ s5S_2 ;
  D_KDJ s5S_3 ;
  D_KDJ s5S_4 ;

  D_KDJ s1F_1 ;
  D_KDJ s1F_2 ;
  D_KDJ s1F_3 ;
  D_KDJ s1F_4 ;
  //-------------------- 变量定义 -----------------------------------
  std::cout << s5S_1.preH << "ha" << endl;
  for(int i=0; i<100; ++i) {
    std::cout << s5S_1.E[i] << "ha" << endl;
  }

  //exit(0);
  //-------------------- 变量定义 -----------------------------------


  //-------------------- initialize -----------------------------------
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

  //-------------------- onTick -----------------------------------
  BB->onTick([&aa,&BB](sTick *tick) {
    char f[512];
    snprintf(ca_errmsg,ERR_MSG_LEN,"T:%s %s %06d S:%d A:%s H:%g L:%g LP:%g AP:%g AV:%d BP:%g BV:%d OI:%g V:%d",
             tick->TradingDay,   tick->UpdateTime,
             tick->UpdateMillisec*1000, 0,            tick->ActionDay,
             tick->HighestPrice, tick->LowestPrice,   tick->LastPrice,
             tick->AskPrice1,    tick->AskVolume1,
             tick->BidPrice1,    tick->BidVolume1,
             tick->OpenInterest, tick->Volume);
    //std::cout << ca_errmsg <<std::endl;
    snprintf(f,512,"../exe/data/tick/%s.%s.tick.txtr",tick->InstrumentID,tick->TradingDay);
    //SaveLine(f,ca_errmsg) ;
  });

  //-------------------- onBars -----------------------------------
  int x = 0;   //非常重要的计数器
  BB->onBars([&](sKbar * bar[], int len) {
    char f[512];
    for(int i=0; i<len; ++i) {
      snprintf(ca_errmsg,ERR_MSG_LEN,"%s T:%s A:%s %s--%s O:%g H:%g L:%g C:%g V:%d vsam:%d",
               BB->InstrumentID, BB->TradingDay, BB->ActionDay,
               bar[i]->cB, bar[i]->cE,
               bar[i]->o, bar[i]->h, bar[i]->l, bar[i]->c,
               bar[i]->v, bar[i]->vsum) ;
      //std::cout << ca_errmsg << std::endl;
      snprintf(f,512,"../exe/data/%s_%d_%di",BB->InstrumentID, bar[i]->iF, bar[i]->iX);
      //SaveLine(f,ca_errmsg) ;

      if(bar[i]->iF == 60) {
        s1F.Insert(x, bar[i]);
        /*
        s5S.O[x] = bar[i]->o ;
        s5S.H[x] = bar[i]->h ;
        s5S.L[x] = bar[i]->l ;
        s5S.C[x] = bar[i]->c ;
        s5S.V[x] = bar[i]->v ;
        */
        s1F_1.Update(x, &s1F, 9, 3, 3, 5);
        /*
        SEE_KDJ(x, x, &s5S.H[0], &s5S.L[0], &s5S.C[0], &s5S_1.preH, &s5S_1.preL, &s5S_1.preF, 9, 3, 3,
                &s5S_1.R[0], &s5S_1.K[0], &s5S_1.D[0], &s5S_1.J[0]) ;
        SEE_EMA(x, x, &s5S_1.D[0], 5, &s5S_1.E[0]) ;
        */
        std::cout <<"kkkkkkkkk: "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<s1F_1.K[x]<<" "<< s1F_1.D[x]<<" "<<s1F_1.J[x]<<" "<<s1F_1.E[x]<<std::endl;
        std::cout <<"ccccccccc: "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<s1F.O[x]<<" "<<s1F.H[x] <<" "<< s1F.L[x] <<" "<< s1F.C[x] << std::endl;
        ++x;
        if(x > 99999) {
          x = 0;
        }
      }
    }
  });

  //-------------------- Run!! -----------------------------------
  BB->Run();
  std::cout << " game over ! " << std::endl;

  while(1) {
    usleep(1000000);
  }
}
