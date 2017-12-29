#include <uWS/uWS.h>
#include <unistd.h>
#include <iostream>

#pragma comment(lib, "uWS.lib")

int main()
{
    uWS::Hub h;
    int count = 0;
    std::map<int, uWS::WebSocket<uWS::SERVER>*> rr ;

    // --------------------------------------------------------------------------------------------
    // 服务端接收到包后原封不动返回
    h.onConnection([&count,&rr](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
        rr.insert(std::pair<int,uWS::WebSocket<uWS::SERVER>*>(count,ws));
        count++;
        std::cout <<"Server onConnection send: --server--" << std::endl;
    });

    h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        std::cout <<"Server onConnection send: --server--" << std::endl;
    });

    bool k = h.listen(3000) ;
    if(!k) {
        std::cout << " listen error !!" << std::endl;
    }
    // --------------------------------------------------------------------------------------------
    // 客户端连上后发送hello
    h.onConnection([](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        std::cout <<"Client --client00--" << std::endl;
    });

    // 客户端打印接收到的消息
    h.onMessage([&count,&rr](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[16];
        memcpy(tmp, message, length);
		tmp[length] = '\0';
        printf("Client receive: %s\n", tmp);
        if(tmp[0] == '0') {
            std::cout << " client 0 \n" ;
            //rr[0]->send("000000");
            ws->send("000000");
        } else if(tmp[0] == '1') {
            std::cout << " client 1 \n" ;
            //rr[1]->send("111111");
            ws->send("111111");
        }
    });

    h.onPing([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length) {
        std::cout << "PING" << std::endl;
        //pings++;
    });

    h.connect("ws://localhost:3001");
    // --------------------------------------------------------------------------------------------

    h.run();
}
