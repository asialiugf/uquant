ls -d x_* | while read kk 
do
	echo $kk
	tar cvfz $kk.tar.gz $kk
done
