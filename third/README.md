### cjson库
https://github.com/DaveGamble/cJSON/releases
#### 编译安装
root 用户·
```c
wget https://github.com/DaveGamble/cJSON/archive/v1.7.0.tar.gz
tar xvf v1.7.0.tar.gz
root@:~/source# cd cJSON-1.7.0/
root@:~/source/cJSON-1.7.0# mkdir build
root@:~/source/cJSON-1.7.0# cd build
root@:~/source/cJSON-1.7.0/build# cmake ..
root@:~/source/cJSON-1.7.0/build# make
root@:~/source/cJSON-1.7.0/build# make install
```
请仔细阅读 https://github.com/DaveGamble/cJSON


### uWebsockets库
https://github.com/uNetworking/uWebSockets/releases

### CTP的目录

  把CTP相关的文件移到下面两个目录里面去。
  /usr/local/include
  /usr/local/lib

```c
root@d:/usr/local/ctp# ll
total 6400
-rwxrwxr-x 1 riddle riddle     184 Dec 12 17:02 error.dtd
-rwxrwxr-x 1 riddle riddle   15366 Dec 12 17:02 error.xml
-rwxrwxr-x 1 riddle riddle    5398 Dec 12 17:02 ThostFtdcMdApi.h
-rwxrwxr-x 1 riddle riddle   31045 Dec 12 17:02 ThostFtdcTraderApi.h
-rwxrwxr-x 1 riddle riddle  238859 Dec 12 17:02 ThostFtdcUserApiDataType.h
-rwxrwxr-x 1 riddle riddle  201803 Dec 12 17:02 ThostFtdcUserApiStruct.h
-rwxrwxr-x 1 riddle riddle 1900961 Dec 12 17:02 thostmduserapi.so
-rwxrwxr-x 1 riddle riddle 4140081 Dec 12 17:02 thosttraderapi.so
root@d:/usr/local/ctp# 
root@d:/usr/local/ctp# 
root@d:/usr/local/ctp# 
root@d:/usr/local/ctp# 
root@d:/usr/local/ctp# 
root@d:/usr/local/ctp# 
root@d:/usr/local/ctp# cp *.so ../lib
root@d:/usr/local/ctp# cp *.h ../include
root@d:/usr/local/ctp# 
```
