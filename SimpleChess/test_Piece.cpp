#include "iostream"
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <gtest/gtest.h>

class test_Piece: public testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

/* 
	tests for Pawn 
*/

TEST_F(test_Piece, test_Pawn_Constructor_getColour)
{  
    Pawn p1(BLACK);
   	Pawn p2(WHITE);

	// check if constructor makes the right colour
	// check also getColour()
	EXPECT_TRUE(p1.getColour() == BLACK);
	EXPECT_TRUE(p2.getColour() == WHITE);
}

TEST_F(test_Piece, test_Pawn_getSymbol)
{
	Pawn p1(BLACK);
	Pawn p2(WHITE);

	// check if constructor makes the right colour
	EXPECT_TRUE('p' == p1.getSymbol());
	EXPECT_TRUE('P' == p2.getSymbol());
}

TEST_F(test_Piece, test_Pawn_canMove_successful_emptyTo)
{
	Board b;
	PiecePtr p = new Pawn(BLACK);

	b.place(p, 5, 7);

	// check for empty "to" position
	EXPECT_TRUE( p->canMove(b, 5, 7, 6, 7));
}

TEST_F(test_Piece, test_Pawn_canMove_successful_Capturing)
{
	Board b;
	PiecePtr p1 = new Pawn(BLACK);
	PiecePtr p2 = new Pawn(WHITE);

	b.place(p1, 5, 6);
	b.place(p2, 6, 7);

	// capturing oppponent diagonally
	EXPECT_TRUE( p1->canMove(b, 5, 6, 6, 7));
}

TEST_F(test_Piece, test_Pawn_canMove_2steps)
{
	Board b;
	PiecePtr p1 = new Pawn(BLACK);

	b.place(p1, 0, 0);

	// Start with 2 steps
	EXPECT_TRUE( p1->canMove(b, 0, 0, 2, 0));
	// try another 2 steps
	p1->notifyMoved();
	EXPECT_FALSE( p1->canMove(b, 2, 0, 4, 0));
	EXPECT_TRUE( p1->canMove(b, 2, 0, 3, 0));
}

TEST_F(test_Piece, test_Pawn_canMove_unsuccessful_illegalSteps)
{
	Board b;
	PiecePtr p1 = new Pawn(BLACK);

	b.place(p1, 3, 5);

	EXPECT_FALSE( p1->canMove(b, 3, 5, 6, 5)); // 3 steps
	EXPECT_FALSE( p1->canMove(b, 3, 5, 4, 6)); // diagonal not capturing
	EXPECT_FALSE( p1->canMove(b, 3, 5, 5, 7)); // diagonal 
}


TEST_F(test_Piece, test_Pawn_canMove_forward)
{
	Board b;
	PiecePtr p1 = new Pawn(BLACK);
	PiecePtr p2 = new Pawn(WHITE);

	b.place(p1, 1, 0);
	b.place(p2, 6, 7);

	// check black piece
	EXPECT_TRUE( p1->canMove(b, 1, 0, 2, 0));
	EXPECT_FALSE( p1->canMove(b, 1, 0, 0, 0));
	// check white piece
	EXPECT_TRUE( p2->canMove(b, 6, 7, 5, 7));
	EXPECT_FALSE( p2->canMove(b, 6, 7, 7, 7));
}


TEST_F(test_Piece, test_Pawn_canMove_horizontal)
{
	Board b;
	PiecePtr p = new Pawn(WHITE);

	b.place(p, 3, 3);

	// moving horizontally
	EXPECT_FALSE( p->canMove(b, 3, 3, 3, 4));
	EXPECT_FALSE( p->canMove(b, 3, 3, 3, 2));
}

TEST_F(test_Piece, test_Pawn_canMove_unsuccessful_OccupiedTo)
{
	Board b;
	PiecePtr p1 = new Pawn(BLACK);
	PiecePtr p2 = new Pawn(BLACK);

	b.place(p1, 5, 8);
	b.place(p2, 6, 8);

	// check for empty "to" position
	EXPECT_FALSE( p2->canMove(b, 5, 8, 6, 8));
}

/*
	tests for Rook	
*/

TEST_F(test_Piece, test_Rook_Constructor_getColour)
{  
    Rook p1(BLACK);
   	Rook p2(WHITE);

	// check if constructor makes the right colour
	// check also getColour()
	EXPECT_TRUE(p1.getColour() == BLACK);
	EXPECT_TRUE(p2.getColour() == WHITE);
}

