
#ifndef GAME2048_H
#define GAME2048_H

#define MAX_SIZE 10
extern int SIZE;
extern int board[MAX_SIZE][MAX_SIZE];
extern int score;
extern int highscore;
extern int previ_board[MAX_SIZE][MAX_SIZE];
extern int previousScore;

#define HIGHSCORE_FILE "highscore.txt"

void loadHighscore();
void saveHighscore();
void printBoard();
void addRandomTile();
int slideAndMerge(int row[MAX_SIZE]);
void rotateClockwise();
int moveLeft();
int makeMove(char move);
int canMove();
void saveState();
void undoMove();
void saveGame();
void loadGame();
void waitForEnter();




#define MAX_PLAYERS 10

typedef struct {
    char name[50];
    int score;
} Player;

void saveToLeaderboard(const char *name, int score);
void appendToAllScores(const char *name, int score);
void displayLeaderboard();
void displayAllScores();
#endif