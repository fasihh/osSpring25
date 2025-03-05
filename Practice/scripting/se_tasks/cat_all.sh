expand() {
	if [[ -f $1 ]]; then
		echo "is file: $1"
		cat $1
	else
		for file in "$1"/*; do
			expand $file
		done
	fi
}

for dir in *; do
	if [[ -f $dir ]]; then
		continue
	fi

	echo $dir
	expand $dir
done
