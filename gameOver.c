#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Initialise.h"
#include "findPlayerMoves.h"
#include "makePlayerMove.h"
#include "flipTiles.h"
#include "playerTurns.h"
#include "gameOver.h"


/* Function to print the winner and save the game status
* - disk board[SIZE][SIZE] : showing the whole board situation, ie. own disk's and opponent's disk in this round
* - player *player1 : player 1's information, ie. player's name, disk type and points in current round
* - player *player2 : player 2's information, ie. player's name, disk type and points in current round
*/
void endScore(disk board[SIZE][SIZE], player *player1, player *player2)
{
    printf("\n%s's points: %d\n", player1->name, player1->points);
    printf("%s's points: %d\n", player2->name, player2->points);

    if (player1->points < player2->points)
        printf("%s is the winner!\n", player2->name);
    else if (player1->points > player2->points)
        printf("%s is the winner!\n", player1->name);
    else
        printf("%s and %s drew!\n", player1->name, player2->name);

	saveGame(board, &player1, &player2);
}

/* Function to write the score into the text file
* - disk board[SIZE][SIZE] : showing the whole board situation, ie. own disk's and opponent's disk in this round
* - player *player1 : player 1's information, ie. player's name, disk type and points in current round
* - player *player2 : player 2's information, ie. player's name, disk type and points in current round
*/
void saveGame(disk board[SIZE][SIZE], player *player1, player *player2)
{
    FILE *fPtr;

    if ((fPtr = fopen("game.txt", "w")) == NULL)
        printf("File cannot be opened\n");

    else
    {
		saveBoard(board, fPtr);

		fprintf(fPtr, "\n%s's points: %d\n", player1->name, player1->points);
		fprintf(fPtr, "%s's points: %d\n", player2->name, player2->points);

		if (player1->points < player2->points)
			fprintf(fPtr, "%s is the winner!\n", player2->name);
		else if (player1->points > player2->points)
			fprintf(fPtr, "%s is the winner!\n", player1->name);
		else
			fprintf(fPtr, "%s and %s drew!\n", player1->name, player2->name);

		fclose(fPtr);
    }
}

/* Function to print the board into the text file
* - disk board[SIZE][SIZE] : showing the whole board situation, ie. own disk's and opponent's disk in this round
* - FILE *fPtr : Our pointer file
*/
void saveBoard(disk board[SIZE][SIZE], FILE *fPtr)
{
    int i, j = 0;

    fprintf(fPtr, "\n    ");
    for(i=0; i<SIZE; i++)
        fprintf(fPtr, "%d   ",i);

    for(i=0; i< SIZE; i++)
    {
        fprintf(fPtr, "\n%d | ", i);

        for(j=0; j<SIZE; j++)
        {
            // printing the values of the disks that are placed on the board
            switch(board[i][j].type)
            {
                case BLACK: // Case when the coordinate is having the value of enum colour BLACK , which means it is placed with the black disk
                    printf("B | ");
                    break;

                case WHITE: // Case when the coordinate is having the value of enum colour WHITE , which means it is placed with the white disk
                    printf("W | ");
                    break;

                case NONE:  // Case when the coordinate is having the value of enum colour NONE , which means it is placed with no disk
                    printf("  | ");
                    break;

                default:
                    break;
            }
        }
    }

}
