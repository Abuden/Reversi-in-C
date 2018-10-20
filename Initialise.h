
#define SIZE 8 // Size of row & col

enum colour
{
    WHITE, // 0 // Player 1
    BLACK, // 1 // Player 2
    NONE // 2//
};

typedef struct position
{
    int row;
    int col;

} position;

typedef struct disk
{
    enum colour type; // Disk color
    position pos; // Position

} disk;

typedef struct player
{
    char name[20]; // Player name
    enum colour type; // Disk color
    int points; // Points

} player;

struct ListNode // Linked list is used to store the coords of possible moves per turn as requested by Liliana
{
	int r;
	int c;
	struct ListNode *nextPtr; // Self referential to point to the next node
};

typedef struct ListNode listNode; // Synonym for struct Listnode
typedef listNode *listNodePtr; // Synonym for pointer to a listnode

void initializePlayers(player *player1, player *player2);
void initializeBoard(disk board[SIZE][SIZE]);
void printBoard(disk board [SIZE][SIZE]);



