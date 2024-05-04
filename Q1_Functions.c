//
// Created by Izabella Svavolya on 10/06/2023.
//

#include "Tree_Functions.h"
#include "Linked_List_Functions.h"


SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src) //MAATEFET
{
    if (istherechecker(board, src))//if there is no checker return null;
    {
        SingleSourceMovesTree* tree;
        tree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));//create tree
        if (tree == NULL)
        {
            printf("ERROR!");
            exit(1);
        }
        if (board[rowtonum(src->row)][coltonum(src->col)] == 'T')//if the checker is T player's
        {
            tree->source = FindSingleSourceMovesHelper_T(board, src,0);
        }
        else
        {
            tree->source = FindSingleSourceMovesHelper_B(board, src,0);//if the checker is B player's
        }
        return tree;
    }
    return NULL;
}

SingleSourceMovesTreeNode* FindSingleSourceMovesHelper_T(Board board, checkersPos* src,int captures)//THE RECURSIVE FUNCTION FOR T CHECKERS
{
    SingleSourceMovesTreeNode* root = createNewSingleSourceMovesTreeNode(board, src, captures, NULL, NULL);
    if (root == NULL)
    {
        printf("ERROR!");
        exit(1);
    }
    int CflagR = 0;//0 if the move is without captures, 1 if with captures.
    int CflagL = 0;//0 if the move is without captures, 1 if with captures.
    bool istherepassR = istherepass_T(board, src, RIGHT, &CflagR);
    bool istherepassL = istherepass_T(board, src, LEFT, &CflagL);
    if (istherechecker(board, src))
    {
        if (istherepassR)
        {
            if (CflagR == 0)
                root->next_move[1] = createNewSingleSourceMovesTreeNode(board, createnewpos(src->col + 1, src->row + 1), captures, NULL, NULL);
            else
                root->next_move[1] = FindSingleSourceMovesHelper_T(board, createnewpos(src->col + 2, src->row + 2), captures + 1);
        }
        else
            root->next_move[1] = NULL;
        if (istherepassL)
        {
            if (CflagL == 0)
                root->next_move[0] = createNewSingleSourceMovesTreeNode(board, createnewpos(src->col -1, src->row + 1), captures, NULL, NULL);
            else
                root->next_move[0] = FindSingleSourceMovesHelper_T(board, createnewpos(src->col - 2, src->row + 2), captures + 1);
        }
        else
            root->next_move[0] = NULL;
    }
    else
    {
        if (istherepassR && CflagR == 1)
            root->next_move[1] = FindSingleSourceMovesHelper_T(board, createnewpos(src->col + 2, src->row + 2), captures + 1);
        else
            root->next_move[1] = NULL;
        if (istherepassL && CflagL == 1)
        {
            root->next_move[0] = FindSingleSourceMovesHelper_T(board, createnewpos(src->col - 2, src->row + 2), captures + 1);
        }
        else
            root->next_move[0] = NULL;
    }
    return root;
}

