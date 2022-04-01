/*
                  
Name:      Kai Ho Chak     
Date:      April 13, 2021     
              
*/

#ifndef BOARD_H
#define BOARD_H

/******************************************************************************
*
*   === Public Functions ===
*
* Board::Board()
*    Constructor to initialize the Board 
* 
* Board::Board (const Board& other)
*    Copy constructor that deep copies the received object of the same type
* 
* Board::~Board()
*    Destuctor that de-allocates all of the dynamic memory, it will also write
*    the final status of the Board to a file called "final_board.txt", format 
*    of each line in this file will be:
*      the piece character, a single space, 
*      the row coordinate, a single space and the column coordinate, such as
*        P 2 2
*        P 5 4
* 
* bool Board::move (bool col, int fromX, int fromY, int toX, int toY)
*    move a piece at a given position to a new position
*
*    receive a bool representing the color of the player making the move
*    receive four integers respectively representing the coordinate x and y of 
*    the Piece at the "from" location, and the coordinate x and y of the Piece
*    at the "to" location
*
*    return true if there is a Piece at the "from" location and no Piece at 
*    the "to" location and false otherwise
*
* bool Board::place (const PiecePtr& p, int x, int y)
*    place a piece at a given position 
*
*    receive piece and the coordinate x and y for the position to place
*
*    return true if the given location is empty and false otherwise
*
* bool Board::remove (int x, int y)
*    remove a piece at a given position
*
*    receive the coordinate x and y for the position to remove
*
*    return true for remove if there is a Piece at the given location and 
*    false otherwise
*
* void Board::write (ostream& out) const
*    print the Board to a given output stream 
*    
* Board& Board::operator= (const Board& other)
*    Assignment operator for Board that performs deep copy 
* 
* ostream& operator<< (ostream& out, const Board& b)
*    Overloaded ouput operator 
*
* bool Board::isOccupied (int x, int y) const
*    take a coordinate and
*    return true if this location is occupied, false otherwise
*  
* PiecePtr Board::getPiece(int x, int y) const
*    takes a coordinate and 
*    return a pointer to the Piece at this location, 
*    a NULL pointer indicates no Piece at the location 
*
* bool Board::kingCaptured () const
*    return true if the king is capture, false otherwise
*
******************************************************************************/

class Board;
#include "Piece.h"
#include <iostream>
using namespace std;

#define MAXROWS 8
#define MAXCOLS 8

typedef Piece* PiecePtr;

class Board
{
public:
   Board();
   Board (const Board& other);
   ~Board();

   bool move (bool col, int fromX, int fromY, int toX, int toY);
   bool place (const PiecePtr& p, int x, int y);
   bool remove (int x, int y);
 
   void write (ostream& out) const;

   Board& operator= (const Board& other);

   bool isOccupied (int x, int y) const;
   PiecePtr getPiece(int x, int y) const;

   bool kingCaptured () const;

private:
   PiecePtr grid[MAXROWS][MAXCOLS];

   void initBoard();
   void clearBoard();
   void copyBoard(const Board& other);
};

ostream& operator<< (ostream& out, const Board& b);

#endif
