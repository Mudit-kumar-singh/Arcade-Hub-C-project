
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory_game.h"

void saveGame(const char *name, char **board, int **revealed, int size, int attempts, int matches) {
    FILE *fp = fopen("savegame.txt", "w");
    if (!fp) return;

    fprintf(fp, "%s\n%d %d %d\n", name, size, attempts, matches);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            fprintf(fp, "%c ", board[i][j]);
        fprintf(fp, "\n");
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            fprintf(fp, "%d ", revealed[i][j]);
        fprintf(fp, "\n");
    }

    fclose(fp);
}

int loadGame(char *name, char **board, int **revealed, int size, int *attempts, int *matches) {
    FILE *fp = fopen("savegame.txt", "r");
    if (!fp) return 0;

    int fileSize;
    fscanf(fp, "%s\n%d %d %d\n", name, &fileSize, attempts, matches);

    if (fileSize != size) {
        fclose(fp);
        return 0;
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            fscanf(fp, " %c", &board[i][j]);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            fscanf(fp, "%d", &revealed[i][j]);

    fclose(fp);
    return 1;
}

void saveHighScore(const char *name, int attempts) {
    FILE *fp = fopen("highscores.txt", "a");
    if (!fp) return;
    fprintf(fp, "%s %d\n", name, attempts);
    fclose(fp);
}

void displayHighScores() {
    FILE *fp = fopen("highscores.txt", "r");
    if (!fp) {
        printf("No high scores recorded yet.\n");
        return;
    }

    char name[50];
    int score;
    while (fscanf(fp, "%s %d", name, &score) != EOF)
        printf(" %s - %d attempts\n", name, score);

    fclose(fp);
}
