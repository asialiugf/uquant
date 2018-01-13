#include <uWS/uWS.h>
#include <iostream>
#include <thread>   // std::thread
#include <unistd.h>

#pragma comment(lib, "uWS.lib")


int client()
{
    std::cout << " in client \n";
    uWS::Hub h;

    // 客户端连上后发送hello
    h.onConnection([](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        ws->send("forkkk===");
    });

    // 客户端打印接收到的消息
    h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[16];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        //printf("Client receive: %s\n", tmp);
        ws->send("forkkk===");
		usleep(1);

    });
    h.connect("ws://localhost:3000");
    h.run();
    return 0;
}

int main()
{
    uWS::Hub h;

	uWS::WebSocket<uWS::SERVER> *ss;

    // 客户端连上后发送hello
    h.onConnection([](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        ws->send("Hello");
    });

    h.onConnection([&ss](uWS::WebSocket<uWS::SERVER> *ws, uWS::HttpRequest req) {
		ss = ws;
        ws->send("Hello");
    });

    // 客户端打印接收到的消息
    h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[16];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        //printf("Client receive: %s\n", tmp);

        ws->close();
    });

    // 服务端接收到包后原封不动返回
    h.onMessage([&ss](uWS::WebSocket<uWS::SERVER> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[16];
        memcpy(tmp, message, length);
        if(tmp[0] == 'H') {
            std::cout << " in H HHH \n" ;
            std::thread t(client);
            t.detach();
        }
        tmp[length] = 0;
        //printf("Server receive: %s\n", tmp);
        ws->send(message, length, opCode);
        ss->send(message, length, opCode); //这里的ss没有初始化
    });

    bool k = h.listen(3000) ;
    if(!k) {
        std::cout << " listen error !!" << std::endl;
    }
    h.connect("ws://localhost:3000");

    h.run();


}
