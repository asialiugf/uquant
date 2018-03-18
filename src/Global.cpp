#include "Global.h"
#include "Bars.h"

namespace uBEE
{
//char ca_errmsg[2048];
uBEE::TimeBlock               *tb;
int InitAll()
{
  std::cout << "uuuuuuuuuuuuuuuuuuuuu\n";
  tb = new uBEE::TimeBlock();
  std::cout << "uuuuuuuuuuuuuuuuuuuuu\n";
}
} //end namespace
