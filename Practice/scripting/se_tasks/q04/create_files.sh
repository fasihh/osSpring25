read -r message

for i in $(seq 1 ${#message}); do
	echo ${message:0:i} > "file$i"
done
