#include <cstdint>
#include <iostream>
#include <vector>

// 协议消息结构体
struct ProtocolMessage {
    uint8_t version_;  // 协议版本
    uint8_t fn_code_;  // 错误代码
    uint8_t er_code_;  // 功能代码
    uint32_t length_;  // 内容长度
    uint8_t *content_; // 指向内容的指针
};

// 使用enum class创建强类型枚举，并指定底层类型为uint8_t
enum class FunctionCode : uint8_t {
    SUBSCRIBE = 0x01, // 订阅操作
    PUBLISH = 0x02,   // 发布操作
    GET = 0x03,       // 获取数据操作
    SET = 0x04,       // 设置数据操作
    PING = 0x05,      // 心跳检测
    PONG = 0x06,      // 心跳响应
    LOGIN = 0x07,     // 用户登录
    LOGOUT = 0x08,    // 用户登出
    UNKNOWN = 0xFF    // 未知功能
};