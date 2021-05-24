include Makefile.variable

LIB_NAME = main

CXX = ccache g++ -std=c++2a
GCOV = gcov
GCOVR = gcovr

COV_FLAGS = -lgcov -coverage
GCOV_FLAGS = -r . --html --html-details
DEBUG_FLAGS = -Wall -Wextra -pedantic -g 
RELEASE_FLAGS = -O2 -s -DNDEBUG -flto -march=native

SRC_DIR = src
TST_DIR = test
OUT_DIR = build
COV_DIR = coverage
LIB_DIR = lib

SRCS = $(shell find $(SRC_DIR) -name '*.cc')
TST_SRCS = $(shell find $(TST_DIR) -name '*.cc' ; find $(SRC_DIR) -name '*.cc' ! -name 'main.cc')
TST_LIBS = $(TST_DIR)/catch_amalgamated.cpp

.PHONY: run clean valgrind test coverage format gdb

$(LIB_NAME):
	mkdir -p $(OUT_DIR)
	$(CXX) $(RELEASE_FLAGS) $(SRCS) -I. -o $(OUT_DIR)/$(LIB_NAME)
	rm -f *.o

debug: 
	mkdir -p $(OUT_DIR)
	$(CXX) $(DEBUG_FLAGS) $(SRCS) -I. -o $(OUT_DIR)/$(LIB_NAME)
	rm -f *.o

run: $(LIB_NAME)
	./build/main

runDebug: debug
	./build/main

analyze:
	clang++ -std=c++20 --analyze -Xanalyzer -analyzer-output=text $(SRCS)

unit_test_src: 
	$(CXX) -c $(TST_LIBS) 
	ar -rcs $(OUT_DIR)/catch.a *.o
	rm -f *.o
	$(CXX) $(DEBUG_FLAGS) $(TST_SRCS) $(OUT_DIR)/catch.a -L$(OUT_DIR) -o $(OUT_DIR)/unit_test_src -I$(SRC_DIR) 
	mkdir -p $(COV_DIR)

test: unit_test_src
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./$(OUT_DIR)/unit_test_src

valgrind:  debug
	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./$(OUT_DIR)/$(LIB_NAME) 

valgrind-v: debug
	valgrind --tool=memcheck -v --leak-check=full --show-reachable=yes --track-origins=yes ./$(OUT_DIR)/$(LIB_NAME)

callgrind: debug
	rm -f $(OUT_DIR)/callgrind.out.*
	valgrind --tool=callgrind ./$(OUT_DIR)/$(LIB_NAME) 
	mv callgrind.out.* build/
	kcachegrind $(OUT_DIR)/callgrind.out.*
	
format:
	clang-format  -i $(shell find . -name '*.cc') $(shell find . -name '*.hpp' ! -name 'catch_amalgamated.hpp') -style=file

clean:
	-rm -rf $(OUT_DIR) $(COV_DIR) 

gdb: debug
	gdb ./$(OUT_DIR)/$(LIB_NAME) -tui

docker: $(LIB_NAME)
	docker build . -t game


### EXPERIMENTS
# ex1: 
# 	mkdir -p $(OUT_DIR)
# 	$(CXX) $(RELEASE_FLAGS) $(SRCS) -I. -o $(OUT_DIR)/$(LIB_NAME) 
# 	rm -f *.
# 	./$(OUT_DIR)/$(LIB_NAME)