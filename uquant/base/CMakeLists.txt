
add_compile_options(-O3)

add_headers_and_sources(data ./)

add_library (uBEEBase STATIC  "")

#    BaseDaemon.cpp
#    GraphiteWriter.cpp
#    SentryWriter.cpp
#)

target_sources(uBEEBase
    PRIVATE
        ${data_sources}
    )

target_include_directories (uBEEBase PUBLIC ..)

#target_link_libraries (uBEEBase PUBLIC loggers PRIVATE clickhouse_common_io clickhouse_common_config common ${EXECINFO_LIBRARIES})
