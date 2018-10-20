
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Initialise.h"
#include "findPlayerMoves.h"
#include "makePlayerMove.h"
#include "flipTiles.h"
#include "playerTurns.h"
#include "gameOver.h"

/* Function to get all the valid move position for the current move player
*- disk board[SIZE][SIZE] : Read the whole board situation, the colour of disks on the board current
*- listNodePtr *sPtr : Points to the start of the linked list
*- player *currentPlayer : The current player move
*- player *opponentPlayer : The opponent
*/
void getPlayerDisk(disk board[SIZE][SIZE], listNodePtr *sPtr, player *currentPlayer, player *opponentPlayer)
{
    size_t r, c; // r = row number , c = column number

    // Spot all the current-move player's disks on the current board
	for(r=0; r<SIZE; r++) // reading the i th row array element
		for(c=0; c<SIZE; c++) // reading the j th column array element
			if(board[r][c].type == currentPlayer->type) // Checks if the tile r, c contains current player's own tile
				getValidMoves(board, r, c, sPtr, currentPlayer, opponentPlayer); // Call function to scan all 8 directions of the board to find the opposinig player's disks

}

void getValidMoves(disk board[SIZE][SIZE], int r, int c, listNodePtr *sPtr, player *currentPlayer, player *opponentPlayer)
{

	int i = 1; // i, j are used to track how many opponent disks there are in a certain direction. Then when a blank spot is found after an opponent disk, the blank spot location is marked.
	int j = 1; // i represents row, and j represents col

	// Condition for checking Upper direction
	if(r-2 >= 0)
	{
		while(board[r-i][c].type == opponentPlayer->type)
        {

			if(board[((r-i)-1)][c].type == NONE) // When an opponent's disk is found on the upper position of the player current read disk
				insertList(sPtr, (r-i)-1, c);

			i++;
        }

        i = 1; // Initialising i, j back to 1 for the next direction
        j = 1;
	}


	// Condition for checking Lower Direction
	if(r+2 < SIZE)
    {
        while(board[r+i][c].type == opponentPlayer->type)
		{

			if(board[((r+i)+1)][c].type == NONE) // When an opponent's disk is found on the lower of the player current read disk
				insertList(sPtr, (r+i)+1, c);


			i++;
		}

		i = 1;
		j = 1;
    }


	// Condition for checking Left Direction
	if(c-2 >= 0)
    {
        while(board[r][c-j].type == opponentPlayer->type)
		{

			if(board[r][((c-j)-1)].type == NONE) // When an opponent's disk is found on the left side of the player current read disk
				insertList(sPtr, r,(c-j)-1);


			j++;
		}

		i = 1;
		j = 1;
    }


	// Condition for checking Right Direction
	if(c+2 < SIZE)
    {
        while(board[r][c+j].type == opponentPlayer->type)
		{

			if(board[r][((c+j)+1)].type == NONE) // When an opponent's disk is found on the right side of the player current read disk
				insertList(sPtr, r, (c+j)+1);


			j++;
		}

        i = 1;
        j = 1;
    }


	/* Two direction conditions required cases :
	*   => Another 4 directions cases
	*   	- Upper Left
	*	- Upper Right
	*	- Lower Left
	*	- Lower Right
	*/

	// Condition for checking Upper Left
	if(r-2 >= 0 && c-2 >= 0)
    {
		while(board[r-i][c-j].type == opponentPlayer->type)
		{

			if(board[((r-i)-1)][((c-j)-1)].type == NONE) // When an opponent's disk is found on the upper left of the player current read disk
				insertList(sPtr, (r-i)-1, (c-j)-1);


			i++;
			j++;
		}

		i = 1;
		j = 1;
    }



	// Condition for checking Upper Right
	if(r-2 >= 0 && c+2 < SIZE)
    {
        while(board[r-i][c+j].type == opponentPlayer->type)
		{

			if(board[((r-i)-1)][((c+j)+1)].type == NONE) // When an opponent's disk is found on the upper right of the player current read disk
				insertList(sPtr, (r-i)-1, (c+j)+1);


			i++;
			j++;
		}

		i = 1;
		j = 1;
    }



	// Condition for checking Lower Left
	if(r+2 < SIZE && c-2 >= 0)
    {
		while(board[r+i][c-j].type == opponentPlayer->type)
		{

			if(board[((r+i)+1)][((c-j)-1)].type == NONE) // When an opponent's disk is found on the lower left of the player current read disks
				insertList(sPtr, (r+i)+1, (c-j)-1);


			i++;
			j++;
		}

		i = 1;
		j = 1;
    }

	// Condition for checking Lower Right
	if (r+2 < SIZE && c+2 < SIZE)
    {
        while (board[r+i][c+j].type == opponentPlayer->type)
		{

			if (board[((r+i)+1)][((c+j)+1)].type == NONE) // When an opponent's disk is found on the lower right of the player current read disk
				insertList(sPtr, (r+i)+1, (c+j)+1);


			i++;
			j++;
		}

		i = 1;
		j = 1;
    }
}

/* Function to get all the valid move position for the current move player
*- listNodePtr *sPtr : Points to the start of the linked list
*- int row : The row (x coordinate) we want to insert
*- int col : The col (y coordinate) we want to insert
*/
void insertList(listNodePtr *sPtr, int row, int col) // Following COMP10120 Linked List example
{
    if (!(checkList(*sPtr, row, col)))
    {
        listNodePtr newPtr = malloc(sizeof(listNode)); // Creates node

        if (newPtr != NULL) // Check if there is enough memory
        {
            newPtr->r = row;
            newPtr->c = col;
            newPtr->nextPtr = NULL;

            listNodePtr previousPtr = NULL;
            listNodePtr currentPtr = *sPtr;

            while (currentPtr != NULL && ((row > currentPtr->r) || (row == currentPtr->r && col > currentPtr->c))) // Finding correct location
            {
                previousPtr = currentPtr;
                currentPtr = currentPtr->nextPtr;
            }


            if (previousPtr == NULL) // If there are no nodes, insert at the start of the list
            {
                newPtr->nextPtr = *sPtr;
                *sPtr = newPtr;
            }

            else // Insert new node between previousPtr, and currentPtr
            {
                previousPtr->nextPtr = newPtr;
                newPtr->nextPtr = currentPtr;
            }
        }

        else
            puts("\nInsufficient Memory\n");
    }
}

/* Function to check if the current row, col coordinate is already in the list.
   This is very important as it prevents the game from glitching
*- listNodePtr *sPtr : Points to the start of the linked list
*- int row : The row (x coordinate) we want to insert
*- int col : The col (y coordinate) we want to insert
*/
int checkList(listNodePtr currentPtr, int row, int col)
{
    while (currentPtr != NULL) // While list isn't empty
    {
        if (currentPtr->r == row && currentPtr->c == col) // If in list
            return 1; // Return true

            currentPtr = currentPtr->nextPtr; // Move to next
    }

    return 0; // Return false
}
