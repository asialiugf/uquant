cd /home/riddle/u/dat

if [ ! -f "*000000" ]; then
 rm *000000
fi

ls * > /tmp/zz
wc /tmp/zz
sed -i ':a;N;$!ba;s/\n/,/g' /tmp/zz


cd /home/riddle/u
cat /tmp/zz | while read LINE  
do
    echo "{\"aid\":\"subscribe_quote\",\"ins_list\":\"$LINE\"}"  > /home/riddle/u/exe/cmd
done
