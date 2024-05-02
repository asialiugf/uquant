/* We simply call the root header file "App.h", giving you uWS::App and uWS::SSLApp */
// 2023-11-26 将这个改成 中转server, 从策略进程收到数据，发送给web端显示。
#include <time.h>

#include <iostream>

#include "../base/yyjson.h"
#include "../uWebSockets/src/App.h"

/* This is a simple WebSocket echo server example.
 * You may compile it with "WITH_OPENSSL=1 make" or with "make" */

// 用于计算程序执行时间
inline uint64_t rdtsc() { return __builtin_ia32_rdtsc(); }

struct MSG_T {
    uint64_t before;
    uint64_t latency;
    char google[512];
};

 struct us_listen_socket_t *test_sock;

uWS::App *globalApp;
int i{0};
void set_timer(int x) {
    std::cout << "globle -- broadcast.cpp --  befor us_timer_set() " << std::endl;
    struct us_loop_t *loop = (struct us_loop_t *)uWS::Loop::get();
    struct us_timer_t *delayTimer = us_create_timer(loop, 0, 0);
    // broadcast the unix time as millis every 8 millis
    us_timer_set(
        delayTimer,
        [](struct us_timer_t * /*t*/) {
            struct timespec ts;
            timespec_get(&ts, TIME_UTC);

            // int64_t millis = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;

            char millis[] = "abcdef";
            char google[1024];

            // std::cout << "Broadcasting timestamp: " << millis << std::endl;

            globalApp->publish("xxxx", std::string_view((char *)millis, 6), uWS::OpCode::BINARY, false);
            uint64_t before;
            uint64_t latency;
            struct MSG_T {
                uint64_t before;
                uint64_t latency;
                char google[7120];
            };
            before = rdtsc();
            struct MSG_T msg1;
            msg1.before = before;
            msg1.google[0] = 'a';
            msg1.latency = rdtsc() - before;
            before = rdtsc();
            msg1.before = before;
            globalApp->publish("GOOG", std::string_view((char *)&msg1, sizeof(struct MSG_T)), uWS::OpCode::BINARY, false);
            // globalApp->publish("GOOG", (char *)&before, uWS::OpCode::BINARY, false);
            latency = rdtsc() - before;
            std::cout << "\n publish:: main " << before << " latency: " << latency << " i: " << std::endl;
            // globalApp->publish("broadcast", std::string_view((char *) millis, 6), uWS::OpCode::BINARY, false);
            // globalApp->publish("broadcast", std::string_view((char *) &millis, sizeof(millis)), uWS::OpCode::BINARY,
            // false);
            i++;
        },
        1000, 2000);
}

int g_id = 0;

struct PerSocketData {
    /* Fill with user data */
    int id;
    uWS::Loop *loop;
    std::string name;
};

void LoopFunc(uWS::WebSocket<false, true, PerSocketData> *ws) {
    std::string name;
    while (true) {
        std::cout << " Loop Thread: " << std::this_thread::get_id() << std::endl;
        name = ws->getUserData()->name;
        std::cout << " Loop  get: " << std::this_thread::get_id() << name << std::endl;

        /* Check break condition. */

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        // sleep(1);
        std::cout << " Loop  get: " << std::this_thread::get_id() << name << std::endl;
        std::string result = "Mission Complete! " + name;
        std::cout << " Loop Thread defer B: " << std::this_thread::get_id() << std::endl;

        struct MSG_T msg1;
        msg1.google[0] = 'a';
        msg1.before = rdtsc();

        // ws->getUserData()->loop->defer([ws, result]() { ws->send(result, uWS::TEXT, true); });
        ws->getUserData()->loop->defer([ws, msg1]() { ws->send(std::string_view((char *)&msg1, sizeof(struct MSG_T)), uWS::BINARY, true); });
        std::cout << " Loop Thread defer E: " << std::this_thread::get_id() << std::endl;
    }
}

