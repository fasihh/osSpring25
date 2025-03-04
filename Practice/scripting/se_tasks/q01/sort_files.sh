self=$(basename $0)

for file in $(ls); do
	if [[ $file == $self || -d $file ]]; then
		continue
	fi

	file_type=${file##*.}

	if [[ ! -d $file_type ]]; then
		mkdir $file_type
	fi

	mv $file "$file_type/$file"
done
