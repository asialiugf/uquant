project(ubeequant)
set(SRC_LIST main.c)
add_executable(hello ${SRC_LIST})

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)
