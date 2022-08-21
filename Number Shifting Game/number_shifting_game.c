#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

const char RED_COLOR[] = "\x1b[31m";
const char GREEN_COLOR[] = "\x1b[32m";
const char YELLOW_COLOR[] = "\x1b[33m";
const char BLUE_COLOR[] = "\x1b[34m";
const char WHITE_COLOR[] = "\033[0;37m";
const char DEFAULT_COLOR[] = "\x1b[0m";
int remaining_moves;
void printWelcomeScreen(const char *USERNAME);
void printColor(const char *COLOR);
void clearScreen();
void pauseScreen();
void pressAnyKeyToStart();
void printWinningMatrix();
void askUserToPlayGameOrNot();
void startGame();
void gameLose();
void gameWin();
void restartGame();
char *getUsername();

char *getUsername()
{
    char *ch = (char *)malloc(30 * sizeof(char));
    clearScreen();
    printf("\n\n\t\t\t\tPlayer Name :   ");
    fgets(ch, 30, stdin);
    ch[strlen(ch) - 1] = '\0';
    return ch;
}

void printColor(const char *COLOR)
{
    printf("%s", COLOR);
}

void clearScreen()
{
    system("cls");
}

void pauseScreen()
{
    system("pause");
}

void pressAnyKeyToStart(const char *str)
{
    printf(str);
    _getch();
}

void printWinningMatrix()
{
    int k = 1;
    for (int i = 0; i < 4; ++i)
    {
        printf("\n\t\t\t\t|");
        for (int j = 0; j < 4; ++j)
        {
            if (k != 16)
            {
                printf(" %d ", k);
                ++k;
            }
            else
            {
                printf("   ");
            }
        }
        printf("|");
    }
}

void askUserToPlayGameOrNot()
{
    char ch = 'd';
    do
    {
        printf("\n\nAre you want to restart the game ? (y / n)  :  ");
        ch = _getch();
    } while (ch != 'y' || ch != 'n');
    if (ch == 'y')
    {
        restartGame();
    }
    else
    {
        exit(0);
    }
}

void startGame()
{
    remaining_moves = 4;
    int isGameWin = 0;
    if (isGameWin == 1)
    {
        gameWin();
    }
    else
    {
        gameLose();
    }
}

void gameLose()
{
    printColor(RED_COLOR);
    printf("\n\n\n\t\t\t\tYou lose the Game !");
    printColor(DEFAULT_COLOR);
    askUserToPlayGameOrNot();
}

void gameWin()
{
    printColor(GREEN_COLOR);
    printf("\n\n\n\t\t\t\tYou won the Game !");
    printColor(DEFAULT_COLOR);
    askUserToPlayGameOrNot();
}

void restartGame()
{
    void startGame();
}

void printWelcomeScreen(const char *USERNAME)
{
    printf("\n\t\t\t%s ,Welcome to NUMBER_SHIFTING_GAME\n\n", USERNAME);
    pressAnyKeyToStart("\t\t\t\tEnter any key to start....    ");
    clearScreen();
    printColor(YELLOW_COLOR);
    printf("\t\t\t\t\t\t ----------------------\n\t\t\t\t\t\t| NUMBER SHIFTING GAME |\n\t\t\t\t\t\t ----------------------\n\n");
    printf("\t\t\t\t\t\t   RULES OF THIS GAME\n\t\t\t\t\t\t   ------------------\n\n\n");
    printColor(RED_COLOR);
    printf("\t\t\t\t1. You can move only 1 step at a time by arrow key\n\n");
    printColor(BLUE_COLOR);
    printf("\t\t\t\t\tMove Up    :  by Up arrow key\n");
    printf("\t\t\t\t\tMove Down  :  by Down arrow key\n");
    printf("\t\t\t\t\tMove Left  :  by Left arrow key\n");
    printf("\t\t\t\t\tMove Right :  by Right arrow key\n");
    printColor(RED_COLOR);
    printf("\n\t\t\t\t2. You Can move number at empty position only\n");
    printf("\n\t\t\t\t3. For each valid move : your total number of move will decrease by 1\n");
    printf("\n\t\t\t\t4. Winning situation : Number in a 4x4 matrix should be in order from 1 to 15\n\n\n");
    printColor(YELLOW_COLOR);
    printf("\n\t\t\t\t\t\t   Winning Situation\n\t\t\t\t\t\t   -----------------\n\n\n\t\t\t\t\t\t---------------------\n\n\n");
    printWinningMatrix();
    printColor(RED_COLOR);
    printf("\n\n\t\t\t\t5. You can exit game at any time by pressing 'E' or 'e'\n\n");
    printColor(DEFAULT_COLOR);
    printf("\t\t\t\tSo Try to win in minimum no of move\n\n\n");
    printf("\t\t\t\t\tHappy gaming , Good Luck\n\n");
    pressAnyKeyToStart("\t\t\t\tEnter any key to start game....    ");
    startGame();
}