CXX  = g++
CXXFLAGS = -Wall -g -std=c++2b -O0 -lgtest -lgtest_main

SRC_PARSER = awafsck.cpp
OBJ_PARSER = $(SRC_PARSER:.cpp=) 

build: 
	${CXX} ${CXXFLAGS} ${GTEST_CFLAGS} ${SRC_PARSER} -o ${OBJ_PARSER} 

clean: 
	@rm -r -f ${OBJ_PARSER}