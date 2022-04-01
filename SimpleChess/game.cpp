/*
              
Name:          Jacob Chak     
Email:         kchak676@mtroyal.ca  
Course:        COMP1633 - 001   
Assignment:    Assignment 5
Due Date:      April 14, 2021       
Instructor:    Paul Pospisil          
Source File:   game.cpp  
                                             
//==============================================================================

Purpose: create a chess game 

Details: this program create a chess game by 

		(1) set up a chess board like this 

    		    0   1   2   3   4   5   6   7
			  +---+---+---+---+---+---+---+---+
			0 | r | n | b | q | k | b | n | r |
			  +---+---+---+---+---+---+---+---+
			1 | p | p | p | p | p | p | p | p |
			  +---+---+---+---+---+---+---+---+
			2 |   |   |   |   |   |   |   |   |
			  +---+---+---+---+---+---+---+---+
			3 |   |   |   |   |   |   |   |   |
			  +---+---+---+---+---+---+---+---+
			4 |   |   |   |   |   |   |   |   |
			  +---+---+---+---+---+---+---+---+
			5 |   |   |   |   |   |   |   |   |
			  +---+---+---+---+---+---+---+---+
			6 | P | P | P | P | P | P | P | P |
			  +---+---+---+---+---+---+---+---+
			7 | R | N | B | Q | K | B | N | R |
			  +---+---+---+---+---+---+---+---+

		where capital letter as white pieces, black pieces otherwise.

		King is represented by K or k that moves one square in any 
		direction (horizontal, vertical, diagonal; forward or backward)

		Queen is represented by Q or q that moves multiple squares in any
		direction.

		Bishop is represented by B or b that moves multiple squares diagonally

		Knight is represented by N or n that moves two squares horizontally 
		and then one vertically, or can move one square horizontally and then 
		two vertically. 

		Rook is represented by R or r that moves multiple squares horizontally,
		or can move multiple squares vertically

		Pawn is P or p that moves one square forward vertically if not capturing,
		or can move one square forward diagonally if capturing.


		(2) handle players that use black and white pieces. Each player can enter
		FROM coordinates and TO coordinates to indicate their moves.


		(3) handle errors by checking 

			- invalid board coordinates and re-prompt for valid ones
			- illegal move and re-prompt for a legal one
		
		(4) keep track on the game when it is over. If one player captures his 
		opponent's king or if a player enters the sentinel board coordinates 
		(–1, –1). Request to quit will be prompted for confirmation
          
Assumptions and Limitation: no check function.
                                       
Any Known Bugs: my Board::getPiece() would trigger seg fault, so I instead call
				the Piece::notifyMoved() inside Board
        
*/

#include <iostream>
#include <cctype>

#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "ioutil.h"

using namespace std;

typedef Piece* PiecePtr;

#define FROM true 
#define TO false

void setUpChess(Board& b);
void promptCoord(bool prompt, int& x, int& y, bool& quit);
bool isCoordValid(int x, int y, bool& quit);
// bool kingCaptured(Board& b, int toX, int toY);

const char START[] = "GAME STARTED\n\n";
const char ENTER_FROM[] = "Enter the Coordinate of the Piece to Move\n\n";
const char PROMPT_FROM_X[] = "From (\"x\", y): ";
const char PROMPT_FROM_Y[] = "From (x, \"y\"): ";
const char ENTER_TO[] = "Enter the Coordinate of Destination\n\n";
const char PROMPT_TO_X[] = "To (\"x\", y): ";
const char PROMPT_TO_Y[] = "To (x, \"y\"): ";
const char CONFIRM_QUIT[] = "(-1,-1) is entered. Do you want to quit? (Y/N)\n";
const char REPROMPT_VALID[] = " is not valid board coordinates.\n";
const char REPROMPT_LEGAL[] = " is not a legal move.\nTry Again\n\n";

