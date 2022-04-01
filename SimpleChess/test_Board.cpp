#include "iostream"
#include "Board.h"
#include "Pawn.h"
#include <gtest/gtest.h>

class test_Board: public testing::Test
{
protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(test_Board, test_DefaultConstructor)
{  
    Board b;
    stringstream output; 

    // expected result 
    stringstream emptyBoard; 
    char columns[] = "    0   1   2   3   4   5   6   7\n";
    char divider[] = "  +---+---+---+---+---+---+---+---+\n";
    char squares[] = " |   |   |   |   |   |   |   |   |\n";
    emptyBoard << columns << divider;
    for ( int i = 0; i < 8; i++ )
    {
        emptyBoard << i << squares << divider;
    }

    // test default constructor
    b.write(output); 
    EXPECT_STREQ(emptyBoard.str().c_str(), output.str().c_str());
}

TEST_F(test_Board, test_place_empty)
{
    Board b;
    PiecePtr p = new Pawn(BLACK);

    // check if it is empty
    EXPECT_TRUE(b.place(p, 2, 3));
}

TEST_F(test_Board, test_place_notEmpty)
{
    Board b;
    PiecePtr p1 = new Pawn(BLACK);
    PiecePtr p2 = new Pawn(BLACK);

    // check if it is empty
    b.place(p1, 2, 3);
    EXPECT_FALSE(b.place(p2, 2, 3));
}

TEST_F(test_Board, test_remove_thereIs)
{
    Board b;
    PiecePtr p = new Pawn(BLACK);
 
    // check if there is a piece
    b.place(p, 2, 3);
    EXPECT_TRUE(b.remove(2, 3));
}

TEST_F(test_Board, test_remove_thereIsNot)
{
    Board b;
 
    // check if there is a piece
    EXPECT_FALSE(b.remove(2, 3));
}

TEST_F(test_Board, test_move_successful_yesFrom_noTo)
{
    Board b;
    PiecePtr p = new Pawn(BLACK);

    // check if it is successfully moved
    b.place(p, 2, 3); // there is a piece at (2,3)
    EXPECT_TRUE(b.move(BLACK, 2, 3, 3, 3));
}

TEST_F(test_Board, test_move_unsuccessful_noFrom)
{
    Board b;

    // test if there is nothing to move from
    EXPECT_FALSE(b.move(BLACK, 2, 3, 3, 2));
}

TEST_F(test_Board, test_move_unsuccessful_yesFrom_yesTo)
{
    Board b;
    PiecePtr p1 = new Pawn(BLACK);
    PiecePtr p2 = new Pawn(BLACK);

    // check if it is successfully moved
    b.place(p1, 2, 3); // there is a piece at (2,3)
    b.place(p2, 3, 2); // but there is also a piece at (3,2)
    EXPECT_FALSE(b.move(BLACK, 2, 3, 3, 2));
}

TEST_F(test_Board, test_remove_unsuccessful_opponentPiece)
{
    Board b;
    PiecePtr p = new Pawn(BLACK);

    b.place(p, 2, 3);

    // check if there is a piece
    EXPECT_FALSE(b.move(WHITE, 2, 3, 3, 2));
}

TEST_F(test_Board, test_CopyConstructor)
{
    Board b;
    PiecePtr p1 = new Pawn(BLACK);
    PiecePtr p2 = new Pawn(BLACK);
    PiecePtr p3 = new Pawn(BLACK);
    b.place(p1, 4, 5);
    b.place(p2, 7, 6);
    b.place(p3, 1, 2);
    
    // check if it is successfully copied
    Board copy = b;
    // remove pieces on the original Board to make sure it's deep copying
    b.remove(4, 5);  
    b.remove(7, 6);
    b.remove(1, 2);
    // check if it is not empty
    PiecePtr p4 = new Pawn(BLACK);  
    PiecePtr p5 = new Pawn(BLACK);
    PiecePtr p6 = new Pawn(BLACK);
    EXPECT_FALSE(copy.place(p4, 4, 5)); 
    EXPECT_FALSE(copy.place(p5, 7, 6)); 
    EXPECT_FALSE(copy.place(p6, 1, 2)); 
}


TEST_F(test_Board, test_AssignmentOperator)
{
    Board b;
    PiecePtr p1 = new Pawn(BLACK);
    PiecePtr p2 = new Pawn(BLACK);
    b.place(p1, 4, 5);
    b.place(p2, 7, 6);

    // check if it is deep copying
    Board copy1;
    Board copy2;
    copy1 = copy2 = b;
    // remove pieces on the original Board to make sure it's deep copying
    b.remove(4, 5);  
    b.remove(7, 6);
    // check if it is not empty
    PiecePtr p3 = new Pawn(BLACK);  
    PiecePtr p4 = new Pawn(BLACK);
    EXPECT_FALSE(copy1.place(p3, 4, 5)); 
    EXPECT_FALSE(copy1.place(p4, 7, 6)); 
    PiecePtr p5 = new Pawn(BLACK);
    PiecePtr p6 = new Pawn(BLACK);
    EXPECT_FALSE(copy2.place(p5, 4, 5)); 
    EXPECT_FALSE(copy2.place(p6, 7, 6)); 
}

TEST_F(test_Board, test_isOccupied)
{
    Board b;
    PiecePtr p = new Pawn(WHITE);

    b.place(p, 2, 3); // there is a piece at (2,3)

    // check if it's occupied
    EXPECT_TRUE(b.isOccupied(2, 3));
    EXPECT_FALSE(b.isOccupied(3, 3));
}

TEST_F(test_Board, test_getPiece)
{
    Board b;
    PiecePtr p = new Pawn(WHITE);

    b.place(p, 2, 3); // there is a piece at (2,3)

    // check if gets the same Piece
    EXPECT_TRUE(p->getSymbol() == b.getPiece(2, 3)->getSymbol());
}