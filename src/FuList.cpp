#include "uBEE.h"
#include <cjson/cJSON.h>
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

void FuList::TK(int a)
{
  const std::map<std::string,std::string> *MP ;

  if(a ==1) {
    std::cout <<  "TK 11111111111111111111111 \n" ;
    MP = &M_SHFE;
  } else {
    std::cout <<  "TK 22222222222222222222222 \n" ;
    MP = &M_CFFE;
  }
  for(auto it = (*MP).begin(); it != (*MP).end(); ++it) {
    std::cout << it->first << ", " << it->second << '\n';
  }
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
    rtc = (d<LastDay16[m-1][type]) ? 0:1;
    return rtc;
    break;
  case 2017:
    rtc = (d<LastDay17[m-1][type]) ? 0:1;
    return rtc;
    break;
  case 2018:
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

  // [1][0]: CFFE  --- [1][1]: SHFE  --- [1][2]: CZCE  --- [1][3]: DCE  ---
  FuList::TK(2);
  FuList::TK(1);
  FuList::TK(3);
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

  for(auto it = M_CFFE.begin(); it != M_CFFE.end(); ++it) {
    std::cout << it->first << ", " << it->second << '\n';
  }
}
void  FuList::ShfeListInit()
{
  int i;
  char future[31];
  int curYear;

  int MM[60] ;
  memset(future,'\0',31);

  for(auto it = M_SHFE.begin(); it != M_SHFE.end(); ++it) {
    std::cout << " ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n" ;
    std::cout << it->first << ", " << it->second << '\n';
    //if( memcmp("au",it->first.c_str(),2) {
    if("au" == it->first) {
      std::cout << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh au !!!\n" ;
      continue;
    }
    if("bu" == it->first) {
      std::cout << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh bu !!!\n" ;
      continue;
    }
    cJSON   *root ;
    cJSON   *jN ;
    cJSON   *jM ;
    cJSON   *tmp;
    int     Nn;      // "N" 的值··
    int     Mn;      // "M" 数组的长度 ..

    root = cJSON_Parse(it->second.c_str());
    if(!root) {
      ErrLog(1000,"message to json error!",1,0,0);
      return ;
    }

    jN = cJSON_GetObjectItem(root, "N");
    if(!jN) {
      uBEE::ErrLog(1000,"no aid error!",1,0,0);
      return ;
    }
    Nn = jN->valueint;

    jM = cJSON_GetObjectItem(root, "M");
    if(!jM) {
      uBEE::ErrLog(1000,"no aid error!",1,0,0);
      return ;
    }
    Mn = cJSON_GetArraySize(jM);
    if(Mn<=0) {
      continue ;
    }

    // ------  fill MM[60] --------------------------
    int tms = 60/Mn ;
    int lst = 60 - Mn*tms ;
    int k =0;
    for(int j =0; j< tms; j++) {
      for(i=0; i<Mn; i++) {
        tmp = cJSON_GetArrayItem(jM,i);
        MM[k] = tmp->valueint + j*12 ;
        k++;
      }
    }
    for(i=0; i<lst; i++) {
      tmp = cJSON_GetArrayItem(jM,i);
      MM[k] = tmp->valueint + tms*12;
      k++;
    }
    // ------- fill MM[2] ------ end -----------------------------------

    for(i=0; i<Nn; i++) {
      std::cout<< Month << "  " << MM[i] << std::endl;
      if(Month <= MM[i]) {
        k=i;
        break;
      }
    }
    if(Month == MM[k]) {
      if(1 == isFirstDay(1,Year,Month,Day)) {
        k++;
      }
    }
    std::cout <<  "oooooooooo:::::::" << k << std::endl;
    for(i=0; i<Nn; i++) {
      tms = (MM[k]-1)/12;
      curYear = Year + tms -2000;
      sprintf(future,"%s%02d%02d",it->first.c_str(),curYear,MM[k]-12*tms);
      k++;
      std::cout << future << std::endl;
    }

    cJSON_Delete(root);
  } // for 1
}
void  FuList::CzceListInit()
{
  int i;
  char future[31];
  int curYear;

  int MM[60] ;
  memset(future,'\0',31);

  for(auto it = M_CZCE.begin(); it != M_CZCE.end(); ++it) {
    std::cout << " ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n" ;
    std::cout << it->first << ", " << it->second << '\n';
    //if( memcmp("au",it->first.c_str(),2) {
    if("au" == it->first) {
      std::cout << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh au !!!\n" ;
      continue;
    }
    if("bu" == it->first) {
      std::cout << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh bu !!!\n" ;
      continue;
    }
    cJSON   *root ;
    cJSON   *jN ;
    cJSON   *jM ;
    cJSON   *tmp;
    int     Nn;      // "N" 的值··
    int     Mn;      // "M" 数组的长度 ..

    root = cJSON_Parse(it->second.c_str());
    if(!root) {
      ErrLog(1000,"message to json error!",1,0,0);
      return ;
    }

    jN = cJSON_GetObjectItem(root, "N");
    if(!jN) {
      uBEE::ErrLog(1000,"no aid error!",1,0,0);
      return ;
    }
    Nn = jN->valueint;

    jM = cJSON_GetObjectItem(root, "M");
    if(!jM) {
      uBEE::ErrLog(1000,"no aid error!",1,0,0);
      return ;
    }
    Mn = cJSON_GetArraySize(jM);
    if(Mn<=0) {
      continue ;
    }

    // ------  fill MM[60] ---------------------------------------------
    int tms = 60/Mn ;
    int lst = 60 - Mn*tms ;
    int k =0;
    for(int j =0; j< tms; j++) {
      for(i=0; i<Mn; i++) {
        tmp = cJSON_GetArrayItem(jM,i);
        MM[k] = tmp->valueint + j*12 ;
        k++;
      }
    }
    for(i=0; i<lst; i++) {
      tmp = cJSON_GetArrayItem(jM,i);
      MM[k] = tmp->valueint + tms*12;
      k++;
    }
    // ------- fill MM[2] ------ end -----------------------------------

    for(i=0; i<Nn; i++) {
      //std::cout<< Month << "  " << MM[i] << std::endl;
      if(Month <= MM[i]) {
        k=i;
        break;
      }
    }
    if(Month == MM[k]) {
      if(1 == isFirstDay(2,Year,Month,Day)) {
        k++;
      }
    }
    std::cout <<  "oooooooooo:::::::" << k << std::endl;
    for(i=0; i<Nn; i++) {
      tms = (MM[k]-1)/12;
      curYear = Year + tms -2010;
      sprintf(future,"%s%d%02d",it->first.c_str(),curYear,MM[k]-12*tms);
      k++;
      std::cout << future << std::endl;
    }

    cJSON_Delete(root);
  } // for 1


}

