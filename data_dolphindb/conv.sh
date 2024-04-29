ls  -d 20* | while read kk
do
	echo $kk
	python3 udata_dolphindb.py $kk
done
