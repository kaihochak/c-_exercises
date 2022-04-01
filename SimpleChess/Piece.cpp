/*
              
Name:      Kai Ho Chak     
Date:      April 13, 2021     
              
*/

#include "Board.h"
#include "Piece.h"
#include <cmath>

/******************************************************************************
*
*   === Private Members ===
*
* bool Piece::colour
*    indicate the Piece's colors
*    return true when it is white and false when it is black
*
* bool Piece::hasMoved
*	 indicate first move for pawn
*    return true if the pawn has not been moved, false otherwise
*	 
* bool Piece::isVertical (int fromX, int fromY, int toX, int toY) const
* bool Piece::isHorizontal (int fromX, int fromY, int toX, int toY) const
* bool Piece::isDiagonal (int fromX, int fromY, int toX, int toY) const
*
* bool Piece::isForward (int fromX, int toX) const
*	  return a Boolean based on:
*       the fromX that indicates the starting "row" (not column), and
*       the ToX that indicates the proposed ending "row" (not column)
*     true if the move is moving forward, false otherwise
*
* int Piece::vertDistance (int fromX, int toX) const
* int Piece::horizDistance (int fromY, int toY) const
*
* bool Piece::isPathClear (const Board& b, int fromX, int fromY,
* 				    int toX, int toY) const
*    return a Boolean based on five input parameters:
*      a Board object on which the given Piece is placed,
*      x and y starting coordinates, and 
*      proposed x and y ending coordinates
*    true if no piece in the board spaces between the starting and 
*    ending coordinates, false otherwise
*
******************************************************************************/

/*
	Private Functions
*/

bool Piece::isVertical (int fromX, int fromY, int toX, int toY) const
{
	return ( fromY == toY );
}

bool Piece::isHorizontal (int fromX, int fromY, int toX, int toY) const
{
	return ( fromX == toX );
}

bool Piece::isDiagonal (int fromX, int fromY, int toX, int toY) const
{
	return ( vertDistance(fromX, toX) == horizDistance(fromY, toY) );
}

bool Piece::isForward (int fromX, int toX) const
{
	bool isForward = false; 

	if ( colour == BLACK ) // for black Piece
	{
		if ( toX - fromX > 0 )
		{
			isForward = true;		
		}	
	} 
	else // for white Piece
	{
		if ( toX - fromX < 0 )
		{
			isForward = true;
		}
	}
	
	return isForward;
}

int Piece::vertDistance (int fromX, int toX) const
{
	return ( abs(toX - fromX) );
}

int Piece::horizDistance (int fromY, int toY) const
{
	return ( abs(toY - fromY) );
}

bool Piece::isPathClear (const Board& b, int fromX, int fromY, 
						int toX, int toY) const
{	
	bool clear = true;
	int largeX, smallX, largeY, smallY;
	bool goLeft, goUp;

	// get the larger X, Y and direction
	if ( fromX > toX )
	{
		largeX = fromX;
		smallX = toX;
		goUp = true;
	}
	else
	{
		largeX = toX;
		smallX = fromX;
		goUp = false;
	}
	if ( fromY > toY )
	{
		largeY = fromY;
		smallY = toY;
		goLeft = true;
	}
	else
	{
		largeY = toY;
		smallY = fromY;
		goLeft = false;
	}

	// case 1: vertical move
	if ( isVertical (fromX, fromY, toX, toY) )
	{
		for ( int i = smallX+1; i < largeX; i++ )
		{
			if ( b.isOccupied(i, fromY) )
			{
				clear = false;
			}
		}	
	}
	// case 2: horizontal move
	else if ( isHorizontal (fromX, fromY, toX, toY) )
	{
		for ( int i = smallY+1; i < largeY; i++ )
		{
			if ( b.isOccupied(fromX, i) )
			{
				clear = false;
			}
		}

	}
	// case 3: diagonal move
	else if ( isDiagonal (fromX, fromY, toX, toY) )
	{	
		// if X and Y are both decreasing 
		if ( (goLeft && goUp) || (!goLeft && !goUp) )
		{
			for ( int i = smallX+1, j = smallY+1; i < largeX; i++, j++ )				
			{
				if ( b.isOccupied(i, j) )
				{
					clear = false;
				}
			}
		}
		else 
		{	
			for ( int i = largeX-1, j = smallY+1; i > smallX; i--, j++ )				
			{
				if ( b.isOccupied(i, j) )
				{
					clear = false;
				}
			}
		}
	}

	return clear;
}

/*
	Public Functions
*/

Piece::Piece (bool col)  
{
	// set piece's colour
	if ( col == BLACK )
	{
		colour = BLACK;
	}
	else
	{
		colour = WHITE;
	}

	hasMoved = false; // only used by Pawn.cpp
}

Piece::~Piece ()  
{

}

bool Piece::getColour() const
{
	return ( colour == WHITE ); // return true if WHITE, otherwise false
}

void Piece::notifyMoved()
{
	return;
}

