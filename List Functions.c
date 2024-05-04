//
// Created by Izabella Svavolya on 10/06/2023.
//

#include "Tree_Functions.h"
#include "Linked_List_Functions.h"

//-----------------------------------------------------------------------------------------------------------------
//------------------------------------SingleSourceMovesList_functions-----------------------------------------------
void makeEmptySingleSourceMovesList(SingleSourceMovesList* lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}

bool isEmptySingleSourceMovesList(SingleSourceMovesList* lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

SingleSourceMovesListCell* createNewSingleSourceMovesListCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next)
{
    SingleSourceMovesListCell* res;
    res = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
    if (res == NULL)
    {
        printf("ERROR!");
        exit(1);
    }
    res->position = position;
    res->captures = captures;
    res->next = next;
    return res;
}

void insertDataToEndSingleSourceMovesList(SingleSourceMovesList* lst, checkersPos* position, unsigned short captures)
{
    SingleSourceMovesListCell* newTail;
    newTail = createNewSingleSourceMovesListCell(position, captures, NULL);
    insertNodeToSingleSourceMovesList(lst, newTail);
}

void insertNodeToSingleSourceMovesList(SingleSourceMovesList* lst, SingleSourceMovesListCell* tail)
{
    if (isEmptySingleSourceMovesList(lst) == true) {
        lst->head = lst->tail = tail;
    }
    else {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}

void freeSingleSourceMovesList(SingleSourceMovesList *lst)
{
    SingleSourceMovesListCell* tmp;
    SingleSourceMovesListCell* head = lst->head;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free(tmp->position);
        free(tmp);
    }
    free(lst);
}
//-----------------------------------------------------------------------------------------------------------------
//------------------------------------MultipleSourceMovesList_functions-----------------------------------------------
void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}

bool isEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst)
{
    if (lst->head == NULL)
        return true;
    else
        return false;
}

MultipleSourceMovesListCell* createNewMultipleSourceMovesListCell(SingleSourceMovesList* single_source_moves_list, MultipleSourceMovesListCell* next)
{
    MultipleSourceMovesListCell* res;
    res = (MultipleSourceMovesListCell*)malloc(sizeof(MultipleSourceMovesListCell));
    if (res == NULL)
    {
        printf("ERROR!");
        exit(1);
    }
    res->single_source_moves_list = single_source_moves_list;
    res->next = next;
    return res;
}

void insertDataToEndMultipleSourceMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_source_moves_list)
{
    MultipleSourceMovesList* newTail;
    newTail = createNewMultipleSourceMovesListCell(single_source_moves_list, NULL);
    insertNodeToMultipleSourceMovesList(lst, newTail);
}

void insertNodeToMultipleSourceMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* tail)
{
    if (isEmptyMultipleSourceMovesList(lst) == true) {
        lst->head = lst->tail = tail;
    }
    else {
        lst->tail->next = tail;
        lst->tail = tail;
    }
    tail->next = NULL;
}

void freeMultipleSourceMovesList(MultipleSourceMovesList lst) {
    MultipleSourceMovesListCell* headNode = lst.head;
    MultipleSourceMovesListCell* currentNode;
    while (headNode != NULL) {
        currentNode = headNode;
        headNode = headNode->next;
        freeSingleSourceMovesList(currentNode->single_source_moves_list);
        free(currentNode);
    }
}
