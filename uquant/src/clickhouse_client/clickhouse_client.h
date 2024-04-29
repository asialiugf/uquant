
#ifndef UBEE_FILE_H
#define UBEE_FILE_H
#include "../base/generator.h"
#include "../extern/clickhouse-cpp/clickhouse/client.h"

using namespace clickhouse;
Client* ch_client;

void Ch_Init();
Client* CreateChClient();
std::generator<int> g_int;

#endif  // UBEE_FILE_H