void  FuList::DceListInit()
{
  int i;
  char future[31];
  int curYear;

  int MM[60] ;
  memset(future,'\0',31);

  for(auto it = M_DCE.begin(); it != M_DCE.end(); ++it) {
    if("au" == it->first) {
      std::cout << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh au !!!\n" ;
      continue;
    }
    if("bu" == it->first) {
      std::cout << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh bu !!!\n" ;
      continue;
    }
    cJSON   *root ;
    cJSON   *jN ;
    cJSON   *jM ;
    cJSON   *tmp;
    int     Nn;      // "N" 的值··
    int     Mn;      // "M" 数组的长度 ..

    root = cJSON_Parse(it->second.c_str());
    if(!root) {
      ErrLog(1000,"message to json error!",1,0,0);
      return ;
    }

    jN = cJSON_GetObjectItem(root, "N");
    if(!jN) {
      uBEE::ErrLog(1000,"no aid error!",1,0,0);
      return ;
    }
    Nn = jN->valueint;

    jM = cJSON_GetObjectItem(root, "M");
    if(!jM) {
      uBEE::ErrLog(1000,"no aid error!",1,0,0);
      return ;
    }
    Mn = cJSON_GetArraySize(jM);
    if(Mn<=0) {
      continue ;
    }

    // ------  fill MM[60] ---------------------------------------------
    int tms = 60/Mn ;
    int lst = 60 - Mn*tms ;
    int k =0;
    for(int j =0; j< tms; j++) {
      for(i=0; i<Mn; i++) {
        tmp = cJSON_GetArrayItem(jM,i);
        MM[k] = tmp->valueint + j*12 ;
        k++;
      }
    }
    for(i=0; i<lst; i++) {
      tmp = cJSON_GetArrayItem(jM,i);
      MM[k] = tmp->valueint + tms*12;
      k++;
    }
    // ------- fill MM[2] ------ end -----------------------------------

    for(i=0; i<Nn; i++) {
      std::cout<< Month << "  " << MM[i] << std::endl;
      if(Month <= MM[i]) {
        k=i;
        break;
      }
    }
    if(Month == MM[k]) {
      if(1 == isFirstDay(3,Year,Month,Day)) {
        k++;
      }
    }
    std::cout <<  "oooooooooo:::::::" << k << std::endl;
    for(i=0; i<Nn; i++) {
      tms = (MM[k]-1)/12;
      curYear = Year + tms - 2000;
      sprintf(future,"%s%02d%02d",it->first.c_str(),curYear,MM[k]-12*tms);
      k++;
      std::cout << future << std::endl;
    }

    cJSON_Delete(root);
  } // for 1
}


} // namespace
