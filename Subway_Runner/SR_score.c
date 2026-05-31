#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "SR_score.h"

#define MAX_PLAYERS 100

typedef struct {
    char name[50];
    int score;
} PlayerScore;

void saveScore(const char *name, int score) {
    PlayerScore players[MAX_PLAYERS];
    int count = 0;

    FILE *f = fopen("leaderboard.txt", "r");
    if (f) {
        while (fscanf(f, "%49s %d", players[count].name, &players[count].score) == 2 && count < MAX_PLAYERS) {
            count++;
        }
        fclose(f);
    }

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(players[i].name, name) == 0) {
            if (score > players[i].score) {
                players[i].score = score;
            }
            found = 1;
            break;
        }
    }

    if (!found && count < MAX_PLAYERS) {
        strncpy(players[count].name, name, 49);
        players[count].score = score;
        count++;
    }

    // Sort scores descending
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (players[j].score > players[i].score) {
                PlayerScore temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    f = fopen("leaderboard.txt", "w");
    if (f) {
        for (int i = 0; i < count; i++) {
            fprintf(f, "%s %d\n", players[i].name, players[i].score);
        }
        fclose(f);
    }
}

void showLeaderboard() {
    PlayerScore players[MAX_PLAYERS];
    int count = 0;

    FILE *f = fopen("leaderboard.txt", "r");
    if (f) {
        while (fscanf(f, "%49s %d", players[count].name, &players[count].score) == 2 && count < MAX_PLAYERS) {
            count++;
        }
        fclose(f);
    }

    printf("[1;37m============================================[0m\n");
    printf("              [1;35mTOP 10 SCORES[0m                \n");
    printf("[1;37m============================================[0m\n");
    printf(" [1;34mRank | Player           | Score[0m\n");
    printf("[1;37m------+------------------+--------[0m\n");
    for (int i = 0; i < count && i < 10; i++) {
        printf("%d. %s - %d\n", i + 1, players[i].name, players[i].score);
    }
}