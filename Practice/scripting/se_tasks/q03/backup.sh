if [[ $# -ne 1 ]]; then
	echo "usage: $0 <file>"
	exit 1
fi

original=$1
backup=$(basename ${original%%.*})_$(echo $(date +"%Y-%m-%d") | awk '{gsub(" ", "-"); print}').${original##*.}

cp $original $backup
