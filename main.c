#include "Tree_Functions.h"
#include "Linked_List_Functions.h"

///////////////////////////////////////MAIN////////////////////////////////////
int main()
{
    Board board;
    initializeBoard(board);

    printf("*************CHEKERS GAME PROJECT*************\n");
    printf("\nBy: David Weiss & Izabella Svavolya\n");
    printf("\n\n\n\nPlease Choose starting player: \n1 - for T\n2 - for B\n");
    int num;
    Player player;

    scanf("%d", &num);
    while (num != 1 && num != 2)
    {
        printf("\nINCORRECT INPUT!\n");
        scanf("%d", &num);
    }
    if (num == 1)//choosing which player starts the game
    {
        player = 'T';
    }
    else
    {
        player = 'B';
    }
    PlayGame(board, player);
}

///////////////////////////////////////////////////////////////////////////////

