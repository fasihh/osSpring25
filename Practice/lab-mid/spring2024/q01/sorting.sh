nums=($@)
n=${#nums[@]}

for ((i=1; i < $n; ++i)); do
	for ((j=1;j < $n; ++j)); do
		if [[ ${nums[j]} -lt ${nums[j-1]} ]]; then
			temp=${nums[j]}
			nums[j]=${nums[j-1]}
			nums[j-1]=$temp
		fi
	done
done

echo ${nums[@]}
