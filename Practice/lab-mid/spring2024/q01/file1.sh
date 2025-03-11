lines=(
	"#include <stdio.h>"
	"#include <stdlib.h>"
	""
	"int main(int argc, char *argv[]) {"
	"    int n = argc - 1;"
	"    int arr[100] = {0};"
	""
	"    for (int i = 0; i < n; ++i)"
	"        arr[i] = atoi(argv[i+1]);"
	""
	"    for (int i = 1; i < n; ++i) {"
	"        for (int j = 1; j < n; ++j) {"
	"            if (arr[j] >= arr[j-1]) continue;"
	"            arr[j] ^= arr[j-1], arr[j-1] ^= arr[j], arr[j] ^= arr[j-1];"
	"        }"
	"    }"
	""
	"    for (int i = 0; i < n; ++i)"
	"        printf(\"%d \", arr[i]);"
	"    printf(\"\\n\");"
	""
	"    return 0;"
	"}"
	""
)

echo "" > sorting.c
for line in "${lines[@]}"; do
	echo "$line" >> sorting.c
done

bash file2.sh
