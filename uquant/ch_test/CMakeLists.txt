cmake_minimum_required(VERSION 3.12)
project(application-example)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(../contribs/clickhouse-cpp)

add_executable(${PROJECT_NAME} "app.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE ../contribs/clickhouse-cpp/ ../contribs/clickhouse-cpp/contrib/absl)

target_link_directories(${PROJECT_NAME} PRIVATE 
../uWebSockets/uSockets
../ctp
~/xquant/exe/lib
)
target_link_libraries(${PROJECT_NAME} PRIVATE clickhouse-cpp-lib)
