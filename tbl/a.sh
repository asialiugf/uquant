#!/bin/bash

echo -n "please enter 日期（格式:20180808）:"
read line
echo $line
mkdir /home/riddle/u/tick/$line
mv    /home/riddle/u/dat             /home/riddle/u/tick/$line/$line.tick
mv    /home/riddle/u/tick/tick.json  /home/riddle/u/tick/$line/tick.$line.json
mkdir /home/riddle/u/dat

echo -n " ---- 结束 ---- "
