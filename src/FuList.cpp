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
    rtc = (d<FirstDay16[m-1][type]) ? NON_FIRST_DAY:FIRST_DAY;
    return rtc;
    break;
  case 2017:
    rtc = (d<FirstDay17[m-1][type]) ? NON_FIRST_DAY:FIRST_DAY;
    return rtc;
    break;
  case 2018:
    rtc = (d<FirstDay18[m-1][type]) ? NON_FIRST_DAY:FIRST_DAY;
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
  if(y<2016 || y>2018) {
    std::cout << "year err!\n";
    return -2;
  }
  m = atoi(mm);
  std::cout << "month err!\n";
  if(m<1 || m>12) {
    return -3;
  }
  d = atoi(dd);
  std::cout << "day err!\n";
  if(m<1 || d>31) {
    return -4;
  }

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

int FuList::Init(char const *pDate)
{
  int rtn;
  rtn = FuList::DateDeal(pDate);    //会初始化成员变量
  if(rtn < 0) {
    std::cout << "日期输入错误！\n" ;
    return -1;
  }
  if(6==Week || 7==Week) {
    std::cout << " not trading day, week: " << Week << std::endl;
    return -1;
  }

  for(int i = 0; i< DCE_NUMBER; i++) {
    memset(ShfeList[i],'\0',FUTRUE_ID_LEN);
    memset(DceList[i], '\0',FUTRUE_ID_LEN);
    memset(CzceList[i],'\0',FUTRUE_ID_LEN);
    pShfeList[i] = nullptr;
    pDceList[i]  = nullptr;
    pCzceList[i] = nullptr;
  }
  for(int i = 0; i< CFFE_NUMBER; i++) {
    memset(CffeList[i],'\0',FUTRUE_ID_LEN);
    pCffeList[i] = nullptr;
  }

  std::cout << "after FuList::DateDeal(pDate)" << Year << Month << Day << "-------\n";

  // [1][0]: CFFE  --- [1][1]: SHFE  --- [1][2]: CZCE  --- [1][3]: DCE  ---
  FuList::CffeListInit();
  FuList::ListInit(TYPE_SHFE);
  FuList::ListInit(TYPE_CZCE);
  FuList::ListInit(TYPE_DCE);
  /*
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< SHFE_NUMBER; i++) {
    std::cout << ShfeList[i] << " " ;
  }
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< SHFE_NUMBER; i++) {
    std::cout << CzceList[i] <<  " " ;
  }
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< SHFE_NUMBER; i++) {
    std::cout << DceList[i] << " " ;
  }
  */
}

void  FuList::CffeListInit()
{
  int isFd = isFirstDay(TYPE_CFFE,Year,Month,Day);
  int m1;
  int m2;
  int j1;
  int j2;
  int FuNum = 0;
  int y1= Year -2000;
  int y2= y1+1;
  char future[31] ;
  memset(future,'\0',31);
  std::cout << "isFirstDay: CFFE :" << isFd << std::endl;

  for(auto it = M_CFFE.begin(); it != M_CFFE.end(); ++it) {
    if(1==isFirstDay(TYPE_CFFE,Year,Month,Day)) {
      m1 = Month + 1;
      m2 = Month + 2;
    } else {
      m1 = Month ;
      m2 = Month + 1;
    }
    //        3     6     9       12       15     18     21     24
    //   1  2  4 5   7 8   10 11    13 14

    if("IF" == it->first || "IC" == it->first || "IH" == it->first) {
      if(m2 < 3) {
        for(int i = 0; i<2; i++) {
          memset(future,'\0',31);
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,(m1+i));
          memcpy(CffeList[FuNum],future,strlen(future));
          FuNum ++;
        }
        for(int i = 0; i<2; i++) {
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,(3+i*3));
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
        }
      } else if(m2 < 6) {
        for(int i = 0; i<2; i++) {
          memset(future,'\0',31);
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,(m1+i));
          memcpy(CffeList[FuNum],future,strlen(future));
          FuNum ++;
        }
        for(int i = 0; i<2; i++) {
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,(6+i*3));
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
        }
        // 6 9
      } else if(m2 < 9) {
        for(int i = 0; i<2; i++) {
          memset(future,'\0',31);
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,(m1+i));
          memcpy(CffeList[FuNum],future,strlen(future));
          FuNum ++;
        }
        for(int i = 0; i<2; i++) {
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,(9+i*3));
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
        }
        //9 12
      } else if(m2 < 12) {
        for(int i = 0; i<2; i++) {
          memset(future,'\0',31);
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,(m1+i));
          memcpy(CffeList[FuNum],future,strlen(future));
          FuNum ++;
        }
        sprintf(future,"%s%d%02d",it->first.c_str(),y1,12);
        memcpy(CffeList[FuNum],future,strlen(future));
        memset(future,'\0',31);
        FuNum ++;
        sprintf(future,"%s%d%02d",it->first.c_str(),y2,3);
        memcpy(CffeList[FuNum],future,strlen(future));
        memset(future,'\0',31);
        FuNum ++;
        //12 3
      } else if(m2 < 15) {
        if(m1<=12) {
            memset(future,'\0',31);
            sprintf(future,"%s%d%02d",it->first.c_str(),y1,m1);
            memcpy(CffeList[FuNum],future,strlen(future));
            FuNum ++;
        } else {
            memset(future,'\0',31);
            sprintf(future,"%s%d%02d",it->first.c_str(),y2,m1-12);
            memcpy(CffeList[FuNum],future,strlen(future));
            FuNum ++;
        }

        if(m2<=12) {
            memset(future,'\0',31);
            sprintf(future,"%s%d%02d",it->first.c_str(),y1,m2);
            memcpy(CffeList[FuNum],future,strlen(future));
            FuNum ++;
        } else {
            memset(future,'\0',31);
            sprintf(future,"%s%d%02d",it->first.c_str(),y2,m2-12);
            memcpy(CffeList[FuNum],future,strlen(future));
            FuNum ++;
        }

        for(int i = 0; i<2; i++) {
          sprintf(future,"%s%d%02d",it->first.c_str(),y2,(3+i*3));
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
        }

      } else if(m2 < 18) {
        //18 21
      }
    }
    
    if("TF" == it->first || "T" == it->first) {
      if(m1 <= 3) {
        for(int i = 0; i<3; i++) {
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,(3+i*3));
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
        }
        //3 6 9
      } else if(m1 <= 6) {
        for(int i = 0; i<3; i++) {
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,(6+i*3));
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
        }
        //6 9 12
      } else if(m1 <= 9) {
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,9);
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,12);
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
          sprintf(future,"%s%d%02d",it->first.c_str(),y2,3);
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
        //9 12 3
      } else if(m1 <= 12) {
          sprintf(future,"%s%d%02d",it->first.c_str(),y1,12);
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
          sprintf(future,"%s%d%02d",it->first.c_str(),y2,3);
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
          sprintf(future,"%s%d%02d",it->first.c_str(),y2,6);
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
        //12 3 6
      } else if(m1 <= 15) {
          sprintf(future,"%s%d%02d",it->first.c_str(),y2,3);
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
          sprintf(future,"%s%d%02d",it->first.c_str(),y2,6);
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
          sprintf(future,"%s%d%02d",it->first.c_str(),y2,9);
          memcpy(CffeList[FuNum],future,strlen(future));
          memset(future,'\0',31);
          FuNum ++;
        //15 18 21
      }
    }
    

  } //for
}

