#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game2048.h"

int SIZE = 4;
int board[MAX_SIZE][MAX_SIZE];
int score = 0;
int highscore = 0;
int previ_board[MAX_SIZE][MAX_SIZE];
int previousScore = 0;

// this function is used to directly give command to grid to make movemnts instead of clicking enter again and again
void waitForEnter() {
    printf("\n\033[1;32mPress Enter to continue...\033[0m");
    while (getchar() != '\n'); 
    getchar(); 
}
void loadHighscore() {
    FILE *f = fopen(HIGHSCORE_FILE, "r");
    if (f != NULL) {
        fscanf(f,"%d",&highscore);
        fclose(f);
    }
}

// highscore in the leaderboard fuction
void saveHighscore() {
    if (score > highscore) {
        FILE *f = fopen(HIGHSCORE_FILE, "w");
        if (f != NULL) {
            fprintf(f,"%d",score);
            fclose(f);
        }
    }
}

// used when undo feature is requested by the player
void saveState() {
    previousScore = score;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            previ_board[i][j] = board[i][j];
        }
    }
}
void undoMove() {
    score = previousScore;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            board[i][j] = previ_board[i][j];
        }
    }
}

// save pre exisiting code
void saveGame() {
    FILE *f = fopen("savegame.dat", "wb");
    if (f) {
        fwrite(&SIZE, sizeof(int), 1, f);
        fwrite(&score, sizeof(int), 1, f);
        fwrite(board, sizeof(int), MAX_SIZE * MAX_SIZE, f);
        fclose(f);
    }
}

void loadGame() {
    FILE *f = fopen("savegame.dat", "rb");
    if (f) {
        fread(&SIZE, sizeof(int), 1, f);
        fread(&score, sizeof(int), 1, f);
        fread(board, sizeof(int), MAX_SIZE * MAX_SIZE, f);
        fclose(f);
    }
}
// print the grid interface
void printBoard() {
    system("cls");
    printf("---------------------------- [1;33m2048 Game[0m ----------------------------\n");
    printf("[1;33mScore: %d  |  High Score: %d[0m\n",score, highscore);
    printf("[1;32mControls (for movements) W = Up | A = Left | S = Down | D = Right, U = Undo, Q = Quit[0m\n\n");

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int val = board[i][j];
            if (val == 0) {
                printf("   . ");
            } else {
                int color = 31 + (val % 6);
                printf("\033[1;%dm%4d\033[0m ", color, val);
            }
        }
        printf("\n");
    }
}

// random generator function when we load a new game 
void addRandomTile() {
    int empty[MAX_SIZE * MAX_SIZE][2], count = 0;
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            if (board[i][j] == 0) {
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0) {
        int r = rand() % count;
        int val = (rand() % 10 == 0) ? 4 : 2;
        board[empty[r][0]][empty[r][1]] = val;
    }
}

// function to moderate commands
int slideAndMerge(int row[MAX_SIZE]) {
    int moved = 0, temp[MAX_SIZE] = {0}, idx = 0;

    for (int i = 0; i < SIZE; i++) {
        if (row[i] != 0) {
            if (temp[idx] == 0) {
                temp[idx] = row[i];
            } else if (temp[idx] == row[i]) {
                temp[idx++] *= 2;
                score += temp[idx - 1];
            } else {
                temp[++idx] = row[i];
            }
        }
    }

    for (int i = 0; i < SIZE; i++) {
        if (row[i] != temp[i]) {
            row[i] = temp[i];
            moved = 1;
        }
    }

    return moved;
}

void rotateClockwise() {
    int temp[MAX_SIZE][MAX_SIZE];
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            temp[j][SIZE - 1 - i] = board[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            board[i][j] = temp[i][j];
        }
    }
}

int moveLeft() {
    int moved = 0;
    for (int i = 0; i < SIZE; i++) {
        if (slideAndMerge(board[i])) {
            moved = 1;
        }
    }
    return moved;
}

int makeMove(char move) {
    int moved = 0;
    saveState();

    switch (move) {
        case 'w': case 'W':
            rotateClockwise(); rotateClockwise(); rotateClockwise();
            moved = moveLeft();
            rotateClockwise();
            break;
        case 's': case 'S':
            rotateClockwise();
            moved = moveLeft();
            rotateClockwise(); rotateClockwise(); rotateClockwise();
            break;
        case 'a': case 'A':
            moved = moveLeft();
            break;
        case 'd': case 'D':
            rotateClockwise(); rotateClockwise();
            moved = moveLeft();
            rotateClockwise(); rotateClockwise();
            break;
    }

    return moved;
}

int canMove() {
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                return 1;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1])
                return 1;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j])
                return 1;
        }
    return 0;
}


#include <string.h>

Player leaderboard[MAX_PLAYERS];
int playerCount = 0;

void saveToLeaderboard(const char *name, int score) {
    FILE *f = fopen("leaderboard.txt", "r");
    playerCount = 0;
    if (f) {
        while (fscanf(f, "%s %d", leaderboard[playerCount].name, &leaderboard[playerCount].score) == 2) {
            playerCount++;
            if (playerCount >= MAX_PLAYERS) break;
        }
        fclose(f);
    }

    int found = 0;
    for (int i = 0; i < playerCount; i++) {
        if (strcmp(leaderboard[i].name, name) == 0) {
            if (score > leaderboard[i].score) leaderboard[i].score = score;
            found = 1;
            break;
        }
    }

    if (!found && playerCount < MAX_PLAYERS) {
        strcpy(leaderboard[playerCount].name, name);
        leaderboard[playerCount].score = score;
        playerCount++;
    }

    for (int i = 0; i < playerCount - 1; i++) {
        for (int j = i + 1; j < playerCount; j++) {
            if (leaderboard[j].score > leaderboard[i].score) {
                Player temp = leaderboard[i];
                leaderboard[i] = leaderboard[j];
                leaderboard[j] = temp;
            }
        }
    }

    f = fopen("leaderboard.txt", "w");
    if (f != NULL) {
        for (int i = 0; i < playerCount; i++) {
            fprintf(f, "%s %d\n", leaderboard[i].name, leaderboard[i].score);
        }
        fclose(f);
    }
}

void appendToAllScores(const char *name, int score) {
    FILE *f = fopen("all_scores.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s %d\n", name, score);
        fclose(f);
    }
}

void displayLeaderboard() {
    FILE *f = fopen("leaderboard.txt", "r");
    if (f != NULL) {
        char name[50];
        int score;
        printf("============================ \033[1;32mLeaderboard\033[0m ============================\n");
        int rank = 1;
        while (fscanf(f, "%s %d", name, &score) == 2) {
            printf("%2d. %-10s - %4d\n", rank++, name, score);
        }
        fclose(f);
    } else {
        printf("No leaderboard data found.\n");
    }
    waitForEnter();
}

void displayAllScores() {
    FILE *f = fopen("all_scores.txt", "r");
    if (f != NULL) {
        char name[50];
        int score;
        printf("==== \033[1;34mAll Scores\033[0m ====\n");
        while (fscanf(f, "%s %d", name, &score) == 2) {
            printf("%-10s - %4d\n", name, score);
        }
        fclose(f);
    } else {
        printf("No score data found.\n");
    }
    waitForEnter();

}
