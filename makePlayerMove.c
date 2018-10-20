#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Initialise.h"
#include "findPlayerMoves.h"
#include "makePlayerMove.h"
#include "flipTiles.h"
#include "playerTurns.h"
#include "gameOver.h"

/* Function to print the possible moves and allow the user to select a move
*- listNodePtr *currentPtr : Points to the start of the linked list
*- player *currentPlayer : The current player's move
*- int *moveChoice : Storing the choice of the user
*/
void printMove(listNodePtr currentPtr, player *currentPlayer, int *numOfMoves)
{
	int i = 1; // i prints out the number of the possible move

    printf("\n\nPlayer %s please choose your next move: \n\n", currentPlayer->name);

    while (currentPtr != NULL)
    {
		if ((currentPtr->r >= 0 && currentPtr->r < 8) && (currentPtr->c < 8 && currentPtr->c >= 0))
		{
			//row = currentPtr->r;
			//col = currentPtr->c;

			printf("%d. (%d, %d)\t", i, currentPtr->r, currentPtr->c);
			i++;
		}

        currentPtr = currentPtr->nextPtr;
    }

    *numOfMoves = i-1;
}

void selectMove(int numOfMoves, int *moveChoice)
{
    puts("");
    scanf("%d", moveChoice);

    while (!(*moveChoice > 0 && *moveChoice < numOfMoves))
    {
        printf("Invalid selection\n");
        printf("Please try again\n");
        scanf("%d", moveChoice);
    }
}

/* Function to find the player's chosen coords in the linked list
*- listNodePtr *sPtr : Points to the start of the linked list
*- int *row : Pointing to the row (x coordinate) we want to insert
*- int *col : Pointing to the col (y coordinate) we want to insert
*/
void traverseList(listNodePtr *sPtr, int moveChoice, int *row, int *col) // Following COMP10120 Linked List sample
{
    int findCoords = 0;

    if (sPtr != NULL)
    {
        listNodePtr previousPtr = *sPtr;
        listNodePtr currentPtr = (*sPtr)->nextPtr;

        while (previousPtr != NULL)
        {
			++findCoords;

            if (findCoords == moveChoice)
            {
                *row = previousPtr->r;
                *col = previousPtr->c;
                break;
            }

            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }
    }

	else
		printf("\nList is empty\n");


    while (*sPtr != NULL)
        dequeue(sPtr);

}

/* Function to free the memory
*- listNodePtr *sPtr : Points to the start of the linked list
*/
void dequeue(listNodePtr *sPtr)
{
	listNodePtr tempPtr = *sPtr;
	*sPtr = (*sPtr)->nextPtr;
	free(tempPtr);
}
