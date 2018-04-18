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
  //fuMap["ag1809"] = {5,15,30,60,300,3600,14401};

  //-------------------- 变量定义 -----------------------------------
  uBEE::Base *BB = new uBEE::Base();
  BB->Mode = 4;
  BB->FuInit(&fuMap);

  //-------------------- 变量定义 -----------------------------------


  //-------------------- 变量定义 -----------------------------------
  D_OHLC *F1 = new D_OHLC() ;
  int &x = F1->x;

  D_RSI *rsi = new D_RSI(F1);

  D_EKE *KE1 = new D_EKE(F1);
  D_EKE *KE2 = new D_EKE(F1);
  D_EKE *KE3 = new D_EKE(F1);
  D_EKE *KE4 = new D_EKE(F1);

  D_MNF *M1 = new D_MNF(KE1);
  D_MNF *M2 = new D_MNF(KE2);
  D_MNF *M3 = new D_MNF(KE3);
  D_MNF *M4 = new D_MNF(KE4);
  //-------------------- initialize -----------------------------------
  gettimeofday(&start,NULL);
  for(int i=0; i<100; i++) {
    BB->getFutureTick((const char *)"20170101",(const char *) "20180101");
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
  });

  //-------------------- onBars -----------------------------------
  BB->onBars([&](sKbar * bar[], int len) {
    for(int i=0; i<len; ++i) {

      // --------------------- F1 begin ---------------------------------
      if(bar[i]->iF == 60) {
        F1->Insert(bar[i]);                 // add OHLC
        //x = F1->x;
        rsi->Update(14) ;

        KE1->Update(36, 1, 12, 4);                    // calculate kdj
        KE2->Update(9*16, 2, 3*16, 16);             // calculate kdj
        KE3->Update(9*64, 21, 3*64, 64);             // calculate kdj
        KE4->Update(9*64*4, 34, 3*64*4, 64*4);     // calculate kdj

        M1->Update(36) ;                          // RSV ---
        M2->Update(9*16) ;
        M3->Update(9*64) ;
        M4->Update(9*64*4) ;

        // --------- for debug ---------------
        //DispKbar(BB->InstrumentID, BB->TradingDay, BB->ActionDay,bar[i]);
        //std::cout <<"mmmmmm1 2 3 4:"<<M1->MNF[x]<<" "<<M2->MNF[x]<<" "<<M3->MNF[x]<<" "<<M4->MNF[x]<<" "<< std::endl ;
        //std::cout <<"ke:"<<M1->KE->K[x]<<" "<<M2->KE->K[x]<<" "<<M3->KE->K[x]<<" "<<M4->KE->K[x]<<" "<< std::endl ;
        //std::cout <<"ssssssss:"<<rsi->RSI[rsi->x] << std::endl;
        // --------- for debug ---------------

        //---------for test ---------------------
        if(rsi->RSI[x] > rsi->RSI[x-1] && rsi->RSI[x] > 30 && rsi->RSI[x-1] < 30) {
          std::cout << "rsi--up:" <<BB->ActionDay<<" "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<bar[i]->c << std::endl;
        }
        if(rsi->RSI[x] < rsi->RSI[x-1] && rsi->RSI[x] < 70 && rsi->RSI[x-1] > 70) {
          std::cout << "rsi--down:" <<BB->ActionDay<<" "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<bar[i]->c << std::endl;
        }
        //---------for test ---------------------

        if(F1->x > 1000) {
          BB->fu->DStopLost(1,bar[i]->c);
          BB->fu->StopProfit(1,bar[i]->c);
         // BB->fu->CurrPL(bar[i]->c) ;
          std::cout << "current pl:" <<BB->ActionDay<<" "<<bar[i]->cB<<"-"<<bar[i]->cE<<" " << BB->fu->mPL <<" "<<bar[i]->c << std::endl;

          if(M3->MNF[x] > M3->MNF[x-1] && M3->MNF[x-1] <= M3->MNF[x-2]) {
            std::cout << "bbbbbbbbb:" <<BB->ActionDay<<" "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<bar[i]->c << std::endl;
            BB->fu->SellShort(1,bar[i]->c);
            BB->fu->BuyLong(1,bar[i]->c);
            std::cout <<" mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
          }
          if(M3->MNF[x] < M3->MNF[x-1] && M3->MNF[x-1] >= M3->MNF[x-2]) {
            std::cout << "sssssssss:" <<BB->ActionDay<<" "<<bar[i]->cB<<"-"<<bar[i]->cE<<" "<<bar[i]->c << std::endl;
            BB->fu->SellLong(1,bar[i]->c);
            BB->fu->BuyShort(1,bar[i]->c);
            std::cout <<" mPL:"<<BB->fu->mPL<< " NL:"<< BB->fu->NL<< " NS:"<< BB->fu->NS << std::endl;
          }

        } // ----- end --- 700

      } // ----- end --- F1 60-----------

    } // -----------------for -----
  });

//-------------------- Run!! -----------------------------------
  BB->Run();
  std::cout << " game over ! " << std::endl;

  while(1) {
    usleep(1000000);
  }
}
