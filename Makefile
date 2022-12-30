CFLAGS =  -Werror -Wextra -Werror -std=c++98 -g
VALFLAGS= 	--vgdb=full \
			--leak-check=full \
			--show-leak-kinds=all\
			--track-origins=yes\
			--verbose

MAIN = main.cpp

all:
	c++ $(CFLAGS) $(MAIN)

test:
	cmake ./tester/CMakeLists.txt -B ./tester
	make -C ./tester all
	./tester/test

clean:
	make -C ./tester clean
	rm -f cmake_install.cmake
	rm -f ./tester/cmake_install.cmake
	rm -f ./tester/CMakeCache.txt
	rm -f ./tester/Makefile
	rm -rf ./tester/CMakeFiles
	rm -rf ./tester/maps_output
	rm -rf ./tester/sets_output
	rm -rf ./tester/stacks_output
	rm -rf ./tester/vectors_output
	rm -f a.out


gdb: test
	gdb ./a.out

valgrind:
	@valgrind $(VALFLAGS) ./a.out

profile:
	c++ $(CFLAGS) -O0 -pg $(MAIN)

profile_png:
	gprof ./a.out gmon.out | gprof2dot -w -s | dot -Gdpi=200 -Tpng -o output.png