TEST_F(test_Piece, test_Rook_getSymbol)
{
	Rook p1(BLACK);
	Rook p2(WHITE);

	// check if constructor makes the right colour
	EXPECT_TRUE('r' == p1.getSymbol());
	EXPECT_TRUE('R' == p2.getSymbol());
}

TEST_F(test_Piece, test_Rook_canMove_successful_empty)
{
	Board b;
	PiecePtr p = new Rook(BLACK);

	// check for empty "to" position
	EXPECT_TRUE( p->canMove(b, 0, 0, 1, 0));
	EXPECT_TRUE( p->canMove(b, 4, 0, 2, 0));
	EXPECT_TRUE( p->canMove(b, 5, 0, 7, 0));
	EXPECT_TRUE( p->canMove(b, 0, 3, 0, 2));
	EXPECT_TRUE( p->canMove(b, 0, 4, 0, 3));
	EXPECT_TRUE( p->canMove(b, 0, 5, 0, 4));
}

TEST_F(test_Piece, test_Rook_canMove_successful_Capturing)
{
	Board b;
	PiecePtr p1 = new Rook(BLACK);
	PiecePtr p2 = new Pawn(WHITE);

	b.place(p2, 6, 7);

	// capturing oppponent
	EXPECT_TRUE( p1->canMove(b, 6, 0, 6, 7));
	EXPECT_TRUE( p1->canMove(b, 0, 7, 6, 7));
}

TEST_F(test_Piece, test_Rook_canMove_unsuccessful_occupiedTo)
{
	Board b;
	PiecePtr p1 = new Rook(WHITE);
	PiecePtr p2 = new Pawn(WHITE);

	b.place(p2, 6, 7);

	// occupied
	EXPECT_FALSE( p1->canMove(b, 6, 0, 6, 7));
	EXPECT_FALSE( p1->canMove(b, 0, 7, 6, 7));
}

TEST_F(test_Piece, test_Rook_canMove_unsuccessful_notClearPath)
{
	Board b;
	PiecePtr p1 = new Rook(WHITE);
	PiecePtr p2 = new Pawn(WHITE);

	b.place(p2, 6, 5);

	// path not clear
	EXPECT_FALSE( p1->canMove(b, 6, 2, 6, 7));
	EXPECT_FALSE( p1->canMove(b, 0, 5, 7, 5));
}

TEST_F(test_Piece, test_Rook_canMove_unsuccessful_illegalMoves)
{
	Board b;
	PiecePtr p1 = new Rook(BLACK);

	// diagonal move
	EXPECT_FALSE( p1->canMove(b, 1, 1, 3, 3));
	EXPECT_FALSE( p1->canMove(b, 5, 5, 3, 3));
	EXPECT_FALSE( p1->canMove(b, 2, 7, 7, 2));
	EXPECT_FALSE( p1->canMove(b, 5, 0, 0, 5));

	// random
	EXPECT_FALSE( p1->canMove(b, 1, 1, 2, 6));
	EXPECT_FALSE( p1->canMove(b, 5, 5, 7, 0));
	EXPECT_FALSE( p1->canMove(b, 2, 7, 3, 5));
	EXPECT_FALSE( p1->canMove(b, 5, 0, 3, 5));
}

/*
	tests for Knight	
*/

TEST_F(test_Piece, test_Knight_Constructor_getColour)
{  
    Knight p1(BLACK);
   	Knight p2(WHITE);

	// check if constructor makes the right colour
	// check also getColour()
	EXPECT_TRUE(p1.getColour() == BLACK);
	EXPECT_TRUE(p2.getColour() == WHITE);
}

TEST_F(test_Piece, test_Knight_getSymbol)
{
	Knight p1(BLACK);
	Knight p2(WHITE);

	// check if constructor makes the right colour
	EXPECT_TRUE('n' == p1.getSymbol());
	EXPECT_TRUE('N' == p2.getSymbol());
}

TEST_F(test_Piece, test_Knight_canMove_successful_empty)
{
	Board b;
	PiecePtr p = new Knight(BLACK);

	// check for empty "to" position
	EXPECT_TRUE( p->canMove(b, 1, 2, 3, 3));
	EXPECT_TRUE( p->canMove(b, 1, 2, 3, 1));
	EXPECT_TRUE( p->canMove(b, 3, 4, 1, 3));
	EXPECT_TRUE( p->canMove(b, 3, 4, 5, 5));
	EXPECT_TRUE( p->canMove(b, 5, 6, 4, 4));
	EXPECT_TRUE( p->canMove(b, 7, 0, 6, 2));
}

