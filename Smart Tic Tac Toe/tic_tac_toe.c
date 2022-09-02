#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

const static char COLOR_BLUE[] = "\x1b[34m";
const static char COLOR_DEFAULT[] = "\x1b[0m";
const static char COLOR_GREEN[] = "\x1b[32m";
const static char COLOR_RED[] = "\x1b[31m";
const static char COLOR_WHITE[] = "\033[0;37m";
const static char COLOR_YELLOW[] = "\x1b[33m";
const static int PLAY_WITH_PLAYER = 2344;
const static int PLAY_WITH_EVIL_COMPUTER = 2343;
const static int PLAY_WITH_SMART_COMPUTER = 2342;
static char inputArray[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
static char resultArray[9] = {'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e', 'e'};
static int remainMove = 9;
static char gameEnd = 'f';
static char gameMove = 'o';

// function declarations
void askUsetToPlayAgainOrNot();
void clearScreen();
char getResult();
int getValidInputMove(const int whichTypeGame, const char *firstPlayerName, const char *secondPlayerName);
int isValidMove(int move);
int *nextMove(int whichTypeGame);
void printBottomBar();
void printBoard(const char *firstPlayerName, const char *secondPlayerName);
void printColor(const char *COLOR);
void printGameOverScreen(const char *firstPlayerName, const char *secondPlayerName);
void printWinScreen(char winner, const char *firstPlayerName, const char *secondPlayerName);
void playGame(const int whichTypeGame, const char *firstPlayerNam, const char *secondPlayerName);
void playWithEvilComputer();
void playWithPlayer();
void playWithSmartComputer();
void restartGame();
void setUsername(char *username, const char *message);
void startGame();

// function definations

void askUsetToPlayAgainOrNot()
{
    char playOrNot;
    int repeat = 0;
    do
    {
        if (repeat == 1)
            printf("\n\t\tPlease enter valid input");
        printf("\n\n\t\tAre you want to play again ? (y / n)  :  ");
        fflush(stdin);
        scanf("%c", &playOrNot);
        if (playOrNot == 'y' || playOrNot == 'Y')
            restartGame();
        else if (playOrNot == 'n' || playOrNot == 'N')
        {
            clearScreen();
            printColor(COLOR_DEFAULT);
            exit(0);
        }
        else
            repeat = 1;
    } while (repeat == 1);
}

void clearScreen() { system("cls"); }

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

int getValidInputMove(const int whichTypeGame, const char *firstPlayerName, const char *secondPlayerName)
{
    int inputMove;
    int vMove = 1;
    do
    {
        if (vMove != 1)
            printf("\n\n\t\tPlease enter valid marking place");
        if (gameMove == 'o')
        {
            printColor(COLOR_GREEN);
            printf("\n\n\t\tPlayer 1 - %s , Enter marking place   :   ", firstPlayerName);
            fflush(stdin);
            inputMove = _getch() - 48;
        }
        else
        {
            printColor(COLOR_BLUE);
            printf("\n\n\t\tPlayer 2 - %s , Enter marking place   :   ", secondPlayerName);
            if (whichTypeGame == PLAY_WITH_PLAYER)
            {
                fflush(stdin);
                inputMove = _getch() - 48;
                printf("%d", inputMove);
                inputMove -= 1;
                system("pause");
            }
            else if (whichTypeGame == PLAY_WITH_SMART_COMPUTER)
            {
                int *moves = nextMove(PLAY_WITH_SMART_COMPUTER);
                inputMove = moves[0];
                free(moves);
                printf("%d", inputMove);
                system("pause");
            }
            else if (whichTypeGame == PLAY_WITH_EVIL_COMPUTER)
            {
                int *size = 0;
                int *moves = nextMove(PLAY_WITH_EVIL_COMPUTER);
                inputMove = moves[0];
                free(moves);
                printf("%d", inputMove);
                system("pause");
            }
        }
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

int isValidMove(int move)
{
    if (move >= 1 && (move <= 9) && (resultArray[move - 1] == 'e'))
        return 1;
    return 0;
}

int *nextMove(int whichTypeGame)
{
    int *move;
    if (whichTypeGame == PLAY_WITH_SMART_COMPUTER)
    {
        move = (int *)malloc(sizeof(int) * 1);
        srand(time(0));
        if (remainMove == 7)
        {
            int corner_arr[4] = {0, 2, 6, 8};
            int side_arr[4] = {1, 3, 5, 7};
            int op;
            for (int i = 0; i < 9; ++i)
            {
                if (resultArray[i] == 'o')
                {
                    op = i;
                    break;
                }
            }
            if (op == corner_arr[0] || op == corner_arr[1] || op == corner_arr[2] || op == corner_arr[3])
                *move = 5;
            else
                *move = corner_arr[rand() % 4] + 1;
        }
        else if (remainMove == 5)
        {
        }
        else if (remainMove == 3)
        {
        }
        else if (remainMove == 1)
        {
        }
    }
    else if (whichTypeGame == PLAY_WITH_EVIL_COMPUTER)
    {
        move = (int *)malloc(sizeof(int) * 2);
    }
    return move;
}

void printBottomBar()
{
    printColor(COLOR_YELLOW);
    printf("\n\n###########################################################################");
}

void printBoard(const char *firstPlayerName, const char *secondPlayerName)
{
    int index = 0;
    clearScreen();
    printColor(COLOR_YELLOW);
    printf("\n\n############################### Tic Tac Toe ###############################");
    printColor(COLOR_GREEN);
    printf("\n\n\n\t\tPlayer 1 - %s   ( O )\n", firstPlayerName);
    printColor(COLOR_BLUE);
    printf("\n\t\tPlayer 2 - %s   ( X )\n\n", secondPlayerName);
    printColor(COLOR_YELLOW);
    printf("\n\t\t\t _______ _______ _______\n");
    for (int i = 0; i < 3; ++i)
    {
        printColor(COLOR_YELLOW);
        printf("\t\t\t|       |       |       |\n");
        for (int j = 0; j < 3; ++j)
        {
            if (j == 0)
                printf("\t\t\t|");
            else
                printf("|");
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
            if ((index + 1) % 3 == 0)
                printf("|");
            ++index;
        }
        printf("\n\t\t\t|_______|_______|_______|\n");
    }
    printf("\n\n###########################################################################");
}

void printColor(const char *COLOR) { printf("%s", COLOR); }

void printGameOverScreen(const char *firstPlayerName, const char *secondPlayerName)
{
    printBoard(firstPlayerName, secondPlayerName);
    printColor(COLOR_WHITE);
    printf("\n\n\t\t\tGame Draw");
    printBottomBar();
    askUsetToPlayAgainOrNot();
}

void printWinScreen(char winner, const char *firstPlayerName, const char *secondPlayerName)
{
    printBoard(firstPlayerName, secondPlayerName);
    if (winner == 'x')
    {
        printColor(COLOR_GREEN);
        printf("\n\n\t\t\tPlayer 1 - %s   ( O ) won", firstPlayerName);
    }
    else if (winner == 'o')
    {
        printColor(COLOR_BLUE);
        printf("\n\n\t\t\tPlayer 2 - %s   ( X ) won", secondPlayerName);
    }
    printBottomBar();
    askUsetToPlayAgainOrNot();
}

void playGame(const int whichTypeGame, const char *firstPlayerName, const char *secondPlayerName)
{
    if (remainMove <= 9 && remainMove >= 1)
    {
        --remainMove;
        printBoard(firstPlayerName, secondPlayerName);
        resultArray[getValidInputMove(whichTypeGame, firstPlayerName, secondPlayerName)] = gameMove;
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

void playWithEvilComputer()
{
    clearScreen();
    char *playerName = (char *)malloc(30 * sizeof(char));
    setUsername(playerName, "\t\t\tEnter player name");
    playGame(PLAY_WITH_EVIL_COMPUTER, playerName, "Evil Computer");
}

void playWithPlayer()
{
    clearScreen();
    char *firstPlayerName = (char *)malloc(30 * sizeof(char));
    char *secondPlayerName = (char *)malloc(30 * sizeof(char));
    setUsername(firstPlayerName, "\t\t\tEnter first player name");
    setUsername(secondPlayerName, "\t\t\tEnter second player name");
    playGame(PLAY_WITH_PLAYER, firstPlayerName, secondPlayerName);
}

void playWithSmartComputer()
{
    clearScreen();
    char *playerName = (char *)malloc(30 * sizeof(char));
    setUsername(playerName, "\t\t\tEnter player name");
    playGame(PLAY_WITH_SMART_COMPUTER, playerName, "Smart Computer");
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

void setUsername(char *username, const char *message)
{
    fflush(stdin);
    printf("\n%s : ", message);
    fgets(username, 30, stdin);
    if (strlen(username) > 1)
        username[strlen(username) - 1] = '\0';
}

void startGame()
{
    int choice, dM = 0;
    do
    {
        clearScreen();
        printf("\n\t\t\t1. Want to play with Smart Computer");
        printf("\n\t\t\t2. Want to play with Evil Computer");
        printf("\n\t\t\t3. Want to play with Player");
        printf("\n\t\t\t4. Exit");
        if (dM == 1)
            printf("\n\n\t\t\tPlease enter valid choice : ");
        else
        {
            printf("\n\n\t\t\tEnter your choice : ");
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
            printColor(COLOR_DEFAULT);
            exit(0);
            break;
        default:
            dM = 1;
        }
    } while (1);
}