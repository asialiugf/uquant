#include "uBEE.h"
#include "Indicator.h"
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

  sRSI *r;

  sEKE *e1;
  sEKE *e2;
  sEKE *e3;
  sEKE *e4;

  sMNF *m1;
  sMNF *m2;
  sMNF *m3;
  sMNF *m4;

  //-------------------- initialize -----------------------------------
  gettimeofday(&start,NULL);
  for(int i=0; i<2; i++) {
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



  //-------------------- onInit -----------------------------------
  BB->onInit([&]() {
    r = new sRSI(BB,(char*)"ru1809", 5, 14);
    e1 = new sEKE(BB,(char*)"ru1809",5, 36, 1, 12, 4);
    e2 = new sEKE(BB,(char*)"ru1809",5, 9*16, 8, 3*16, 16);
    e3 = new sEKE(BB,(char*)"ru1809",5, 9*64, 21, 3*64, 64);
    e4 = new sEKE(BB,(char*)"ru1809",5, 9*64*4, 34, 3*64*4, 64*4);
    m1 = new sMNF(BB,e1,(char*)"ru1809",5, 36);
    m2 = new sMNF(BB,e2,(char*)"ru1809",5, 9*16);
    m3 = new sMNF(BB,e3,(char*)"ru1809",5, 9*64);
    m4 = new sMNF(BB,e4,(char*)"ru1809",5, 9*64*4);
    std::cout << "whyyyyy333333\n" ;
  });
  //-------------------- onTick -----------------------------------
  BB->onTick([&](sTick *tick) {
    std::cout << "tick mnf4::" <<  m4->MNF[m4->x] << std::endl;
  });

  //-------------------- onBars -----------------------------------
  BB->onBars([&](sKbar * bar[], int len) {
    for(int i=0; i<len; ++i) {
      // --------------------- F1 begin ---------------------------------
      if(bar[i]->iF == 5) {
        std::cout << r->RSI[r->x] << std::endl;
        std::cout << "bar mnf4::" <<  m4->MNF[m4->x] << std::endl;
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
