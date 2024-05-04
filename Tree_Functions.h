//
// Created by Izabella Svavolya on 10/06/2023.
//

#ifndef UNTITLED32_TREE_FUNCTIONS_H
#define UNTITLED32_TREE_FUNCTIONS_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int TorB; //TMOVE or BMOVE  (flag for second section task function)

int ISWON;//-1 - no winner, TMOVE if T player won, BMOVE is B player won

int BmovesCount;//counter for amount of B player moves

int TmovesCount;//counter for amount of T player moves

int BcheckCount;//counter for B checkers amount on the board

int TcheckCount;//counter for T checkers amount on the board

int Beststreak;//counter for the biggest capture streak made,

////////////////////////////TYPES_STRUCTS_AND_DEFINES////////////////////////////
#define BOARD_SIZE 8
#define RIGHT 1//move direction flag
#define LEFT -1//move direction flag
#define TMOVE 1//wich player move flag
#define BMOVE 0//wich player move flag

typedef struct _checkersPos
{
    char row, col;
}checkersPos;

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct _SingleSourceMovesTreeNode
{
    Board board;
    checkersPos* pos;
    unsigned short total_captures_so_far;
    struct _SingleSourceMovesTreeNode* next_move[2];

}SingleSourceMovesTreeNode;


typedef struct _SingleSourceMovesTree
{
    SingleSourceMovesTreeNode* source;
}SingleSourceMovesTree;


////////////////////////////SUPPORT_FUNCTIONs_PROTOTYPES///////////////////////

void initializeBoard(Board board);
//initializing the board to start game postion

void initializeBoardTESTER(Board board);
//initializing empty board. function for code testing

void displayBoard(Board board);
//printing the board

SingleSourceMovesTreeNode* createNewSingleSourceMovesTreeNode(Board board, checkersPos* pos, unsigned short total, SingleSourceMovesTreeNode* leftmove, SingleSourceMovesTreeNode* rightmove);

void copyboard(Board src, Board dest);
//copying board fron src to dest

void freeSingleSourceMovesTree(SingleSourceMovesTree* tr);
//freeing all allocated memory of the tree

void freeSingleSourceMovesTreeHelper(SingleSourceMovesTreeNode* root);
//freeing all allocated memory of the tree node and its children


void gamestatsupdate(int streak, Player player);
//updates the game statistics needed in the 5th section task

/////////////////////////////MAIN_FUNCTIONS_PROTOTYPES/////////////////////////

SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos *src);

void Turn(Board board, Player player);

void PlayGame(Board board, Player starting_player);

#endif //UNTITLED32_TREE_FUNCTIONS_H
