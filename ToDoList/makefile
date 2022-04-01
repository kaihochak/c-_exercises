TODO=todo
MODULES=todo.o ToDoList.o ioutil.o

CPPFLAGS=-ansi -pedantic-errors -Wall -Wconversion
GCOVFLAGS=-fprofile-arcs -ftest-coverage
GTFLAGS=-lgtest -lgtest_main

TESTING=test_ToDoList
GCOVFILE=ToDoList

$(TODO): $(MODULES)
	g++ $(GTFLAGS) $(MODULES) $(GCOVFLAGS) -o $(TODO)

$(TESTING): $(TESTING).o $(GCOVFILE).o
	g++ $(TESTING).o $(GCOVFILE).o $(GTFLAGS) $(GCOVFLAGS) -o $(TESTING)
	valgrind --tool=memcheck --leak-check=full $(TESTING)
	gcov $(GCOVFILE).cpp 2> /dev/null | grep -A 1 $(GCOVFILE).cpp		

clean:
	/bin/rm -f *~ *.o $(TODO) $(TESTING) *.gcda *.gcov *.gcno

all: clean $(TODO) $(TESTING)

todo.o: todo.cpp ToDoList.o ToDoList.h ioutil.h
	g++ $(CPPFLAGS) -c todo.cpp

ToDoList.o: ToDoList.cpp ToDoList.h
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c ToDoList.cpp

$(TESTING).o: test_ToDoList.cpp ToDoList.h
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c $(TESTING).cpp

ioutil.o: ioutil.cpp ioutil.h
	g++ $(CPPFLAGS)  -c ioutil.cpp 
