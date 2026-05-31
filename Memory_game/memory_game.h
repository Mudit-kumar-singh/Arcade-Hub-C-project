
#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H

extern int SIZE;

char **allocateBoard(int size);
int **allocateRevealed(int size);
void freeBoard(char **board, int size);
void freeRevealed(int **revealed, int size);

void initializeBoard(char **board, int size);
void shuffleBoard(char **board, int size);
void printBoard(char **board, int **revealed, int size);
int checkMatch(char **board, int r1, int c1, int r2, int c2);
void revealTile(int **revealed, int row, int col);
void hideTiles(int **revealed, int r1, int c1, int r2, int c2);

void saveHighScore(const char *playerName, int attempts);
void displayHighScores();

void clearScreen();
void printWelcomeScreen();

void saveGame(const char *name, char **board, int **revealed, int size, int attempts, int matches);
int loadGame(char *name, char **board, int **revealed, int size, int *attempts, int *matches);

#endif
