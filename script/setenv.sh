#!/bin/bash

# 定义别名
ALIAS_RR='alias rr="cd ~/xquant/trader/run"'
ALIAS_BB='alias bb="cd ~/xquant/exe/bin"'
ALIAS_MM='alias mm="cd ~/xquant/uquant/build && make"'
ALIAS_TT='alias tt="cd ~/xquant/uquant/build && make && cd ~/xquant/exe/bin && ./uquant_test.x"'

SET_LD='export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib64:/usr/local/lib'
SET_CDPATH='export CDPATH=~/xquant:~/xquant/uquant'

# 检查.bashrc文件是否存在
if [ -f ~/.bashrc ]; then
    # 检查别名是否已经存在于.bashrc中，以避免重复添加
    if ! grep -q "^$ALIAS_RR\$" ~/.bashrc; then
        echo "$ALIAS_RR" >> ~/.bashrc
    fi
    if ! grep -q "^$ALIAS_BB\$" ~/.bashrc; then
        echo "$ALIAS_BB" >> ~/.bashrc
    fi
    if ! grep -q "^$ALIAS_MM\$" ~/.bashrc; then
        echo "$ALIAS_MM" >> ~/.bashrc
    fi
    if ! grep -q "^$ALIAS_TT\$" ~/.bashrc; then
        echo "$ALIAS_TT" >> ~/.bashrc
    fi
    if ! grep -q "^$SET_LD\$" ~/.bashrc; then
        echo "$SET_LD" >> ~/.bashrc
    fi
    if ! grep -q "^$SET_CDPATH\$" ~/.bashrc; then
        echo "$SET_CDPATH" >> ~/.bashrc
    fi
else
    echo "创建新的.bashrc文件"
    echo "$ALIAS_RR" > ~/.bashrc
    echo "$ALIAS_BB" >> ~/.bashrc
    echo "$ALIAS_MM" >> ~/.bashrc
    echo "$ALIAS_TT" >> ~/.bashrc
    echo "$SET_LD" >> ~/.bashrc
fi

# 通知用户需要重新加载.bashrc
echo "请运行 'source ~/.bashrc' 以使更改生效"



# 检查并创建目录
mkdir -p ~/xquant/exe
mkdir -p ~/xquant/exe/data
mkdir -p ~/xquant/exe/data/tick


#============
# 定义需要创建的目录
DIR_XQUANT='~/xquant'
DIR_TRADER="$DIR_XQUANT/trader"
DIR_RUN="$DIR_TRADER/run"
DIR_TBL="$DIR_RUN/tbl"
DIR_LOG="$DIR_RUN/log"

# 定义需要复制的文件
FILE_TRADE_JSON='~/xquant/uquant/tests/mock/tbl/trade.json'
FILE_DEST="$DIR_TBL/trade.json"

# 创建trader目录及其子目录
mkdir -p ~/xquant/trader
mkdir -p ~/xquant/trader/run
mkdir -p ~/xquant/trader/run/tbl
mkdir -p ~/xquant/trader/run/log


# 复制trade.json到指定位置
if [ -f ~/xquant/uquant/tests/mock/tbl/trade.json ]; then
    cp  ~/xquant/uquant/tests/mock/tbl/trade.json ~/xquant/trader/run/tbl
else
    echo " trader.json 不存在！" 
fi


