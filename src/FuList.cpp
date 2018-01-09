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
  memcpy(Date,pDate,8);

  memcpy(yy,Date,4);
  memcpy(mm,Date+4,2);
  memcpy(dd,Date+6,2);
  y = atoi(yy);
  m = atoi(mm);
  d = atoi(dd);
  Year = y;
  Month = m;
  Day = d;

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
  week = FuList::DateDeal(pDate);
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
}

} // namespace
