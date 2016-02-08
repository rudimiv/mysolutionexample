obj = tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o task.o module.o solution.o greedy_alghorithm.o main.o
CXX = g++

all: $(obj)
	g++ -o prog $(obj)

main.o: main.cpp
	g++ -c -o main.o main.cpp

tinystr.o: tinyxml/tinystr.cpp
	g++  $(options) -c -o tinystr.o tinyxml/tinystr.cpp

tinyxml.o: tinyxml/tinyxml.cpp
	g++  $(options) -c -o tinyxml.o tinyxml/tinyxml.cpp

tinyxmlerror.o: tinyxml/tinyxmlerror.cpp
	g++  $(options) -c -o tinyxmlerror.o tinyxml/tinyxmlerror.cpp

tinyxmlparser.o: tinyxml/tinyxmlparser.cpp
	g++  $(options) -c -o tinyxmlparser.o tinyxml/tinyxmlparser.cpp

task.o: task.cpp
	g++  $(options) -c -o task.o task.cpp

module.o: module.h	
	g++  $(options) -c -o module.o module.cpp

solution.o: solution.cpp solution.h	
	g++  $(options) -c -o solution.o solution.cpp

greedy_alghorithm.o: greedy_alghorithm.cpp greedy_alghorithm.h	
	g++  $(options) -c -o greedy_alghorithm.o greedy_alghorithm.cpp


clean:
	rm *.o

