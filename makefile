CXX = g++
CXX_OPTS = -O3 

EXE_SOLVER = ./bin/6dof.x
EXE_TESTS = ./bin/tests.x

SRCS_SOLVER = ./src/main.cpp ./src/Body.cpp
SRCS_TEST = ./tests/main.cpp ./src/Body.cpp

OBJS_SOLVER = $(SRCS_SOLVER:.cpp=.o)
OBJS_TEST = $(SRCS_TEST:.cpp=.o)

GTESTDIR = ./TPLs/gtest/gtest-1.7.0/
GTEST_LIB = $(GTESTDIR)/lib
GTEST_INCLUDES = $(GTESTDIR)/include

EIGENDIR = ./TPLs/eigen/eigen-3.2.4/
EIGEN_INCLUDES = $(EIGENDIR)

INCLUDES = -I$(GTEST_INCLUDES) -I$(EIGEN_INCLUDES) -I./src

CXXLIBS = -lstdc++
LCXXFLAGS = -L$(GTEST_LIB)

$(EXE_SOLVER): $(OBJS_SOLVER)
	$(CXX) $(LINK_OPTS) -o $(EXE_SOLVER) $(LCXXFLAGS) $(OBJS_SOLVER) $(CXXLIBS) 

$(EXE_TESTS): $(OBJS_TEST) $(GTEST_LIB)/libgtest.la
	$(CXX) $(LINK_OPTS) -o $(EXE_TESTS) $(LCXXFLAGS) $(OBJS_TEST) $(CXXLIBS) -lgtest -lpthread

$(GTEST_LIB)/libgtest.la:
	@orig=$$PWD;\
	cd $$PWD/$(GTESTDIR);\
	./configure;\
	$(MAKE)

ROOT = $$PWD

all: $(EXE_SOLVER) $(EXE_TESTS) 

.cpp.o:
	$(CXX) -c $< $(CXX_OPTS) $(INCLUDES) -o $@

clean:
	rm $(OBJS_SOLVER); \
	rm $(OBJS_TEST); \
	rm $(EXE_SOLVER); \
	rm $(EXE_TESTS); \
	rm Make.depend

Make.depend:
	$(CXX) -MM $(INCLUDES) $(SRCS_SOLVER) $(SRCS_TESTS) > Make.depend

include Make.depend

