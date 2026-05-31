#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;
    do {
        printf(" [35m                      $    $$$$    $$$$    $     $$$$   $$$$$    $   $  $   $  $$$$ [0m\n");
        printf("                     [35m $ $   $   $  $       $ $    $   $  $        $   $  $   $  $   $[0m\n");
        printf("=====================[35m$$$$$  $$$$   $      $$$$$   $   $  $$$$     $$$$$  $   $  $$$$ [0m=====================\n");
        printf("[35m                     $   $  $ $    $      $   $   $   $  $        $   $  $   $  $   $[0m\n");
        printf("[35m                     $   $  $  $    $$$$  $   $   $$$$   $$$$$    $   $   $$$   $$$$ [0m\n");
        printf("1. [34m2048[0m\n");
        printf("2.[34m MEMORY GAME[0m\n");
        printf("3. [34mSUBWAY SURFER[0m\n");
        printf("4. [34mEXIT[0m\n");
        printf("[33mENTER CHOICE: [0m");
        scanf("%d", &choice);

        switch(choice) {
            case 1: system("D:\\b24cm1064_b24ci1032_b24ci1052_b24mt1010_b24me1084_major_project\\2048\\2048.exe"); break;
            case 2: system("D:\\b24cm1064_b24ci1032_b24ci1052_b24mt1010_b24me1084_major_project\\Memory_game\\memory_game.exe"); break;
            case 3: system("D:\\b24cm1064_b24ci1032_b24ci1052_b24mt1010_b24me1084_major_project\\Subway_Runner\\subway_runner.exe"); break;
            case 4: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while(choice != 4);

    return 0;
}
