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
	char current;   // current character we're reading
	int result = 0; // final result we'll return
	int first_digit = 0;  // first digit (10's place)
	int second_digit = 0;
  int current_digit;
	
	while((current = fgetc(file_stream)) != EOF) {
		if((current_digit = is_digit(current)) > 0) {
			if (!first_digit) {
				first_digit = 1;
				result += current_digit * 10;
			}
			second_digit = current_digit;
		}
		if(current == '\n') {
			result += second_digit;
			first_digit = 0;
			second_digit = 0;
		}
	}
	
		
	fclose(file_stream);
	printf("Part 1: %d\n", result);
	CLOCK_END
	return 0;
}

