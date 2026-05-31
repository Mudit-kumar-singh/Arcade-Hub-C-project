#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "game2048.h"

int main() {
    srand(time(NULL));
    loadHighscore();

    // Show main menu
    char choice;
    char playerName[50];
    do {
        system("cls");
        printf("============================[1;36mWelcome to 2048![0m ============================\n");
        printf("\t\t\t\t[1;35m1. New Game[0m \t\t\t\t\n");
        printf("\t\t\t\t[1;35m2. Load Game[0m \t\t\t\t\n");
        printf("\t\t\t\t[1;35m3. Quit[0m \t\t\t\t\n");
        printf("\t\t\t\t[1;35m4. View Leaderboard[0m \t\t\t\t\n");
        printf("\t\t\t\t[1;35m5. View All Scores[0m \t\t\t\t\n");

        printf("[1;33mEnter your choice:[0m ");
        choice = getch();
        printf("[1;33m%c[0m\n", choice);
        
        if (choice == '1') {
            printf("[1;31mEnter your name:[0m ");
            scanf("%s", playerName);
            printf("[1;31mEnter grid size (2 to %d):[0m ", MAX_SIZE);
            scanf("%d", &SIZE);
            if (SIZE < 2 || SIZE > MAX_SIZE) SIZE = 4;
            score = 0;
            for (int i = 0; i < MAX_SIZE; i++)
                for (int j = 0; j < MAX_SIZE; j++)
                    board[i][j] = 0;
            addRandomTile();
            addRandomTile();
            break;
        } else if (choice == '2') {
            printf("[1;31mEnter your name:[0m ");
            scanf("%s", playerName);
            loadGame();
            break;
        } else if (choice == '4') {
            displayLeaderboard();
            continue;
        } else if (choice == '5') {
            displayAllScores();
            continue;
        } else if (choice == '3') {
            printf("[1;31mGoodbye![0m\n");
            return 0;
        } else {
            printf("[1;31mInvalid choice.[0m");
            waitForEnter();            
        }
    } while (1);

    while (1) {
        printBoard();
// canMove function if not satisfied that is all the blocks are blocked and game is over
        if (!canMove()) {
            printf("\n[1;33mGame Over! Final score: %d\n[0m", score);
            break;
        }

        printf("\n[1;33mEnter your move:[0m ");
        char ch = getch();
        printf("[1;33m%c[0m\n", ch); 
        

        if (ch == 'q' || ch == 'Q')
            break;

        if (ch == 'u' || ch == 'U') {
            undoMove();
            continue;
        }

        if (makeMove(ch))
            addRandomTile();
    }

    saveHighscore();
    saveToLeaderboard(playerName, score);
    appendToAllScores(playerName, score);
    saveGame();
    return 0;
}
