/*
              
Name:      Kai Ho Chak     
Date:      April 13, 2021   
              
*/

#ifndef KNIGHT_H
#define KNIGHT_H

/******************************************************************************
*
*   === Public Functions ===
*
* Knight::Knight (bool col)
*    Constructor that receives a boolean value indicating colour, with WHITE 
*    being true and BLACK being false
*  
* virtual Knight::~Knight ()
*    destructor
*
* virtual char Knight::getSymbol() const
*    return a character that indicates the type of piece, where
*      A black Knight will be displayed with a lowercase 'p' symbol, and 
*      a white Knight with an uppercase 'P'.
*
* virtual bool Knight::canMove(const Board& b, int fromX, int fromY,
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

class Knight;
#include "Board.h"
#include "Piece.h"
#include "Knight.h"
#include <iostream>
#include <cmath>
using namespace std;


#define WHITE true 
#define BLACK false

class Knight : public Piece
{
public:
  Knight (bool col);
  virtual ~Knight();
  
  virtual char getSymbol() const;
  virtual bool canMove(const Board& b, int fromX, int fromY,
                      int toX, int toY) const;

  virtual PiecePtr clone() const;
};

#endif
