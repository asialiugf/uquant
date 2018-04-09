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
  x = -1;
}
/*
 x: index !
*/
int D_OHLC::Insert(sKbar *bar)
{
  x++;
  O[x] = bar->o ;
  H[x] = bar->h ;
  L[x] = bar->l ;
  C[x] = bar->c ;
  V[x] = bar->v ;
  memcpy(cB,bar->cB,9);
  memcpy(cE,bar->cE,9);
  return 0;
}


D_KDJ::D_KDJ(D_OHLC * o):
  R(100000,SEE_NULL),
  K(100000,SEE_NULL),
  D(100000,SEE_NULL),
  J(100000,SEE_NULL),
  E(100000,SEE_NULL)
{
  preH = SEE_NULL;
  preL = SEE_NULL;
  preF = SEE_NULL;
  x = -1;
  ohlc = o ;
}
/*
  x: index;
*/
int D_KDJ::Update(int N, int M1, int M2, int N2)
{
  SEE_KDJ(ohlc->x, ohlc->x,
          &ohlc->H[0], &ohlc->L[0], &ohlc->C[0],
          &preH, &preL, &preF,
          N, M1, M2,
          &R[0], &K[0], &D[0], &J[0]) ;
  SEE_EMA(ohlc->x, ohlc->x, &K[0], N2, &E[0]) ;


  if(ohlc->x>1) {
    Kx = K[ohlc->x] - K[ohlc->x-1] ;
    Dx = D[ohlc->x] - D[ohlc->x-1] ;
    Jx = J[ohlc->x] - J[ohlc->x-1] ;
    Ex = E[ohlc->x] - E[ohlc->x-1] ;
  }

  if(K[ohlc->x]<20) {
    Kp = 0 ;
  } else if(K[ohlc->x]>=20 && K[ohlc->x]<=50) {
    Kp = 1 ;
  } else if(K[ohlc->x]>50 && K[ohlc->x]<=80) {
    Kp = 2 ;
  } else {
    Kp = 3 ;
  }

  if(D[ohlc->x]<20) {
    Dp = 0 ;
  } else if(D[ohlc->x]>=20 && D[ohlc->x]<=50) {
    Dp = 1 ;
  } else if(D[ohlc->x]>50 && D[ohlc->x]<=80) {
    Dp = 2 ;
  } else {
    Dp = 3 ;
  }

  if(J[ohlc->x]<20) {
    Jp = 0 ;
  } else if(J[ohlc->x]>=20 && J[ohlc->x]<=50) {
    Jp = 1 ;
  } else if(J[ohlc->x]>50 && J[ohlc->x]<=80) {
    Jp = 2 ;
  } else {
    Jp = 3 ;
  }

  if(E[ohlc->x]<20) {
    Ep = 0 ;
  } else if(E[ohlc->x]>=20 && E[ohlc->x]<=50) {
    Ep = 1 ;
  } else if(E[ohlc->x]>50 && E[ohlc->x]<=80) {
    Ep = 2 ;
  } else {
    Ep = 3 ;
  }

  return 0;
}

} // namespace
