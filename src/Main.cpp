#include "uBEE.h"
//#include <Base.h>
#include <thread>
#include <unistd.h>
#include <iostream>

int main()
{

  //  for testing !! ------------------------------

  uBEE::FuList fl;
  fl.Init("20170418");
  std::cout << "week:"<< fl.Week << std::endl;
  std::cout << "date:"<< fl.Date << std::endl;
  std::cout << "date:"<< fl.Year << std::endl;
  std::cout << "date:"<< fl.Month << std::endl;
  std::cout << "date:"<< fl.Day << std::endl;


  // testing end -----------------------------------
  struct  timeval start;
  struct  timeval end;

  uBEE::Base b;

  //std::thread t(b.MainHubInit);
  //t.detach();

  //b.MainHubInit();
  //b.Init();

  //usleep(1000000);

  gettimeofday(&start,NULL);
  for(int i=0; i<100; i++) {
    b.getTick();
  }
  gettimeofday(&end,NULL);
  unsigned  long diff = 1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
  diff = diff/10000;
  printf("thedifference is %ld\n",diff);
  //uBEE::ErrLog(1000,"kkkk",1,(const char*)&diff,sizeof(unsigned  long));
  //uBEE::ErrLog(1000,"notttttttttttttt",1,0,0);

  std::cout << " end getTick() !!\n";

  int aa = 1009;

  b.onTick([&aa](char* message, size_t len) {
    message[len] = 0;
    std::cout<<" I am in onTick !"<<std::endl;
    std::cout<<message<<std::endl;
    std::cout << aa << std::endl;
    aa = 5990;
    std::cout << aa << std::endl;
  });

  b.onBars([&aa](char* message, size_t len) {
    message[len] = 0;
    std::cout<<" I am in onBars !"<<std::endl;
    std::cout<<message<<std::endl;
    std::cout << aa << std::endl;
    aa = 5990;
    std::cout << aa << std::endl;
  });

  b.Start();
  std::cout << " game over ! " << std::endl;

  while(1) {
    // b.cs[0]->send("------------------------from main -----------");
    usleep(1);
  }
  usleep(8000000);


}
