CC		?= gcc
CCFLAGS 	?= -Wall -Werror -Wextra -pedantic

EXECUTABLE	?= colouring

colouring: colouring.c
	$(CC) $(CCFLAGS) $? -o $(EXECUTABLE)

.PHONY: clean
clean:
	rm -rvf *.exe *.o *.dSYM *.gch *.stackdump *.out $(EXECUTABLE)

rebuild: clean colouring
