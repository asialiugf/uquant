#ifndef UBEE_INDEX_H
#define UBEE_INDEX_H

#include "see_talib.h"
#include "uBEE.h"
#include <stdlib.h>
#include <string.h>
#include <vector>

namespace uBEE
{
struct D_OHLC {
  std::vector<double> O;
  std::vector<double> H;
  std::vector<double> L;
  std::vector<double> C;
  std::vector<int> V;
  char cB[9];
  char cE[9];
  int  x;    // index !! O[0]... O[1]... O[x] ...
public:
  D_OHLC();
  int Insert(sKbar * bar);
};

struct D_KDJ {
  std::vector<double>    R;
  std::vector<double>    K;
  std::vector<double>    D;
  std::vector<double>    J;
  std::vector<double>    E;
  double                 preH;
  double                 preL;
  int                    preF;
  D_OHLC               * ohlc ;
  int                    x ;
  // ---- 上涨下跌
  double                 Kx ;  // = K[x] - K[x-1]
  double                 Dx ;
  double                 Jx ;
  double                 Ex ;
  int  Kc ;
  int  Dc ;
  int  Jc ;
  int  Ec ;            // --- E cross up Ec=1, Ec=2 -------------- Ec = -1, Ec=-2 -----------
  // ---- 在哪个区间
  int                    Kp ; // <20 |  20< <50 |  50< <80  | 80<
  int                    Dp ;
  int                    Jp ;
  int                    Ep ;
  // ---- 大级别内 紧临 小级别 的第几次拐头
  //int



public:
  D_KDJ(D_OHLC *o);
  int Update(int N, int M1, int M2, int N2);
};


struct G_KDJ {
  D_OHLC      * ohlc ;
  D_KDJ       * G1 ;
  D_KDJ       * G2 ;
  D_KDJ       * G3 ;
  D_KDJ       * G4 ;

  int  cu1 ;   // 当第二级别处于金叉状态时，第一个级别的金叉次数
  int  cu2 ;
  int  cu3 ;
  int  cu4 ;

  int  cd1 ;  // 当第二级别处于金叉状态时，第一个级别的死叉次数
  int  cd2 ;
  int  cd3 ;
  int  cd4 ;

  G_KDJ(D_KDJ *g1, D_KDJ *g2, D_KDJ *g3, D_KDJ *g4);
  int Update() ;

}; //-----------


} //namespace

#endif // UBEE_INDEX_H