int main() {
    auto loop1 = uWS::Loop::get();
    int n = 1;
    /* ws->getUserData returns one of these */

    /* Keep in mind that uWS::SSLApp({options}) is the same as uWS::App() when compiled without SSL support.
     * You may swap to using uWS:App() if you don't need SSL */
    uWS::App app = uWS::App({
        /* There are example certificates in uWebSockets.js repo */
        .key_file_name = "misc/key.pem",
        .cert_file_name = "misc/cert.pem",
        .passphrase = "1234",
    });

    app.ws<PerSocketData>("/*", // ---
                          {
                              /* Settings */
                              .compression = uWS::SHARED_COMPRESSOR,
                              .maxPayloadLength = 16 * 1024 * 1024,
                              .idleTimeout = 60,
                              // .maxBackpressure = 1 * 1024 * 1024,
                              .maxBackpressure = 100,
                              .closeOnBackpressureLimit = false,
                              .resetIdleTimeoutOnSend = false,
                              .sendPingsAutomatically = true,
                              /* Handlers */
                              .upgrade = nullptr,
                              .open =
                                  [](auto *ws) {
                                      /* Open event here, you may access ws->getUserData() which points to a
                                       * PerSocketData struct */
                                      // ws->subscribe("broadcast");
                                      auto x = ws->getUserData();
                                      x->id = g_id;
                                      g_id ++;
                                      x->name = "tttt";
                                      x->loop = uWS::Loop::get(); // 一个线程一个loop, 一个线程可以有多个 uWS::App app1,app2
                                                                  //  std::thread th1(LoopFunc, ws);
                                                                  //  th1.detach();

                                      //  ws->subscribe("xxxx");
                                      //  ws->subscribe("GOOG");
                                      std::cout << ".open!" << std::endl;

                                      std::string message = "{ from open hellow !!!!!! }" ;

                                      int x1 = 0;
                                      while(ws->getBufferedAmount() < 100) {
                                       //  std::cout << " hello: " << message << std::endl;
                                       //  std::cout << ws->getBufferedAmount() << std::endl;
                                        std::string str = std::to_string(x1);
                                        std::string s(message) ;
                                        std::string sss = s + " " + str; 
                                        auto xxx = ws->send( sss ) ;
                                       //  std::cout << "xxxx is: " << xxx  << std::endl;
                                        x1++ ;
                                      } 
                                      std::cout << "id: " << x->id << " hhhh go out while in messge() : buffer amount:  "  << ws->getBufferedAmount() << "  " << x << std::endl;




                                  },
                              .message =
                                  [&](auto *ws, std::string_view message, uWS::OpCode /*opCode*/) {
                                      // ws->subscribe("GOOG");
                                      std::cout << message << " : " << message.length() << "  from .message !\n";
                                      // ws->send(message, uWS::BINARY, true);

                                      // 从 message中解读json
                                      // yyjson用法： https://github.com/ibireme/yyjson/blob/master/doc/API.md

                                      std::string s(message); // 这里有一个copy动作。 todo性能
                                      std::cout << s << " : " << s.length() << "  from .s  !\n";
                                    
                                    /*
                                      int x = 0;
                                      while(ws->getBufferedAmount() < 100) {
                                        std::cout << " hello: " << message << std::endl;
                                        std::cout << ws->getBufferedAmount() << std::endl;
                                        std::string str = std::to_string(x);
                                        std::string s(message) ;
                                        std::string sss = s + " " + str; 
                                        auto xxx = ws->send( sss ) ;
                                        std::cout << "xxxx is: " << xxx  << std::endl;
                                        x++ ;
                                      } 
                                      std::cout << "hhhh go out while in messge() : buffer amount:  "  << ws->getBufferedAmount() << "  " << x << std::endl;
                                      */


                                      
                                      /*
                                      globalApp->publish("xxxx", message, uWS::OpCode::BINARY, false);

                                      yyjson_doc *doc = yyjson_read(s.c_str(), s.length(), 0);
                                      if (doc) {
                                          yyjson_val *root = yyjson_doc_get_root(doc);
                                          yyjson_val *action = yyjson_obj_get(root, "action");
                                          if (action) {
                                              if (strcmp(yyjson_get_str(action), "sub") == 0) {
                                                  ws->subscribe("xxxx");
                                                  std::cout << message << " here !!" << std::endl;
                                              }
                                              if (strcmp(yyjson_get_str(action), "pub") == 0) {
                                                  globalApp->publish("xxxx", message, uWS::OpCode::BINARY, false);
                                              }
                                          }
                                      }

                                      yyjson_doc_free(doc);
                                      std::cout << s << " : " << s.length() << "  from .s sss !\n";
                                      */
                                  },
                              .drain =
                                  [](auto * ws) {
                                      /* Check ws->getBufferedAmount() here */
                                    int amount = ws->getBufferedAmount() ; 
                                    std::string str = std::to_string(amount);
                                    std::string result = "{ This is a message, let's call it " + str + "}"; 
                                    std::cout << result << std::endl;
                                    while ( ws->getBufferedAmount() < 100) {
                                        ws->send(result);
                                        amount = ws->getBufferedAmount() ; 
                                       //  std::cout << " in drain while : " << amount << std::endl; 
                                    }
                                     auto x = ws->getUserData();
                                     amount = ws->getBufferedAmount() ; 
                                     std::cout << " id : " << x->id <<  " tttttttttttt out drain while : " << amount << std::endl; 
                                    /*
                                    while (ws.getBufferedAmount() < backpressure) {
                                        ws.send("This is a message, let's call it " ); //+ messageNumber
                                        messageNumber++;
                                        messages++;
                                    }
                                    */
                                  },
                              .ping =
                                  [](auto * /*ws*/, std::string_view) {
                                      /* Not implemented yet */
                                  },
                              .pong =
                                  [](auto * /*ws*/, std::string_view) {
                                      /* Not implemented yet */
                                  },
                              .close =
                                  [](auto * ws, int code, std::string_view message) {
                                      /* You may access ws->getUserData() here */
                                      std::cout << " go into .close ! code is: " << code << std::endl;
                                  },
                          });

    app.listen(9001, [](auto *listen_socket) {
        test_sock = listen_socket;
        if (listen_socket) {
            std::cout << "Listening on port " << 9001 << std::endl;
        }
        else {
            us_listen_socket_close(0,test_sock);
            test_sock = nullptr;
        }
    });

    app.listen(7001, [](auto *listen_socket) {
        if (listen_socket)
            std::cout << "Listening on port " << 7001 << std::endl;
    });

    std::cout << "-- broadcast.cpp --  befor uWS::Loop::get(); " << std::endl;
    struct us_loop_t *loop = (struct us_loop_t *)uWS::Loop::get();

    struct us_timer_t *delayTimer = us_create_timer(loop, 0, 0);
    std::cout << "-- broadcast.cpp --  befor us_timer_set() " << std::endl;
    // broadcast the unix time as millis every 8 millis
    us_timer_set(
        delayTimer,
        [](struct us_timer_t * /*t*/) {
            struct timespec ts;
            timespec_get(&ts, TIME_UTC);

            // int64_t millis = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;

            char millis[] = "abcdef";
            char google[1024];

            // std::cout << "Broadcasting timestamp: " << millis << std::endl;

            //  globalApp->publish("xxxx", std::string_view((char *)millis, 6), uWS::OpCode::BINARY, false);
            uint64_t before;
            uint64_t latency;
            before = rdtsc();
            struct MSG_T msg1;
            msg1.before = before;
            msg1.google[0] = 'a';
            msg1.latency = rdtsc() - before;
            before = rdtsc();
            msg1.before = before;
            // globalApp->publish("GOOG", std::string_view((char *)&msg1, sizeof(struct MSG_T)), uWS::OpCode::BINARY, false);
            latency = rdtsc() - before;
            // std::cout << "\n publish::  " << before << " latency: " << latency << std::endl;
            // globalApp->publish("broadcast", std::string_view((char *) millis, 6), uWS::OpCode::BINARY, false);
            // globalApp->publish("broadcast", std::string_view((char *) &millis, sizeof(millis)), uWS::OpCode::BINARY, false);
        },
        100, 100);

    globalApp = &app;

    // app.run();
    uWS::run();
}
