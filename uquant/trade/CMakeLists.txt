cmake_minimum_required(VERSION 3.5  FATAL_ERROR)

set(CMAKE_EXPORT_COMPILECOMMANDS ON)

set (CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/Common/config_version.h)
#configure_file (Common/config.h.in ${CONFIG_COMMON})

add_compile_options(-O3)

if(LINUX)
#if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../trader/run) # 可执行文件

message("${Red} -------- tmain.x  -----------  ${ColourReset}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("${Red} -------- tmain.x  -----------  ${ColourReset}")

include(../cmake/glob_sources.cmake)
# add_headers_and_sources() 这是一个宏，定义在 xquant/uquant/cmake/glob_sources.cmake 下面
# 由 上一级 xquant/uquant/CMakeLists.txt 中的 include(./cmake/glob_sources.cmake) 包含进来
# 它会生成 ${data_headers}  ${data_sources}两个变量 
add_headers_and_sources(tmain ./)
# add_headers_and_sources(tmain ../base)
add_headers_only(uquant_test ../base)

# 添加相应的头文件目录
# 当前src目录下的.cpp文件，只需要 #include "ErrLog.h" 即可，不必写成 "../base/ErrLog.h"
include_directories(../base)

#也可以用以下方式
# 在 ./src/Bars.cpp中， 写成 #include <base/ErrLog.h> 下面 将 ../base 改成 ../
include_directories(../)

# 输出可执行文件:tmain.x。
add_executable(tmain.x "")

message(" ${tmain_headers} ")

set(tmain_list ${tmain_sources})

message( "------------------" )
message( " ${tmain_list} " )
message( "------------------" )


#set(MAKE_CMD "${CMAKE_CURRENT_SOURCE_DIR}/makeHeaders.sh")
set(MAKE_CMD "ls")
MESSAGE("COMMAND: ${MAKE_CMD} ${CMAKE_CURRENT_SOURCE_DIR} ${INC_DIR}")
execute_process(COMMAND ${MAKE_CMD} ${CMAKE_CURRENT_SOURCE_DIR} ${INC_DIR}
   RESULT_VARIABLE CMD_ERROR
   # OUTPUT_FILE CMD_OUTPUT)
   OUTPUT_VARIABLE CMD_OUTPUT)
  MESSAGE( STATUS "CMD_ERROR:" ${CMD_ERROR})
  MESSAGE( STATUS "CMD_OUTPUT:" ${CMD_OUTPUT})

target_sources(tmain.x
  PRIVATE
    ${tmain_headers}
    ${tmain_list}
  )

# target_link_directories(tmain.x PUBLIC /home/rabbit/xquant/uquant/extern/ctp)
target_link_directories(tmain.x PUBLIC 
	#../extern/ctp2
	../ctp
  ~/xquant/exe/lib
  )


find_package(fmt)

set(YYJSON_DISABLE_NON_STANDARD ON CACHE INTERNAL "")
 
# Add the `yyjson` subdirectory
# add_subdirectory(../extern/yyjson)
 
# Link yyjson to your target
# target_link_libraries(tmain.x PRIVATE yyjson)
target_link_libraries(tmain.x
  PUBLIC
    #mduser
    #trader
    #libmduser1.so
    #libtrader1.so
    # cjson
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

message("${Green} -------- tmain/src  -----------  ${ColourReset}")

target_include_directories(tmain.x PUBLIC
                           ${CMAKE_CURRENT_LIST_DIR}
                           #${PROJECT_BINARY_DIR}
                           #${EXTRA1_INCLUDES}
                          )
