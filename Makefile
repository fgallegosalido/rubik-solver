SHELL = /bin/bash

BIN = bin
INC = include
OBJ = obj
SRC = source
TEST = tests

CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -pedantic -I$(INC)

EXEC = $(BIN)/main
TESTS = $(BIN)/unit_tests $(BIN)/debug
DEPS = $(INC)/cube.hpp $(INC)/storage.hpp

.PRECIOUS: $(OBJ)/%.o

.PHONY: all
all: $(EXEC) $(TESTS)

$(EXEC): $(OBJ)/main.o $(OBJ)/cube.o
	$(CXX) $^ -o $@

$(OBJ)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: test
test: CXXFLAGS += -g
test: $(TESTS)

$(BIN)/%: $(OBJ)/%.o $(OBJ)/cube.o
	$(CXX) $^ -o $@

$(OBJ)/%.o: $(TEST)/%.cpp $(DEPS)
	$(CXX) -c $(CXXFLAGS) $< -o $@

.PHONY: exec
exec: $(EXEC)
	./$(EXEC)

.PHONY: exec_tests
exec_tests: test
	./$(BIN)/unit_tests

.PHONY: exec_debug
exec_debug: test
	./$(BIN)/debug

.PHONY: clean
clean:
	-rm $(OBJ)/* 2> /dev/null

.PHONY: mrproper
mrproper: clean
	-rm $(BIN)/* 2> /dev/null
