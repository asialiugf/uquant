#!/bin/bash

# 使用ss命令查找SSH连接的远程IP地址
# 我们假设SSH监听在默认的22端口上
ssh_ips=$(ss -tn | grep ':22' | awk '{print $5}' | cut -d: -f1)

# 检查是否找到了IP地址
if [ -z "$ssh_ips" ]; then
    echo "没有找到SSH连接。"
else
    # 打印所有找到的SSH连接的IP地址
    echo "找到的SSH连接的IP地址如下："
    echo "$ssh_ips"
fi
