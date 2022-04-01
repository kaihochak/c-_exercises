/*
              
Name:      Kai Ho Chak     
Date:      April 13, 2021               

*/

#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Bishop.h"
#include <cmath>

/*
	Public Functions
*/

Bishop::Bishop (bool col) : Piece::Piece(col) 
{
}

Bishop::~Bishop () 
{
}

char Bishop::getSymbol() const
{
	char symbol;

	if ( Piece::getColour() == BLACK )
	{
		symbol = 'b';
	}
	else 
	{
		symbol = 'B';
	}

	return symbol;
}

bool Bishop::canMove(const Board& b, int fromX, int fromY,
					 int toX, int toY) const
{
	bool canMove = false;
	bool occupiedColor;	

	// check if it move diagonally
	if ( isDiagonal (fromX, fromY, toX, toY) )
	{
		// check if the path is clear
		if ( isPathClear (b, fromX, fromY, toX, toY) )
		{
			// check if "TO" position is occupied
			// if not occupied, movable
			if ( !b.isOccupied(toX, toY) )
			{
				canMove = true;
			}
			// if occupied, only movable when capturing
			else 
			{
				occupiedColor = b.getPiece(toX, toY)->Piece::getColour();
				if ( Piece::getColour() != occupiedColor )
				{
					canMove = true;
				}
			}
		}
	}
	return canMove;
}

PiecePtr Bishop::clone() const
{
	return ( new Bishop(*this) );
}
