CXX ?= g++
CXXFLAGS ?= -Wall -Werror -pedantic -g --std=c++11 -fsanitize=address -fsanitize=undefined

.PHONY: clean
clean:
	rm -rvf *.exe *.o *.dSYM *.gch *.stackdump *.out
