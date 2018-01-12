#include <uWS/uWS.h>
#include "uBEE.h"
#include <iostream>
#include <sys/time.h>

#pragma comment(lib, "uWS.lib")

int main()
{
  uWS::Hub h;

  int tt = 0 ;
  int y,m,d;
  char filename[256];

  std::cout << std::endl;
  std::cout << "            Input type description: " << std::endl;
  std::cout << "            1: Quotes only" << std::endl;
  std::cout << "            2: Klines only" << std::endl;
  std::cout << "            3: Ticks  only" << std::endl;
  std::cout << "            4: Klines & Ticks  " << std::endl;
  std::cout << "            5: Quotes & Kicks  " << std::endl;
  std::cout << "            6: Quotes & Ticks  " << std::endl;
  std::cout << "            7: All  Q & K & T  " << std::endl;
  std::cout << "            Please Input type: ";
  std::cin >> tt ;
  std::cout << std::endl;
  std::cout << "            X: Pleae Input Year:  ";
  std::cin >> y;
  std::cout << std::endl;
  std::cout << "            X: Pleae Input Month:  ";
  std::cin >> m ;
  std::cout << std::endl;
  std::cout << "            X: Pleae Input Month:  ";
  std::cin >> d ;
  std::cout << std::endl;

  uBEE::FuList fl;
  int rtn = fl.Init(y,m,d);
  if(rtn < 0) {
    exit(-1);
  }

  memset(filename,'\0',256);
  sprintf(filename,"%s",fl.Date);

  std::cout << "week:"<< fl.Week << std::endl;
  std::cout << "date:"<< fl.Date << std::endl;
  std::cout << "date:"<< fl.Year << std::endl;
  std::cout << "date:"<< fl.Month << std::endl;
  std::cout << "date:"<< fl.Day << std::endl;
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< SHFE_NUMBER; i++) {
    std::cout << fl.ShfeList[i] << " " ;
    if(strlen(fl.ShfeList[i]) == 0) continue;
    uBEE::SaveLine(filename,fl.ShfeList[i]);
    if(memcmp(fl.ShfeList[i],fl.ShfeList[i+1],2)!=0) {
      std::cout << std::endl;
    }
  }
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< SHFE_NUMBER; i++) {
    std::cout << fl.CzceList[i] <<  " " ;
    if(strlen(fl.CzceList[i]) == 0) continue;
    uBEE::SaveLine(filename,fl.CzceList[i]);
    if(memcmp(fl.CzceList[i],fl.CzceList[i+1],2)!=0) {
      std::cout << std::endl;
    }
  }
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< SHFE_NUMBER; i++) {
    std::cout << fl.DceList[i] << " " ;
    if(strlen(fl.DceList[i]) == 0) continue;
    uBEE::SaveLine(filename,fl.DceList[i]);
    if(memcmp(fl.DceList[i],fl.DceList[i+1],2)!=0) {
      std::cout << std::endl;
    }
  }
  std::cout << " \n---------------------------------------------------------------------------\n";
  for(int i = 0; i< CFFE_NUMBER; i++) {
    std::cout << fl.CffeList[i] << " " ;
    if(strlen(fl.CffeList[i]) == 0) continue;
    uBEE::SaveLine(filename,fl.CffeList[i]);
    if(memcmp(fl.CffeList[i],fl.CffeList[i+1],2)!=0) {
      std::cout << std::endl;
    }
  }
  std::cout << " \n---------------------------------------------------------------------------\n";
  std::cout << fl.Date << "????" << std::endl;


  // --------------------------------------------------------------------------------------------
  // 服务端接收到包后原封不动返回
  /*
  h.onConnection([&tt](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
    if(tt != 1) {
      std::vector<std::string> cmds = uBEE::Command("./cmd");
      for_each(cmds.cbegin(), cmds.cend(), [&ws](const std::string &request)->void{
        ws->send(request.c_str());
        std::cout << request << std::endl;
      });
    }
    std::cout <<"Server onConnection send: --server--" << std::endl;
  });

  h.onMessage([&tt](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
    if(length>0) {
      std::cout << "message!" << std::endl;
      //usleep(5000000);
      //message[length] = 0;
      struct  timeval start;
      struct  timeval end1;
      unsigned  long diff;
      gettimeofday(&start,NULL);
      uBEE::Tqjson(message,tt);
      gettimeofday(&end1,NULL);
      diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
      printf("thedifference is %ld\n",diff);
    }
  });
  h.onPong([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length) {
    std::cout<< "ok ping\n";
  });
  h.getDefaultGroup<uWS::SERVER>().startAutoPing(2000);

  //bool k = h.listen(3000) ;
  //if(!k) {
  //  std::cout << " listen error !!" << std::endl;
  //}
  */
  // --------------------------------------------------------------------------------------------
  // 客户端

  h.onDisconnection([](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
    std::cout << "onDisconnection !!" << std::endl;
    std::cout << message << std::endl;
  });


  h.onConnection([&tt,&filename](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
    std::cout <<"Tqdata.x onConnection !!" << std::endl;
    if(tt != 1) {
      //char caCmd[4096];
      //std::vector<std::string> cmds = uBEE::Command("./cmd");
      std::vector<std::string> cmds = uBEE::Command(filename);

      int count = cmds.size();
      for(int i = 0; i <200; i++) {
      //for(int i = 0; i<count; i++) {
        std::cout << cmds[i] << std::endl;
        ws->send(cmds[i].c_str());
      }

      /*

      for_each(cmds.cbegin(), cmds.cend(), [&ws](const std::string &request)->void{
        ws->send(request.c_str());
        std::cout << request << std::endl;
      });

      memset(caCmd,'\0',4096) ;
      uBEE::MkRequest("./cmd", caCmd,4096);
      std::cout << caCmd << std::endl;
      //ws->send(caCmd);
      memset(caCmd,'\0',4096) ;
      */
      //sprintf(caCmd,"{\"aid\":\"set_chart\",\"chart_id\":\"abcd123\",\"ins_id\":\"cu1801,ru1801,ru1805\",\"duration\":0,\"view_width\": 500,}");
      //sprintf(caCmd,"{\"aid\":\"set_chart\",\"chart_id\":\"abcd123\",\"ins_id\":\"cu1801,ru1801,ru1805\",\"duration\":0,\"view_width\": 500,}");
      /*
      {"chart_id": "VN_ag1701,ru1701,al1607,TA609,FG609,MA609,SR609,T1606,c1701_0", "aid": "set_chart", "duration": 0, "view_width": 8000, "ins_list": "ag1701,ru1701,al1607,TA609,FG609,MA609,SR609,T1606,c1701"}
      //sprintf(caCmd,"{\"chart_id\":\"VN_ag1701,ru1701,al1607,TA609,FG609,MA609,SR609,T1606,c1701_0\",\"aid\":\"set_chart\",\"duration\":0,\"view_width\":8000,\"ins_list\":\"ag1701,ru1701,al1607,TA609,FG609,MA609,SR609,T1606,c1701\"}");
      sprintf(caCmd,"{\"chart_id\":\"VN_FG609_0\",\"aid\":\"set_chart\",\"duration\":0,\"view_width\":8000,\"ins_list\":\"FG609\"}");
      ws->send(caCmd);
      sprintf(caCmd,"{\"chart_id\":\"VN_T1606\",\"aid\":\"set_chart\",\"duration\":0,\"view_width\":8000,\"ins_list\":\"T1606\"}");
      ws->send(caCmd);
      sprintf(caCmd,"{\"chart_id\":\"VN_SR609\",\"aid\":\"set_chart\",\"duration\":0,\"view_width\":8000,\"ins_list\":\"SR609\"}");
      ws->send(caCmd);
      sprintf(caCmd,"{\"chart_id\":\"VN_MA609\",\"aid\":\"set_chart\",\"duration\":0,\"view_width\":8000,\"ins_list\":\"MA609\"}");
      ws->send(caCmd);
      sprintf(caCmd,"{\"chart_id\":\"VN_TA609\",\"aid\":\"set_chart\",\"duration\":0,\"view_width\":8000,\"ins_list\":\"TA609\"}");
      ws->send(caCmd);
      std::cout << caCmd << std::endl;
      */
    }
  });

  h.onError([](void *user) {
    switch((long) user) {
    case 1:
      std::cout << "login error!!" << std::endl;
      exit(-1);
    default:
      std::cout << "FAILURE: " << user << " should not emit error!" << std::endl;
      exit(-1);
    }
  });

  h.onMessage([&tt](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
    if(length>0) {
      std::cout << "message!" << std::endl;
      //usleep(5000000);
      //message[length] = 0;
      struct  timeval start;
      struct  timeval end1;
      unsigned  long diff;
      //uBEE::SaveBin("../tick/tick.json",(const char*)message,length);
      gettimeofday(&start,NULL);
      uBEE::Tqjson(message,tt);
      gettimeofday(&end1,NULL);
      diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
      printf("thedifference is %ld\n",diff);
    }
  });

  h.onPong([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length) {
    std::cout<< "ping\n";
  });
  h.getDefaultGroup<uWS::CLIENT>().startAutoPing(2000);

  h.connect("ws://192.168.3.4:7777",(void *) 1);
  // --------------------------------------------------------------------------------------------

  h.run();
}
