C_FILES=$(wildcard *.c)
O_FILES=$(patsubst %.c, %.o, $(C_FILES))

main: $(O_FILES)
	gcc $^ -o $@

%.o: %.c
	gcc -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(O_FILES) main
