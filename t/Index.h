#ifndef UBEE_INDEX_H
#define UBEE_INDEX_H

#include "see_talib.h"
#include <vector>

namespace uBEE
{
struct MY_KDJ {
  std::vector<double>    R;
  std::vector<double>    K;
  std::vector<double>    D;
  std::vector<double>    J;
  std::vector<double>    E;
  double                 preH;
  double                 preL;
  int                    preF;
public:
  MY_KDJ();
};

struct MY_OHLC {
  std::vector<double> O;
  std::vector<double> H;
  std::vector<double> L;
  std::vector<double> C;
  std::vector<int> V;
public:
  MY_OHLC();
};

} //namespace

#endif // UBEE_INDEX_H
