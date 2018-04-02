#include "uBEE.h"
#include <thread>
#include <unistd.h>
#include <iostream>

using namespace uBEE;
int main()
{

  struct  timeval start;
  struct  timeval end;

  uBEE::Base b;

  //static std::string   Future[] = {"ru1801","zn1801"};
  //static int           Period[] = { 60,300,3600 } ;
  std::map<std::string,std::vector<int>> M_futures ;
  M_futures["ru1801"] = {0,60,300,3600};
  M_futures["ru1805"] = {60,300,3600};
  M_futures["ru1807"] = {60,300,3600};
  M_futures["ru1809"] = {5,15,30,60,300,3600};

  //-------------------- 变量定义 -----------------------------------
  b.Mode = 4;
  //b.Init(Future,Period) ;


  //-------------------- 变量定义 -----------------------------------


  gettimeofday(&start,NULL);
  for(int i=0; i<100; i++) {
    b.getFutureTick("20170101", "20180101");
  }
  gettimeofday(&end,NULL);
  unsigned  long diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
  diff = diff/10000;
  printf("thedifference is %ld\n",diff);
  //uBEE::ErrLog(1000,"kkkk",1,(const char*)&diff,sizeof(unsigned  long));
  //uBEE::ErrLog(1000,"notttttttttttttt",1,0,0);

  std::cout << " end getTick() !!\n";

  int aa = 1009;

  b.onTick([&aa](char* data, size_t len) {
    barSG * KBuf = (barSG *)data ; 
    std::cout << KBuf->InstrumentID << " " << KBuf->ActionDay<<" "<< KBuf->iN  << std::endl ;
    for(int i = 0; i< KBuf->iN ; ++i ) {
      std::cout << KBuf->KK[i].cK << std::endl;
    }
    // usleep(1000000);
    //std::cout << aa << std::endl;
    //aa = 5990;
    //std::cout << aa << std::endl;
  });

  b.onBars([&aa](char* message, size_t len) {
    //message[len] = 0;
    //std::cout<<" I am in onBars !"<<std::endl;
    //std::cout<<message<<std::endl;
    //std::cout << aa << std::endl;
    //aa = 5990;
    //std::cout << aa << std::endl;
  });

  b.Run();
  std::cout << " game over ! " << std::endl;

  while(1) {
    // b.cs[0]->send("------------------------from main -----------");
    usleep(1000000);
  }
  usleep(8000000);


}
