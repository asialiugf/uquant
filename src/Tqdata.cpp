#include <uWS/uWS.h>
#include <uBEE.h>
#include <iostream>
#include <sys/time.h>

#pragma comment(lib, "uWS.lib")

int main()
{
  uWS::Hub h;

  int tt = 0 ;

  std::cout << "phase 1 ==> cmd ! " << std::endl;
  std::cout << "please input phase:" << std::endl;
  std::cin >> tt ;

  // --------------------------------------------------------------------------------------------
  // 服务端接收到包后原封不动返回
  h.onConnection([&tt](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
    if(tt == 1) {
      std::vector<std::string> cmds = uBEE::Command("./cmd");
      for_each(cmds.cbegin(), cmds.cend(), [&ws](const std::string &request)->void{
        ws->send(request);
        std::cout << request << std::endl;
      });
    }
    std::cout <<"Server onConnection send: --server--" << std::endl;
  });

  h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
    if(length>0) {
      std::cout << "message!" << std::endl;
      //usleep(5000000);
      //message[length] = 0;
      struct  timeval start;
      struct  timeval end1;
      unsigned  long diff;
      gettimeofday(&start,NULL);
      uBEE::Tqjson(message);
      gettimeofday(&end1,NULL);
      diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
      printf("thedifference is %ld\n",diff);
    }
  });
  h.onPong([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length) {
    std::cout<< "ok ping\n";
  });
  h.getDefaultGroup<uWS::SERVER>().startAutoPing(2000);

  bool k = h.listen(3000) ;
  if(!k) {
    std::cout << " listen error !!" << std::endl;
   }

  // --------------------------------------------------------------------------------------------
  // 客户端

  h.onDisconnection([](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
    std::cout << "onDisconnection !!" << std::endl;
    std::cout << message << std::endl;
  });


  h.onConnection([&tt](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
    std::cout <<"Tqdata.x onConnection !!" << std::endl;
    if(tt == 1) {
      //char caCmd[4096];
      std::vector<std::string> cmds = uBEE::Command("./cmd");
      for_each(cmds.cbegin(), cmds.cend(), [&ws](const std::string &request)->void{
        ws->send(request);
        std::cout << request << std::endl;
      });

      /*
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

  h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
    if(length>0) {
      std::cout << "message!" << std::endl;
      //usleep(5000000);
      //message[length] = 0;
      struct  timeval start;
      struct  timeval end1;
      unsigned  long diff;
      //uBEE::SaveBin("../tick/tick.json",(const char*)message,length);
      gettimeofday(&start,NULL);
      uBEE::Tqjson(message);
      gettimeofday(&end1,NULL);
      diff = 1000000 * (end1.tv_sec-start.tv_sec)+ end1.tv_usec-start.tv_usec;
      printf("thedifference is %ld\n",diff);
    }
  });

  h.onPong([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length) {
    std::cout<< "ping\n";
  });
  h.getDefaultGroup<uWS::CLIENT>().startAutoPing(2000);

  h.connect("ws://192.168.3.7:7777",(void *) 1);
  // --------------------------------------------------------------------------------------------

  h.run();
}
