#include "uBEE.h"
//#include <Base.h>
#include <thread>
#include <unistd.h>
#include <iostream>

int main()
{

  std::cout << "请输入日期:" << std::endl;
  char str1[20];
  std::cin >> str1;
  // ------------------------------------------------------------
  uBEE::FuList fl;
  int rtn = fl.Init(str1);
  if(rtn < 0) {
    exit (-1);
  }
  //fl.Init("20170418");
  std::cout << "week:"<< fl.Week << std::endl;
  std::cout << "date:"<< fl.Date << std::endl;
  std::cout << "date:"<< fl.Year << std::endl;
  std::cout << "date:"<< fl.Month << std::endl;
  std::cout << "date:"<< fl.Day << std::endl;
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< SHFE_NUMBER; i++) {
    std::cout << fl.ShfeList[i] << " " ;
    if(memcmp(fl.ShfeList[i],fl.ShfeList[i+1],2)!=0) {
       std::cout << std::endl;
    }
  }
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< SHFE_NUMBER; i++) {
    std::cout << fl.CzceList[i] <<  " " ;
    if(memcmp(fl.CzceList[i],fl.CzceList[i+1],2)!=0) {
       std::cout << std::endl;
    }
  }
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< SHFE_NUMBER; i++) {
    std::cout << fl.DceList[i] << " " ;
    if(memcmp(fl.DceList[i],fl.DceList[i+1],2)!=0) {
       std::cout << std::endl;
    }
  }
  std::cout << " \n---------------------------------------------------------------------------\n";
  return 0;
}
