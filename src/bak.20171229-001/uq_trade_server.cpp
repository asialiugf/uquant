#include <uWS/uWS.h>
#include <unistd.h>
#include <iostream>

#pragma comment(lib, "uWS.lib")

int main()
{
    uWS::Hub h;

    // --------------------------------------------------------------------------------------------
    // 服务端接收到包后原封不动返回
    h.onConnection([](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
        ws->send("--server--");
		std::cout <<"Server onConnection send: --server--" << std::endl;
    });

    h.onMessage([](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[256];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Server onMessage receive: %s\n", tmp);
        ws->send(message, length, opCode);
        ws->send(message, length, opCode);
        printf("Server onMessage send: %s\n", tmp);
    });

    bool k = h.listen(3000) ;
    if(!k) {
        std::cout << " listen error !!" << std::endl;
    }
    // --------------------------------------------------------------------------------------------

    // 客户端连上后发送hello
    h.onConnection([](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        ws->send("--client0000--");
		std::cout <<"Client onConnection send: --client00--" << std::endl;
    });

    // 客户端打印接收到的消息
    h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[256];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Client onMessage receive: %s\n", tmp);
        ws->send(message, length, opCode);
        printf("Client onMessage send: %s\n", tmp);
        //usleep(1000);

        //ws->close();
    });

    h.connect("ws://localhost:3000");
    // --------------------------------------------------------------------------------------------

    h.run();
}
