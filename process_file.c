#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include "state_machine.h"
#include "transition.h"
#include "process_file.h"

#define SIZE 512

void process_file(const char *csv_file) {
	//printf("Processing file: %s\n", csv_file);
	FILE *file = fopen(csv_file, "r");
	if (!file) {
		printf("Failed to open file: %s\n", csv_file);
		return;
	}

	wchar_t line[SIZE];
	while (fgetws(line, SIZE, file)) {
		//printf("Read line: %ls\n", line);
		wchar_t *state_ptr;
		wchar_t *curr_state = wcstok(line, L",", &state_ptr);
		wchar_t *ip = wcstok(NULL, L",", &state_ptr);
		wchar_t *next_state = wcstok(NULL, L",", &state_ptr);
		wchar_t *op = wcstok(NULL, L",", &state_ptr);

		if (!curr_state || !ip || !next_state || !op) {
			//printf("Error parsing line: %ls\n", line);
			continue;
		}
		//printf("DOne parsing\n");

		int state_index = (int)wcstol(curr_state, NULL, 10);
		int next_state_index = (int)wcstol(next_state, NULL, 10);
		int unicode_ip = (int)ip[0];  // Get the Unicode number of the first character of the IP string
		
		//printf("Parsed values - State: %d, Input: %d, Next State: %d, Output: %ls\n", state_index, unicode_ip, next_state_index, op);

		add_transition(state_index, unicode_ip, next_state_index, op);
	}

	fclose(file);
	//printf("Finished processing file: %s\n", csv_file);
}

