【2023-12-24】
###  trade-main.cpp
在 trade/main.cpp中可以看到输入的配置文件以及数据文件及相关目录。
- cd ~/xquant/etc/runenv
- cp -r ./tdx_data  ~/tdx_data
- cp -r ./tbl ~/xquant/trader/run
#### 执行过程
```
alias rr='cd ~/xquant/trader/run'
alias bb='cd ~/xquant/exe/bin'
alias mm='cd ~/xquant/uquant/build && make'
alias tt='cd ~/xquant/uquant/build && make &&  cd  ~/xquant/exe/bin && ./uquant_test.x '
```
编译过程请看： xquant：整体编译运行+服务器nginx配置  https://www.yuque.com/asialine/fo2koz/xt0p24mdi65y7nll
 还要配置nginx。
在浏览器上打开，请看 website/chart/index.html，里面有ip address 可能需要修改。338行附近的websocket IP地址。
如果在本地的话， 下面两句配置都一样，如果在远程，要改成8300由nginx转发。
        // let socket = new WebSocket('ws://192.168.1.26:9001');
        let socket = new WebSocket('ws://192.168.1.26:8300');
要配置 防火墙。
```
[root @ mozart /etc/nginx] # ufw status
Status: active

To                         Action      From
--                         ------      ----
9001                       ALLOW       Anywhere                  
80                         ALLOW       Anywhere                  
8300                       ALLOW       Anywhere                  
22/tcp                     ALLOW       Anywhere                  
9001 (v6)                  ALLOW       Anywhere (v6)             
80 (v6)                    ALLOW       Anywhere (v6)             
8300 (v6)                  ALLOW       Anywhere (v6)             
22/tcp (v6)                ALLOW       Anywhere (v6)             

[root @ mozart /etc/nginx] # 
```

先执行 bin下面的 ./broadcast.x
然后执行 run下面的 ./tmain.x 

# proxyip.sh使用
 在script目录下, proxyip.sh 通过 ss -t 命令找出笔记本电脑的ip，并将其设置为 git的环境。
 注意：要通过 vscode 连接到服务器上， ss -t 才能查出 ssh连接，找出IP。
       只能有一个ssh连接，否则会出错。

