#include "Base.h"
#include <iostream>
#include <thread>

namespace uGG
{
Base::Base():cs(4,nullptr)
{
}

void Base::Init()
{
    std::thread t(&Base::AssiHubInit,this);
    t.detach();
}

void Base::MainHubInit()
{
    std::cout << "enter into MainHubInit !!\n";
    mainHub.onConnection([this](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        switch((long) ws->getUserData()) {
        case 1:
            this->cs[1] = ws;
            break;
        case 2:
            this->cs[2] = ws;
            break;
        case 3:
            this->cs[3] = ws;
            break;
        default:
            std::cout << "FAILURE: " << ws->getUserData() << " should not connect!" << std::endl;
            exit(-1);
        }
    });

    std::cout << "enter into MainHubInit !!\n";
    // 客户端打印接收到的消息
    mainHub.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char tmp[256];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        printf("Client receive: %s\n", tmp);
        ws->send("Torkkk===");
        usleep(1000000);
        ws->send("----new-----");
        usleep(1);

    });

    std::cout << "enter into MainHubInit !!\n";
    mainHub.onDisconnection([this](uWS::WebSocket<uWS::CLIENT> *ws, int code, char *message, size_t length) {
        this->mainHub.getDefaultGroup<uWS::SERVER>().close();
        this->mainHub.getDefaultGroup<uWS::CLIENT>().close();
    });

    std::cout << "enter into MainHubInit !!\n";
    mainHub.connect("ws://localhost:3000",(void *) 1);  //  web server
    mainHub.connect("ws://localhost:4000",(void *) 2);  //  data server
    mainHub.connect("ws://localhost:5000",(void *) 3);  //  trading server
    std::cout << "-------------- !!\n";
    mainHub.run();
    std::cout << "after run \n";
}

void Base::AssiHubInit()
{
    assiHub.onConnection([this](uWS::WebSocket<uWS::CLIENT> *ws, uWS::HttpRequest req) {
        switch((long) ws->getUserData()) {
        case 0:
            this->cs[0] = ws;
            break;
        default:
            std::cout << "FAILURE: " << ws->getUserData() << " should not connect!" << std::endl;
            exit(-1);
        }
    });

    assiHub.onMessage([this](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
        char *tmp = new char[length+1];
        //char tmp[256];
        memcpy(tmp, message, length);
        tmp[length] = 0;
        usleep(1000000);
        printf("Client receive: %s\n", tmp);
        this->buf.push(tmp);
        this->cv.notify_all();
        //ws->send("-------fro assiHub ===");
        //usleep(1000000);

    });
    assiHub.connect("ws://localhost:4000",(void *) 0);
    assiHub.run();
}

void Base::getTick()
{
	if(cs[0] == nullptr) {
		std::cout<< " not init !!\n";
		exit(-1);
	}
    cs[0]->send("----------from gettick -----------");

    std::cout<< " go to sleep!! \n";
    std::unique_lock <std::mutex> l(mtx);
    //while(!ready)  // 如果标志位不为 true, 则等待...
    cv.wait(l); // 当前线程被阻塞, 当全局标志位变为 true 之后,
    std::cout<< " waked!! \n";
    char * tmp = buf.front();
    buf.pop();
    std::cout<< tmp << std::endl;
	delete [] tmp;
}

}
