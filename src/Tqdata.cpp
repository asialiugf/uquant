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
  h.onConnection([](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
    //ws->send("--server--");
    std::cout <<"Server onConnection send: --server--" << std::endl;
  });

  h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
    if(length>0) {
      message[length] = 0;
      uBEE::SaveBin("../tick/tick.json",(const char*)message,length);
      uBEE::Tqjson(message);
      //uBEE::ErrLog(1000,"json error!",1,0,0);
      //uBEE::ErrLog(1000,"kkkk",1,(const char*)message,length);
      //printf("Server onMessage receive: %s\n", message);
    }
    //ws->send(message, length, opCode);
    //std::printf("Server onMessage send: %s\n", tmp);
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

  // 客户端连上后发送hello
  h.onConnection([&tt](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
    if(tt == 1) {
      char caCmd[4096];
      /*
      memset(caCmd,'\0',4096) ;
      uBEE::MkRequest("./cmd", caCmd,4096);
      std::cout << caCmd << std::endl;
      //ws->send(caCmd);

            {
      "aid": "set_chart",         // 必填, 请求图表数据
      "chart_id": "abcd123",      // 必填, 图表id, 服务器只会维护每个id收到的最后一个请求的数据
      "ins_id": "cu1701",         // 必填, 填空表示删除该图表，多个合约以逗号分割，第一个合约是主合约，所有id都是以主合约为准
              "duration": 180000000000,   // 必填, 周期，单位ns, tick:0, 日线: 3600 * 24 * 1000 * 1000 * 1000
              "view_width": 500,          // 必填, 图表宽度, 请求最新N个数据，并保持滚动(新K线生成会移动图表)
            }
      */
      memset(caCmd,'\0',4096) ;
      //sprintf(caCmd,"{\"aid\": \"set_chart\",\"chart_id\": \"abcd123\",\"ins_id\": \"cu1801,ru1801,ru1805\",\"duration\":0,\"view_width\": 500,}");
      //sprintf(caCmd,"{\"aid\": \"set_chart\",\"chart_id\": \"abcd123\",\"ins_id\": \"cu1801,ru1801,ru1805\",\"duration\":0,\"view_width\": 500,}");
      sprintf(caCmd,"{\"chart_id\": \"TT_ru1701_0\", \"aid\": \"set_chart\", \"duration\": 3000000000, \"view_width\": 30000, \"ins_list\": \"ru1701\"}");
      ws->send(caCmd);
      std::cout << caCmd << std::endl;
    }
    std::cout <<"Tqdata.x onConnection !!" << std::endl;
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
      uBEE::SaveBin("../tick/tick.json",(const char*)message,length);
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
