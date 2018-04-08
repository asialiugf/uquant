#include "Index.h"
#include "uBEE.h"
#include <stdlib.h>
#include <vector>

namespace uBEE
{
using namespace std;

D_OHLC::D_OHLC():
  O(100000,SEE_NULL),
  H(100000,SEE_NULL),
  L(100000,SEE_NULL),
  C(100000,SEE_NULL),
  V(100000,SEE_NULL)
{
  memset(cB,'\0',9);
  memset(cE,'\0',9);
}
/*
 x: index !
*/
int D_OHLC::Insert(int x, sKbar *bar)
{
  O[x] = bar->o ;
  H[x] = bar->h ;
  L[x] = bar->l ;
  C[x] = bar->c ;
  V[x] = bar->v ;
  memcpy(cB,bar->cB,9);
  memcpy(cE,bar->cE,9);
  return 0;
}


D_KDJ::D_KDJ():
  R(100000,SEE_NULL),
  K(100000,SEE_NULL),
  D(100000,SEE_NULL),
  J(100000,SEE_NULL),
  E(100000,SEE_NULL)
{
  preH = SEE_NULL;
  preL = SEE_NULL;
  preF = SEE_NULL;
}
/*
  x: index;
*/
int D_KDJ::Update(int x, D_OHLC *bar, int N, int M1, int M2, int N2)
{
  SEE_KDJ(x, x,
          &bar->H[0], &bar->L[0], &bar->C[0],
          &preH, &preL, &preF,
          N, M1, M2,
          &R[0], &K[0], &D[0], &J[0]) ;
  SEE_EMA(x, x, &K[0], N2, &E[0]) ;
  return 0;
}

} // namespace
