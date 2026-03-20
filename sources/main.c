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

static int isWinner(char symbol)
{
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
            return 1;
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
            return 1;
    }
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
        return 1;
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
        return 1;
    return 0;
}

static int findWinningMove(char symbol, int *x, int *y)
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != ' ')
                continue;
            board[i][j] = symbol;
            if (isWinner(symbol)) {
                board[i][j] = ' ';
                *x = i;
                *y = j;
                return 1;
            }
            board[i][j] = ' ';
        }
    }
    return 0;
}

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
    int x = -1;
    int y = -1;
    const int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    const int edges[4][2] = {{0, 1}, {1, 0}, {1, 2}, {2, 1}};

    if (findWinningMove(COMPUTER, &x, &y) || findWinningMove(PLAYER, &x, &y)) {
        board[x][y] = COMPUTER;
        return;
    }
    if (board[1][1] == ' ') {
        board[1][1] = COMPUTER;
        return;
    }
    for (int i = 0; i < 4; i++) {
        x = corners[i][0];
        y = corners[i][1];
        if (board[x][y] == ' ') {
            board[x][y] = COMPUTER;
            return;
        }
    }
    for (int i = 0; i < 4; i++) {
        x = edges[i][0];
        y = edges[i][1];
        if (board[x][y] == ' ') {
            board[x][y] = COMPUTER;
            return;
        }
    }
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
    char reset2 = ' ';
    int moveCount = 0;
    int first = 0;
    char currentPlayer = PLAYER;

    srand(time(NULL));

    while (reset != 'N') {
        winner = ' ';
        reset = ' ';
        resetBoard();
        first = rand() % 2;
        moveCount = 0;
        currentPlayer = (first == 0) ? PLAYER : COMPUTER;
        while (winner == ' ' && checkFreeSpace() != 0) {
            printf("Current player: %c\n", currentPlayer);
            printf("Move count: %d\n", moveCount);

            printBoard();
            if (currentPlayer == PLAYER) {
                playerMove();
            } else {
                computerMove();
            }
            moveCount++;
            winner = checkWinner();
            if (winner != ' ' || checkFreeSpace() == 0)
                break;
            currentPlayer = (currentPlayer == PLAYER) ? COMPUTER : PLAYER;
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