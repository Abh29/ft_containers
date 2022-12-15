CFLAGS =  -Werror -Wextra -Werror -std=c++98 -g
VALFLAGS= 	--vgdb=full \
			--leak-check=full \
			--show-leak-kinds=all\
			--track-origins=yes\
			--verbose
MAIN = test.cpp

all:
	c++ $(CFLAGS) $(MAIN)


test:
	c++ -g -std=c++98 $(MAIN)


gdb: test
	gdb ./a.out

valgrind:
	@valgrind $(VALFLAGS) ./a.out 