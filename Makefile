CXX:=clang++
CXXFLAGS:= -std=c++14 -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
FILES= main.o generator.o

mainx: main.o generator.o
	$(CXX) -o simplepass.out main.o generator.o 
	
main.o generator.o : generator.hpp

clean:
	-rm -f a.out core *.o
