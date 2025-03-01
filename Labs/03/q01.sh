if [[ $# -ne 2 ]]; then
	echo "failed"
	exit 1
fi

echo $(($1 * $2))
