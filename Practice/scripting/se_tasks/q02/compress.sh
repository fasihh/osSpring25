if [[ $# -lt 1 || $# -gt 2 ]]; then
	echo "usage: $0 <dir> [option]"
	exit 1
fi

dir=$1

extract() {
	tar -xzvf $dir.tar.gz
}

compress() {
	tar -czvf $dir.tar.gz $dir
}

view() {
	tar -tvf $dir.tar.gz
}

if [[ $# -eq 1 ]]; then
	compress
	exit 0
fi

for param in $@; do
	case $param in
		-c) compress ;;
		-x) extract ;;
		-v) view ;;
	esac
done