TEST_F(test_Piece, test_Knight_canMove_successful_capturing)
{
	Board b;
	PiecePtr p1 = new Knight(BLACK);
	PiecePtr p2 = new Knight(BLACK);
	PiecePtr p3 = new Knight(WHITE);	
	PiecePtr p4 = new Knight(WHITE);

	// BLACK captures WHITE
	b.place(p3, 3, 3);
	b.place(p4, 3, 1);
	EXPECT_TRUE( p1->canMove(b, 1, 2, 3, 3));
	EXPECT_TRUE( p2->canMove(b, 1, 2, 3, 1));

	// WHITE captures BLACK
	b.place(p1, 5, 5);
	b.place(p2, 4, 4);
	EXPECT_TRUE( p3->canMove(b, 3, 4, 5, 5));
	EXPECT_TRUE( p4->canMove(b, 5, 6, 4, 4));
}

TEST_F(test_Piece, test_Knight_canMove_unsuccessful_occupied)
{
	Board b;
	PiecePtr p1 = new Knight(BLACK);
	PiecePtr p2 = new Knight(BLACK);
	PiecePtr p3 = new Knight(BLACK);	
	PiecePtr p4 = new Knight(BLACK);

	// BLACK captures WHITE
	b.place(p3, 3, 3);
	b.place(p4, 3, 1);
	EXPECT_FALSE( p1->canMove(b, 1, 2, 3, 3));
	EXPECT_FALSE( p2->canMove(b, 1, 2, 3, 1));

	// WHITE captures BLACK
	b.place(p1, 5, 5);
	b.place(p2, 4, 4);
	EXPECT_FALSE( p3->canMove(b, 3, 4, 5, 5));
	EXPECT_FALSE( p4->canMove(b, 5, 6, 4, 4));
}

/*
	tests for Bishop	
*/

TEST_F(test_Piece, test_Bishop_Constructor_getColour)
{  
    Bishop p1(BLACK);
   	Bishop p2(WHITE);

	// check if constructor makes the right colour
	// check also getColour()
	EXPECT_TRUE(p1.getColour() == BLACK);
	EXPECT_TRUE(p2.getColour() == WHITE);
}

TEST_F(test_Piece, test_Bishop_getSymbol)
{
	Bishop p1(BLACK);
	Bishop p2(WHITE);

	// check if constructor makes the right colour
	EXPECT_TRUE('b' == p1.getSymbol());
	EXPECT_TRUE('B' == p2.getSymbol());
}

TEST_F(test_Piece, test_Bishop_canMove_successful_empty)
{
	Board b;
	PiecePtr p = new Bishop(BLACK);

	// down and right
	EXPECT_TRUE( p->canMove(b, 0, 0, 1, 1));
	EXPECT_TRUE( p->canMove(b, 0, 0, 4, 4));
	EXPECT_TRUE( p->canMove(b, 0, 0, 7, 7));
	// up and left
	EXPECT_TRUE( p->canMove(b, 6, 6, 2, 2));
	EXPECT_TRUE( p->canMove(b, 5, 7, 2, 4));
	EXPECT_TRUE( p->canMove(b, 2, 5, 0, 3));
	// down and left
	EXPECT_TRUE( p->canMove(b, 4, 4, 7, 1));
	EXPECT_TRUE( p->canMove(b, 0, 7, 4, 3));
	EXPECT_TRUE( p->canMove(b, 5, 2, 6, 1));
	// down and right
	EXPECT_TRUE( p->canMove(b, 4, 2, 7, 5));
	EXPECT_TRUE( p->canMove(b, 0, 3, 4, 7));
	EXPECT_TRUE( p->canMove(b, 5, 1, 6, 2));
}

TEST_F(test_Piece, test_Bishop_canMove_successful_Capturing)
{
	Board b;
	PiecePtr p1 = new Bishop(BLACK);
	PiecePtr p2 = new Bishop(WHITE);

	// capturing oppponent
	b.place(p2, 4, 4);
	EXPECT_TRUE( p1->canMove(b, 2, 2, 4, 4));
	EXPECT_TRUE( p1->canMove(b, 7, 7, 4, 4));
	b.place(p1, 2, 7);
	EXPECT_TRUE( p2->canMove(b, 0, 5, 2, 7));
	EXPECT_TRUE( p2->canMove(b, 6, 3, 2, 7));
}

