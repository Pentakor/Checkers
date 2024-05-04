#include "Tree_Functions.h"
#include "Linked_List_Functions.h"

Player BeststreakPlayer;// variable for the biggest capture streak player

//////////////////////////////////MAIN_FUNCTIONS///////////////////////////////

void PlayGame(Board board, Player starting_player)
{
    //initializing game stats
    ISWON = -1;
    BmovesCount = 0;
    TmovesCount = 0;
    BcheckCount = 12;
    TcheckCount= 12;
    Beststreak = 0;

    //initializing player before entering the game loop

    Player currentplayer;

    if (starting_player == 'T')
        currentplayer = 'B';
    else
        currentplayer = 'T';
    displayBoard(board);

    while ((ISWON == -1)&&((BcheckCount!=0)&&(TcheckCount != 0)))
    {
        char scan;
        scanf("%c",&scan);//just to be able to see the game's proccess. every turn you should press a button to continue.
        if (currentplayer == 'T')//changing TURN player;
        {
            currentplayer = 'B';
            TorB = BMOVE;
        }
        else
        {
            currentplayer = 'T';
            TorB = TMOVE;
        }
        Turn(board, currentplayer);//making turn
    }
    if (ISWON == BMOVE|| TcheckCount == 0)
    {
        printf("\nB WINS!");
        printf("\nB performed %d moves.", BmovesCount);
    }
    else
    {
        printf("\nT WINS!");
        printf("\nT performed %d moves.", TmovesCount);
    }
    printf("\n%c performed the highest number of captures in a single move - %d\n\n", BeststreakPlayer, Beststreak);
}
////////////////////////////SUPPORT_FUNCTIONs//////////////////////////////////

//---------------------coordinate type change functions-------------------------
int rowtonum(char a)//row char to coordinate
{
    int anum = (int)a - 'A';
    return anum;
}

int coltonum(char a)//col char to coordinate
{
    int anum = (int)a - (int)'0' - 1;
    return anum;
}

char numtorow(int a)//row coordinate to char
{
    char achar = (char)(a + (int)'A');
    return achar;
}

char numtocol(int a)//col coordinate to char
{
    char achar = (char)(a + (int)'0' + 1);
    return achar;
}


//---------------------------------board functions-----------------------

void initializeBoard(Board board)
{
    int i, j;

    // Fill the board with empty spaces
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = ' ';
        }
    }

    // Fill the board with checkers pieces
    for (i = 0; i < BOARD_SIZE; i++) {
        for (j = 0; j < BOARD_SIZE; j++) {
            if ((i % 2 == 0 && j % 2 == 1 && i < 3) || (i % 2 == 1 && j % 2 == 0 && i < 3)) {
                board[i][j] = 'T'; // Represents player 1's piece
            }
            else if ((i % 2 == 0 && j % 2 == 1 && i > 4) || (i % 2 == 1 && j % 2 == 0 && i > 4)) {
                board[i][j] = 'B'; // Represents player 2's piece
            }
        }
    }
}

void initializeBoardTESTER(Board board)
{
    int i, j;
    for (i = 0; i < 8; i++)//fill the board with empty spaces
    {
        for (j = 0; j < 8; j++)
            board[i][j] = ' ';
    }
}

void displayBoard(Board board) {
    int i, j;
    printf("\n");
    // Print the column indicators
    printf("+-+-+-+-+-+-+-+-+-+\n");
    printf("+ |");
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("%d|", i + 1);
    }
    printf("\n");
    printf("+-+-+-+-+-+-+-+-+-+\n");
    // Print the board with row indicators
    for (i = 0; i < BOARD_SIZE; i++) {
        printf("|%c|", 'A' + i);
        for (j = 0; j < BOARD_SIZE; j++) {
            printf("%c|", board[i][j]);
        }
        printf("\n");
        printf("+-+-+-+-+-+-+-+-+-+\n");
    }
}

void copyboard(Board src, Board dest)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            dest[i][j] = src[i][j];
        }
    }
}

