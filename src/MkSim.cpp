#include "../ctp/ThostFtdcMdApi.h"
#include <uWS/uWS.h>
#include "MdSpi.h"
#include "Bars.h"
#include "FuList.h"
#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include <ctime>

namespace uBEE
{

//--- 
uWS::Group<uWS::SERVER> * sg;
//---

void MkSim(uWS::Group<uWS::SERVER> * new_sg)
{
  sg = new_sg;

}

} // end namespace uBEE
