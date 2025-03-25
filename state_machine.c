#include <stdio.h>
#include <stdlib.h>
#include "state_machine.h"

State *states = NULL;
int total_states = INIT_SIZE_STATES;

void initialize_states() {
	//printf("Initializing states with size: %d\n", INIT_SIZE_STATES);
	states = (State *)calloc(INIT_SIZE_STATES, sizeof(State));
	if (!states) {
		printf("Failed to allocate memory for states\n");
		exit(1);
	}
	printf("States initialized successfully\n");
}

void expand_states(int required_index) {
	//printf("Expanding states for required index: %d\n", required_index);
	int new_size = total_states;
	while (new_size <= required_index) {
		new_size *= 2;
	}
	//printf("New size after expansion: %d\n", new_size);

	State *new_states = (State *)realloc(states, new_size * sizeof(State));
	if (!new_states) {
		printf("Memory reallocation failed for states\n");
		return;
	}

	for (int i = total_states; i < new_size; i++) {
		new_states[i].no_of_transition = 0;
		new_states[i].total_size = 0;
		new_states[i].transitions = NULL;
	}

	states = new_states;
	total_states = new_size;
	//printf("States expanded successfully\n");
}

void free_states() {
	//printf("Freeing states\n");
	for (int i = 0; i < total_states; i++) {
		free(states[i].transitions);
	}
	free(states);
	//printf("States freed successfully\n");
}

void print_states() {
	printf("\n--- State Machine ---\n");
	for (int i = 0; i < total_states; i++) {
		printf("State %d: %d transitions\n", i, states[i].no_of_transition);
		
		for (int j = 0; j < states[i].no_of_transition; j++) {
			Transition *t = &states[i].transitions[j];
			printf("	- Transition %d -> Next State: %d, Input: %d, Output: %ls\n",
				   j, t->next_state, t->unicode_ip, t->unicode_op);
		}
	}
	printf("--- End of State Machine ---\n");
}

int compare_transitions(const void *a, const void *b) {
	int unicode_ip_a = *(int *)a;
	Transition *t2 = (Transition *)b;
	return unicode_ip_a - t2->unicode_ip;
}

void sort_states() {
	//printf("Sorting transitions within each state by unicode input\n");
	for (int i = 0; i < total_states; i++) {
		if (states[i].no_of_transition > 0) {
			qsort(states[i].transitions, states[i].no_of_transition, sizeof(Transition), compare_transitions);
		}
	}
	//printf("Sorting completed\n");
}
