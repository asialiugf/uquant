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
public:
  D_OHLC();
  int Insert(int x, sKbar * bar);
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
public:
  D_KDJ();
  int Update(int x, D_OHLC *bar, int N, int M1, int M2, int N2);
};

} //namespace

#endif // UBEE_INDEX_H
