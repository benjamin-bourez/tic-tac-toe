/*
** EPITECH PROJECT, 2022
** tic-tac-toe
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "tic_tac_toe.h"

int checkFreeSpace(void)
{
    int free = 0;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == ' ')
                free++;
    return free;
}

void playerMove(void)
{
    int x;
    int y;

    printf("enter row (1-3): ");
    scanf("%d", &x);
    x--;
    printf("enter column (1-3): ");
    scanf("%d", &y);
    y--;
    if (board[x][y] != ' ') {
        printf("invalid move\n");
        playerMove();
    } else {
        board[x][y] = PLAYER;
    }
}

void computerMove(void)
{
    srand(time(0));
    int x = 0;
    int y = 0;

    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');
    board[x][y] = COMPUTER;
}

void resetBoard(void)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = ' ';
}

void printBoard(void)
{
    for (int i = 0; i < 3; i++) {
        printf("%c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        printf("---------\n");
    }
}

char checkWinner(void)
{
    //check row
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
    }
    //check column
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    //check diagonal
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
            return board[0][0];
    else if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
            return board[0][2];
    return ' ';
}

void printWinner(char winner)
{
    printBoard();
    if (winner == PLAYER)
        printf("You win\n");
    else if (winner == COMPUTER)
        printf("You lose\n");
    else 
        printf ("Tie\n");
}

int main(void)
{
    char winner = ' ';
    char reset = ' ';
    char reset2= ' ';

    while (reset != 'N') {
        winner = ' ';
        reset = ' ';
        resetBoard();
        while (winner == ' ' && checkFreeSpace() != 0) {
            printBoard();
            playerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpace() == 0)
            {
                break;
            }
            computerMove();
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpace() == 0)
            {
                break;
            }
        }
        printWinner(winner);
        do {
            printf("Do you want to play again (Y/N): ");
            scanf("%c", &reset);
            scanf("%c", &reset2);
            reset = toupper(reset2);
        } while (reset != 'Y' && reset != 'N');
    }
    printf("Thanks for playing\n");
}