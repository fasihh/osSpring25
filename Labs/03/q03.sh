if [[ $# -ne 1 ]]; then
	echo "usage: ./q03 <filename>"
	exit 1
fi

if [[ ! -e $1 ]]; then
	echo "file does not exist"
	exit 1
fi

echo $(date) >> $1

