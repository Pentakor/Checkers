//
// Created by Izabella Svavolya on 10/06/2023.
//

#include "Tree_Functions.h"
#include "Linked_List_Functions.h"

//=================================== B FUNCTIONS ===============================================

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
    if (moves_tree == NULL) //if there are moves at all
        return NULL;
    SingleSourceMovesList* list = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
    if (list == NULL)
    {
        printf("ERROR");
        exit(1);
    }
    makeEmptySingleSourceMovesList(list);//initializing the list to be returned
    FindSingleSourceOptimalMoveHelper(moves_tree->source,list);//recursive helping function that does the work
    return list;
}

void FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode * root, SingleSourceMovesList* list)
{
    if (root == NULL)
        return;

    checkersPos* currentpos = createnewpos(root->pos->col, root->pos->row);
    insertDataToEndSingleSourceMovesList(list, currentpos, root->total_captures_so_far);
    SingleSourceMovesList* listleft = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
    SingleSourceMovesList* listright = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
    if (listleft == NULL||listright==NULL)
    {
        printf("ERROR");
        exit(1);
    }
    makeEmptySingleSourceMovesList(listleft);
    makeEmptySingleSourceMovesList(listright);

    FindSingleSourceOptimalMoveHelper(root->next_move[1], listright);
    FindSingleSourceOptimalMoveHelper(root->next_move[0], listleft);
    combinethebestpath(list, listleft, listright);

}

void printbestpath(SingleSourceMovesList* list)
{
    SingleSourceMovesListCell* head = list->head;
    SingleSourceMovesListCell* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        if (head != NULL)
        {
            printf("%c%c->", temp->position->row, temp->position->col);
        }
        else
            printf("%c%c", temp->position->row, temp->position->col);
    }
}

void combinethebestpath(SingleSourceMovesList* dest, SingleSourceMovesList* left, SingleSourceMovesList* right)
{
    if (left->head != NULL || right->head != NULL)
    {

        if (right->head != NULL && left->head == NULL)
        {
            combinethebestpathhelper(dest, right);
            freeSingleSourceMovesList(left);
        }
        else if (left->head != NULL && right->head == NULL)
        {
            combinethebestpathhelper(dest, left);
            freeSingleSourceMovesList(right);
        }
        else if (right->tail->captures < left->tail->captures)
        {
            combinethebestpathhelper(dest, left);
            freeSingleSourceMovesList(right);
        }
        else if (right->tail->captures > left->tail->captures)
        {
            combinethebestpathhelper(dest, right);
            freeSingleSourceMovesList(left);
        }
        else if (TorB == TMOVE)
        {

            combinethebestpathhelper(dest, right);
            freeSingleSourceMovesList(left);
        }
        else
        {
            combinethebestpathhelper(dest, left);
            freeSingleSourceMovesList(right);
        }
    }
}

void combinethebestpathhelper(SingleSourceMovesList* dest, SingleSourceMovesList* addition)//"pasting" the addition list to the end of dest list
{

    if (dest->head != NULL)
    {
        dest->tail->next = addition->head;
        dest->tail = addition->tail;
    }
    else
    {
        dest->head = addition->head;
        dest->tail = addition->tail;
    }
}