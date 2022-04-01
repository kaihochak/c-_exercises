/*

Name:      Kai Ho Chak     
Date:      April 13, 2021    
              
*/

#ifndef PAWN_H
#define PAWN_H

/******************************************************************************
*
*   === Public Functions ===
*
* Pawn::Pawn (bool col)
*    Constructor that receives a boolean value indicating colour, with WHITE 
*    being true and BLACK being false
*  
* virtual Pawn::~Pawn ()
*    destructor
*
* virtual char Pawn::getSymbol() const
*    return a character that indicates the type of piece, where
*      A black pawn will be displayed with a lowercase 'p' symbol, and 
*      a white pawn with an uppercase 'P'.
*
* virtual bool Pawn::canMove(const Board& b, int fromX, int fromY,
*                           int toX, int toY) const
*    returns a Boolean based on five input parameters:
*      a Board object on which the given Piece is placed,
*      x and y starting coordinates, and 
*      proposed x and y ending coordinates
*    true if the move is legal, false otherwise
*
* virtual void Pawn::notifyMoved()
*    allow the pawn to be informed that it has been moved
*
* virtual PiecePtr Piece::clone() const
*    copy pieces polymorphically by dynamically creates an exact duplicate 
*    of the invoking Piece and returns a pointer to it
*
******************************************************************************/

class Pawn;
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include <iostream>
#include <cmath>
using namespace std;


#define WHITE true 
#define BLACK false

class Pawn : public Piece
{
public:
  Pawn (bool col);
  virtual ~Pawn();
  
  virtual char getSymbol() const;
  virtual bool canMove(const Board& b, int fromX, int fromY,
                      int toX, int toY) const;
  virtual void notifyMoved();

  virtual PiecePtr clone() const;
};

#endif
