set(CMAKE_EXPORT_COMPILECOMMANDS ON)

set (CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/Common/config_version.h)
#configure_file (Common/config.h.in ${CONFIG_COMMON})

message(" src ---------: ${CMAKE_CURRENT_SOURCE_DIR}")
message(" uquant/src ---psd------: ${PROJECT_SOURCE_DIR}")

add_headers_and_sources(data ./)
add_headers_and_sources(data ../base)

add_compile_options(-O3)

# 添加相应的头文件目录
# 当前src目录下的.cpp文件，只需要 #include "ErrLog.h" 即可，不必写成 "../base/ErrLog.h"
# include_directories(../base)

#也可以用以下方式
# 在 ./src/Bars.cpp中， 写成 #include <base/ErrLog.h> 下面 将 ../base 改成 ../
include_directories(../)

# 输出可执行文件:xquant。
add_executable(xquant "")
add_executable(broadcast "")
add_executable(back_test_server "")

message(" ${data_headers} ")

set(quant_server_list ${data_sources})
set(broadcast_list ${data_sources})
set(back_test_server_list ${data_sources})

message( "------------------" )
message( " ${quant_server_list} " )
message( " ${gettick_list} " )
message( "------------------" )

list(REMOVE_ITEM quant_server_list broadcast.cpp)
list(REMOVE_ITEM quant_server_list back_test_server.cpp)

list(REMOVE_ITEM broadcast_list quant_server.cpp)
list(REMOVE_ITEM broadcast_list back_test_server.cpp)

list(REMOVE_ITEM back_test_server_list broadcast.cpp)
list(REMOVE_ITEM back_test_server_list quant_server.cpp)

message( "------------------" )
message( " ${quant_server_list} " )
message( " ${broadcast_list} " )
message( "------------------" )

set(broadcast_list broadcast.cpp)
set(back_test_server_list back_test_server.cpp)

target_sources(xquant
  PRIVATE
    ${data_headers}
    ${quant_server_list}
  )

target_sources(broadcast
  PRIVATE
    ${data_headers}
    ${broadcast_list}
  )

target_sources(back_test_server
  PRIVATE
    ${data_headers}
    ${back_test_server_list}
  )

target_link_directories(xquant PUBLIC ../ctp)
target_link_libraries(xquant
  PUBLIC
    # clickhouse-cpp-lib
    mduser1
    trader1
    cjson
    uWS
    -lssl
    -lz
    -ldeflate
    -lglog
    # -luuid -lssl -pthread -lz
  )

#  在 ../uSockets 和 ../ctp 目录下找链接库
target_link_directories(broadcast PUBLIC 
../uWebSockets/uSockets
../ctp
~/xquant/exe/lib
)
target_link_libraries(broadcast
  PUBLIC
    # clickhouse-cpp-lib
    libuBEEBase.a
    mduser1
    trader1
    uWS
    cjson
    -flto
    -lz
    libuSockets.a
    -ldeflate
    -lglog
    # -luuid -lssl -pthread -lz
  )

#  在 ../uSockets 和 ../ctp 目录下找链接库
target_link_directories(back_test_server PUBLIC 
../uWebSockets/uSockets
../ctp
~/xquant/exe/lib
)
target_link_libraries(back_test_server
  PUBLIC
    # clickhouse-cpp-lib
    libuBEEBase.a
    mduser1
    trader1
    uWS
    cjson
    -flto
    -lz
    libuSockets.a
    -ldeflate
    -lglog
    # -luuid -lssl -pthread -lz
  )


message("${Green} -------- Uquant/src  -----------  ${ColourReset}")

target_include_directories(xquant PUBLIC
                           ${CMAKE_CURRENT_LIST_DIR}
                           #${PROJECT_BINARY_DIR}
                           #${EXTRA1_INCLUDES}
                           extern/clickhouse-cpp/
                           extern/clickhouse-cpp/contrib/absl
                          )
