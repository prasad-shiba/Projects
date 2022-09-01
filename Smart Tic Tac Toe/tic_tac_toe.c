#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

const static char COLOR_RED[] = "\x1b[31m";
const static char COLOR_GREEN[] = "\x1b[32m";
const static char COLOR_YELLOW[] = "\x1b[33m";
const static char COLOR_BLUE[] = "\x1b[34m";
const static char COLOR_WHITE[] = "\033[0;37m";
const static char COLOR_DEFAULT[] = "\x1b[0m";
const static int PLAY_WITH_SMART_COMPUTER = 2342;
const static int PLAY_WITH_EVIL_COMPUTER = 2343;
const static int PLAY_WITH_PLAYER = 2344;
static char resultArray[9] = {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'};
static char inputArray[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
static int remainMove = 9;
static char gameMove = 'o';
static char gameEnd = 'f';

// function declarations
void clearScreen();
void printColor(const char *COLOR);
void startGame();
void playWithPlayer();
void playWithSmartComputer();
void playWithEvilComputer();
char getResult();
void setUsername(char *username, const char *message);
void playGame(const int whichTypeGame, const char *firstPlayerNam, const char *secondPlayerName);
void restartGame();
void askUsetToPlayAgainOrNot();
int isValidMove(int move);
int *nextMove(int whichTypeGame);
void printBottomBar();
int getValidInputMove(const char *firstPlayerName, const char *secondPlayerName);
void printBoard(const char *firstPlayerName, const char *secondPlayerName);
void printWinScreen(char winner, const char *firstPlayerName, const char *secondPlayerName);
void printGameOverScreen(const char *firstPlayerName, const char *secondPlayerName);

// function definations
void clearScreen()
{
    system("cls");
}

void printColor(const char *COLOR) { printf("%s", COLOR); }

void startGame()
{
    int choice, dM = 0;
    do
    {
        clearScreen();
        printf("\n1. Want to play with Smart Computer");
        printf("\n2. Want to play with Evil Computer");
        printf("\n3. Want to play with Player");
        printf("\n4. Exit");
        if (dM == 1)
            printf("\n\nPlease enter valid choice : ");
        else
        {
            printf("\n\nEnter your choice : ");
            dM = 0;
        }
        fflush(stdin);
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            playWithSmartComputer();
            break;
        case 2:
            playWithEvilComputer();
            break;
        case 3:
            playWithPlayer();
            break;
        case 4:
            clearScreen();
            exit(0);
            break;
        default:
            dM = 1;
        }
    } while (1);
}

void playWithPlayer()
{
    clearScreen();
    char *firstPlayerName = (char *)malloc(30 * sizeof(char));
    char *secondPlayerName = (char *)malloc(30 * sizeof(char));
    setUsername(firstPlayerName, "Enter first player name");
    setUsername(secondPlayerName, "Enter second player name");
    playGame(PLAY_WITH_PLAYER, firstPlayerName, secondPlayerName);
}

void playWithSmartComputer()
{
    clearScreen();
    char *playerName = (char *)malloc(30 * sizeof(char));
    setUsername(playerName, "Enter player name");
    playGame(PLAY_WITH_SMART_COMPUTER, playerName, "Smart Computer");
}

void playWithEvilComputer()
{
    clearScreen();
    char *playerName = (char *)malloc(30 * sizeof(char));
    setUsername(playerName, "Enter player name");
    playGame(PLAY_WITH_EVIL_COMPUTER, playerName, "Evil Computer");
}

char getResult()
{
    char result = 'd';
    if ((resultArray[0] == resultArray[1]) && (resultArray[1] == resultArray[2]) && (resultArray[0] != 'e'))
        result = resultArray[0];
    else if ((resultArray[0] == resultArray[4]) && (resultArray[4] == resultArray[8]) && (resultArray[0] != 'e'))
        result = resultArray[0];
    else if ((resultArray[0] == resultArray[3]) && (resultArray[3] == resultArray[6]) && (resultArray[0] != 'e'))
        result = resultArray[0];
    else if ((resultArray[1] == resultArray[4]) && (resultArray[4] == resultArray[7]) && (resultArray[1] != 'e'))
        result = resultArray[1];
    else if ((resultArray[2] == resultArray[4]) && (resultArray[4] == resultArray[6]) && (resultArray[2] != 'e'))
        result = resultArray[2];
    else if ((resultArray[2] == resultArray[5]) && (resultArray[5] == resultArray[8]) && (resultArray[2] != 'e'))
        result = resultArray[2];
    else if ((resultArray[3] == resultArray[4]) && (resultArray[4] == resultArray[5]) && (resultArray[3] != 'e'))
        result = resultArray[3];
    else if ((resultArray[6] == resultArray[7]) && (resultArray[7] == resultArray[8]) && (resultArray[6] != 'e'))
        result = resultArray[6];
    return result;
}

void setUsername(char *username, const char *message)
{
    fflush(stdin);
    printf("\n%s : ", message);
    fgets(username, 30, stdin);
    if (strlen(username) > 1)
        username[strlen(username) - 1] = '\0';
}

void playGame(const int whichTypeGame, const char *firstPlayerName, const char *secondPlayerName)
{
    if (remainMove <= 9 && remainMove >= 1)
    {
        --remainMove;
        printBoard(firstPlayerName, secondPlayerName);
        resultArray[getValidInputMove(firstPlayerName, secondPlayerName)] = gameMove;
        switch (getResult())
        {
        case 'x':
            gameEnd = 't';
            printWinScreen('x', firstPlayerName, secondPlayerName);
            break;
        case 'o':
            gameEnd = 't';
            printWinScreen('o', firstPlayerName, secondPlayerName);
            break;
        default:
            gameEnd = 'f';
            playGame(whichTypeGame, firstPlayerName, secondPlayerName);
        }
    }
    else
    {
        gameEnd = 't';
        printGameOverScreen(firstPlayerName, secondPlayerName);
    }
}

void restartGame()
{
    fflush(stdin);
    remainMove = 9;
    gameMove = 'o';
    gameMove = 'f';
    for (int i = 0; i < 9; ++i)
    {
        resultArray[i] = 'e';
        inputArray[i] = i + 1;
    }
    startGame();
}

void askUsetToPlayAgainOrNot()
{
    char playOrNot;
    int repeat = 0;
    do
    {
        if (repeat == 1)
            printf("\nPlease enter valid input");
        printf("\n\nAre you want to play again ? (y / n)  :  ");
        fflush(stdin);
        scanf("%c", &playOrNot);
        if (playOrNot == 'y' || playOrNot == 'Y')
            restartGame();
        else if (playOrNot == 'n' || playOrNot == 'N')
        {
            clearScreen();
            exit(0);
        }
        else
            repeat = 1;
    } while (repeat == 1);
}

int isValidMove(int move)
{
    if (move >= 1 && (move <= 9) && (resultArray[move - 1] == 'e'))
        return 1;
    return 0;
}

int *nextMove(int whichTypeGame)
{
    if (whichTypeGame == PLAY_WITH_SMART_COMPUTER)
    {
    }
    else if (whichTypeGame == PLAY_WITH_EVIL_COMPUTER)
    {
    }
    return NULL;
}

void printBottomBar()
{
    printColor(COLOR_YELLOW);
    printf("\n\n###########################################################################");
}

int getValidInputMove(const char *firstPlayerName, const char *secondPlayerName)
{
    int inputMove;
    int vMove = 1;
    do
    {
        if (vMove != 1)
            printf("\n\nPlease enter valid marking place");
        if (gameMove == 'o')
        {
            printColor(COLOR_GREEN);
            printf("\n\nPlayer 1 - %s , Enter marking place   :   ", firstPlayerName);
        }
        else
        {
            printColor(COLOR_BLUE);
            printf("\n\nPlayer 2 - %s , Enter marking place   :   ", secondPlayerName);
        }
        fflush(stdin);
        inputMove = _getch() - 48;
        printf("%d", inputMove);
        if (isValidMove(inputMove))
            vMove = 1;
        else
            vMove = 0;
    } while (vMove != 1);
    if (gameMove == 'x')
        gameMove = 'o';
    else
        gameMove = 'x';
    return inputMove - 1;
}

void printBoard(const char *firstPlayerName, const char *secondPlayerName)
{
    int index = 0;
    clearScreen();
    printColor(COLOR_YELLOW);
    printf("\n\n############################### Tic Tac Toe ###############################");
    printColor(COLOR_GREEN);
    printf("\n\nPlayer 1 - %s   ( O )", firstPlayerName);
    printColor(COLOR_BLUE);
    printf("\nPlayer 2 - %s   ( X )\n\n\n", secondPlayerName);
    for (int i = 0; i < 3; ++i)
    {
        printColor(COLOR_YELLOW);
        printf("       |       |       \n");
        for (int j = 0; j < 3; ++j)
        {
            if (resultArray[index] == 'x')
                printColor(COLOR_GREEN);
            else if (resultArray[index] == 'o')
                printColor(COLOR_BLUE);
            else
                printColor(COLOR_WHITE);
            if (resultArray[index] == 'e')
                printf("   %c   ", inputArray[index]);
            else
                printf("   %c   ", resultArray[index]);
            printColor(COLOR_YELLOW);
            if ((index + 1) % 3 != 0)
                printf("|");
            ++index;
        }
        printf("\n_______|_______|_______\n");
    }
    printf("\n\n###########################################################################");
}

void printWinScreen(char winner, const char *firstPlayerName, const char *secondPlayerName)
{
    printBoard(firstPlayerName, secondPlayerName);
    if (winner == 'x')
    {
        printColor(COLOR_GREEN);
        printf("\n\nPlayer 2 - %s   ( X ) won", firstPlayerName);
    }
    else if (winner == 'o')
    {
        printColor(COLOR_BLUE);
        printf("\n\nPlayer 1 - %s   ( O ) won", secondPlayerName);
    }
    printBottomBar();
    askUsetToPlayAgainOrNot();
}

void printGameOverScreen(const char *firstPlayerName, const char *secondPlayerName)
{
    printBoard(firstPlayerName, secondPlayerName);
    printColor(COLOR_WHITE);
    printf("\n\nGame Draw");
    printBottomBar();
    askUsetToPlayAgainOrNot();
}