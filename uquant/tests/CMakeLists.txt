set(CMAKE_EXPORT_COMPILECOMMANDS ON)

set (CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/Common/config_version.h)
#configure_file (Common/config.h.in ${CONFIG_COMMON})

message(" src ---------: ${CMAKE_CURRENT_SOURCE_DIR}")
message(" uquant/src ---psd------: ${PROJECT_SOURCE_DIR}")

# add_headers_and_sources() 这是一个宏，定义在 xquant/uquant/cmake/glob_sources.cmake 下面
# 由 上一级 xquant/uquant/CMakeLists.txt 中的 include(./cmake/glob_sources.cmake) 包含进来
# 它会生成 ${data_headers}  ${data_sources}两个变量 
add_headers_and_sources(uquant_test ./)
#add_headers_and_sources(uquant_test ../base)
add_headers_only(uquant_test ../base)
# 添加相应的头文件目录
# 当前src目录下的.cpp文件，只需要 #include "ErrLog.h" 即可，不必写成 "../base/ErrLog.h"
include_directories(../base)

#也可以用以下方式
# 在 ./src/Bars.cpp中， 写成 #include <base/ErrLog.h> 下面 将 ../base 改成 ../
include_directories(../)

# 输出可执行文件:uquant_test.x。
add_executable(uquant_test.x "")

message(" ${uquant_test_headers} ")

set(uquant_test_list ${uquant_test_sources})

message( "------------------" )
message( " ${uquant_test_list} " )
message( "------------------" )

find_package(fmt)

target_sources(uquant_test.x
  PRIVATE
    ${uquant_test_headers}
    ${uquant_test_list}
  )

# 指定库的目录在哪里
target_link_directories(uquant_test.x PUBLIC 
	#../extern/ctp2
	../ctp
  ~/xquant/exe/lib
  )

# 指定连接的库，可以写全名，必须以lib开头。
target_link_libraries(uquant_test.x
  PUBLIC
    #mduser
    #trader
    libmduser1.so
    libtrader1.so
    libgtest.so
    libuBEEBase.a
    # cjson
    # uWS
    # -luuid -lssl -pthread -lz
    # libyyjson.a
    libuBEEBase.a
    #  下面不能写成 -uWS
    libuWS.so  
    -lz
    -ldeflate
    -lssl
    -lglog
    # fmt::fmt
    # fmt-header-only
    # PRIVATE fmt::fmt-header-only
    PRIVATE fmt::fmt
  )

message("${Green} -------- uquant_test/src  -----------  ${ColourReset}")

target_include_directories(uquant_test.x PUBLIC
                           ${CMAKE_CURRENT_LIST_DIR}
                           #${PROJECT_BINARY_DIR}
                           #${EXTRA1_INCLUDES}
                          )
