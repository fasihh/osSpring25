if [[ $# -ne 1 ]]; then
	echo "usage: $0 <file>"
	exit 1
fi

file=$1_$(echo $(date) | awk '{gsub(" ", "-"); print}')

echo $file