TEST_F(test_Piece, test_Bishop_canMove_unsuccessful_occupiedTo)
{
	Board b;
	PiecePtr p1 = new Bishop(WHITE);
	PiecePtr p2 = new Pawn(WHITE);
	PiecePtr p3 = new Pawn(WHITE);

	b.place(p2, 4, 4);
	b.place(p3, 2, 7);

	// occupied
	EXPECT_FALSE( p1->canMove(b, 6, 2, 4, 4));
	EXPECT_FALSE( p1->canMove(b, 4, 5, 2, 7));
}

TEST_F(test_Piece, test_Bishop_canMove_unsuccessful_notClearPath)
{
	Board b;
	PiecePtr p1 = new Bishop(WHITE);
	PiecePtr p2 = new Pawn(WHITE);
	PiecePtr p3 = new Pawn(BLACK);

	b.place(p2, 4, 4);
	b.place(p3, 2, 4);

	// path not clear
	EXPECT_FALSE( p1->canMove(b, 6, 2, 3, 5));
	EXPECT_FALSE( p1->canMove(b, 0, 2, 4, 6));
}

TEST_F(test_Piece, test_Bishop_canMove_unsuccessful_illegalMoves)
{
	Board b;
	PiecePtr p1 = new Bishop(BLACK);

	// horizontal move
	EXPECT_FALSE( p1->canMove(b, 1, 1, 1, 3));
	EXPECT_FALSE( p1->canMove(b, 5, 5, 5, 3));

	// vertical move
	EXPECT_FALSE( p1->canMove(b, 3, 7, 7, 7));
	EXPECT_FALSE( p1->canMove(b, 5, 5, 0, 5));

	// random
	EXPECT_FALSE( p1->canMove(b, 1, 1, 2, 6));
	EXPECT_FALSE( p1->canMove(b, 5, 5, 7, 0));
	EXPECT_FALSE( p1->canMove(b, 5, 0, 3, 5));
}

/*
	tests for Queen
*/

TEST_F(test_Piece, test_Queen_Constructor_getColour)
{  
    Queen p1(BLACK);
   	Queen p2(WHITE);

	// check if constructor makes the right colour
	// check also getColour()
	EXPECT_TRUE(p1.getColour() == BLACK);
	EXPECT_TRUE(p2.getColour() == WHITE);
}

TEST_F(test_Piece, test_Queen_getSymbol)
{
	Queen p1(BLACK);
	Queen p2(WHITE);

	// check if constructor makes the right colour
	EXPECT_TRUE('q' == p1.getSymbol());
	EXPECT_TRUE('Q' == p2.getSymbol());
}

TEST_F(test_Piece, test_Queen_canMove_successful_empty)
{
	Board b;
	PiecePtr p = new Queen(BLACK);

	// Diagonal 
	// down and right
	EXPECT_TRUE( p->canMove(b, 0, 0, 1, 1));
	EXPECT_TRUE( p->canMove(b, 0, 0, 7, 7));
	// up and left
	EXPECT_TRUE( p->canMove(b, 6, 6, 2, 2));
	EXPECT_TRUE( p->canMove(b, 2, 5, 0, 3));
	// down and left
	EXPECT_TRUE( p->canMove(b, 4, 4, 7, 1));
	EXPECT_TRUE( p->canMove(b, 5, 2, 6, 1));
	// down and right
	EXPECT_TRUE( p->canMove(b, 4, 2, 7, 5));
	EXPECT_TRUE( p->canMove(b, 5, 1, 6, 2));

	// Horizontal and Vertical
	EXPECT_TRUE( p->canMove(b, 0, 0, 1, 0));
	EXPECT_TRUE( p->canMove(b, 4, 0, 2, 0));
	EXPECT_TRUE( p->canMove(b, 5, 0, 7, 0));
	EXPECT_TRUE( p->canMove(b, 0, 3, 0, 2));
	EXPECT_TRUE( p->canMove(b, 0, 4, 0, 3));
	EXPECT_TRUE( p->canMove(b, 0, 5, 0, 4));
}

