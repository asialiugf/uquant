#include "uBEE.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include<time.h>

namespace uBEE
{

FuList::FuList()
{
}
int FuList::isFirstDay(int type,int y,int m, int d)
{
  int rtc = -1;
  if(type <0 || type > 3) {
    std::cout << " type error !   [0]: CFFE  --- [1]: SHFE  --- [2]: CZCE  --- [3]: DCE  --- \n";
    return -1;
  }
  if(m<=0 || m>12) {
    std::cout << " month error !: " << m << std::endl;
    return -1;
  }
  if(d<=0 || d>31) {
    std::cout << " day error !: " << m << std::endl;
    return -1;
  }
  switch(y) {
  case 2016:
    std::cout << "+++++ year:" << y << "   month:" << m << "   day:" << d << "  type: " << type  << std::endl;
    std::cout << "+++++ LastDay16[m-1][type]:   " << LastDay16[m-1][type] << std::endl;
    rtc = (d<LastDay16[m-1][type]) ? 0:1;
    return rtc;
    break;
  case 2017:
    std::cout << "+++++ year:" << y << "   month:" << m << "   day:" << d << "  type: " << type  << std::endl;
    std::cout << "+++++ LastDay17[m-1][type]:   " << LastDay18[m-1][type] << std::endl;
    rtc = (d<LastDay17[m-1][type]) ? 0:1;
    return rtc;
    break;
  case 2018:
    std::cout << "+++++ year:" << y << "   month:" << m << "   day:" << d << "  type: " << type  << std::endl;
    std::cout << "+++++ LastDay18[m-1][type]:   " << LastDay18[m-1][type] << std::endl;
    rtc = (d<LastDay18[m-1][type]) ? 0:1;
    return rtc;
    break;
  default:
    std::cout << " year error !  year should be 2016 ,2017 or 2018 ! \n";
    return -1;
  }
}

int FuList::DateDeal(char const *pDate)
{
  int y,m,d;
  int week = 0;

  char yy[5];
  char mm[3];
  char dd[3];
  memset(yy,'\0',5);
  memset(mm,'\0',3);
  memset(dd,'\0',3);

  if(strlen(pDate) != 8) {
    return -1;
  }
  memset(Date,'\0',9);
  memcpy(Date,pDate,8);  // 成员变量

  memcpy(yy,Date,4);
  memcpy(mm,Date+4,2);
  memcpy(dd,Date+6,2);
  y = atoi(yy);
  m = atoi(mm);
  d = atoi(dd);

  Year = y;          // 成员变量
  Month = m;         // 成员变量
  Day = d;           // 成员变量

  if(m<0||m>12||d<0||d>31||y<0) {
    memset(Date,'\0',9);
    std::cout << " date is invalid !!\n";
    return -1;
  }

  if(m==1) {
    m=13;
    y--;
  }
  if(m==2) {
    m=14;
    y--;
  }
  if((y<1752)||((y==1752)&&(m<9))||((y==1752)&&(m==9)&&(d<3))) 	//判断是否在1752年9月3日之前
    week =(d+2*m+3*(m+1)/5+y+y/4+5)%7; 							//1752年9月3日之前的公式
  else
    week =(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7; 				//1752年9月3日之后的公式

  Week = week+1;
  return Week;

}

void FuList::Init(char const *pDate)
{
  int week;
  week = FuList::DateDeal(pDate);    //会初始化成员变量
  std::cout << "after FuList::DateDeal(pDate)" << Year << Month << Day << "-------\n";
  /*
  for(auto it = M_CFFE.begin(); it != M_CFFE.end(); ++it) {
    std::cout << it->first << ", " << it->second << '\n';
  }
  for(auto it = M_SHFE.begin(); it != M_SHFE.end(); ++it) {
    std::cout << it->first << ", " << it->second << '\n';
  }
  for(auto it = M_DCE.begin(); it != M_DCE.end(); ++it) {
    std::cout << it->first << ", " << it->second << '\n';
  }
  for(auto it = M_CZCE.begin(); it != M_CZCE.end(); ++it) {
    std::cout << it->first << ", " << it->second << '\n';
  }
  */
  // [1][0]: CFFE  --- [1][1]: SHFE  --- [1][2]: CZCE  --- [1][3]: DCE  ---
 
  std::cout << "============================\n";
  FuList::CffeListInit();
  FuList::ShfeListInit();
  FuList::CzceListInit();
  FuList::DceListInit();
}

void  FuList::CffeListInit()
{
  std::cout << "in  FuList::CffeListInit() :" << Year << Month << Day << "-------\n";
  int isFd = isFirstDay(0,Year,Month,Day);
  std::cout << "isFirstDay: CFFE :" << isFd << std::endl;
}
void  FuList::ShfeListInit()
{
  std::cout << "in  FuList::ShfeListInit() :" << Year << Month << Day << "-------\n";
  int isFd = isFirstDay(1,Year,Month,Day);
  std::cout << "isFirstDay: SHFE :" << isFd << std::endl;
}
void  FuList::CzceListInit()
{
  std::cout << "in  FuList::CzceListInit() :" << Year << Month << Day << "-------\n";
  int isFd = isFirstDay(2,Year,Month,Day);
  std::cout << "isFirstDay: CZCE :" << isFd << std::endl;
}
void  FuList::DceListInit()
{
  std::cout << "in  FuList::DceListInit() :" << Year << Month << Day << "-------\n";
  int isFd = isFirstDay(3,Year,Month,Day);
  std::cout << "isFirstDay: DCE :" << isFd << std::endl;
}

} // namespace