void FuList::ListInit(int type)
{
  int DifYear=2000;
  const std::map<std::string,std::string> *MP ;

  char (*pFL)[FUTRUE_ID_LEN];

  if(TYPE_CFFE == type) {
    pFL = CffeList ;
    MP = &M_CFFE;
  } else if(TYPE_SHFE == type) {
    pFL = ShfeList;
    MP = &M_SHFE;
  } else if(TYPE_CZCE == type) {
    DifYear = 2010;
    pFL = CzceList;
    MP = &M_CZCE;
  } else if(TYPE_DCE  == type) {
    pFL = DceList;
    MP = &M_DCE;
  } else {
    return;
  }

  int i;
  char future[31];
  int curYear;
  int MM[60] ;

  memset(future,'\0',31);

  int FuNum = 0;
  for(auto it = (*MP).begin(); it != (*MP).end(); ++it) {
    // -------------begin---------------  各种异常处理 ---------------------
    if("AP" == it->first) {
      if(memcmp(Date,"20171222",8)<0) {
        continue;
      }
    }
    if("au" == it->first) {
      std::cout << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh au !!!\n" ;
      continue;
    }
    if("bu" == it->first) {
      std::cout << "hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh bu !!!\n" ;
      continue;
    }
    // -------------endi ---------------  各种异常处理 ---------------------
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
    for(i=0; i<60; i++) {
      std::cout << MM[i] << " " ;
    }
    std::cout << std::endl;

    k=0;
    i=0;
    /*
    for(i=0; i<Nn; i++) {
      std::cout << i << " " << Month << " " << MM[i] << std::endl ;
      if(Month <= MM[i]) {
        k=i;
        std::cout <<  "::::" << k << std::endl;
        break;
      }
    }
    */
    while(Month > MM[i]) {
      i++;
    }
    k=i;
    std::cout <<  "::::" << k << std::endl;
    std::cout <<  "oooooooooo:::::::" << k << std::endl;
    if(Month == MM[k]) {
      if(1 == isFirstDay(type,Year,Month,Day)) {
        k++;
      }
    }
    std::cout <<  "oooooooooo:::::::" << k << std::endl;
    for(i=0; i<Nn; i++) {
      tms = (MM[k]-1)/12;
      curYear = Year + tms - DifYear;
      sprintf(future,"%s%d%02d",it->first.c_str(),curYear,MM[k]-12*tms);
      k++;
      if(memcmp(future,"AP801",5)==0)  continue;
      if(memcmp(future,"AP803",5)==0)  continue;
      memcpy(pFL[FuNum],future,strlen(future));
      FuNum ++;
      std::cout << future << " ";
    }
    std::cout << future << "\n";

    cJSON_Delete(root);
  } // for 1

}

} // namespace
