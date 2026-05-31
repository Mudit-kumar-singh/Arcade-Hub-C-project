#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "memory_game.h"

char **allocateBoard(int size) {
    char **board = (char **)malloc(size * sizeof(char *));
    for (int i = 0; i < size; i++){
        board[i] = (char *)malloc(size * sizeof(char));
    }
    return board;
}

// for the ones which are being paired to display them
int **allocateRevealed(int size) {
    int **revealed = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++){
        revealed[i] = (int *)calloc(size, sizeof(int));
    }
    return revealed;
}

// free the memory allocation
void freeBoard(char **board, int size) {
    for (int i = 0; i < size; i++){
        free(board[i]);
    }
    free(board);
}

void freeRevealed(int **revealed, int size) {
    for (int i = 0; i < size; i++){
        free(revealed[i]);
    }
    free(revealed);
}

// randomly assigned any 13 alphabets which would be entered into the grid
void initializeBoard(char **board, int size) {
    char symbols[] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M'
    }; 

    int index = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++) {
            board[i][j] = symbols[index / 2];
            index++;
        }
    }
}

void shuffleBoard(char **board, int size) {
    for (int i = size * size - 1; i > 0; i--) {
        int x1 = i / size;
        int y1 = i % size;
        int j = rand() % (i + 1);
        int x2 = j / size;
        int y2 = j % size;

        char temp = board[x1][y1];
        board[x1][y1] = board[x2][y2];
        board[x2][y2] = temp;
    }
}

void printBoard(char **board, int **revealed, int size) {
    printf("\n     ");
    for (int j = 0; j < size; j++)
        printf("   [1;31m%d[0m   ", j);
    printf("\n        +");
    for (int j = 0; j < size; j++)
        printf("----+");
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf(" [1;31m%d[0m     |", i);
        for (int j = 0; j < size; j++) {
            if (revealed[i][j])
                printf("   [1;35m%c[0m   |", board[i][j]);
            else
                printf("  [1;36m*[0m  |");
        }
        printf("\n        +");
        for (int j = 0; j < size; j++)
            printf("----+");
        printf("\n");
    }
}
 // checking the matched pair function
int checkMatch(char **board, int r1, int c1, int r2, int c2) {
    return (board[r1][c1] == board[r2][c2]) && !(r1 == r2 && c1 == c2);
}

// once paired made the pair would be remained 
void revealTile(int **revealed, int row, int col) {
    revealed[row][col] = 1;
}

// add the tiles if the pair is not formed
void hideTiles(int **revealed, int r1, int c1, int r2, int c2) {
    for (int i = 0; i < 25; i++);
    revealed[r1][c1] = 0;
    revealed[r2][c2] = 0;
}

void clearScreen() {
    system("cls");
}

void printWelcomeScreen() {
    clearScreen();
    printf("[1;37m=====================================[0m\n");
    printf("        [1;36mMEMORY MATCHING GAME[0m        \n");
    printf("[1;37m=====================================[0m\n");
    printf(" [1;32mMatch all the pairs with least tries[0m\n");
    printf(" [1;32mBoard size: 5 x 5 (Positions: 0-4)[0m   \n");
    printf("[1;37m-------------------------------------[0m\n");
}