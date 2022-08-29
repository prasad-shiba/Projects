#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

#define numOW_DOWN_KEY 80
#define numOW_UP_KEY 72
#define numOW_LEFT_KEY 75
#define numOW_RIGHT_KEY 77
#define E 69
#define e 101

const char COLOR_RED[] = "\x1b[31m";
const char COLOR_GREEN[] = "\x1b[32m";
const char COLOR_YELLOW[] = "\x1b[33m";
const char COLOR_BLUE[] = "\x1b[34m";
const char COLOR_WHITE[] = "\033[0;37m";
const char COLOR_DEFAULT[] = "\x1b[0m";
int remaining_moves;
int matrix[4][4];
char *username;
void printWelcomeScreen(const char *USERNAME);
void printColor(const char *COLOR);
void clearScreen();
void pauseScreen();
void pressAnyKeyToStart();
void printWinningMatrix();
int askUserToPlayGameOrNot();
void startGame();
void gameLose();
void gameWin();
void restartGame();
char *getUsername();
int getEnteredKey();
void onDownArrowKeyPressed();
void onLeftArrowKeyPressed();
void onRightArrowKeyPressed();
void onUpArrowKeyPressed();
void printRandomMatrix();
void printMatrix();

int getEnteredKey()
{
    fflush(stdin);
    return getch();
}

char *getUsername()
{
    char *ch = (char *)malloc(30 * sizeof(char));
    // pauseScreen();
    clearScreen();
    printf("\n\n\t\t\t\tPlayer Name :   ");
    fgets(ch, 30, stdin);
    ch[strlen(ch) - 1] = '\0';
    username = ch;
    return ch;
}

void printColor(const char *COLOR) { printf("%s", COLOR); }

void clearScreen() { system("cls"); }

void pauseScreen() { system("pause"); }

void restartGame()
{
    clearScreen();
    void startGame();
}

void pressAnyKeyToStart(const char *message)
{
    printf(message);
    _getch();
}

void printWinningMatrix()
{
    int k = 1;
    for (int i = 0; i < 4; ++i)
    {
        printf("\n\t\t\t\t\t\t|");
        for (int j = 0; j < 4; ++j)
        {
            if (k != 16)
            {
                printf(" %2d ", k);
                ++k;
                printf("|");
            }
            else
            {
                printf("    |");
            }
        }
    }
}

int askUserToPlayGameOrNot()
{
    fflush(stdin);
    char ch;

    do
    {
        printf("\n\n\t\t\t\t\t    Are you want to restart the game ? (y / n)  :  ");
        scanf("%c", &ch);
    } while (ch != 'y' && ch != 'n' && ch != 'Y' && ch != 'N');
    // printf("%c", ch);
    if (ch == 'y' || ch == 'Y')
    {
        return 1;
    }
    else if (ch == 'n' || ch == 'Y')
    {
        return 0;
    }
}

void startGame()
{
    clearScreen();
    int isGameWin = 0;
    while (1)
    {
        remaining_moves = 4;
        printf("\n\n\n\t\t\t\t\t    %s  , Remaining moves - %d", username, remaining_moves);
        printRandomMatrix(matrix);
        int check;
        while (remaining_moves >= 1)
        {
            check = getEnteredKey();
            switch (check)
            {
            case E:
                exit(0);
                break;
            case e:
                exit(0);
                break;
            case numOW_DOWN_KEY:
                onDownArrowKeyPressed();
                break;
            case numOW_LEFT_KEY:
                onLeftArrowKeyPressed();
                break;
            case numOW_RIGHT_KEY:
                onRightArrowKeyPressed();
                break;
            case numOW_UP_KEY:
                onUpArrowKeyPressed();
                break;
            }
        }
        if (isGameWin == 1)
        {
            gameWin();
        }
        else
        {
            gameLose();
        }
    }
}

void gameLose()
{
    clearScreen();
    printColor(COLOR_RED);
    printf("\n\n\n\t\t\t\t\t\t\tYou lose the Game !\n");
    printColor(COLOR_DEFAULT);
    if (askUserToPlayGameOrNot())
    {
        restartGame();
    }
    else
    {
        clearScreen();
        exit(0);
    }
}

void gameWin()
{
    clearScreen();
    printColor(COLOR_GREEN);
    printf("\n\n\n\t\t\t\t\t\t\tYou won the Game !\n");
    printColor(COLOR_DEFAULT);
    if (askUserToPlayGameOrNot())
    {
        restartGame();
    }
    else
    {
        clearScreen();
        exit(0);
    }
}

