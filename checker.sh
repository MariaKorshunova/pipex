i=1
retry=1000
rm result
rm text
while [ $i -le $retry ]
do
	$1 > text
    wc -m text | awk '{print $1}' >> result
    cat text >> result
	let i+=1
done
wc -l grep "2" result