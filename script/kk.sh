ls | while read kk
do
	echo $kk
	iconv -f gb18030 -t utf-8 $kk > $kk.ok
	mv $kk.ok $kk
done
