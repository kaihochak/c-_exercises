/*
              
Name:          Jacob Chak     
Email:         kchak676@mtroyal.ca  
Course:        COMP1633 - 001   
Assignment:    Assignment 5
Due Date:      April 13, 2021       
Instructor:    Paul Pospisil          
Source File:   Knight.cpp  
              
*/
#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Knight.h"
#include <cmath>

/*
	Public Functions
*/

Knight::Knight (bool col) : Piece::Piece(col) 
{
}

Knight::~Knight () 
{
}

char Knight::getSymbol() const
{
	char symbol;

	if ( Piece::getColour() == BLACK )
	{
		symbol = 'n';
	}
	else 
	{
		symbol = 'N';
	}

	return symbol;
}

bool Knight::canMove(const Board& b, int fromX, int fromY,
					 int toX, int toY) const
{
	bool canMove = false;
	bool occupiedColor;	

	// check if it move two squares horizontally and then one vertically,
	// or can move square horizontally and then two vertically.
	if ( (vertDistance(fromX, toX) == 2 && horizDistance(fromY, toY) == 1) ||
		(vertDistance(fromX, toX) == 1 && horizDistance(fromY, toY) == 2) ) 
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

PiecePtr Knight::clone() const
{
	return ( new Knight(*this) );
}


