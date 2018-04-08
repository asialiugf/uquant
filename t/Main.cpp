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
  fuMap["ru1809"] = {5,60};
  fuMap["xu1807"] = {60,19,300,3600};
  fuMap["zz1805"] = {5,15,30,60,300,3600,14401};
  fuMap["ag1809"] = {5,15,30,60,300,3600,14401};

  //-------------------- 变量定义 -----------------------------------
  uBEE::Base *BB = new uBEE::Base();
  BB->Mode = 4;
  BB->FuInit(&fuMap);

  D_OHLC S5 ;
  D_OHLC F1 ;
  D_OHLC F5 ;
  //int x;
  //-------------------- 变量定义 -----------------------------------
  D_KDJ S5_1 ;
  D_KDJ S5_2 ;
  D_KDJ S5_3 ;
  D_KDJ S5_4 ;

  D_KDJ F1_1 ;
  D_KDJ F1_2 ;
  D_KDJ F1_3 ;
  D_KDJ F1_4 ;
  //-------------------- 变量定义 -----------------------------------
  //exit(0);


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
    //std::cout << BB->fu->ID2 <<" "<<BB->fu->mMPF<<" "<< BB->fu->mLot<<" "<<BB->fu->mOP<<" "<<BB->fu->mCP<< std::endl;
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
  int S5x = 0;
  int F1x = 0;
  BB->onBars([&](sKbar * bar[], int len) {
    //std::cout << BB->fu->ID2 <<" "<<BB->fu->mMPF<<" "<< BB->fu->mLot<<" "<<BB->fu->mOP<<" "<<BB->fu->mCP<< std::endl;
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

      /*
      if(bar[i]->iF == 60) {
        s1F.Insert(x, bar[i]);                 // add OHLC
        s1F_1.Update(x, &s1F, 9, 3, 3, 5);     // calculate kdj

        std::cout <<"kkkkkkkkk: "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<s1F_1.K[x]<<" "<< s1F_1.D[x]<<" "<<s1F_1.J[x]<<" "<<s1F_1.E[x]<<std::endl;
        std::cout <<"ccccccccc: "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<s1F.O[x]<<" "<<s1F.H[x] <<" "<< s1F.L[x] <<" "<< s1F.C[x] << std::endl;

        if(x>30) {
          if((s1F_1.D[x] > s1F_1.E[x]) && (s1F_1.D[x-1] < s1F_1.E[x-1])) {
            std::cout <<"llllll:mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
            BB->fu->SellShort(1,bar[i]->c);
            BB->fu->BuyLong(1,bar[i]->c);
            std::cout <<"llllll:mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
          } else if((s1F_1.D[x] < s1F_1.E[x]) && (s1F_1.D[x-1] > s1F_1.E[x-1])) {
            std::cout <<"ssssss:mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
            BB->fu->SellLong(1,bar[i]->c);
            BB->fu->BuyShort(1,bar[i]->c);
            std::cout <<"ssssss:mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
          }
          std::cout <<"mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
        }

        ++x;
        if(x > 99999) {
          x = 0;
        }
      } // end--1F--
      */

      /*
      //---------------------------- S5 begin ----------------------------------------
      if(bar[i]->iF == 5) {
        S5.Insert(S5x, bar[i]);                 // add OHLC
        S5_1.Update(S5x, &S5, 36, 12, 12, 4);     // calculate kdj
        S5_2.Update(S5x, &S5, 9*16, 3*16, 3*16, 16);     // calculate kdj
        S5_3.Update(S5x, &S5, 9*64, 3*64, 3*64, 64);     // calculate kdj
        S5_4.Update(S5x, &S5, 9*64*4, 3*64*4, 3*64*4, 64*4);     // calculate kdj

        std::cout <<"kkkkkk: "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<S5_1.K[S5x]<<" "<<S5_2.K[S5x]<<" "<<S5_3.K[S5x]<<" "<<S5_4.K[S5x] <<std::endl;
        std::cout <<"cccccc: "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<S5.O[S5x]<<" "<<S5.H[S5x] <<" "<<S5.L[S5x]<<" "<<S5.C[S5x] <<std::endl;

        if(S5x > 256*11) {

          if(S5_2.K[S5x]>S5_2.K[S5x-1] &&
             S5_3.K[S5x]>S5_3.K[S5x-1] &&
             S5_4.K[S5x]>S5_4.K[S5x-1]) {
            if(BB->fu->NL==0) {
              BB->fu->SellShort(1,bar[i]->c);
              BB->fu->BuyLong(1,bar[i]->c);
              std::cout <<"llllll:"<<bar[i]->cB<<"-"<<bar[i]->cE<<" mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
            }
          } else if(S5_2.K[S5x]<S5_2.K[S5x-1] &&
                    S5_3.K[S5x]<S5_3.K[S5x-1] &&
                    S5_4.K[S5x]<S5_4.K[S5x-1]) {
            if(BB->fu->NS==0) {
              BB->fu->SellLong(1,bar[i]->c);
              BB->fu->BuyShort(1,bar[i]->c);
              std::cout <<"ssssss:"<<bar[i]->cB<<"-"<<bar[i]->cE<<" mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
            }
          }
        }
        ++S5x ;
        if(S5x > 99999) {
          x = 0;
        }
      } // end --5S-----------------------------------------
      */

      // --------------------- F1 begin ---------------------------------
      if(bar[i]->iF == 60) {
        F1.Insert(F1x, bar[i]);                 // add OHLC
        F1_1.Update(F1x, &F1, 36, 12, 12, 4);     // calculate kdj
        F1_2.Update(F1x, &F1, 9*16, 3*16, 3*16, 16);     // calculate kdj
        F1_3.Update(F1x, &F1, 9*64, 3*64, 3*64, 64);     // calculate kdj
        F1_4.Update(F1x, &F1, 9*64*4, 3*64*4, 3*64*4, 64*4);     // calculate kdj

        std::cout <<"kkkkkk: "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<F1_1.K[F1x]<<" "<<F1_2.K[F1x]<<" "<<F1_3.K[F1x]<<" "<<F1_4.K[F1x] <<std::endl;
        std::cout <<"cccccc: "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<F1.O[F1x]<<" "<<F1.H[F1x] <<" "<<F1.L[F1x]<<" "<<F1.C[F1x] <<std::endl;

        if(F1x > 700) {
          if(F1_1.K[F1x]>F1_1.K[F1x-1] &&
             F1_2.K[F1x]>F1_2.K[F1x-1] &&
             F1_3.K[F1x]>F1_3.K[F1x-1]) {
            if(BB->fu->NL==0) {
              BB->fu->SellShort(1,bar[i]->c);
              BB->fu->BuyLong(1,bar[i]->c);
              std::cout <<"llllll:"<<bar[i]->cB<<"-"<<bar[i]->cE<<" mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
            }
          } else if(F1_1.K[F1x]<F1_1.K[F1x-1] &&
                    F1_2.K[F1x]<F1_2.K[F1x-1] &&
                    F1_3.K[F1x]<F1_3.K[F1x-1]) {
            if(BB->fu->NS==0) {
              BB->fu->SellLong(1,bar[i]->c);
              BB->fu->BuyShort(1,bar[i]->c);
              std::cout <<"ssssss:"<<bar[i]->cB<<"-"<<bar[i]->cE<<" mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
            }
          }
        }
        ++F1x ;
        if(F1x > 99999) {
          x = 0;
        }

      } // ----- end --- F1 -----------



    } // -----------------for -----
  });

//-------------------- Run!! -----------------------------------
  BB->Run();
  std::cout << " game over ! " << std::endl;

  while(1) {
    usleep(1000000);
  }
}
