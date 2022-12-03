CFLAGS =  -Werror -Wextra -Werror -std=c++98 -g
VALFLAGS= 	--vgdb=full \
			--leak-check=full \
			--show-leak-kinds=all\
			--track-origins=yes\
			--verbose

all:
	c++ $(CFLAGS) main.cpp


test:
	c++ -g -std=c++98 main.cpp


gdb: test
	gdb ./a.out

valgrind:
	@valgrind $(VALFLAGS) ./a.out 