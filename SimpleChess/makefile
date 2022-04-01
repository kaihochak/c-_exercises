GAME=game
MODULES=game.o Board.o Piece.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o ioutil.o

TESTING_B=test_Board
TEST_MOD_B=test_Board.o Board.o Piece.o Pawn.o 

TESTING_P=test_Piece
TEST_MOD_P=test_Piece.o Board.o Piece.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o

CPPFLAGS=-ansi -pedantic-errors -Wall -Wconversion
GCOVFLAGS=-fprofile-arcs -ftest-coverage
GTFLAGS=-lgtest -lgtest_main

$(GAME): $(MODULES)
	g++ $(GTFLAGS) $(MODULES) $(GCOVFLAGS) -o $(GAME)

#	valgrind --tool=memcheck --leak-check=full 

$(TESTING_B): $(TEST_MOD_B)
	g++ $(TEST_MOD_B) $(GTFLAGS) $(GCOVFLAGS) -o $(TESTING_B)
	$(TESTING_B)
	gcov Board.cpp 2> /dev/null | grep -A 1 Board.cpp		

$(TESTING_P): $(TEST_MOD_P)
	g++ $(TEST_MOD_P) $(GTFLAGS) $(GCOVFLAGS) -o $(TESTING_P)
	$(TESTING_P)
	gcov Piece.cpp 2> /dev/null | grep -A 1 Piece.cpp
	gcov Pawn.cpp 2> /dev/null | grep -A 1 Pawn.cpp
	gcov Rook.cpp 2> /dev/null | grep -A 1 Rook.cpp
	gcov Knight.cpp 2> /dev/null | grep -A 1 Knight.cpp
	gcov Bishop.cpp 2> /dev/null | grep -A 1 Bishop.cpp
	gcov Queen.cpp 2> /dev/null | grep -A 1 Queen.cpp
	gcov King.cpp 2> /dev/null | grep -A 1 King.cpp

clean:
	/bin/rm -f *~ *.o $(GAME) $(TESTING_B) $(TESTING_P) *.gcda *.gcov *.gcno

all: clean $(GAME) $(TESTING_B) $(TESTING_P) 
	
game.o: game.cpp Board.o Board.h Piece.o Piece.h ioutil.h
	g++ $(CPPFLAGS) -c game.cpp

Board.o: Board.cpp Board.h
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c Board.cpp

Piece.o: Piece.cpp Piece.h
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c Piece.cpp

Pawn.o: Pawn.cpp Pawn.h 
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c Pawn.cpp

Rook.o: Rook.cpp Rook.h 
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c Rook.cpp

Knight.o: Knight.cpp Knight.h 
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c Knight.cpp

Bishop.o: Bishop.cpp Bishop.h 
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c Bishop.cpp

Queen.o: Queen.cpp Queen.h 
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c Queen.cpp

King.o: King.cpp King.h 
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c King.cpp

$(TESTING_B).o: test_Board.cpp Board.h
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c $(TESTING_B).cpp

$(TESTING_P).o: test_Piece.cpp Piece.h Board.h
	g++ $(CPPFLAGS) $(GCOVFLAGS) -c $(TESTING_P).cpp

ioutil.o: ioutil.cpp ioutil.h
	g++ $(CPPFLAGS)  -c ioutil.cpp 
