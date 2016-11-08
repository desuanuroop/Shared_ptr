all:
	g++ test.cpp -g -std=c++11 -Wall -Wextra -pedantic
	./a.out
v:
	g++ test.cpp -g -std=c++11 -Wall -Wextra -pedantic
	valgrind ./a.out