void printWelcomeScreen(const char *USERNAME)
{
    printf("\n\t\t\t%s ,Welcome to NUMBER_SHIFTING_GAME\n\n", USERNAME);
    pressAnyKeyToStart("\t\t\t\tEnter any key to start....    ");
    clearScreen();
    printColor(COLOR_YELLOW);
    printf("\t\t\t\t\t\t ----------------------\n\t\t\t\t\t\t| NUMBER SHIFTING GAME |\n\t\t\t\t\t\t ----------------------\n\n");
    printf("\t\t\t\t\t\t   RULES OF THIS GAME\n\t\t\t\t\t\t   ------------------\n\n\n");
    printColor(COLOR_RED);
    printf("\t\t\t\t1. You can move only 1 step at a time by numow key\n\n");
    printColor(COLOR_BLUE);
    printf("\t\t\t\t\tMove Up    :  by Up numow key\n");
    printf("\t\t\t\t\tMove Down  :  by Down numow key\n");
    printf("\t\t\t\t\tMove Left  :  by Left numow key\n");
    printf("\t\t\t\t\tMove Right :  by Right numow key\n");
    printColor(COLOR_RED);
    printf("\n\t\t\t\t2. You Can move number at empty position only\n");
    printf("\n\t\t\t\t3. For each valid move : your total number of move will decrease by 1");
    printf("\n\t\t\t\t4. Winning situation : Number in a 4x4 matrix should be in order from 1 to 15\n\n\n");
    printColor(COLOR_YELLOW);
    printf("\n\t\t\t\t\t\t   Winning Situation\n\t\t\t\t\t\t   -----------------\n\n\n\t\t\t\t\t\t -------------------");
    printWinningMatrix();
    printf("\n\t\t\t\t\t\t -------------------");
    printColor(COLOR_RED);
    printf("\n\n\t\t\t\t5. You can exit game at any time by pressing 'E' or 'e'\n\n");
    printColor(COLOR_DEFAULT);
    printf("\t\t\t\tSo Try to win in minimum no of move\n\n\n");
    printf("\t\t\t\t\tHappy gaming , Good Luck\n\n");
    pressAnyKeyToStart("\t\t\t\tEnter any key to start game....    ");
    startGame();
}

void printMatrix()
{
    printColor(COLOR_YELLOW);
    printf("\n\n\n\t\t\t\t\t\t -------------------");
    for (int i = 0; i < 4; ++i)
    {
        printf("\n\t\t\t\t\t\t|");
        for (int j = 0; j < 4; ++j)
        {
            if (matrix[i][j] == 0)
            {
                printf("    |");
            }
            else
            {
                printf(" %2d ", matrix[i][j]);
                printf("|");
            }
        }
    }
    printf("\n\t\t\t\t\t\t -------------------\n\n");
    printColor(COLOR_DEFAULT);
}

void printRandomMatrix()
{
    int size = 15, lastindex = 14, index;
    int num[size - 1];
    for (int i = 0; i < size; ++i)
        num[i] = i + 1;
    srand(time(NULL));
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if (lastindex >= 0)
            {
                index = rand() % (lastindex + 1);
                matrix[i][j] = num[index];
                num[index] = num[lastindex--];
            }
        }
    }
    matrix[3][3] = 0;
    printMatrix(matrix);
}

void onDownArrowKeyPressed()
{
    --remaining_moves;
    clearScreen();
    printf("\n\n\n\t\t\t\t\t    %s  , Remaining moves - %d", username, remaining_moves);
    printMatrix();
    printf("down key");
}
void onLeftArrowKeyPressed()
{
    --remaining_moves;
    clearScreen();
    printf("\n\n\n\t\t\t\t\t    %s  , Remaining moves - %d", username, remaining_moves);
    printMatrix();
    printf("left key");
}
void onRightArrowKeyPressed()
{
    --remaining_moves;
    clearScreen();
    printf("\n\n\n\t\t\t\t\t    %s  , Remaining moves - %d", username, remaining_moves);
    printMatrix();
    printf("right key");
}
void onUpArrowKeyPressed()
{
    --remaining_moves;
    clearScreen();
    printf("\n\n\n\t\t\t\t\t    %s  , Remaining moves - %d", username, remaining_moves);
    printMatrix();
    printf("up key");
}