cmake_minimum_required(VERSION 3.5  FATAL_ERROR)

# CMAKE_EXPORT_COMPILECOMMANDS 主要用于编译命令行的输出，输出到 build/compile_commands.json这个文伯中
# 这个文件可以用于 vim中的 ale的 检查。
# ompile commands output to file: compile_commands.json
# mkdir build
# cd build
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../ -G Ninja  # 如果下面的set不生效，可以用这个命令行直接输出。
set(CMAKE_EXPORT_COMPILECOMMANDS ON)

#set(CMAKE_C_COMPILER "/usr/bin/clang++")
#set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_compile_options(-O3)

set(LINUX ON)
set(WIN32 OFF)
set(CMAKE_VERBOSE_MAKEFILE ON)

# set output color system ，下面是设定输出的颜色系统。 使用 message输出，如下:
# message("${Green} -------- Uquant  -----------  ${ColourReset}")
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

foreach(policy
        CMP0023
        CMP0048 # CMake 3.0
        CMP0063
        CMP0069
        CMP0074 # CMake 3.12
        CMP0077
        CMP0079
    )
    if(POLICY ${policy})
        cmake_policy(SET ${policy} NEW)
    endif()
endforeach()

#设置项目的名称，版本，编译语言
project(UQUANT VERSION 1.0.0 LANGUAGES C CXX)

# globel setting
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-O3 -Wl,-Bsymbolic -g")
# or :
#set_target_properties(myTarget
#    PROPERTIES
#        CXX_STANDARD 11
#        CXX_STANDARD_REQUIRED YES
#        CXX_EXTENSIONS NO
#)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 静态库
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # 动态库
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # 可执行文件

if(EXISTS "${CMAKE_BINARY_DIR}/../../exe/lib")
  message(STATUS "mydir exists")
else()
  message(STATUS "mydir does not exist")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../exe/lib) # 静态库
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../exe/lib) # 动态库
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../exe/bin) # 可执行文件

file(MAKE_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/../../trader/run)

include(./cmake/glob_sources.cmake)

#macro(add_headers_and_sources prefix common_path)
#    add_glob(${prefix}_headers ${CMAKE_CURRENT_SOURCE_DIR} ${common_path}/*.h)
#    add_glob(${prefix}_sources ${common_path}/*.cpp ${common_path}/*.c ${common_path}/*.h)
#endmacro()
#
#macro(add_headers_only prefix common_path)
#    add_glob(${prefix}_headers ${CMAKE_CURRENT_SOURCE_DIR} ${common_path}/*.h)
#endmacro()

message("${Green} -------- Uquant  -----------  ${ColourReset}")

# 用cmake为项目生成 version.h文件
set (CONFIG_VERSION ${CMAKE_CURRENT_BINARY_DIR}/Common/config_version.h)
configure_file (src/Common/Version.h.in Version.h)


# 包含被编译的子目录，每个目录下必须有 CMakeLists.txt文件。
# add_subdirectory (extern EXCLUDE_FROM_ALL)
# add_subdirectory(extern/clickhouse-cpp)
# add_subdirectory (utils)
# add_subdirectory(yyjson)
add_subdirectory (base)
add_subdirectory (src)
# add_subdirectory (tools)
# add_subdirectory (ctp668)
add_subdirectory (trade)

# 第三方库
# add_subdirectory (third/fmt)

add_subdirectory (tests)

# 包含其它的库文件
include(./cmake/cJSON.cmake)
include(./cmake/FinduWS.cmake)
include(./cmake/Findctp.cmake)


message("ccccccccccccccccc=  ${cJSON_DIR}")
message("------${CJSON_INCLUDE_DIR}")
message("cJSON LIB------${CJSON_LIBARY}")

message(" uws:------ ${uWS_INCLUDE_DIR}")
message(" uws:------ ${uWS_LIBRARY}")

message(" ctp:------ ${ctp_INCLUDE_DIR}")
message(" ctp:------ ${mduser_LIBRARY}")
message(" ctp:------ ${trader_LIBRARY}")
