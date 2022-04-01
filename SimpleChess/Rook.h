/*
              
Name:      Kai Ho Chak     
Date:      April 13, 2021   
              
*/

#ifndef ROOK_H
#define ROOK_H

/******************************************************************************
*
*   === Public Functions ===
*
* Rook::Rook (bool col)
*    Constructor that receives a boolean value indicating colour, with WHITE 
*    being true and BLACK being false
*  
* virtual Rook::~Rook ()
*    destructor
*
* virtual char Rook::getSymbol() const
*    return a character that indicates the type of piece, where
*      A black Rook will be displayed with a lowercase 'p' symbol, and 
*      a white Rook with an uppercase 'P'.
*
* virtual bool Rook::canMove(const Board& b, int fromX, int fromY,
*                           int toX, int toY) const
*    returns a Boolean based on five input parameters:
*      a Board object on which the given Piece is placed,
*      x and y starting coordinates, and 
*      proposed x and y ending coordinates
*    true if the move is legal, false otherwise
*
* virtual PiecePtr Piece::clone() const
*    copy pieces polymorphically by dynamically creates an exact duplicate 
*    of the invoking Piece and returns a pointer to it
*
******************************************************************************/

class Rook;
#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include <iostream>
#include <cmath>
using namespace std;


#define WHITE true 
#define BLACK false

class Rook : public Piece
{
public:
  Rook (bool col);
  virtual ~Rook();
  
  virtual char getSymbol() const;
  virtual bool canMove(const Board& b, int fromX, int fromY,
                      int toX, int toY) const;

  virtual PiecePtr clone() const;
};

#endif
