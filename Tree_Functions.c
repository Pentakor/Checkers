//
// Created by Izabella Svavolya on 10/06/2023.
//

#include "Tree_Functions.h"
#include "Linked_List_Functions.h"

//-----------------------------------------------SingleSourceMovesTree_Functions------------------------------------------------------------------
SingleSourceMovesTreeNode* createNewSingleSourceMovesTreeNode(Board board, checkersPos* pos, unsigned short total, SingleSourceMovesTreeNode* leftmove, SingleSourceMovesTreeNode* rightmove)
{
    SingleSourceMovesTreeNode* res;
    res = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
    if (res == NULL)
    {
        printf("ERROR!");
        exit(1);
    }
    copyboard(board, res->board);
    res->pos = pos;
    res->pos->row = pos->row;
    res->total_captures_so_far = total;
    res->next_move[0] = leftmove;
    res->next_move[1] = rightmove;
    return res;
}

void freeSingleSourceMovesTree(SingleSourceMovesTree* tr)
{
    freeSingleSourceMovesTreeHelper(tr->source);
    tr->source = NULL;
    free(tr);
}

void freeSingleSourceMovesTreeHelper(SingleSourceMovesTreeNode* root)
{
    if (root == NULL)
        return;
    else
    {

        if(root->next_move[0]!=NULL)
            freeSingleSourceMovesTreeHelper(root->next_move[0]);
        if (root->next_move[1]!= NULL)
            freeSingleSourceMovesTreeHelper(root->next_move[1]);

        /*free(root->board);//We cannot understand why this lines are making an error to accure, according to our knowledge from the course it's supposed to work.
        free(root->pos);*/
        free(root);
    }
}
