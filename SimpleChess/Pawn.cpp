/*
              
Name:          Jacob Chak     
Email:         kchak676@mtroyal.ca  
Course:        COMP1633 - 001   
Assignment:    Assignment 5
Due Date:      April 13, 2021       
Instructor:    Paul Pospisil          
Source File:   Pawn.cpp  
              
*/

#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include <cmath>

/*
	Public Functions
*/

Pawn::Pawn (bool col) : Piece::Piece(col) 
{
}

Pawn::~Pawn () 
{
}

char Pawn::getSymbol() const
{
	char symbol;

	if ( Piece::getColour() == BLACK )
	{
		symbol = 'p';
	}
	else 
	{
		symbol = 'P';
	}

	return symbol;
}

bool Pawn::canMove(const Board& b, int fromX, int fromY,
					 int toX, int toY) const
{
	bool canMove = false;
	int step = vertDistance(fromX, toX);

	// check if it moves foward with legal steps
	if ( isForward(fromX, toX) == true && step > 0 && step <= 2) 
	{
		// check if the move is capturing 
		if ( b.isOccupied(toX, toY) &&	
			b.getPiece(toX, toY)->Piece::getColour() != Piece::getColour() )
		{
			// if capturing, check if it moves one square diagonally 
			if ( isDiagonal(fromX, fromY, toX, toY) && step == 1 )
			{
				canMove = true;
			}
		}
		// if not capturing, check if "To" position is available and vertical
		else if ( !b.isOccupied(toX, toY) && isVertical(fromX, fromY, toX, toY) )
		{
			// check for legal number of steps
			if ( step == 1 )
			{
				canMove = true;
			}
			// if has not moved, 2 steps is allowed, with clear path
			else if ( !hasMoved && step == 2 && 
				isPathClear(b, fromX, fromY, toX, toY) )
			{
				canMove = true;
			}
		}
	}
	return canMove;
}

void Pawn::notifyMoved()
{
	hasMoved = true;
	return;
}

PiecePtr Pawn::clone() const
{
	return ( new Pawn(*this) );
}


