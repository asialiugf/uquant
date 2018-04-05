#include <vector>

namespace uBEE
{
using namespace std;

MY_OHLC::MY_OHLC():
  O(100000,SEE_NULL),
  H(100000,SEE_NULL),
  L(100000,SEE_NULL),
  C(100000,SEE_NULL),
  V(100000,SEE_NULL)
{
}

MY_KDJ::MY_KDJ():
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

} // namespace
