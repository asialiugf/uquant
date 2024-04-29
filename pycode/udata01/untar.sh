ls -d 20*| while read kk
do
	echo $kk
	tar cvfz $kk.tar.gz $kk 
done
