// Compile me using: gcc -m64 -static -fno-stack-protector -o vulnOut vuln.c 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read_input(char *ptr, const char *filename);

void secretFunction()
{
	printf("Congratulations!\n");
	printf("You have entered in the secret function!\n");
	exit(0);
}

void vuln(char *filename)
{
	char buffer[20];
	read_input(buffer, filename);
	printf("You entered: %s\n", buffer);	
}

int main(int argc, char **argv)
{
	if(argc != 2) {
		fprintf(stderr, "Error: need a command-line argument\n");
		return 1;
	}

	vuln(argv[1]);

	return 0;
}

void read_input_with_limit(char *ptr, const char *filename, size_t limit) {
	size_t left_to_read = limit;
	FILE* file = fopen(filename, "rb");
	if (file == NULL) {
		perror("Error opening input file");
		exit(1);
	}

	while (!feof(file) && left_to_read > 0) {
		const size_t elements_to_read = left_to_read > 0x400 ? 0x400 : left_to_read;

		const size_t elements_read = fread(ptr, sizeof(char), elements_to_read, file);
		if (ferror(file)) {
			perror("Error reading input file");
			exit(1);
		}

		left_to_read -= elements_read;
		ptr += elements_read;
	}

	fclose(file);
}

void read_input(char *ptr, const char *filename) {
	read_input_with_limit(ptr, filename, 0xffffffffffffffff);
}


