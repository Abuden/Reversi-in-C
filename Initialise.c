#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Initialise.h"
#include "findPlayerMoves.h"
#include "makePlayerMove.h"
#include "flipTiles.h"
#include "playerTurns.h"
#include "gameOver.h"

void initializePlayers(player *player1, player *player2)
{
    int nameSize;

    // Insert player 1 information:
    printf("Player 1 please insert your name: ");  // Enter player's name here
    fgets(player1->name, 20, stdin);

    nameSize = strlen(player1->name);
    player1->name[nameSize -1] = '\0'; // End up the record of the string of player name before the newline key

    player1->type = WHITE; // Assign colours and points to player 1
    player1->points = 2; // Initially there are 2 black disks on the board

    // Insert player 2 information:
    printf("Player 2 please insert your name: ");
    fgets(player2->name, 20, stdin);

    nameSize = strlen(player2->name);
    player2->name[nameSize -1] = '\0'; // End up the record of the string of player name before the newline key


    player2->type = BLACK; // Assign colours and points to player 2
    player2->points = 2; // Initially there are 2 white disks on the board
}

void initializeBoard(disk board [SIZE][SIZE])
{
    int i, j;

    for(i=0; i<SIZE; i++) // Board initialization
        for(j=0; j<SIZE; j++)
            if(i == 3) // When the compiler is executing to the forth row
                if(j == 3)
                    board[i][j].type = WHITE; // Initialize the position of white disk on the board in row 4 column 4

                else if(j == 4)
                        board[i][j].type = BLACK; // Initialize the position of black disk on the board in row 4 column 5
                    else
                        board[i][j].type = NONE; // The other position on the board with no disk on the row 4

            else if(i == 4) // When the compiler is executing to the fifth row
                if(j == 3)
                    board[i][j].type = BLACK; // Initialize the position of black disk on the board in row 5 column 4

                else if(j == 4) // Initialize the position of white disk on the board in row 5 column 5
                        board[i][j].type = WHITE;
                    else
                        board[i][j].type = NONE;  // The other position on the board with no disk on the row 5
            else
                board[i][j].type = NONE; // The other position on the board with no disk

            board[i][j].pos.row = i;
            board[i][j].pos.col = j;
}

// Function to print the intialized board
void printBoard(disk board[SIZE][SIZE])
{
    int i, j = 0;

    printf("\n    ");
    for(i=0; i<SIZE; i++)
        printf("%d   ",i);

    for(i=0; i< SIZE; i++)
    {
        printf("\n%d | ", i);

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