int main()
{
	int fromX, fromY, toX, toY;
	bool quit;
	bool repromptNeeded;
	int moveCount = 1;
	bool color;
	Board board; // instantiate a Board object

	setUpChess(board);

	// Game Starts
	cout << START << endl << board << endl;

	// prompt for move
	do 
	{
		// white: true; black: false
		color = moveCount % 2;
		cout << "Round of ";
		if ( color == BLACK)
		{
			cout << "BLACK\n\n";
		}
		else 
		{
			cout << "WHITE\n\n";
		}

		// prompt for FROM coordinates
		promptCoord(FROM, fromX, fromY, quit);	
		if ( !quit )
		{
			// prompt for TO coordinates
			promptCoord(TO, toX, toY, quit);
			if ( !quit )
			{
				// if move is invalid, reprompt FROM and TO otherwise
				repromptNeeded = !board.move(color, fromX, fromY, toX, toY);
			}
		}
		if ( !repromptNeeded )
		{
			moveCount++;
			//board.getPiece(fromX, fromY)->notifyMoved();

			// Display board
			cout << board << endl;
		}
		else 
		{
			cout << "(" << fromX << ", " << fromY << ") to (" 
				 << toX << ", " << toY << ") " << REPROMPT_LEGAL;
		}
	}
	while ( !quit && !board.kingCaptured() ); // repeat until game over 


	// print game over message
	if ( board.kingCaptured() )
	{
		if ( color == BLACK)
		{
			cout << "BLACK\n";
		}
		else 
		{
			cout << "WHITE\n";
		}
		cout  << " Wins. Game Over.\n" << board << endl;
	}

	return 0;
} // main ends

/*
Function: setUpChess

Purpose:  set up the chess board

Details:  this function set up a given Board object as a chess game setUpChess
		  At the start of a game, the Board is set up as shown below. 

			    0   1   2   3   4   5   6   7
			  +---+---+---+---+---+---+---+---+
			0 | r | n | b | q | k | b | n | r |
			  +---+---+---+---+---+---+---+---+
			1 | p | p | p | p | p | p | p | p |
			  +---+---+---+---+---+---+---+---+
			2 |   |   |   |   |   |   |   |   |
			  +---+---+---+---+---+---+---+---+
			3 |   |   |   |   |   |   |   |   |
			  +---+---+---+---+---+---+---+---+
			4 |   |   |   |   |   |   |   |   |
			  +---+---+---+---+---+---+---+---+
			5 |   |   |   |   |   |   |   |   |
			  +---+---+---+---+---+---+---+---+
			6 | P | P | P | P | P | P | P | P |
			  +---+---+---+---+---+---+---+---+
			7 | R | N | B | Q | K | B | N | R |
			  +---+---+---+---+---+---+---+---+

		  Black moves down, and white moves up.	  

Input:
   	  	n/a
Output:
		b         - a board object that the chess game will be set up on
Return:
   	  	n/a
*/

void setUpChess(Board& b)
{
	PiecePtr p = NULL;

	// set up board for black pawns
 	for ( int i = 0; i < 8; i++ )
 	{
 		p = new Pawn(BLACK);
 		b.place(p, 1, i);
 	}

	// set up board for white pawns
 	for ( int i = 0; i < 8; i++ )
 	{
 		p = new Pawn(WHITE);
 		b.place(p, 6, i);
 	}

	// set up rooks
	p = new Rook(BLACK);
	b.place(p, 0, 0);
	p = new Rook(BLACK);
	b.place(p, 0, 7);
	p = new Rook(WHITE);
	b.place(p, 7, 7);
	p = new Rook(WHITE);
	b.place(p, 7, 0);

	// set up knights
	p = new Knight(BLACK);
	b.place(p, 0, 1);
	p = new Knight(BLACK);
	b.place(p, 0, 6);
	p = new Knight(WHITE);
	b.place(p, 7, 6);
	p = new Knight(WHITE);
	b.place(p, 7, 1);

	// set up bishops
	p = new Bishop(BLACK);
	b.place(p, 0, 2);
	p = new Bishop(BLACK);
	b.place(p, 0, 5);
	p = new Bishop(WHITE);
	b.place(p, 7, 5);
	p = new Bishop(WHITE);
	b.place(p, 7, 2);

	// set up queens
	p = new Queen(BLACK);
	b.place(p, 0, 3);
	p = new Queen(WHITE);
	b.place(p, 7, 3);

	// set up kings
	p = new King(BLACK);
	b.place(p, 0, 4);
	p = new King(WHITE);
	b.place(p, 7, 4);

	p = NULL;

 	return;
} // setUpChess ends

