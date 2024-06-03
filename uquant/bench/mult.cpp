#include <uWS/uWS.h>
#include <thread>
#include <algorithm>
#include <iostream>

int main() {
    // std::vector<std::thread *> threads(std::thread::hardware_concurrency());
    std::vector<std::thread *> threads(4000);
    std::transform(threads.begin(), threads.end(), threads.begin(), [](std::thread *t) {
        return new std::thread([]() {
            uWS::Hub h;

	    h.onConnection([](uWS::WebSocket<uWS::CLIENT>  *ws, uWS::HttpRequest req) {
                printf("main hub onConnection B -- \n");
		ws->send("{\"action\":\"sub\", \"share\":\"GOOG\"}");
                // ws->send(message, length, opCode);
            });



            h.onMessage([](uWS::WebSocket<uWS::CLIENT> *ws, char *message, size_t length, uWS::OpCode opCode) {
               //  ws->send(message, length, opCode);
            });

            // This makes use of the SO_REUSEPORT of the Linux kernel
            // Other solutions include listening to one port per thread
            // with or without some kind of proxy inbetween
            // if (!h.listen(3000, nullptr, uS::ListenOptions::REUSE_PORT)) {
            //     std::cout << "Failed to listen" << std::endl;
            // }
	    h.connect("ws://localhost:9001");
            h.run();
        });
    });

    std::for_each(threads.begin(), threads.end(), [](std::thread *t) {
        t->join();
    });
}
