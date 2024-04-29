#!/bin/bash


# 使用ss命令查找SSH连接的远程IP地址
# 我们假设SSH监听在默认的22端口上
ssh_ip=$(ss -tn | grep ':22' | awk '{print $5}' | cut -d: -f1)

# 检查是否找到了IP地址
if [ -z "$ssh_ip" ]; then
    echo "没有找到SSH连接。"
    exit 1
else # ===============================================
    # 打印所有找到的SSH连接的IP地址
    echo "找到的SSH连接的IP地址如下："
    echo "$ssh_ip"



# 检查是否提供了一个参数
#if [ "$#" -ne 1 ]; then
#    echo "Usage: $0 <IPv4 address>"
#    exit 1
#fi

# 接收的参数存储在 $1 中
ip_address=$ssh_ip

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

git config --global -l

fi  # ==============================================
