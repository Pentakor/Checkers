//
// Created by Izabella Svavolya on 10/06/2023.
//

#include "Tree_Functions.h"
#include "Linked_List_Functions.h"

/////////////////////////////////////////////////C FUNCTIONS/////////////////////////////////
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
    MultipleSourceMovesList* mlist = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
    if (mlist == NULL)
    {
        printf("ERROR");
        exit(1);
    }
    makeEmptyMultipleSourceMovesList(mlist);
    if (player == 'T')//for player T the list will be from up left to down right
    {

        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (board[i][j] == player)
                {
                    FindAllPossiblePlayerMovesHelper(i, j, board, mlist);
                }
            }
        }
    }
    else//for player B the list will be from down right to up left
    {
        for (int i = 7; i >= 0; i--)
        {
            for (int j = 7; j >= 0; j--)
            {
                if (board[i][j] == player)
                {
                    FindAllPossiblePlayerMovesHelper(i, j, board, mlist);
                }
            }
        }

    }
    return mlist;
}


// Player "player" parameter is never used here//
void FindAllPossiblePlayerMovesHelper(int row, int col, Board board, MultipleSourceMovesList* mlist)
{
    checkersPos pos;
    pos.col = numtocol(col);
    pos.row = numtorow(row);

    SingleSourceMovesTree* tree = FindSingleSourceMoves(board, &pos);
    SingleSourceMovesList* passlist = FindSingleSourceOptimalMove(tree);
    insertDataToEndMultipleSourceMovesList(mlist, passlist);
    freeSingleSourceMovesTree(tree);///BUGS HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}


void printmultlist(MultipleSourceMovesList* mlist)
{
    MultipleSourceMovesListCell* head = mlist->head;
    while (head != NULL)
    {
        printbestpath(head->single_source_moves_list);
        printf("\n");
        head = head->next;
    }
}
