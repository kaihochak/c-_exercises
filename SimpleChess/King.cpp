/*
              
Name:          Jacob Chak     
Email:         kchak676@mtroyal.ca  
Course:        COMP1633 - 001   
Assignment:    Assignment 5
Due Date:      April 13, 2021       
Instructor:    Paul Pospisil          
Source File:   King.cpp  
              
*/
#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "King.h"
#include <cmath>

/*
	Public Functions
*/

King::King (bool col) : Piece::Piece(col) 
{
}

King::~King () 
{
}

char King::getSymbol() const
{
	char symbol;

	if ( Piece::getColour() == BLACK )
	{
		symbol = 'k';
	}
	else 
	{
		symbol = 'K';
	}

	return symbol;
}

bool King::canMove(const Board& b, int fromX, int fromY,
					 int toX, int toY) const
{
	bool canMove = false;
	bool occupiedColor;	

	// check if it move diagonally, vertically, or horizontally with one step
	if ((isDiagonal(fromX,fromY,toX,toY) && vertDistance(fromX,toX) == 1) ||
	    (isVertical(fromX,fromY,toX,toY) && vertDistance(fromX,toX) == 1) ||
	    (isHorizontal(fromX,fromY,toX,toY) && horizDistance(fromY,toY) == 1))
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
	return canMove;
}

PiecePtr King::clone() const
{
	return ( new King(*this) );
}