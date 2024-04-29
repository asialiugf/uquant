#!/bin/bash

# 检查是否提供了一个参数
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <IPv4 address>"
    exit 1
fi

# 接收的参数存储在 $1 中
ip_address=$1

# 使用正则表达式检查 IPv4 地址格式
re='^([0-9]{1,3}\.){3}[0-9]{1,3}$'

# 使用正则表达式匹配 IPv4 地址
if echo $ip_address | grep -qP $re; then
    # 每个段都不能超过255
    IFS='.' read -ra addr <<< "$ip_address"
    for i in "${addr[@]}"; do
        if [ "$i" -gt 255 ]; then
            echo "Error: $ip_address is not a valid IPv4 address."
            exit 1
        fi
    done

    echo "$ip_address is a valid IPv4 address."
else
    echo "Error: $ip_address is not in the form of an IPv4 address."
    exit 1
fi

git config --global https.proxy $ip_address:23457
git config --global http.proxy $ip_address:23457
git config --global http.sslVerify false
git config --global http.version HTTP/1.1
git config --global http.postBuffer 524288000
