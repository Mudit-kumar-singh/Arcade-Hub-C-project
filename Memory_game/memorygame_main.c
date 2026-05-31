#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "memory_game.h"

int SIZE = 5;

int main() {
    srand(time(NULL));
    printWelcomeScreen();

    char name[50];
    int attempts = 0, matches = 0;

    char **board = allocateBoard(SIZE);
    int **revealed = allocateRevealed(SIZE);

    printf("[33mDo you want to load a saved game? (y/n):[0m ");
    char choice;
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        if (loadGame(name, board, revealed, SIZE, &attempts, &matches)) {
            printf("[32mGame loaded successfully![0m\n");
        } 
        else {
            printf("No saved game found. Starting new game.\n");
            initializeBoard(board, SIZE);
            shuffleBoard(board, SIZE);
            printf("[33mEnter your name:[0m ");
            scanf("%s", name);
        }
    } 
    else {
        initializeBoard(board, SIZE);
        shuffleBoard(board, SIZE);
        printf("[33mEnter your name:[0m ");
        scanf("%s", name);
    }

    while (matches < (SIZE * SIZE) / 2) {
        int r1, c1, r2, c2;

        clearScreen();
        printWelcomeScreen();
        printBoard(board, revealed, SIZE);

        printf("\n[33m%s[0m, [32mAttempt[0m #%d\n", name, attempts + 1);
        printf("[33mPick first tile (ROW and COL, e.g 0 1):[0m ");
        scanf("%d %d", &r1, &c1);

        revealTile(revealed, r1, c1);
        clearScreen();
        printWelcomeScreen();
        printBoard(board, revealed, SIZE);

        printf("\n[33mPick second tile (ROW and COL): [0m");
        scanf("%d %d", &r2, &c2);

        revealTile(revealed, r2, c2);
        clearScreen();
        printWelcomeScreen();
        printBoard(board, revealed, SIZE);

        if (checkMatch(board, r1, c1, r2, c2)) {
            printf("\n[1;32mMatch found![0m\n");
            matches++;
        } 
        else {
            printf("\n[1;31mNo match. HIDE the tiles!!.[0m\n");
            hideTiles(revealed, r1, c1, r2, c2);
        }

        attempts++;
        saveGame(name, board, revealed, SIZE, attempts, matches);

        printf("\nPress Enter to continue...");
        getchar(); getchar();
    }

    printf("\n[1;37mGreat job %s!!! You completed the game in %d attempts.[0m\n", name, attempts);
    if(attempts == 12 || (attempts > 12 && attempts <= 15)){
        printf("[1;32mYOU ARE A PRO!!!![0m");
    }
    if(attempts >= 16 && attempts <= 20 ){
        printf("[1;34mPRO LEVEL MASTERY IS CLOSE, WELL DONE!!![0m");
    }
    else{
        printf("[1;33mAVERAGE SCORE, LET'S PLAY AGAIN TO IMPROVE[0m");
    }
    saveHighScore(name, attempts);

    printf("\n High Scores:\n");
    displayHighScores();

    freeBoard(board, SIZE);
    freeRevealed(revealed, SIZE);
    return 0;
}