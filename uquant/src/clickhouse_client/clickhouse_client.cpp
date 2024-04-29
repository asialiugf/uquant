#include "clickhouse_client.h"

#include "../base/generator.h"

void Ch_Init() { ch_client = new Client({.host = "localhost", .password = "qQOat4bB"}); }

Client* CreateChClient() { return new Client({.host = "localhost"}); }

/* 
auto g_int_0 = [&](const std::string& ch_select, int num = 18) -> std::generator<int> {
    for (int i = 0; i < intn; i++) co_yield i;
};

std::generator<Block> GetOHLCV(Client* ch_client, const std::string& query, int num = 18) {
    Block block;
    ch_client->Select(query, [](const Block& block) -> void {
        for (size_t i = 0; i < block.GetRowCount(); ++i) {
            //  std::cout << block[0]->As<ColumnUInt64>()->At(i) << " " << block[1]->As<ColumnString>()->At(i) << "\n";
            co_yield block;
        }
    });
}
*/