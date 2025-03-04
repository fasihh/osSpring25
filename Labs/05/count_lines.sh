if [[ $# -ne 1 ]]; then
	echo "usage: ./count_lines.sh <filename>"
	exit 1
fi

cat $1 | wc -l
