#include "uBEE.h"
//#include <Base.h>
#include <thread>
#include <unistd.h>
#include <iostream>

int main()
{


  struct  timeval start;
  struct  timeval end;

  uBEE::Base b;

  //std::thread t(b.MainHubInit);
  //t.detach();

  //b.MainHubInit();
  //b.Init();

  usleep(1000000);

  gettimeofday(&start,NULL);
  for(int i=0; i<100; i++) {
    b.getTick();
  }
  gettimeofday(&end,NULL);
  unsigned  long diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
  diff = diff/10000;
  printf("thedifference is %ld\n",diff);
  diff = 8;
  uBEE::ErrLog(1000,"kkkk",1,(const char*)&diff,sizeof(unsigned  long));
  uBEE::ErrLog(1000,"notttttttttttttt",1,0,0);
  uBEE::ErrLog(1000,"kkkk",1,(const char*)"kkqddddddddddddddddddddddddddddddddddddddddfffffffffffffffffffff888888888888888888888888888ddddddddddpweruqrew",40);

  b.onTick([](char* message, size_t len) {
    message[len] = 0;
    std::cout<<" I am in onTick !"<<std::endl;
    std::cout<<message<<std::endl;
  });

  b.onBars([](char* message, size_t len) {
    message[len] = 0;
    std::cout<<" I am in onBars !"<<std::endl;
    std::cout<<message<<std::endl;
  });

  b.MainHubInit();

  while(1) {
    // b.cs[0]->send("------------------------from main -----------");
    usleep(1);
  }
  usleep(8000000);


}