#include "uBEE.h"
#include <iostream>
#include <unistd.h>
#include <cjson/cJSON.h>
namespace uBEE
{
int Quotes(cJSON *quotes);
int Klines(cJSON *quotes);
int Tqjson(const char*message)
{
  cJSON   *root ;
  cJSON   *json ;
  cJSON   *temp ;
  cJSON   *temp1 ;
  cJSON   *item ;
  cJSON   *data ;
  cJSON   *futu ;
  cJSON   *quotes ;
  cJSON   *klines ;
  int   num=0;
  int   j=0;
  char *buf;
  root = cJSON_Parse(message);
  if(!root) {
    uBEE::ErrLog(1000,"message to json error!",1,0,0);
    return -1;
  }
  temp = cJSON_GetObjectItem(root, "aid");
  if(!temp) {
    uBEE::ErrLog(1000,"no aid error!",1,0,0);
    return -1;
  }
  if(memcmp(temp->valuestring,"rtn_data",8)!=0) {
    uBEE::ErrLog(1000,"aid is not <rtn_data>!",1,0,0);
    return 0;
  }

  data = cJSON_GetObjectItem(root, "data");
  if(!data) {
    uBEE::ErrLog(1000,"data error!",1,0,0);
  }

  num = cJSON_GetArraySize(data);
  if(num <=0) {
    uBEE::ErrLog(1000,"cJSON_GetArraySize(data) error! ",1,0,0);
  }
  for(int i=0; i<num; i++) {
    temp = cJSON_GetArrayItem(data,i);
    if(!temp) {
      uBEE::ErrLog(1000,"cJSON_GetArrayItem(data,i) error!",1,0,0);
      continue;
    }
    quotes = cJSON_GetObjectItem(temp, "quotes");
    if(quotes) {
      Quotes(quotes);
      continue;
    }
    klines = cJSON_GetObjectItem(temp, "klines");
    if(klines) {
      Klines(klines);
      continue;
    }
  }
  cJSON_Delete(root);
  uBEE::ErrLog(1000,"cJSON_Delete(root) !!!",1,0,0);
  return 0;
}


int Quotes(cJSON *quotes)
{
  int i=0;
  int num=0;
  cJSON *temp;
  cJSON *instrument_id;
  cJSON *futu;
  char * buf=NULL;
  //quotes = cJSON_GetObjectItem(temp, "quotes");
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
    SaveBin(futu->valuestring, buf, strlen(buf));
    free(buf);
  }
  return 0;
}

int Klines(cJSON *klines)
{
  int i=0;
  int ii=0;

  int j=0;
  int jj=0;

  int k=0;
  int kk=0;

  int l=0;
  int ll=0;

  cJSON *futu;
  cJSON *period;
  cJSON *data;
  cJSON *item;
  cJSON *datetime;

  char * buf=NULL;
  char * pd=NULL;

  uBEE::ErrLog(1000," enter into Klines()!",1,0,0);
  ii = cJSON_GetArraySize(klines);
  if(ii<=0) {
    uBEE::ErrLog(1000,"-K---- num = cJSON_GetArraySize(klines); ----  error!",1,0,0);
    return -1;
  };
  for(i=0; i<ii; i++) {
    futu = cJSON_GetArrayItem(klines,i);  // get future 1,2,3...
    if(!futu) {
      uBEE::ErrLog(1000,"int Klines 1111111",1,0,0);
      continue;
    }

    jj = cJSON_GetArraySize(futu);
    if(jj <=0) {
      uBEE::ErrLog(1000,"-K---- num = cJSON_GetArraySize(klines); ----  error!",1,0,0);
      continue;
    };
    for(j=0; j<jj; j++) {
      period = cJSON_GetArrayItem(futu,j);   // get period 3s 1m 5m ...
      if(!period) {
        uBEE::ErrLog(1000,"int Klines 3333333333",1,0,0);
        continue;
      }

      size_t len = strlen(period->string);
      if(len<6) {
        uBEE::ErrLog(1000,"len < 6 ",1,0,0);
        continue;
      }

      pd = period->string ;

      if(memcmp((char *)(pd+(len-6)),"000000",6)!=0) {
        uBEE::ErrLog(1000,pd,1,0,0);
        uBEE::ErrLog(1000,(char *)(pd+(len-6)),1,0,0);
        continue;
      }

      kk = cJSON_GetArraySize(period);
      if(kk <=0) {
        uBEE::ErrLog(1000,"-K---- num = cJSON_GetArraySize(klines); ----  error!",1,0,0);
        continue;
      };
      for(k=0; k<kk; k++) {
        data = cJSON_GetArrayItem(period,k);  // get data from period ...
        if(!data) {
          uBEE::ErrLog(1000,"int Klines 3333333333",1,0,0);
          continue;
        }

        ll = cJSON_GetArraySize(data);
        if(ll <=0) {
          uBEE::ErrLog(1000,"-K---- num = cJSON_GetArraySize(klines); ----  error!",1,0,0);
          continue;
        };
        for(l=0; l<ll; l++) {
          item = cJSON_GetArrayItem(data,l);  // get item from data ...
          if(!item) {
            uBEE::ErrLog(1000,"int Klines 3333333333",1,0,0);
            continue;
          }
          datetime = cJSON_GetObjectItem(item, "datetime");
          if(!datetime) {
            continue;
          }

          buf = cJSON_Print(item);
          if(!buf) {
            uBEE::ErrLog(1000,"-K---- buf = cJSON_Print(futu) ---- error!",1,0,0);
            continue;
          }
          uBEE::ErrLog(1000,"-K---- befor SaveBin ---!",1,0,0);
          SaveBin(period->string, buf, strlen(buf));
          free(buf);
        } // l
      } // k
    } // j
  } // i
  return 0;
}
} // namespace uBEE
