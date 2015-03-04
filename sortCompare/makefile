sortTest: sortFunTest.o sortFun.o
	g++ -o sortTest sortFunTest.o sortFun.o

sortFunTest.o : sortFunTest.cpp
	g++ -c -g -o sortFunTest.o sortFunTest.cpp

sortFun.o : sortFun.h sortFun.cpp
	g++ -c -g -o sortFun.o sortFun.cpp

.PHONY: clean
clean:
	-rm *.o
	-rm sortTest
