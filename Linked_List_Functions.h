//
// Created by Izabella Svavolya on 10/06/2023.
//

#ifndef UNTITLED32_LINKED_LIST_FUNCTIONS_H
#define UNTITLED32_LINKED_LIST_FUNCTIONS_H

typedef struct _SingleSourceMovesListCell
{
    checkersPos* position;
    unsigned short captures;
    struct _SingleSourceMovesListCell* next;
}SingleSourceMovesListCell;


typedef struct _SingleSourceMovesList
{
    SingleSourceMovesListCell* head;
    SingleSourceMovesListCell* tail;
}SingleSourceMovesList;

typedef struct _multipleSourceMovesListCell
{
    SingleSourceMovesList* single_source_moves_list;
    struct _multipleSourceMovesListCell* next;
}MultipleSourceMovesListCell;

typedef struct _multipleSourceMovesList
{
    MultipleSourceMovesListCell* head;
    MultipleSourceMovesListCell* tail;
}MultipleSourceMovesList;


void makeEmptySingleSourceMovesList(SingleSourceMovesList* lst);

bool isEmptySingleSourceMovesList(SingleSourceMovesList* lst);
//checking if the list is empty

SingleSourceMovesListCell* createNewSingleSourceMovesListCell(checkersPos* position, unsigned short captures, SingleSourceMovesListCell* next);

void insertDataToEndSingleSourceMovesList(SingleSourceMovesList* lst, checkersPos* position, unsigned short captures);

void insertNodeToSingleSourceMovesList(SingleSourceMovesList* lst, SingleSourceMovesListCell* tail);

void freeSingleSourceMovesList(SingleSourceMovesList * lst);
//freeing all allocated memory of the list

void makeEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst);

bool isEmptyMultipleSourceMovesList(MultipleSourceMovesList* lst);

MultipleSourceMovesListCell* createNewMultipleSourceMovesListCell(SingleSourceMovesList* single_source_moves_list, MultipleSourceMovesListCell* next);

void insertDataToEndMultipleSourceMovesList(MultipleSourceMovesList* lst, SingleSourceMovesList* single_source_moves_list);

void insertNodeToMultipleSourceMovesList(MultipleSourceMovesList* lst, MultipleSourceMovesListCell* tail);

void freeMultipleSourceMovesList(MultipleSourceMovesList lst);
//freeing all allocated memory of the list

bool istherechecker(Board board, checkersPos* src);
//checking if there is a checker in the given position on the board

SingleSourceMovesTreeNode* FindSingleSourceMovesHelper_T(Board board, checkersPos* src,int captures);
//recursive function for the tree build if the tree is for T checker

SingleSourceMovesTreeNode* FindSingleSourceMovesHelper_B(Board board, checkersPos* src,int captures);
//recursive function for the tree build if the tree is for B checker

checkersPos* createnewpos(char col, char row);

bool istherepass_T(Board board, checkersPos* src, int direction, int* flag);
//checking if there's a pass for the given T cheker's position in the given direction. returning in flag 0 if there is pass without cuptures and 1 if there was captures

bool istherepass_B(Board board, checkersPos* src, int direction, int* flag);
//checking if there's a pass for the given B cheker's position in the given direction. returning in flag 0 if there is pass without cuptures and 1 if there was captures

void printtree(SingleSourceMovesTreeNode* root);
//test function

void FindSingleSourceOptimalMoveHelper(SingleSourceMovesTreeNode* root, SingleSourceMovesList* list);
//recursive function that finds the optimal move for one specific checker

void combinethebestpath(SingleSourceMovesList* dest, SingleSourceMovesList* left, SingleSourceMovesList* right);//choose the best pass between left and right and combines it with the dest pass

void combinethebestpathhelper(SingleSourceMovesList* dest, SingleSourceMovesList* addition);
//helping function for combinethebestpath function

void printbestpath(SingleSourceMovesList* list);
//printing the given pass coordinates

void FindAllPossiblePlayerMovesHelper(int row, int col, Board board, MultipleSourceMovesList* mlist);
//helping function for the FindAllPossiblePlayerMoves function

char numtorow(int a);
//getting matrix value of row and returning its board value

char numtocol(int a);
//getting matrix value of col and returning its board value

int rowtonum(char a);
//getting char of the row and returning its matrix value

int coltonum(char a);
//getting char of the column and returning its matrix value

void printmultlist(MultipleSourceMovesList* mlist);
//testing function

MultipleSourceMovesListCell* bestofthebestmoveT(MultipleSourceMovesList* mlist);
//returning the list cell containing the best move for the T player to make.

MultipleSourceMovesListCell* bestofthebestmoveB(MultipleSourceMovesList* mlist);
//returning the list cell containing the best move for the B player to make.

void themove(Board board, SingleSourceMovesList* list, Player player);
//helping function for turn function. makes the changes on the board according to the given move

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree *moves_tree);

MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board,Player player);


#endif //UNTITLED32_LINKED_LIST_FUNCTIONS_H