/*
Function: promptCoord

Purpose:  prompt users for the coordinates of the target 

Details:  this function prompts a user for either the "FROM" or "TO" coordinates, 
		  it returns two integers x and y representing the prompted coordinates 
		  (x, y). If the user instead requests to quit the program, it will be 
		  indicated by the boolean value "quit".

Input:
   	  	prompt    - a bool that indicates if the prompt is for "FROM" to "TO"
   	  				coordinates. FROM is defined as true, TO is false
Output:
		x         - an integer that indicates the x coordinate of the target 
					position, representing the column
		y         - an integer that indicates the x coordinate of the target 
					position, representing the row
		quit      - a bool that indicates whether the user requests to quit 
					program, true means quit, false otherwise
Return:
   	  	n/a
*/

void promptCoord(bool prompt, int& x, int& y, bool& quit)
{
	bool eof = false;
	bool reprompt = false;
	quit = false;

	do {
		// prompt for coordinates
		if ( prompt == FROM )
		{
			cout << ENTER_FROM;
			x = readInt (PROMPT_FROM_X, eof);
			if ( !eof ) 
			{
				y = readInt (PROMPT_FROM_Y, eof);
			}
		}
		else 
		{
			cout << ENTER_TO;
			x = readInt (PROMPT_TO_X, eof);
			if ( !eof )
			{
				y = readInt (PROMPT_TO_Y, eof);				
			}
		}	
		if ( eof )
		{
			quit = true;
		}
		else 
		{
			reprompt = !isCoordValid(x, y, quit); // check if coordinates are valid
		}
		cout << endl;
	}
	while ( reprompt && !eof && !quit);

	return;
} // promptCoord ends

/*
Function: isCoordValid

Purpose:  check if the given coordinate is valid

Details:  this function checks if the given coordinates is valid by examining 
		  three situations. 

		  	Case 1: coordinates are valid such that both x and y are within 
		  			the range of 0 - 7, true will be returned

		  	Case 2: sentinel coordinates are entered by the user, such that 
		  			both x and y are -1. This function will prompt user for 
		  			confirmation to quit the program. If 'Y' or 'y' is entered,
		  			bool 'quit' will notify the function caller as true, 
		  			isValid will be returned as false; if 'N' or 'n'
		  			is entered, 'quit' will show false. Other input will 
		  			reprompt confirmation
			
			Case 3: other out of range coordinates will be seen as invalid, 
					function will print a reprompt message and return isValid
					as false

Input:
 		x         - an integer that indicates the x coordinate of the target 
					position, representing the column
		y         - an integer that indicates the x coordinate of the target 
					position, representing the row
Output:
		quit      - a bool that indicates whether the user requests to quit 
					program, true means quit, false otherwise
Return:
   	  	isValid   - a bool that indicates if the given coordinates is valid
   	  				true means valid, false otherwise
*/

bool isCoordValid(int x, int y, bool& quit)
{
	bool isValid;
	char answer[2];
	bool eof;
	char c;
	quit = false;

	// case 1: valid coordinates
	// return true
	if ( x >= 0 && x <= 7 && y >= 0 && y <= 7 )
	{
		isValid = true;
	}
	// case 2: sentinel coordinates
	// return false, and confirm it user wants to quit
	else if ( x == -1 && y == -1 )
	{
		do {
			// prompt for confirmation
			readString(CONFIRM_QUIT, answer, 1, 1, eof);
			c = static_cast<char>(tolower(answer[0]));

			if ( eof || c == 'y')
			{
				quit = true;
				isValid = false;
			}
		} 
		while ( c != 'y' && c != 'x' && !eof ); // reprompt if no answer
	}
	// case 3: invalid coordinates
	// return false
	else 
	{
		isValid = false;
		cout << "(" << x << ", " << y << ")" << REPROMPT_VALID;
	}

	return isValid;
} // isCoordValid ends

/*
Function: kingCaptured

Purpose:  check if the king is captured

Input:
 		toX       - an integer that indicates the x coordinate of the target 
					position, representing the column
		toY       - an integer that indicates the x coordinate of the target 
					position, representing the row
Output:
		b         - a board object that the chess game will be set up on
Return:
   	  	bool   	  - a bool that returns true if the given coordinates is the King 

bool kingCaptured(Board& b, int toX, int toY)
{
	char c = b.getPiece(toX, toY)->getSymbol();
	c = static_cast<char>( tolower(c) );

	return ( c == 'k' );
}
*/