TEST_F(test_Piece, test_Queen_canMove_successful_Capturing)
{
	Board b;
	PiecePtr p1 = new Queen(BLACK);
	PiecePtr p2 = new Queen(WHITE);
	PiecePtr p3 = new Rook(WHITE);

	// Diagonal
	b.place(p2, 4, 4);
	EXPECT_TRUE( p1->canMove(b, 2, 2, 4, 4));
	EXPECT_TRUE( p1->canMove(b, 7, 7, 4, 4));
	b.place(p1, 2, 7);
	EXPECT_TRUE( p2->canMove(b, 0, 5, 2, 7));
	EXPECT_TRUE( p2->canMove(b, 6, 3, 2, 7));

	// Horizontal and Vertical
	b.place(p3, 6, 7);
	EXPECT_TRUE( p1->canMove(b, 6, 0, 6, 7));
	EXPECT_TRUE( p1->canMove(b, 3, 7, 6, 7));
}

TEST_F(test_Piece, test_Queen_canMove_unsuccessful_occupiedTo)
{
	Board b;
	PiecePtr p1 = new Queen(WHITE);
	PiecePtr p2 = new Pawn(WHITE);
	PiecePtr p3 = new Pawn(WHITE);
	PiecePtr p4 = new Rook(WHITE);

	// diagonal
	b.place(p2, 4, 4);
	b.place(p3, 2, 7);
	EXPECT_FALSE( p1->canMove(b, 6, 2, 4, 4));
	EXPECT_FALSE( p1->canMove(b, 4, 5, 2, 7));

	// vertical and horizontal
	b.place(p4, 6, 7);
	EXPECT_FALSE( p1->canMove(b, 6, 0, 6, 7));
	EXPECT_FALSE( p1->canMove(b, 0, 7, 6, 7));
}

TEST_F(test_Piece, test_Queen_canMove_unsuccessful_notClearPath)
{
	Board b;
	PiecePtr p1 = new Queen(WHITE);
	PiecePtr p2 = new Pawn(WHITE);
	PiecePtr p3 = new Pawn(WHITE);
	PiecePtr p4 = new Rook(WHITE);

	// diagonal
	b.place(p2, 4, 4);
	b.place(p3, 2, 4);
	EXPECT_FALSE( p1->canMove(b, 6, 2, 3, 5));
	EXPECT_FALSE( p1->canMove(b, 0, 2, 4, 6));

	// horizontal and vertical
	b.place(p4, 6, 5);
	EXPECT_FALSE( p1->canMove(b, 6, 2, 6, 7));
	EXPECT_FALSE( p1->canMove(b, 0, 5, 7, 5));
}

TEST_F(test_Piece, test_Queen_canMove_unsuccessful_illegalMoves)
{
	Board b;
	PiecePtr p1 = new Queen(BLACK);

	EXPECT_FALSE( p1->canMove(b, 1, 2, 3, 3));
	EXPECT_FALSE( p1->canMove(b, 1, 2, 3, 1));
	EXPECT_FALSE( p1->canMove(b, 3, 4, 1, 3));
	EXPECT_FALSE( p1->canMove(b, 3, 4, 5, 5));
	EXPECT_FALSE( p1->canMove(b, 1, 1, 2, 6));
	EXPECT_FALSE( p1->canMove(b, 5, 5, 7, 0));
	EXPECT_FALSE( p1->canMove(b, 5, 0, 3, 5));
}

/*
	tests for King
*/

TEST_F(test_Piece, test_King_Constructor_getColour)
{  
    King p1(BLACK);
   	King p2(WHITE);

	// check if constructor makes the right colour
	// check also getColour()
	EXPECT_TRUE(p1.getColour() == BLACK);
	EXPECT_TRUE(p2.getColour() == WHITE);
}

TEST_F(test_Piece, test_King_getSymbol)
{
	King p1(BLACK);
	King p2(WHITE);

	// check if constructor makes the right colour
	EXPECT_TRUE('k' == p1.getSymbol());
	EXPECT_TRUE('K' == p2.getSymbol());
}

TEST_F(test_Piece, test_King_canMove_successful_empty)
{
	Board b;
	PiecePtr p = new King(BLACK);

	// Diagonal 
	// down and right
	EXPECT_TRUE( p->canMove(b, 0, 0, 1, 1));
	EXPECT_TRUE( p->canMove(b, 6, 6, 7, 7));
	// up and left
	EXPECT_TRUE( p->canMove(b, 6, 6, 5, 5));
	EXPECT_TRUE( p->canMove(b, 2, 5, 1, 4));
	// down and left
	EXPECT_TRUE( p->canMove(b, 4, 4, 5, 3));
	EXPECT_TRUE( p->canMove(b, 5, 4, 6, 5));
	// down and right
	EXPECT_TRUE( p->canMove(b, 4, 2, 5, 3));
	EXPECT_TRUE( p->canMove(b, 5, 1, 6, 2));

	// Horizontal and Vertical
	EXPECT_TRUE( p->canMove(b, 0, 0, 1, 0));
	EXPECT_TRUE( p->canMove(b, 4, 0, 3, 0));
	EXPECT_TRUE( p->canMove(b, 5, 0, 4, 0));
	EXPECT_TRUE( p->canMove(b, 0, 3, 0, 2));
	EXPECT_TRUE( p->canMove(b, 0, 4, 0, 3));
	EXPECT_TRUE( p->canMove(b, 0, 5, 0, 4));
}

