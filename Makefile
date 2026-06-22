CXX  = g++
CXXFLAGS = -Wall -g -std=c++2b -O0 -lgtest -lgtest_main

SRC_TEST = tests/machineTests.cpp
OBJ_TEST = $(SRC_TEST:.cpp=.o) 

build: 
	${CXX} ${CXXFLAGS} ${GTEST_CFLAGS} ${SRC_TEST} -o ${OBJ_TEST} 

test: build
	@echo "Compilation successful!"
	@./${OBJ_TEST}
	@rm -r -f ${OBJ_TEST}

clean: 
	@rm -r -f ${OBJ_TEST}