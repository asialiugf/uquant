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
  cPL = 0;
  NL = 0;
  NS = 0;
} // ---------

double  LP ;     // long position 多头头寸
double  SP ;     // short position 空头头寸
double  BL ;
double  BS ;
double  SL ;
double  SS ;
int     NL ;       // number of long
int     NS ;       // number of short
double  mPL ;      // 盈亏 profit and loss
// n 下单手数 c:信号产生时的收盘价
int Future::BuyShort(int n, double c)
{
  NS = n;
  SP = c - mMPF ;
  std::cout << "TdRate:BuyShort:SP:"<<SP<< std::endl;
  return 0;
}
int Future::BuyLong(int n, double c)
{
  NL = n;
  LP = c + mMPF ;
  std::cout << "TdRate:BuyLong:LP:"<<LP<< std::endl;
  return 0;
}
int Future::SellShort(int n, double c)
{
  if(NS < n) {
    return -1;
  }
  NS = 0;
  mPL += (SP-c-mMPF)/mMPF*mLot*n ;
  std::cout << "TdRate:SellShort:mPL:"<<mPL<< std::endl;
  return 0;
}
int Future::SellLong(int n, double c)
{
  if(NL < n) {
    return -1;
  }
  NL = 0;
  mPL += (c-mMPF-LP)/mMPF*mLot*n ;
  std::cout << "TdRate:SellLong:mPL:"<<mPL<< std::endl;
  return 0;
}
// ------- 动态止损 ----------------------------
int Future::DStopLost(int n, double c)
{
  if(NS >= n) {
    if((SP-c-mMPF)/mMPF <= -15) {
      NS = 0;
      mPL += (SP-c-mMPF)/mMPF*mLot*n ;
      std::cout << "TdRate:DStopLost:SP:"<<SP<<" c:"<<c<<" "<< (SP-c-mMPF)/mMPF << std::endl;
      return 0;
    }
    if(SP>c) {
      mPL += (SP-c-mMPF)/mMPF*mLot*n ;
      SP = c;
    } else if(SP<c) {
      //mPL += (SP-c-mMPF)/mMPF*mLot*n ;
    }
  }

  if(NL >= n) {
    if((c-mMPF-LP)/mMPF <= -15) {
      NL = 0;
      mPL += (c-mMPF-LP)/mMPF*mLot*n ;
      std::cout << "TdRate:DStopLost:LP:"<<LP<<" c:"<<c<<" "<< (c-mMPF-LP)/mMPF << std::endl;
      return 0;
    }
    if(LP<c) {
      mPL += (c-mMPF-LP)/mMPF*mLot*n ;
      LP = c;
    } else if(LP>c) {
      //todo
    }
  }
}

// ------- 止损 ----------------------------
int Future::StopLost(int n, double c)
{
  if(NS >= n) {
    if((SP-c-mMPF)/mMPF <= -8) {
      NS = 0;
      mPL += (SP-c-mMPF)/mMPF*mLot*n ;
      std::cout << "stoplost:SP:"<<SP<<" c:"<<c<<" "<< (SP-c-mMPF)/mMPF << std::endl;
      return 0;
    }
  }

  if(NL >= n) {
    if((c-mMPF-LP)/mMPF <= -8) {
      NL = 0;
      mPL += (c-mMPF-LP)/mMPF*mLot*n ;
      std::cout << "stoplost:LP:"<<LP<<" c:"<<c<<" "<< (c-mMPF-LP)/mMPF << std::endl;
      return 0;
    }
  }
}

//--------- 止赢 ----------------------------
int Future::StopProfit(int n, double c)
{
  if(NS >= n) {
    if((SP-c-mMPF)/mMPF >= 4) {
      NS = 0;
      mPL += (SP-c-mMPF)/mMPF*mLot*n ;
      std::cout << "TdRate:stopprofit:SP:"<<SP<<" c:"<<c<<" "<< (SP-c-mMPF)/mMPF << std::endl;
      return 0;
    }
  }

  if(NL >= n) {
    if((c-mMPF-LP)/mMPF >= 4) {
      NL = 0;
      mPL += (c-mMPF-LP)/mMPF*mLot*n ;
      std::cout << "TdRate:stopprofit:LP:"<<LP<<" c:"<<c<<" "<< (c-mMPF-LP)/mMPF << std::endl;
      return 0;
    }
  }
  return 0;
}

// ----------动态计算显示当前收益 -----------------
int Future::CurrPL(double c)
{
  if(NS > 0) {
    cPL = mPL + (SP-c-mMPF)/mMPF*mLot*NS ;
    return 0;
  }
  if(NL >0) {
    cPL = mPL + (c-mMPF-LP)/mMPF*mLot*NL ;
    return 0;
  }
} // --------

} //end namespace
