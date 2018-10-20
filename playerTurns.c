#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Initialise.h"
#include "findPlayerMoves.h"
#include "makePlayerMove.h"
#include "flipTiles.h"
#include "playerTurns.h"
#include "gameOver.h"

void getPlayerTurn(disk board[SIZE][SIZE], player *player1, player *player2)
{
    int turn = 1;
    int gameRunning = (SIZE*SIZE) - (player1->points + player2->points);

    listNodePtr sPtr = NULL;

    int row = 0;
    int col = 0;
    int moveChoice = 0;

    while (gameRunning)
    {
        if (turn % 2 != 0)
        {
            makeMove(board, player1, player2);

            getPlayerPoints(board, player1);

            turn++;
        }

        if (turn % 2 == 0)
        {
            makeMove(board, player2, player1);

            getPlayerPoints(board, player2);

            turn++;
        }

        gameRunning = (SIZE*SIZE) - (player1->points + player2->points);
    }
}

void makeMove(disk board[SIZE][SIZE], player *currentPlayer, player *opponentPlayer)
{
    int numOfMoves = 0;
    int moveChoice = 0;

    listNodePtr sPtr = NULL;

    getPlayerDisk(board, &sPtr, currentPlayer, opponentPlayer);

    printMove(sPtr, currentPlayer, &numOfMoves);

    if (numOfMoves != 0)
    {
        selectMove(numOfMoves, &moveChoice);
        traverseList(&sPtr, moveChoice, &row, &col);
        findOpponent(board, row, col, currentPlayer, opponentPlayer);
        printBoard(board); // Update board

    }

}
