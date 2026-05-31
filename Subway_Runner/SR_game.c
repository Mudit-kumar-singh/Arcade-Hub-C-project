
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "SR_score.h"

#define ROWS 20
#define COLS 3
#define POWER_DURATION 8

int playerPos = 1;
int gameOver = 0;
int score = 0;
int level = 1;
int ticks = 0;
int powerMode = 0;
time_t powerStart;

char track[ROWS][COLS];

void clearTrack() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            track[i][j] = ' ';
}

void draw() {
    system("cls");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (i == ROWS - 1 && j == playerPos)
                printf("[1;37m[@][0m");
            else
                printf("[%c]", track[i][j]);
        }
        printf("\n");
    }
    printf("[1;34mScore: %d[0m | [1;33mLevel: %d[0m", score, level);
    if (powerMode)
        printf(" [1;32m| POWER MODE ON![0m");
    printf("\n");
}

void generateRow() {
    for (int j = 0; j < COLS; j++) {
        int r = rand() % 100;
        if (r < 5) track[0][j] = '#';
        else if (r < 10) track[0][j] = '^';
        else if (r < 15) track[0][j] = '*';
        else if (r < 20) track[0][j] = '!';
        else if (r < 30) track[0][j] = '-';
        else track[0][j] = ' ';
    }
}

void shiftTrack() {
    for (int i = ROWS - 2; i >= 0; i--)
        for (int j = 0; j < COLS; j++)
            track[i + 1][j] = track[i][j];
    generateRow();
}

void updatePowerMode() {
    if (powerMode && (time(NULL) - powerStart >= POWER_DURATION)) {
        powerMode = 0;
    }
}

void input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a' && playerPos > 0) playerPos--;
        else if (key == 's' && playerPos < 2) playerPos++;
        else if (key == 'k' && track[ROWS - 1][playerPos] == '^') track[ROWS - 1][playerPos] = ' ';
        else if (key == 'l' && track[ROWS - 1][playerPos] == '*') track[ROWS - 1][playerPos] = ' ';
    }
}

void logic() {
    char curr = track[ROWS - 1][playerPos];
    if (curr == '-' || curr == '!' || curr == '#' || curr == '^' || curr == '*') {
        if (curr == '-') score++;
        else if (curr == '!') {
            powerMode = 1;
            powerStart = time(NULL);
            printf("\n [1;37mPOWER MODE ACTIVATED! You are invincible for 8 seconds![0m\n");
        } else if (!powerMode) {
            gameOver = 1;
        }
    }
    track[ROWS - 1][playerPos] = ' ';
    if (score >= level * 100) level++;
}

void runGame() {
    clearTrack();
    while (!gameOver) {
        draw();
        input();
        logic();
        updatePowerMode();
        shiftTrack();
        int delay = 300 - level * 10;
        if (delay < 50) delay = 50;
        Sleep(delay);
        ticks++;
    }
    draw();
    printf("\n[1;37m============================================[0m\n");
    printf("         [1;31mGAME OVER! RUN COMPLETE[0m          \n");
    printf("[1;37m============================================[0m\n");
    printf("[1;32mYour final score: %d[0m\n", score);
    printf("[1;36mBetter luck next time! [0m\n\n");

    char name[50];
    printf("[1;33mEnter your name for storing your score: [0m");
    scanf("%s", name);
    saveScore(name, score);
}

int main() {
    srand(time(0));
    int choice;
    while (1) {
        system("cls");
        printf("[1;37m============================================[0m \n");
        printf("     [1;35mWELCOME TO SUBWAY RUNNER XTREME![0m    \n");
        printf("[1;37m============================================[0m\n");
        printf("         [1;35mDash | Dodge | Dominate[0m          \n");
        printf("         [1;37m-----------------------[0m          \n");
        printf("                [1;35mMAIN MENU[0m                 \n\n");
        printf("[1;36m1. New Game\n2. Instructions\n3. Leaderboard\n4. Exit\nEnter your choice: [0m  ");
        scanf("%d", &choice);
        if (choice == 1) {
            playerPos = 1;
            gameOver = 0;
            score = 0;
            level = 1;
            runGame();
            system("pause");
        } else if (choice == 2) {
            system("cls");
            printf("[1;36m- Use 'A' to move left[0m \n");
            printf("[1;36m- Use 'S' to move right[0m \n");
            printf("[1;36m- Press 'K' to jump low barrier (^), 'L' for HIGH BARRIER (*)[0m \n");
            printf("[1;36m- Avoid '#' unless in POWER MODE[0m \n");
            printf("[1;36m- Collect '-' for points[0m \n");
            printf("[1;36m-'!' for 8-second POWER MODE[0m \n");
            system("pause");
        } else if (choice == 3) {
            system("cls");
            showLeaderboard();
            system("pause");
        } else if (choice == 4) break;
        else {
            printf("[1;31mFeature not implemented yet.[0m\n");
            system("pause");
        }
    }
    return 0;
}