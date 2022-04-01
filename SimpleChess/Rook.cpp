/*
              
Name:          Jacob Chak     
Email:         kchak676@mtroyal.ca  
Course:        COMP1633 - 001   
Assignment:    Assignment 5
Due Date:      April 13, 2021       
Instructor:    Paul Pospisil          
Source File:   Rook.cpp  
              
*/
#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Rook.h"
#include <cmath>

/*
	Public Functions
*/

Rook::Rook (bool col) : Piece::Piece(col) 
{
}

Rook::~Rook () 
{
}

char Rook::getSymbol() const
{
	char symbol;

	if ( Piece::getColour() == BLACK )
	{
		symbol = 'r';
	}
	else 
	{
		symbol = 'R';
	}

	return symbol;
}

bool Rook::canMove(const Board& b, int fromX, int fromY,
					 int toX, int toY) const
{
	bool canMove = false;
	bool occupiedColor;	

	// check if it moves vertically or horizontally
	if (  isVertical (fromX, fromY, toX, toY) 
		|| isHorizontal (fromX, fromY, toX, toY) )
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

PiecePtr Rook::clone() const
{
	return ( new Rook(*this) );
}


