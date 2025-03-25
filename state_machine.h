#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <wchar.h>

#define INIT_SIZE_STATES 36
#define INIT_SIZE_TRANSITIONS 4

typedef struct {
	int unicode_ip;
	int next_state;
	wchar_t *unicode_op;
} Transition;

typedef struct {
	int no_of_transition;
	int total_size;
	Transition *transitions;
} State;

extern State *states;
extern int total_states;

void initialize_states();
void expand_states(int required_index);
void free_states();
void print_states();
int compare_transitions(const void *a, const void *b);
void sort_states();

#endif
