CC = gcc

MAIN_OBJ = main.o state_machine.o transition.o process_file.o process_input.o

all: main

main: $(MAIN_OBJ)
	$(CC)  -o main $(MAIN_OBJ)


main.o: main.c state_machine.h process_file.h process_input.h
	$(CC)  -c main.c

state_machine.o: state_machine.c state_machine.h
	$(CC)  -c state_machine.c

transition.o: transition.c state_machine.h transition.h
	$(CC)  -c transition.c

process_file.o: process_file.c state_machine.h transition.h process_file.h
	$(CC)  -c process_file.c

process_input.o: process_input.c state_machine.h process_input.h
	$(CC)  -c process_input.c


clean:
	rm -f *.o main notify
