for file in q02_*.c; do
	file_name=${file%%.*}
	if [[ -e $file_name ]]; then
		rm $file_name
	fi
	gcc $file -o $file_name
done
