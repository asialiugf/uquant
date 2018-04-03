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
  M_futures["ru1805"] = {60,300,3600};
  M_futures["xu1807"] = {60,19,300,3600};
  M_futures["zn1805"] = {5,15,30,60,300,3600,14401};

  //-------------------- 变量定义 -----------------------------------
  b.Mode = 4;
  b.FuInit(&M_futures,&fr[0],5);

  //exit(0);

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
    //std::cout << KBuf->InstrumentID << " " << KBuf->ActionDay<<" "<< KBuf->iN  << std::endl ;
    std::cout << KBuf->KK[0].cK <<std::endl;
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