SingleSourceMovesTreeNode* FindSingleSourceMovesHelper_B(Board board, checkersPos* src,int captures)//THE RECURSIVE FUNCTION FOR B CHECKERS
{
    SingleSourceMovesTreeNode* root = createNewSingleSourceMovesTreeNode(board, src, captures, NULL, NULL);
    if (root == NULL)
    {
        printf("ERROR!");
        exit(1);
    }
    int CflagR = 0;//0 if the move is without captures, 1 if with captures.
    int CflagL = 0;//0 if the move is without captures, 1 if with captures.
    bool istherepassR = istherepass_B(board, src, RIGHT, &CflagR);
    bool istherepassL = istherepass_B(board, src, LEFT, &CflagL);
    if (istherechecker(board, src))
    {
        if (istherepassR)
        {
            if (CflagR == 0)
                root->next_move[1] = createNewSingleSourceMovesTreeNode(board, createnewpos(src->col + 1, src->row - 1), captures, NULL, NULL);
            else
                root->next_move[1] = FindSingleSourceMovesHelper_B(board, createnewpos(src->col + 2, src->row - 2), captures + 1);
        }
        else
            root->next_move[1] = NULL;
        if (istherepassL)
        {
            if (CflagL == 0)
                root->next_move[0] = createNewSingleSourceMovesTreeNode(board, createnewpos(src->col - 1, src->row - 1), captures, NULL, NULL);
            else
                root->next_move[0] = FindSingleSourceMovesHelper_B(board, createnewpos(src->col - 2, src->row - 2), captures + 1);
        }
        else
            root->next_move[0] = NULL;
    }
    else
    {
        if (istherepassR && CflagR == 1)
            root->next_move[1] = FindSingleSourceMovesHelper_B(board, createnewpos(src->col + 2, src->row - 2), captures + 1);
        else
            root->next_move[1] = NULL;
        if (istherepassL && CflagL == 1)
        {
            root->next_move[0] = FindSingleSourceMovesHelper_B(board, createnewpos(src->col - 2, src->row - 2), captures + 1);
        }
        else
            root->next_move[0] = NULL;
    }
    return root;
}

bool istherepass_B(Board board, checkersPos* src, int direction, int* flag)
{
    char directionvarone;
    char directionvarborder;
    int col = coltonum(src->col);
    int row = rowtonum(src->row);
    if (direction == LEFT)
    {
        directionvarone = '2';
        directionvarborder = '1';
    }
    else
    {
        directionvarone = '7';
        directionvarborder = '8';
    }
    if (src->col == directionvarborder || src->row == 'A')
        return false;
    if (src->col == directionvarone)
    {
        if (board[row - 1][col + direction] != ' ')
            return false;
    }
    if (board[row - 1][col + direction] == 'B')
        return false;
    if (src->row == 'B')
    {
        if (board[row - 1][col + direction] != ' ')
            return false;
    }

    else if (board[row - 1][col + direction] == 'T' && (src->col != directionvarone && src->row != 'B'))
    {
        *flag = 1;
        if (board[row - 2][col + 2 * direction] != ' ')
            return false;
    }
    return true;
}

bool istherepass_T(Board board, checkersPos* src, int direction,int *flag)
{
    char directionvarone;
    char directionvarborder;
    int col = coltonum(src->col);
    int row = rowtonum(src->row);
    if (direction == LEFT)
    {
        directionvarone = '2';
        directionvarborder = '1';
    }
    else
    {
        directionvarone = '7';
        directionvarborder = '8';
    }

    if (src->col == directionvarborder || src->row == 'H')
        return false;
    if (src->col == directionvarone)
    {
        if (board[row + 1][col + direction] != ' ')
            return false;
    }
    if (board[row + 1][col + direction] == 'T')
        return false;
    if (src->row == 'G')
    {
        if (board[row + 1][col + direction] != ' ')
            return false;
    }
    else if (board[row + 1][col + direction] == 'B'&&(src->col!=directionvarone&&src->row!='G'))
    {
        *flag = 1;
        if (board[row + 2][col + 2 * direction] != ' ')
            return false;
    }
    return true;
}

checkersPos* createnewpos(char col, char row)
{
    checkersPos* newpos = (checkersPos*)malloc(sizeof(checkersPos));
    if (newpos == NULL)
    {
        printf("ERROR");
        exit(1);
    }
    newpos->col = col;
    newpos->row = row;
    return newpos;
}

bool istherechecker(Board board,checkersPos * src)//checking if there is a checker in given position
{
    int col = coltonum(src->col);
    int row = rowtonum(src->row);
    if(board[row][col] == ' ')
        return false;
    else
        return true;
}

void printtree(SingleSourceMovesTreeNode* root)
{
    if (root == NULL)
        return;
    else
    {
        printtree(root->next_move[0]);
        printf("%c%c ", root->pos->row, root->pos->col);
        printtree(root->next_move[1]);
    }
}
