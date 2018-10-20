
// Reversi in C//

// Written by Braddy Yeoh - 17357376 //
// Written by Ee En Goh - //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Initialise.h"
#include "findPlayerMoves.h"
#include "makePlayerMove.h"
#include "flipTiles.h"
#include "playerTurns.h"
#include "gameOver.h"


int main()
{
    //setbuf(stdout, NULL);

    player player1 = {{NULL}, WHITE, 2}; // Declaration of player1 and player 2 with their information
    player player2 = {{NULL}, BLACK, 2};

    disk board[SIZE][SIZE]; // Declaration of the board with size 8x8

    initializePlayers(&player1, &player2);  // Function to initialize the players with their input information

    initializeBoard(board); // Function to initialize the whole board : with 2 black and white disks located on the middle of the board diagonally

    printBoard(board); // Function to print the initialized board

    getPlayerTurn(board, &player1, &player2); // Function to find the valid moves for players

	endScore(board, &player1, &player2); // Function to print the winner and store the game details
}
