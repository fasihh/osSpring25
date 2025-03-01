if [[ $# -ne 1 ]]; then
	echo "usage: ./q04.sh <file/dir name>"
	exit 1
fi

if [[ ! -e $1 ]]; then
	echo "file/directory does not exist"
	exit 1
fi

stat -c "name=%n; size=%s; creator=%U; group=%G; perms=%A" $1
if [[ -d $1 ]]; then
	ls -l $1
fi
