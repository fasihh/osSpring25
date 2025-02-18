#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int input_file, output_file;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;

    input_file = open("input.txt", O_RDONLY);
    if (input_file < 0) {
        printf("Error opening input file");
        return 1;
    }

    output_file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_file < 0) {
        printf("Error opening output file\n");
        close(input_file);
        return 1;
    }

    while ((bytes_read = read(input_file, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(output_file, buffer, bytes_read);
        if (bytes_written < 0) {
            printf("error writing to output file\n");
            close(input_file);
            close(output_file);
            return 1;
        }
    }

    if (bytes_read < 0) {
        printf("error reading from input file\n");
				return 1;
    }

    close(input_file);
    close(output_file);
    return 0;
}

