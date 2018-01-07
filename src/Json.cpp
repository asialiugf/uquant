#include "uBEE.h"
#include <iostream>
#include <unistd.h>
#include <cjson/cJSON.h>
#include <string>
namespace uBEE
{

int Quotes(cJSON *quotes);
int Klines(cJSON *quotes);
int Ticks(cJSON *ticks);
int SaveError(cJSON *json, const char *msg);
std::string m_replace(std::string , const std::string &, const std::string &,int);
std::string QuotesReplace(std::string strSrc);
std::string KlinesReplace(std::string strSrc);
std::string TicksReplace(std::string strSrc);

int Tqjson(const char*message)
{
  cJSON   *root ;
  cJSON   *json ;
  cJSON   *temp ;
  cJSON   *item ;
  cJSON   *data ;
  cJSON   *futu ;
  cJSON   *quotes ;
  cJSON   *klines ;
  cJSON   *ticks ;
  int   num=0;
  int   j=0;
  char *buf = nullptr;

  root = cJSON_Parse(message);
  if(!root) {
    uBEE::ErrLog(1000,"message to json error!",1,0,0);
    return -1;
  }

  buf = cJSON_Print(root);
  if(!buf) {
    uBEE::ErrLog(1000,"---- buf = cJSON_Print(root) ---- error!",1,0,0);
    return -1;
  }

  SaveBin("newtick.json", buf, strlen(buf));
  free(buf);

  temp = cJSON_GetObjectItem(root, "aid");
  if(!temp) {
    uBEE::ErrLog(1000,"no aid error!",1,0,0);
    return -1;
  }
  if(memcmp(temp->valuestring,"rtn_data",8)!=0) {
    uBEE::ErrLog(1000,"aid is not <rtn_data>!",1,0,0);
    return -1;
  }

  data = cJSON_GetObjectItem(root, "data");
  if(!data) {
    uBEE::ErrLog(1000,"data error!",1,0,0);
  }

  num = cJSON_GetArraySize(data);
  if(num <=0) {
    return 0;
  }
  for(int i=0; i<num; i++) {
    temp = cJSON_GetArrayItem(data,i);
    if(!temp) {
      continue;
    }
    quotes = cJSON_GetObjectItem(temp, "quotes");
    if(quotes) {
      std::cout << "befor Quotes() \n";
      Quotes(quotes);
      std::cout << "after Quotes() \n";
    }
    klines = cJSON_GetObjectItem(temp, "klines");
    if(klines) {
      std::cout << "enter into Klines() \n";
      Klines(klines);
      std::cout << "after Klines() \n";
    }
    ticks = cJSON_GetObjectItem(temp, "ticks");
    if(ticks) {
      Ticks(ticks);
    }
  }
  cJSON_Delete(root);
  //uBEE::ErrLog(1000,"cJSON_Delete(root) !!!",1,0,0);
  return 0;
}


int Quotes(cJSON *quotes)
{
  char    ca_filename[512];
  int i=0;
  int num=0;
  cJSON *temp;
  cJSON *instrument_id;
  cJSON *futu;
  char * buf=NULL;
  num = cJSON_GetArraySize(quotes);
  if(num <=0) {
    uBEE::ErrLog(1000,"---- cJSON_GetArraySize(quotes); ----  error!",1,0,0);
    return -1;
  };
  for(i=0; i<num; i++) {
    temp = cJSON_GetArrayItem(quotes,i);
    if(!temp) {
      uBEE::ErrLog(1000,"---- cJSON_GetArrayItem(quotes,i) ---- error!",1,0,0);
      continue;
    }
    futu = cJSON_GetObjectItem(temp, "instrument_id");
    if(!futu) {
      uBEE::ErrLog(1000,"---- no instrument_id ---- error!",1,0,0);
      continue;
    }
    buf = cJSON_Print(temp);
    if(!buf) {
      uBEE::ErrLog(1000,"---- buf = cJSON_Print(temp) ---- error!",1,0,0);
      continue;
    }
    memset(ca_filename,'\0',512);
    sprintf(ca_filename,"../dat/%s",futu->valuestring);
    std::string mm = buf;
    std::string kk = QuotesReplace(mm);
    SaveBin(ca_filename, kk.c_str(), kk.length());
    //std::cout << "loop quotes:" << futu->valuestring << std::endl;

    free(buf);
  }
  return 0;
}

int Klines(cJSON *klines)
{
  char    ca_filename[512];
  int i,j,k,l,ii,jj,kk,ll;

  cJSON *futu;
  cJSON *period;
  cJSON *data;
  cJSON *item;
  cJSON *datetime;

  char * buf=NULL;
  char * pd=NULL;
  char * js=NULL;

  //uBEE::ErrLog(1000," enter into Klines()!",1,0,0);
  std::cout << " in Klines !!\n" ;
  memset(ca_filename,'\0',512);
  ii = cJSON_GetArraySize(klines);
  if(ii<=0) {
    SaveError(klines,"-K ----  ii = cJSON_GetArraySize(klines)  ---- error!\n");
    return -1;
  };

  for(i=0; i<ii; i++) {
    futu = cJSON_GetArrayItem(klines,i);  // get future 1,2,3...
    if(!futu) {
      SaveError(klines,"-K ----  cJSON_GetArrayItem(klines,i) ---- error! ");
      continue;
    }

    jj = cJSON_GetArraySize(futu);
    if(jj <=0) {
      SaveError(klines,"-K ---- jj = cJSON_GetArraySize(futu) ---- error!\n");
      continue;
    };
    for(j=0; j<jj; j++) {
      period = cJSON_GetArrayItem(futu,j);   // get period 3s 1m 5m ...
      if(!period) {
        SaveError(klines,"-K ---- period = cJSON_GetArrayItem(futu,j) ---- error!\n");
        continue;
      }

      size_t len = strlen(period->string);
      if(len<6) {
        SaveError(klines,"-K ---- period error  len<6---- error!\n");
        continue;
      }

      pd = period->string ;

      if(memcmp((char *)(pd+(len-6)),"000000",6)!=0) {
        uBEE::ErrLog(1000,pd,1,0,0);
        uBEE::ErrLog(1000,(char *)(pd+(len-6)),1,0,0);
        SaveError(klines,"-K ---- period error ---- error!\n");
        continue;
      }

      kk = cJSON_GetArraySize(period);
      if(kk <=0) {
        SaveError(klines,"-K ---- kk = cJSON_GetArraySize(period) ---- error!\n");
        continue;
      };
      for(k=0; k<kk; k++) {
        data = cJSON_GetArrayItem(period,k);  // get data from period ...
        if(!data) {
          SaveError(klines,"-K ---- data ---- error!\n");
          continue;
        }

        ll = cJSON_GetArraySize(data);
        if(ll <=0) {
          SaveError(klines,"-K---- ll = cJSON_GetArraySize(data) ----  error!\n");
          continue;
        };
        for(l=0; l<ll; l++) {
          item = cJSON_GetArrayItem(data,l);  // get item from data ...
          if(!item) {
            SaveError(klines,"-K---- item error ---- error!\n");
            continue;
          }
          datetime = cJSON_GetObjectItem(item, "datetime");
          if(!datetime) {
            SaveError(klines,"-K---- datetime ---- error!\n");
            continue;
          }

          buf = cJSON_Print(item);
          if(!buf) {
            SaveError(klines,"-K---- buf = cJSON_Print(item) ---- error!\n");
            continue;
          }

          uBEE::ErrLog(1000,"-K---- befor SaveBin ---!",1,0,0);


          memset(ca_filename,'\0',512);
          sprintf(ca_filename,"../dat/%s.",futu->string);
          strcat(ca_filename,period->string);

          std::string mm = buf;
          std::string kk = KlinesReplace(mm);
          //SaveBin(ca_filename, kk.c_str(), kk.length());
	      char * bar = (char *)malloc(kk.length() + 50);
		  memset(ca_filename,'\0',kk.length() + 50);
          sprintf(bar,"%s:%s\n",item->string,kk.c_str());
          SaveLine(ca_filename,bar);
          free(buf);
          free(bar);

        } // l
      } // k
    } // j
  } // i
  return 0;
}

//------------------------------------------------------------------------------------------------
int Ticks(cJSON *ticks)
{



}

//------------------------------------------------------------------------------------------------

int MkRequest(const char *filename, char *cmd, size_t cmd_len)
{
  FILE    *f = NULL;
  //char    *buf ;
  size_t   len = 0;
  size_t   iRc = 0;

  f = fopen(filename,"rb");
  if(f == NULL) {
    uBEE::ErrLog(1000,"cmd open error!",1,0,0);
    return errno ;
  }

  fseek(f, 0, SEEK_END);
  len = ftell(f);
  fseek(f, 0, SEEK_SET);
  if(len==0) {
    uBEE::ErrLog(1000,"cmd len  = 0  error!",1,0,0);
    return -2 ;
  }

  if(len > cmd_len) {
    uBEE::ErrLog(1000,"cmd buff is not enough!",1,0,0);
    return -1;
  }
  /*
  buf = (char*)malloc(len + 1);
  if(buf == NULL) {
    see_errlog(1000,"see_file_to_json(): Failed to allocate memory !!",RPT_TO_LOG,0,0) ;
    return errno ;
  }
  */
  iRc = fread(cmd, 1, len, f);
  cmd[len] = '\0';
  fclose(f);
  return 0;
}

std::string m_replace(std::string strSrc, const std::string &oldStr, const std::string &newStr,int count=-1)
{
  std::string strRet=strSrc;
  size_t pos = 0;
  int l_count=0;
  if(-1 == count) // replace all
    count = strRet.size();
  while((pos = strRet.find(oldStr, pos)) != std::string::npos) {
    strRet.replace(pos, oldStr.size(), newStr);
    if(++l_count >= count) break;
    pos += newStr.size();
  }
  return strRet;
}

std::string QuotesReplace(std::string strSrc)
{
  std::string mm=strSrc;
  std::string kk;
  kk = m_replace(mm,"\"amount\"","\"a\"",-1);
  mm = m_replace(kk,"\"average\"","\"b\"",-1);
  kk = m_replace(mm,"\"close\"","\"c\"",-1);
  mm = m_replace(kk,"\"datetime\"","\"d\"",-1);
  kk = m_replace(mm,"\"last_price\"","\"e\"",-1);
  mm = m_replace(kk,"\"instrument_id\"","\"f\"",-1);
  kk = m_replace(mm,"\"open_interest\"","\"g\"",-1);
  mm = m_replace(kk,"\"highest\"","\"h\"",-1);
  kk = m_replace(mm,"\"pre_close\"","\"i\"",-1);
  mm = m_replace(kk,"\"pre_open_interest\"","\"j\"",-1);
  kk = m_replace(mm,"\"pre_settlement\"","\"k\"",-1);
  mm = m_replace(kk,"\"lowest\"","\"l\"",-1);
  kk = m_replace(mm,"\"ask_price1\"","\"m\"",-1);
  mm = m_replace(kk,"\"ask_volume1\"","\"n\"",-1);
  kk = m_replace(mm,"\"open\"","\"o\"",-1);
  mm = m_replace(kk,"\"bid_price1\"","\"p\"",-1);
  kk = m_replace(mm,"\"bid_volume1\"","\"q\"",-1);
  mm = m_replace(kk,"\"settlement\"","\"s\"",-1);
  kk = m_replace(mm,"\"lower_limit\"","\"t\"",-1);
  mm = m_replace(kk,"\"upper_limit\"","\"u\"",-1);
  kk = m_replace(mm,"\"volume\"","\"v\"",-1);
  mm = m_replace(kk,"\"status\"","\"z\"",-1);
  kk = m_replace(mm,"\t","",-1);
  mm = m_replace(kk,"\n","",-1);
  //std::cout<< mm;
  return mm;
}
std::string KlinesReplace(std::string strSrc)
{
  std::string mm=strSrc;
  std::string kk;
  kk = m_replace(mm,"\"open_oi\"","\"g\"",-1);
  mm = m_replace(kk,"\"datetime\"","\"d\"",-1);
  kk = m_replace(mm,"\"open\"","\"o\"",-1);
  mm = m_replace(kk,"\"close_oi\"","\"j\"",-1);
  kk = m_replace(mm,"\"volume\"","\"v\"",-1);
  mm = m_replace(kk,"\"highest\"","\"h\"",-1);
  kk = m_replace(mm,"\"close\"","\"c\"",-1);
  mm = m_replace(kk,"\"lowest\"","\"l\"",-1);
  kk = m_replace(mm,"\t","",-1);
  mm = m_replace(kk,"\n","",-1);
  return mm;
}
std::string TicksReplace(std::string strSrc)
{
  std::string mm=strSrc;
  std::string kk;
  kk = m_replace(mm,"\"ask_price1\"","\"m\"",-1);
  mm = m_replace(kk,"\"ask_volume1\"","\"n\"",-1);
  kk = m_replace(mm,"\"bid_volume1\"","\"q\"",-1);
  mm = m_replace(kk,"\"bid_price1\"","\"p\"",-1);
  kk = m_replace(mm,"\"last_price\"","\"e\"",-1);
  mm = m_replace(kk,"\"open_interest\"","\"g\"",-1);
  kk = m_replace(mm,"\"close\"","\"c\"",-1);
  mm = m_replace(kk,"\"datetime\"","\"d\"",-1);
  kk = m_replace(mm,"\"open\"","\"o\"",-1);
  mm = m_replace(kk,"\"highest\"","\"h\"",-1);
  kk = m_replace(mm,"\"lowest\"","\"l\"",-1);
  mm = m_replace(kk,"\"volume\"","\"v\"",-1);
  kk = m_replace(mm,"\t","",-1);
  mm = m_replace(kk,"\n","",-1);
  return mm;
}

int SaveError(cJSON *json, const char *msg)
{
  std::cout << msg << std::endl;
  char ca_filename[512];
  char * js= cJSON_Print(json);
  memset(ca_filename,'\0',512);
  sprintf(ca_filename,"../dat/%s",json->string);
  uBEE::ErrLog(1000,msg,1,0,0);
  SaveLine(ca_filename, msg);
  std::cout << ca_filename << std::endl;
  SaveBin(ca_filename, js, strlen(js));
  free(js);
  return 0;
}

} // namespace uBEE
