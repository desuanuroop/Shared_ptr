all:
	g++ test.cpp -g -std=c++11 -Wall -Wextra -pedantic
	./a.out
v:
	g++ test.cpp -g -std=c++11 -Wall -Wextra -pedantic
	valgrind ./a.out
s:
	g++ SharedPtr_test.cpp -g -std=c++11 -Wall -Wextra -pedantic
	valgrind ./a.out
d:
	g++ demo.cpp -std=c++11
	./a.out
