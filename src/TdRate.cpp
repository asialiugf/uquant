#include "TdRate.h"
#include "ErrLog.h"

namespace uBEE
{

Future::Future(std::string f)
{
  const char *id = f.c_str() ;

  see_memzero(InstrumentID,31);
  see_memzero(ID2,3);

  char fn[3] ;
  see_memzero(fn,3);
  memcpy(fn,id,2) ;
  if(fn[1] <= '9' && fn[1] >= '0') {
    fn[1] = '\0';
  }
  memcpy(ID2,fn,strlen(fn));
  memcpy(InstrumentID,id,strlen(id));

  std::map<std::string,std::string>::const_iterator it;
  it = M_FuRate.find(ID2);
  if(it==M_FuRate.end()) {
    sprintf(ca_errmsg,"M_FuRate in TdRate.h : %s %s not found!",InstrumentID,ID2) ;
    uBEE::ErrLog(1000,ca_errmsg,1,0,0) ;
  } else {
    sscanf(it->second.c_str(), "mMPF:%lf mLot:%lf mOP:%lf mCP:%lf",
           &mMPF,   &mLot,   &mOP,   &mCP);
  }

  for(int i=0; i<50; i++) {
    iP[i] = -1;
  }
  mPL = 0;
  NL = 0;
  NS = 0;
} // ---------

double  LP ;     // long position 多头头寸
double  SP ;     // short position 空头头寸
double  BL ;
double  BS ;
double  SL ;
double  SS ;
int     NL ;
int     NS ;
double  mPL ;      // 盈亏 profit and loss
// n 下单手数 c:信号产生时的收盘价
int Future::BuyShort(int n, double c)
{
  NS = n;
  SP = c - mMPF ;
  return 0;
}
int Future::BuyLong(int n, double c)
{
  NL = n;
  LP = c + mMPF ;
  return 0;
}
int Future::SellShort(int n, double c)
{
  if(NS < n) {
    return -1;
  }
  NS = 0;
  mPL += (SP-c-mMPF)/mMPF*mLot*n ;
  return 0;
}
int Future::SellLong(int n, double c)
{
  if(NL < n) {
    return -1;
  }
  NL = 0;
  mPL += (c-mMPF-LP)/mMPF*mLot*n ;
  return 0;
}

} //end namespace
