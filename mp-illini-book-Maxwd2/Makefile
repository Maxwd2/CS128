CXX=clang++
INCLUDES=-Iincludes/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++2a -g -fstandalone-debug

exec: bin/exec
tests: bin/tests

bin/exec: ./src/utilities.cc ./src/driver.cc ./src/illini_book.cc ./includes/illini_book.hpp ./includes/utilities.hpp
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) ./src/utilities.cc ./src/driver.cc ./src/illini_book.cc -o $@

bin/tests: ./tests/tests.cc obj/catch.o ./src/illini_book.cc ./includes/illini_book.hpp ./includes/utilities.hpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) ./tests/tests.cc obj/catch.o ./src/illini_book.cc -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -fr bin/* obj/*
