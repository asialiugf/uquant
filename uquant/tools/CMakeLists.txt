set(CMAKE_EXPORT_COMPILECOMMANDS ON)

set (CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/Common/config_version.h)
#configure_file (Common/config.h.in ${CONFIG_COMMON})

message(" src ---------: ${CMAKE_CURRENT_SOURCE_DIR}")
message(" uquant/src ---psd------: ${PROJECT_SOURCE_DIR}")

# add_headers_and_sources() 这是一个宏，定义在 xquant/uquant/cmake/glob_sources.cmake 下面
# 由 上一级 xquant/uquant/CMakeLists.txt 中的 include(./cmake/glob_sources.cmake) 包含进来
# 它会生成 ${data_headers}  ${data_sources}两个变量 
add_headers_and_sources(ctpping ./)
add_headers_and_sources(ctpping ../base)

# 添加相应的头文件目录
# 当前src目录下的.cpp文件，只需要 #include "ErrLog.h" 即可，不必写成 "../base/ErrLog.h"
include_directories(../base)

#也可以用以下方式
# 在 ./src/Bars.cpp中， 写成 #include <base/ErrLog.h> 下面 将 ../base 改成 ../
include_directories(../)

# 输出可执行文件:ctpping.x。
add_executable(ctpping.x "")

message(" ${ctpping_headers} ")

set(ctpping_list ${ctpping_sources})

message( "------------------" )
message( " ${ctpping_list} " )
message( "------------------" )


target_sources(ctpping.x
  PRIVATE
    ${ctpping_headers}
    ${ctpping_list}
  )

# target_link_directories(ctpping.x PUBLIC /home/rabbit/xquant/uquant/extern/ctp)
target_link_directories(ctpping.x PUBLIC 
	#../extern/ctp2
	../ctp)

target_link_libraries(ctpping.x
  PUBLIC
    #mduser
    #trader
    libmduser1.so
    libtrader1.so
    # cjson
    # uWS
    # -luuid -lssl -pthread -lz
  )

message("${Green} -------- ctpping/src  -----------  ${ColourReset}")

target_include_directories(ctpping.x PUBLIC
                           ${CMAKE_CURRENT_LIST_DIR}
                           #${PROJECT_BINARY_DIR}
                           #${EXTRA1_INCLUDES}
                          )
