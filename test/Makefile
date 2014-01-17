CXX=g++-4.7
CXXFLAGS=-std=c++0x -I.. -I.
GTEST_LIBS=/usr/local/lib/libgtest.a /usr/local/lib/libgtest_main.a

all: test

test: test.cpp
	$(CXX) $(CXXFLAGS) -std=c++0x -o $@ $^ ${GTEST_LIBS} -lpthread 

