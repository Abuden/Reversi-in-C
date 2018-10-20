#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Initialise.h"
#include "findPlayerMoves.h"
#include "makePlayerMove.h"
#include "flipTiles.h"
#include "playerTurns.h"
#include "gameOver.h"

/* Function to find the opponent tiles in the perimeter of the chosen move
*- disk board[SIZE][SIZE] : Game board
*- int r : Row from the chosen move
*- int c : Col from the chosen move
*- player *currentPlayer : The current player's move
*- player *opponentPlayer : The opposing player
*/
void findOpponent(disk board[SIZE][SIZE], int r, int c, player *currentPlayer, player *opponentPlayer)
{
	int i, j; // To store the coordinate of the perimter pieces

	board[r][c].type = currentPlayer->type;

	for (i=r-1; i<=r+1; i++)
		for (j=c-1; j<=c+1; j++)
			if (board[i][j].type == opponentPlayer->type)
			{
			    printf("i: %d, j: %d\n", i, j); // If opponent piece if found
				flipTiles(board, r, c, currentPlayer, opponentPlayer); // Call function to flip the tiles
			}
}

/* Function to flip the opponent's disk after the current player make a move
* - disk board[SIZE][SIZE] : showing the whole board situation, ie. own disk's and opponent's disk in this round
* - int r : the row number of the move
* - int c : the column number of the move
* - player *currentPlayer : current player's information, ie. player's name, disk type and points in current round
* - player *opponentPlayer : opponent player's information, ie. player's name, disk type and points in current round
*/
void flipTiles(disk board[SIZE][SIZE], int r, int c, player *currentPlayer, player *opponentPlayer)
{
	int i = 1; // Loop counter for scanning the row number
	int j = 1; // Loop counter for scanning the column number
	int m = 0; // For storing the number of times we must reverse in a direction to flip the tiles - row
	int n = 0; // For storing the number of times we must reverse in a direction to flip the tiles - col

    printf("r: %d, c: %d\n", r, c);
	// Condition for checking Upper
    if(r-2 >0 )//&& board[r-2][c].type == opponentPlayer->type)
	{
		while(board[r-i][c].type == opponentPlayer->type) // when there are continuous of opponent's disk in a direction
        {
            i++;

            if (board[r-i][c].type == currentPlayer->type)
            {
                for (m = r-i; m<=r; m++)
                {
                    board[m][c].type = currentPlayer->type;
                    printf("Here1\n");
                }
                // break;
            }
        }

        i = 1;
	}

	printf("hi\n");
    // Lower direction
	if(r+2 < SIZE )//&& board[r+2][c].type == opponentPlayer->type)
	{
	    printf("r: %d, c: %d\n", r, c);
		while(board[r+i][c].type == opponentPlayer->type)
        {
            i++;
            printf("here2\n");

            if (board[r+i][c].type == currentPlayer->type)
            {
                for (m = r+i; m>=r; m--)
                    board[m][c].type = currentPlayer->type;
            }
            //break;
        }

        i = 1;
	}

	// Condition for checking Left Direction
	if(c-2 >= 0 )//&& board[r][c-2].type == opponentPlayer->type)
	{
	    //printf("r: %d, c: %d\n", r, c);
		while (board[r][c-j].type == opponentPlayer->type)
        {
            //printf("r: %d, c: %d\n", r, c);
            j++;
            if (board[r][c-j].type == currentPlayer->type)
            {
                 for (n = c-j; n<=c; n++)
                    board[r][n].type = currentPlayer->type;
            }
            // break;
        }
        j = 1;
	}


	// Condition for checking Right Direction
	if(c+2 < SIZE )//&& board[r][c+2].type == opponentPlayer->type)
	{
		while(board[r][c+j].type == opponentPlayer->type)
        {
            j++;

            if (board[r][c+j].type == currentPlayer->type)
            {
                for (n = c+j; n>=c; n--)
                    board[r][n].type = currentPlayer->type;
            }
            //break;
        }
        j = 1;
	}


    /* Two direction conditions required cases :
	*   => Another 4 directions cases
	*   - Upper Left
	*	- Upper Right
	*	- Lower Left
	*	- Lower Right
	*/

	// Condition for checking Upper Left
	if(r-2 >= 0 && c-2 >= 0)// && board[r-2][c-2].type == opponentPlayer->type)
	{
		while(board[r-i][c-j].type == opponentPlayer->type)
        {
            i++;
            j++;
            if (board[r-i][c-j].type == currentPlayer->type)
                for (m=r-i,n=c-i;m<r,n<c;m++,n++) // i, j always have the same number but different signs
                {
                    board[m][n].type = currentPlayer->type;

                }
        }
        i = 1;
        j = 1;
	}

	// Condition for checking Upper Right
	if(r-2 >= 0 && c+2 < SIZE )//&& board[r-2][c+2].type == opponentPlayer->type)
	{
		while(board[r-i][c+j].type == opponentPlayer->type)
        {
            i++;
            j++;
            if (board[r-i][c+j].type == currentPlayer->type)
                for (m=r-i, n=c+j; m<r, n>c; m++, n--)
                {
                    board[m][n].type = currentPlayer->type;
                }
        }
        i = 1;
        j = 1;
	}

	// Condition for checking Lower Left
	if(r+2 < SIZE && c-2 >= 0)// && board[r+2][c-2].type == opponentPlayer->type)
	{
		while(board[r+i][c-j].type == opponentPlayer->type)
        {
            i++;
            j++;
            if (board[r+i][c-j].type == currentPlayer->type)

                for(m=r+i,n=c-j;m>r,n<c;m--,n++)
                {
                    board[m][n].type = currentPlayer->type;
                }
        }
        i = 1;
        j = 1;
	}

	// Condition for checking Lower Right
	if (r+2 < SIZE && c+2 < SIZE)// && board[r+2][c+2].type == opponentPlayer->type)
	{
		while(board[r+i][c+j].type == opponentPlayer->type) // case if there are continuous of opponent's disk in diagonal,
        {
            i++; // then increase the value of counter i and j to search for player's disk
            j++;

            if (board[r+i][c+j].type == currentPlayer->type)
                for (m=r+i,n=c+j;m>r,n>c;m--,n--)
                {
                    board[m][n].type = currentPlayer->type;
                }
        }
        i = 1;
        j = 1;
	}
}

/* Function to update the players' points after every move
* - disk board[SIZE][SIZE] : showing the whole board situation, ie. own disk's and opponent's disk in this round
* - player *currentPlayer : current player's information, ie. player's name, disk type and points in current round
*/
void getPlayerPoints(disk board[SIZE][SIZE], player *currentPlayer)
{
	int i, j; // Loop counters
	int temp = 0; // To store the number of pointers found and add it into the struct currentPlayer->points

	for (i=0; i<SIZE; i++)
		for (j=0; j<SIZE; j++)
			if (board[i][j].type == currentPlayer->type) // If found current player's disk
				temp++; // Increase point by one

	currentPlayer->points = 0; // Reset points
	currentPlayer->points += temp; // Add new total

	printf("\nPlayer points: %d\n", currentPlayer->points); // Debugging
}