TEST_F(test_Piece, test_King_canMove_successful_Capturing)
{
	Board b;
	PiecePtr p1 = new King(BLACK);
	PiecePtr p2 = new King(WHITE);
	PiecePtr p3 = new Rook(WHITE);

	// Diagonal
	b.place(p2, 4, 4);
	EXPECT_TRUE( p1->canMove(b, 3, 3, 4, 4));
	EXPECT_TRUE( p1->canMove(b, 5, 5, 4, 4));
	b.place(p1, 2, 7);
	EXPECT_TRUE( p2->canMove(b, 1, 6, 2, 7));
	EXPECT_TRUE( p2->canMove(b, 3, 6, 2, 7));

	// Horizontal and Vertical
	b.place(p3, 6, 7);
	EXPECT_TRUE( p1->canMove(b, 6, 6, 6, 7));
	EXPECT_TRUE( p1->canMove(b, 5, 7, 6, 7));
}

TEST_F(test_Piece, test_King_canMove_unsuccessful_occupiedTo)
{
	Board b;
	PiecePtr p1 = new King(WHITE);
	PiecePtr p2 = new Pawn(WHITE);
	PiecePtr p3 = new Pawn(WHITE);
	PiecePtr p4 = new Rook(WHITE);

	// diagonal
	b.place(p2, 4, 4);
	b.place(p3, 2, 7);
	EXPECT_FALSE( p1->canMove(b, 5, 3, 4, 4));
	EXPECT_FALSE( p1->canMove(b, 3, 6, 2, 7));

	// vertical and horizontal
	b.place(p4, 6, 7);
	EXPECT_FALSE( p1->canMove(b, 6, 6, 6, 7));
	EXPECT_FALSE( p1->canMove(b, 7, 7, 6, 7));
}

TEST_F(test_Piece, test_King_canMove_unsuccessful_illegalSteps)
{
	Board b;
	PiecePtr p = new King(BLACK);

	// Diagonal 
	// down and right
	EXPECT_FALSE( p->canMove(b, 0, 0, 2, 2));
	EXPECT_FALSE( p->canMove(b, 0, 0, 7, 7));
	// up and left
	EXPECT_FALSE( p->canMove(b, 6, 6, 2, 2));
	EXPECT_FALSE( p->canMove(b, 2, 5, 0, 3));
	// down and left
	EXPECT_FALSE( p->canMove(b, 4, 4, 7, 1));
	EXPECT_FALSE( p->canMove(b, 5, 2, 7, 0));
	// down and right
	EXPECT_FALSE( p->canMove(b, 4, 2, 7, 5));
	EXPECT_FALSE( p->canMove(b, 5, 1, 7, 3));

	// Horizontal and Vertical
	EXPECT_FALSE( p->canMove(b, 0, 0, 3, 0));
	EXPECT_FALSE( p->canMove(b, 4, 0, 2, 0));
	EXPECT_FALSE( p->canMove(b, 5, 0, 7, 0));
	EXPECT_FALSE( p->canMove(b, 0, 5, 0, 2));
}

TEST_F(test_Piece, test_King_canMove_unsuccessful_illegalMoves)
{
	Board b;
	PiecePtr p1 = new King(BLACK);

	EXPECT_FALSE( p1->canMove(b, 1, 2, 3, 3));
	EXPECT_FALSE( p1->canMove(b, 1, 2, 3, 1));
	EXPECT_FALSE( p1->canMove(b, 3, 4, 1, 3));
	EXPECT_FALSE( p1->canMove(b, 3, 4, 5, 5));
	EXPECT_FALSE( p1->canMove(b, 1, 1, 2, 6));
	EXPECT_FALSE( p1->canMove(b, 5, 5, 7, 0));
	EXPECT_FALSE( p1->canMove(b, 5, 0, 3, 5));
}

