CXXFLAGS = -std=c++0x
CXX=g++

all: imentor

imentor: imentor.o
	$(CXX) $(CXXFLAGS) -o imentor imentor.o -I/usr/include/cppconn -L/usr/lib -lmysqlcppconn
imentor.o: imentor.cc
	$(CXX) $(CXXFLAGS) -c imentor.cc

clean:
	rm -f imentor *.o

.PHONY: all clean
