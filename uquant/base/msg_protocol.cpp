#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#include "msg_protocol.h"

// 序列化函数
std::vector<uint8_t> serialize(const ProtocolMessage &msg) {
    std::vector<uint8_t> buffer;
    buffer.resize(sizeof(msg.version_) + sizeof(msg.fn_code_) + sizeof(msg.er_code_) + sizeof(msg.length_) +
                  msg.length_);

    // 填充协议版本
    *(uint8_t *)(buffer.data()) = msg.version_;
    // 填充功能代码
    *(uint8_t *)(buffer.data() + 1) = msg.fn_code_;
    // 填充错误代码
    *(uint8_t *)(buffer.data() + 2) = msg.er_code_;
    // 填充长度
    *(uint32_t *)(buffer.data() + 3) = msg.length_;
    // 填充内容
    memcpy(buffer.data() + sizeof(msg.version_) + sizeof(msg.fn_code_) + sizeof(msg.er_code_) + sizeof(msg.length_),
           msg.content_, msg.length_);

    return buffer;
}

// 反序列化函数
ProtocolMessage deserialize(const std::vector<uint8_t> &buffer) {
    ProtocolMessage msg;
    msg.version_ = *(uint8_t *)(buffer.data());
    msg.fn_code_ = *(uint8_t *)(buffer.data() + 1);
    msg.er_code_ = *(uint8_t *)(buffer.data() + 2);
    msg.length_ = *(uint32_t *)(buffer.data() + 3);
    msg.content_ = new uint8_t[msg.length_];
    memcpy(msg.content_,
           buffer.data() + sizeof(msg.version_) + sizeof(msg.fn_code_) + sizeof(msg.er_code_) + sizeof(msg.length_),
           msg.length_);

    return msg;
}