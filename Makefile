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
	make -C ./tester
	./tester/ft_container_tester

clean:
	make -C ./tester fclean


gdb: test
	gdb ./a.out

valgrind:
	@valgrind $(VALFLAGS) ./tester/ft_container_tester

profile:
	c++ $(CFLAGS) -O0 -pg $(MAIN)

profile_png:
	gprof ./a.out gmon.out | gprof2dot -w -s | dot -Gdpi=200 -Tpng -o output.png
