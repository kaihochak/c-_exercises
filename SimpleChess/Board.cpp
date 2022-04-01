/*
              
Name:          Jacob Chak     
Email:         kchak676@mtroyal.ca  
Course:        COMP1633 - 001   
Assignment:    Assignment 5
Due Date:      April 13, 2021       
Instructor:    Paul Pospisil          
Source File:   Board.cpp  
              
*/

/******************************************************************************
*
*   === Private Members ===
*
* PiecePtr grid[MAXROWS][MAXCOLS];
*	 grid pointer array that represents the coordinate of the chest board such 
*    that, for instance, grid[0][2] point to the piece at position (0,2) 
*
* void Board::initBoard()
*    initialize the grid pointer array in Board
* 
* void Board::clearBoard()   
*    deallocate the grid pointer array in Board and set in to NULL
*
* void Board::copyBoard(const Board& other)
*    receive an object of Board and copy its grid pointer array to the caller's
*    grid pointer array
*
******************************************************************************/

#include <iostream>
#include <fstream>
#include <cctype>
#include "Board.h"
#include "Piece.h"

using namespace std;

/*
	Private Methods
 */

void Board::initBoard()
{	
	// initialize Board to be NULL
	for ( int i = 0; i < MAXROWS; i++ ) // iterate over rows 
	{
		for ( int j = 0; j < MAXCOLS; j++ ) // iterate over columns 
		{
			grid[i][j] = NULL;
		}
	}
	return;
}

void Board::clearBoard()
{
	// deallocate and set the grid array to be NULL
	for ( int i = 0; i < MAXROWS; i++ ) // iterate over rows 
	{
		for ( int j = 0; j < MAXCOLS; j++ ) // iterate over columns 
		{
			if ( grid[i][j] != NULL )
			{
				delete grid[i][j];
				grid[i][j] = NULL;
			}
		}
	}
	return;
}

void Board::copyBoard(const Board& other)
{
	for ( int i = 0; i < MAXROWS; i++ ) // iterate over rows
	{
		for ( int j = 0; j < MAXCOLS; j++ ) // iterate over columns
		{
			if ( other.grid[i][j] != NULL )
			{
				grid[i][j] = other.grid[i][j]->clone();			
			}
		}
	}
	return;
}

/*
	Public Methods
 */

Board::Board()
{
    initBoard();	// initialize the grid array
}

Board::Board (const Board& other)
{
    initBoard(); 	// initialize the grid array
    copyBoard(other);    // copy the grid array
}

Board::~Board()
{
	// write final status
	ofstream outfile;
	outfile.open ("final_board.txt");
	if (outfile.fail())
	{
		cout << "fail to open \"final_board.txt\"\n";
	}
	else 
	{
		for ( int i = 0; i < 8; i++ ) // traverse rows
		{
			for ( int j = 0; j < 8; j++ ) // traverse columns
			{
				if ( grid[i][j] != NULL )
				{
					outfile << grid[i][j]->getSymbol()
							<< " " << i << " " << j << endl;
				}
			}
		}
		outfile.close();
	}

	clearBoard();    // clear the grid array
}

bool Board::move (bool col, int fromX, int fromY, int toX, int toY)
{
	bool isMoved = false;


	// make sure player not moving opponent's piece
	if ( grid[fromX][fromY] != NULL &&
		col == grid[fromX][fromY]->getColour() )
	{
		// check if the piece can be moved
		isMoved = grid[fromX][fromY]->canMove(*this, fromX, fromY, toX, toY);

		if ( isMoved == true )
		{
			grid[fromX][fromY]->notifyMoved();
			place(grid[fromX][fromY], toX, toY);
			remove(fromX, fromY);
		}		
	}

	return isMoved;
}

bool Board::place (const PiecePtr& p, int x, int y)
{
	bool isEmpty = false;

	if ( grid[x][y] == NULL )
	{
		isEmpty = true;
		grid[x][y] = p;
	}	

	return isEmpty;
}

bool Board::remove (int x, int y)
{
	bool thereIsPiece = false;

	if ( grid[x][y] != NULL )
	{
		grid[x][y] = NULL;
		thereIsPiece = true;
	}	

	return thereIsPiece;
}

void Board::write (ostream& out) const
{
	const char column[] = "    0   1   2   3   4   5   6   7\n";
	const char divider[] = "  +---+---+---+---+---+---+---+---+\n";

	// print rows
	out << column 
		<< divider;
	for ( int i = 0; i < 8; i++ ) // iterate over columns
	{
		out << i << " |";
		// print squares
		for ( int j = 0; j < 8; j++ ) // iterate over rows
		{
			out << " ";
			if ( grid[i][j] == NULL )
			{
				out << " ";
			} 
			else
			{
				out << grid[i][j]->getSymbol();
			}
			out << " |"; 
		}
		out << "\n" << divider;
	}
	return;
}

Board& Board::operator= (const Board& other)
{
	if (this != &other)
	{
		clearBoard();		// deallocate current grid array
		copyBoard(other);	// copy the grid array
	}

	return (*this);
}

ostream& operator<< (ostream& out, const Board& b)
{
	b.write(out);
	return out;
}

bool Board::isOccupied (int x, int y) const
{
	return (grid[x][y] != NULL);
}

PiecePtr Board::getPiece(int x, int y) const
{
	return (grid[x][y]->clone());
}

bool Board::kingCaptured () const
{
	bool isCaptured = false;
	int numKing = 0;

	for ( int i = 0; i < 0; i++ )
	{
		for ( int j = 0; j < 0; j++ )
		{
			if ( grid[i][j]->getSymbol() == 'k' 
				|| grid[i][j]->getSymbol() == 'K' )
			{
				numKing++;
			}
		}
	} 

	if ( numKing == 2 )
	{
		isCaptured = true;
	}

	return isCaptured;
}

