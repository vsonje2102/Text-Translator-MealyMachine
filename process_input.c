#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>
#include "state_machine.h"
#include "process_input.h"

void process_file_input(int flag,const char *input_filename, const char *output_filename) {
	setlocale(LC_ALL, "en_US.UTF-8");

	printf("Opening input file: %s\n", input_filename);
	FILE *input_file = fopen(input_filename, "r, ccs=UTF-8");  
	if (input_file == NULL) {
		printf("Error: Unable to open input file '%s'.\n", input_filename);
		return;
	}

	printf("Opening output file: %s\n", output_filename);
	FILE *output_file = fopen(output_filename, "w, ccs=UTF-8");
	if (output_file == NULL) {
		printf("Error: Unable to open output file '%s'.\n", output_filename);
		fclose(input_file);
		return;
	}

	//printf("Starting to process input file character by character.\n");
	wchar_t ch = fgetwc(input_file);  
	int current_state ;
	if(flag==0){
		printf("Translating Hindi to English\n");
		current_state = 33;
	}
	else{
		printf("Translating English to Hindi\n");
		current_state = 1;
	}
	int other_flag = 0;
	int old_unicode_ip = 0;
	int unicode_ip = 0;
	while (1) {
		//printf("\n------------------------------------\n");
		if (ch == (wchar_t)WEOF) {
			//printf("End of file reached.\n");
			break;
		}
		if(other_flag == 2){
			other_flag = 0;
			unicode_ip = old_unicode_ip;
		}
		else if (other_flag == 0){
			unicode_ip = (int)ch;
		}
		//printf("Current character: %lc (Unicode: %d), Current state: %d\n", ch, unicode_ip, current_state);

		State *state = &states[current_state];
		//printf("Searching for a transition in state %d.\n", current_state);

		Transition *transition = bsearch(&unicode_ip, state->transitions, state->no_of_transition, sizeof(Transition), compare_transitions);
		
		if(transition){
			//printf("Transition found for input %d.\n", unicode_ip);
			current_state = transition->next_state;
			// if output not NULL then write to output file
			if(wcscmp(transition->unicode_op, L"NULL") != 0){
				wchar_t *pos;
				if((pos = wcschr(transition->unicode_op, L'\n')) != NULL){
					*pos = L'\0';
				}
				fwprintf(output_file, L"%ls", transition->unicode_op);
			}
			
			if(other_flag == 1){
				other_flag = 2;
			}
			else{
				ch = fgetwc(input_file);
			}
		}
		else{
			//printf("No transition found for input %d.\n", unicode_ip);
			if((flag == 0 && current_state == 33) || (flag == 1 && current_state == 1)){
				fwprintf(output_file, L"%lc", ch);
				ch = fgetwc(input_file);
			}
			else{
				//printf("Attempting fallback transition for input %d.\n", unicode_ip);
				old_unicode_ip = unicode_ip;
				unicode_ip = 64976;
				other_flag = 1;
			}
		}

	
	}

	//printf("Closing input and output files.\n");
	fclose(input_file);
	fclose(output_file);
}
