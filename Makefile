CXX  = g++
CXXFLAGS = -Wall -g -std=c++2b -O0 -lgtest -lgtest_main

SRC_MACHINE_TEST = tests/machineTests
SRC_PROGRAM_TEST = tests/programTests
SRC_BRAINFSCK_TEST = tests/brainFsckTests
SRC = ${SRC_MACHINE_TEST} ${SRC_PROGRAM_TEST} ${SRC_BRAINFSCK_TEST}

build: 
	${CXX} ${CXXFLAGS} ${GTEST_CFLAGS} ${SRC_MACHINE_TEST}.cpp -o ${SRC_MACHINE_TEST}.o
	${CXX} ${CXXFLAGS} ${GTEST_CFLAGS} ${SRC_PROGRAM_TEST}.cpp -o ${SRC_PROGRAM_TEST}.o
	${CXX} ${CXXFLAGS} ${GTEST_CFLAGS} ${SRC_BRAINFSCK_TEST}.cpp -o ${SRC_BRAINFSCK_TEST}.o

test: build
	@echo "Compilation successful!"
	@./${SRC_MACHINE_TEST}.o
	@./${SRC_PROGRAM_TEST}.o
	@./${SRC_BRAINFSCK_TEST}.o
	@rm -r -f $(SRC:=.o)

clean: 
	@rm -r -f $(SRC:=.o)
