//
// Created by Izabella Svavolya on 10/06/2023.
//

#include "Tree_Functions.h"
#include "Linked_List_Functions.h"

Player BeststreakPlayer;// variable for the biggest capture streak player
/////////////////////////////////////////////////D FUNCTIONS////////////////////////////////
void Turn(Board board, Player player)
{

    MultipleSourceMovesList* mlist = FindAllPossiblePlayerMoves(board, player);
    MultipleSourceMovesListCell* bestmove;
    int currentkillstreak;
    if (player == 'T')
    {
        bestmove = bestofthebestmoveT(mlist);//finding the turn's move
    }
    else
    {
        bestmove = bestofthebestmoveB(mlist);//finding the turn's move
    }
    currentkillstreak = bestmove->single_source_moves_list->tail->captures;
    themove(board, bestmove->single_source_moves_list, player);//deleting the checkers eaten by the move and changing the chekers position
    printf("\n%c's Turn\n", player);
    printbestpath(bestmove->single_source_moves_list);//printing the turn
    displayBoard(board);

    gamestatsupdate(currentkillstreak, player);//updating game stats
    freeMultipleSourceMovesList(*mlist);//BUGS HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}
void gamestatsupdate(int streak, Player player)
{
    if (player == 'T')
    {
        BcheckCount -= streak;
        TmovesCount++;
    }
    else
    {
        TcheckCount -= streak;
        BmovesCount++;
    }
    if (streak >= Beststreak)
    {
        Beststreak = streak;
        BeststreakPlayer = player;
    }


}
void themove(Board board, SingleSourceMovesList* list, Player player)
{
    int startcol, startrow, endcol, endrow, midcol, midrow;
    SingleSourceMovesListCell* currentstart = list->head;
    if (currentstart == NULL)
    {
        return;
    }
    board[rowtonum(currentstart->position->row)][coltonum(currentstart->position->col)] = ' ';
    SingleSourceMovesListCell* currentend = currentstart->next;
    while (currentstart != NULL && currentend != NULL)
    {
        startcol = coltonum(currentstart->position->col);
        startrow = rowtonum(currentstart->position->row);
        endcol = coltonum(currentend->position->col);
        endrow = rowtonum(currentend->position->row);
        if ((startrow + endrow) % 2 == 0)//it means that there was capture
        {
            midrow = (startrow + endrow) / 2;
            midcol = (startcol + endcol) / 2;
            board[midrow][midcol] = ' ';
        }
        currentstart = currentstart->next;
        currentend = currentend->next;
    }
    board[rowtonum(list->tail->position->row)][coltonum(list->tail->position->col)] = player;
    //checking if there is a win
    if (player == 'T')
    {
        if (list->tail->position->row == 'H')
            ISWON = TMOVE;
    }
    else
    {
        if (list->tail->position->row == 'A')
            ISWON = BMOVE;
    }
}
MultipleSourceMovesListCell* bestofthebestmoveB(MultipleSourceMovesList* mlist)
{
    MultipleSourceMovesListCell* current = mlist->head;
    MultipleSourceMovesListCell* bestmove = current;
    while (current != NULL)
    {
        if (current->single_source_moves_list->tail->captures > bestmove->single_source_moves_list->tail->captures)
        {
            bestmove = current;
        }
        else if (current->single_source_moves_list->tail->captures == bestmove->single_source_moves_list->tail->captures)
        {
            if (current->single_source_moves_list->tail != current->single_source_moves_list->head)
            {

                if (current->single_source_moves_list->tail->position->row < bestmove->single_source_moves_list->tail->position->row)
                {
                    bestmove = current;
                }
                else if (current->single_source_moves_list->tail->position->row == bestmove->single_source_moves_list->tail->position->row)
                {
                    if (current->single_source_moves_list->head->position->col <= bestmove->single_source_moves_list->head->position->col)
                        bestmove = current;
                }
            }
        }
        current = current->next;
    }
    return bestmove;
}
MultipleSourceMovesListCell* bestofthebestmoveT(MultipleSourceMovesList* mlist)
{
    MultipleSourceMovesListCell* current = mlist->head;
    MultipleSourceMovesListCell* bestmove = current;
    while (current != NULL)
    {
        if (current->single_source_moves_list->tail->captures > bestmove->single_source_moves_list->tail->captures)
        {
            bestmove = current;
        }
        else if (current->single_source_moves_list->tail->captures == bestmove->single_source_moves_list->tail->captures)
        {
            if (current->single_source_moves_list->tail != current->single_source_moves_list->head)
            {

                if (current->single_source_moves_list->tail->position->row > bestmove->single_source_moves_list->tail->position->row)
                {
                    bestmove = current;
                }
                else if (current->single_source_moves_list->tail->position->row == bestmove->single_source_moves_list->tail->position->row)
                {
                    if (current->single_source_moves_list->head->position->col >= bestmove->single_source_moves_list->head->position->col)
                        bestmove = current;
                }
            }
        }
        current = current->next;
    }
    return bestmove;
}