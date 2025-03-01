if [[ $# -ne 2 ]]; then
    echo "usage: ./q05.sh <src> <dst>"
    exit 1
fi

src=$1
base_dst=$2

if [[ ! -d $src ]]; then
    echo "$src does not exist"
    exit 1
fi

dst="${base_dst}/backup_$(date +"%Y-%m-%d")"
mkdir -p "$dst"

cp -r "$src"/* "$dst"

file_count=$(find "$src" -type f | wc -l)
dir_count=$(find "$src" -type d | wc -l)

echo "backup successful"
echo "backedup-files=$file_count"
echo "backedup-dirs=$dir_count"
echo "backup-location=$dst"

