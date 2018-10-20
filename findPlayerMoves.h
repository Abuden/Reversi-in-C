void getPlayerDisk(disk board[SIZE][SIZE], listNodePtr *sPtr, player *currentPlayer, player *opponentPlayer);

void getValidMoves(disk board[SIZE][SIZE], int r, int c, listNodePtr *sPtr, player *currentPlayer, player *opponentPlayer);

void insertList(listNodePtr *sPtr, int row, int col);

int checkList(listNodePtr currentPtr, int row, int col);

