#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// benchmarking macros
#define CLOCK_INIT clock_t start_time, end_time;
#define CLOCK_START start_time = clock();
#define CLOCK_END end_time = clock(); printf("Executed in %.6f ms\n", (float)(end_time - start_time)/CLOCKS_PER_SEC*1000);

/* Determine if a character is a digit. Return that character
 * as an integer if so, otherwise return -1 */
int is_digit(char chr) {
	int res = chr - '0';
	if(res <= 9) {
		return res;
	}
	return -1;
}

int main(int argc, char *argv[]) {
	CLOCK_INIT

	char* datafile = "inputs/01";
	FILE *file_stream = fopen(datafile, "r");
	if (file_stream == NULL) {
		printf("Error: could not open file %s: %s.\n", datafile, strerror(errno));
		exit(-1);
	}

	CLOCK_START
	char current_chr;   // current character we're reading
	int result = 0; // final result we'll return
	int first_digit = 0;  // flag to indicate that we've found the first digit in a line
	int second_digit;
	int current_digit;
	
	// read every byte in the file
	while((current_chr = fgetc(file_stream)) != EOF) {
		if((current_digit = is_digit(current_chr)) > 0) {
			// if we haven't yet found the first digit in a line, set the first_digit
			// flag to indicate that we have, and add 10 times that digit to the result
			if (!first_digit) {
				first_digit = 1;
				result += current_digit * 10;
			}
			// set the second digit to the current digit regardless; we'll only add it
			// to the result once we know it's the last digit in the line. This also
			// covers the case where a line has only one digit, e.g. "se7en" should yield 77.
			second_digit = current_digit;
		}
		// if we're at the end of a line, add the second digit, and reset the 
		// flag to indicate we haven't found the first digit
		if(current_chr == '\n') {
			result += second_digit;
			first_digit = 0;
		}
	}
	
		
	CLOCK_END
	fclose(file_stream);
	printf("Part 1: %d\n", result);
	return 0;
}

