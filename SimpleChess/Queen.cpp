/*
              
Name:          Jacob Chak     
Email:         kchak676@mtroyal.ca  
Course:        COMP1633 - 001   
Assignment:    Assignment 5
Due Date:      April 13, 2021       
Instructor:    Paul Pospisil          
Source File:   Queen.cpp  
              
*/
#include <iostream>

#include "Board.h"
#include "Piece.h"
#include "Queen.h"
#include <cmath>

/*
	Public Functions
*/

Queen::Queen (bool col) : Piece::Piece(col) 
{
}

Queen::~Queen () 
{
}

char Queen::getSymbol() const
{
	char symbol;

	if ( Piece::getColour() == BLACK )
	{
		symbol = 'q';
	}
	else 
	{
		symbol = 'Q';
	}

	return symbol;
}

bool Queen::canMove(const Board& b, int fromX, int fromY,
					 int toX, int toY) const
{
	bool canMove = false;
	bool occupiedColor;	

	// check if it move diagonally, vertically, or horizontally
	if ( isDiagonal (fromX, fromY, toX, toY) 
		|| isVertical (fromX, fromY, toX, toY) 
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

PiecePtr Queen::clone() const
{
	return ( new Queen(*this) );
}


