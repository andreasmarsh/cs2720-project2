compile: SortedListDr

SortedListDr: SortedList.o Student.o SortedListDr.cpp
	g++ -Wall  -g -o SortedListDr SortedList.o Student.o SortedListDr.cpp

SortedList.o: SortedList.cpp SortedList.h
	g++ -Wall -c -std=c++14 -O0 -pedantic-errors -g SortedList.cpp

Student.o: Student.cpp Student.h
	g++ -Wall -c -std=c++14 -O0 -pedantic-errors -g Student.cpp

run:
	./SortedListDr

clean:
	/bin/rm *.o SortedListDr
