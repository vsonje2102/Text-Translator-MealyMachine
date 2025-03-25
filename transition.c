#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "state_machine.h"
#include "transition.h"

void add_transition(int state_index, int unicode_ip, int next_state, const wchar_t *unicode_op) {
    //printf("Adding transition - State: %d, Input: %d, Next State: %d, Output: %ls\n",state_index, unicode_ip, next_state, unicode_op);

    if (state_index >= total_states) {
        //printf("State index %d is greater than total states %d, expanding states\n", state_index, total_states);
        expand_states(state_index);
    }

    State *state = &states[state_index];

    if (state->transitions == NULL) {
        //printf("Initializing transitions for state %d\n", state_index);
        state->total_size = INIT_SIZE_TRANSITIONS;
        state->transitions = (Transition *)malloc(state->total_size * sizeof(Transition));
        if (!state->transitions) {
            printf("Memory allocation failed for transitions\n");
            exit(1);
        }
        state->no_of_transition = 0;
    }

    if (state->no_of_transition >= state->total_size) {
        //printf("State %d transitions array is full, expanding transitions\n", state_index);
        //printf("Old size was - %d transitions\n", state->total_size);
        int old_size = state->total_size;
        int new_size = old_size * 2;
        //printf("New Size should be %d\n", new_size);

        Transition *new_transitions = (Transition *)realloc(state->transitions, new_size * sizeof(Transition));
        if (!new_transitions) {
            printf("Memory reallocation failed for transitions in state %d\n", state_index);
            exit(1);
        }

        state->transitions = new_transitions;
        state->total_size = new_size;

        // Zero-initialize new memory to prevent garbage values
        memset(&state->transitions[old_size], 0, (new_size - old_size) * sizeof(Transition));
    }

    //printf("Adding transition at index %d for state %d\n", state->no_of_transition, state_index);
    state->transitions[state->no_of_transition].unicode_ip = unicode_ip;
    state->transitions[state->no_of_transition].next_state = next_state;

    // Ensure unicode_op is not NULL
    if (!unicode_op) {
        unicode_op = L"NULL";
    }

    size_t len = wcslen(unicode_op) + 1;
    state->transitions[state->no_of_transition].unicode_op = (wchar_t *)malloc(len * sizeof(wchar_t));
    if (!state->transitions[state->no_of_transition].unicode_op) {
        printf("Memory allocation failed for output string.\n");
        exit(1);
    }
    wcscpy(state->transitions[state->no_of_transition].unicode_op, unicode_op);

    state->no_of_transition++;  // ✅ Increment after adding transition
    //printf("%d",state->no_of_transition);
    //printf("Transition added successfully\n");
}
