/*
              
Name:      Kai Ho Chak     
Date:      April 13, 2021   
              
*/

#ifndef PIECE_H
#define PIECE_H

/******************************************************************************
*
*   === Public Functions ===
*
* Piece::Piece (bool col)
*    Constructor that receives a boolean value indicating colour, with WHITE 
*    being true and BLACK being false
*
* virtual Piece::~Piece()
*    destructor 
*  
* virtual Piece::char Piece::getSymbol() const = 0
*    pure virtual function
*
* bool Piece::getColour() const
*    return true if the piece is white, false if it is black
*
* virtual bool Piece::canMove(const Board& b, int fromX, int fromY,
*                            int toX, int toY) const = 0
*    pure virtual function
*
* void Piece::notifyMoved()
*    allow a Piece to be informed that it has been moved
*
* virtual PiecePtr Piece::clone() const = 0 
*    pure virtual function
*
******************************************************************************/

class Piece;
#include "Board.h"
#include <iostream>
#include <cmath>
using namespace std;

#define WHITE true 
#define BLACK false

typedef Piece* PiecePtr;

class Piece
{
public:
  Piece (bool col);
  virtual ~Piece();

  bool getColour() const;
  virtual void notifyMoved();

  // pure virtual functions
  virtual char getSymbol() const = 0;
  virtual bool canMove(const Board& b, int fromX, int fromY, 
                      int toX, int toY) const = 0;
  virtual PiecePtr clone() const = 0;

protected:
  bool colour;
  bool hasMoved; 
  
  bool isVertical (int fromX, int fromY, int toX, int toY) const;
  bool isHorizontal (int fromX, int fromY, int toX, int toY) const;
  bool isDiagonal (int fromX, int fromY, int toX, int toY) const;
  bool isForward (int fromX, int toX) const;
  int vertDistance (int fromX, int toX) const;
  int horizDistance (int fromY, int toY) const;
  bool isPathClear (const Board& b, int fromX, int fromY, int toX, int toY) const;
};

#endif
