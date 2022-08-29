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
static int remainMove = 9;

// function declarations
void clearScreen();
void printColor(const char *COLOR);
void startGame();
void playWithPlayer();
void playWithSmartComputer();
void playWithEvilComputer();
int isGameOver();
char getResult();
void setUsername(char *username, const char *message);
void printGame(const int whichTypeGame, const char gameResult, const char *firstPlayerNam, const char *secondPlayerName);
void restartGame();
int askUsetToPlayAgainOrNot();

// function definations
void clearScreen() { system("cls"); }

void printColor(const char *COLOR) { printf("%s", COLOR); }

void startGame()
{
    int dM = 0;
    const char *defaultMessage = "\n\nPlease enter valid choice : ";
    clearScreen();
    int choice;
    printf("\n1. Want to play with Smart Computer");
    printf("\n2. Want to play with Evil Computer");
    printf("\n3. Want to play with Player");
    printf("\n4. Exit");
    printf("\n\nEnter your choice : ");
    scanf("%d", &choice);
    do
    {
        if (dM == 1)
        {
            printf("%s", defaultMessage);
            fflush(stdin);
            scanf("%d", &choice);
        }
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

    char *firstPlayerName = (char *)malloc(30 * sizeof(char));
    char *secondPlayerName = (char *)malloc(30 * sizeof(char));
    setUsername(firstPlayerName, "Enter first player name");
    setUsername(secondPlayerName, "Enter second player name");
    printGame(PLAY_WITH_PLAYER, getResult(), firstPlayerName, secondPlayerName);
}

void playWithSmartComputer()
{
    char *playerName = (char *)malloc(30 * sizeof(char));
    setUsername(playerName, "Enter player name");
    printGame(PLAY_WITH_SMART_COMPUTER, getResult(), playerName, "Smart Computer");
}

void playWithEvilComputer()
{
    char *playerName = (char *)malloc(30 * sizeof(char));
    setUsername(playerName, "Enter player name");
    printGame(PLAY_WITH_EVIL_COMPUTER, getResult(), playerName, "Evil Computer");
}

int isGameOver()
{
    if (remainMove == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char getResult()
{
    char result = 'd';
    if ((resultArray[0] == resultArray[1]) && (resultArray[1] == resultArray[2]) && (resultArray[0] != 'e'))
    {
        result = resultArray[0];
    }
    else if ((resultArray[0] == resultArray[4]) && (resultArray[4] == resultArray[8]) && (resultArray[0] != 'e'))
    {
        result = resultArray[0];
    }
    else if ((resultArray[0] == resultArray[3]) && (resultArray[3] == resultArray[6]) && (resultArray[0] != 'e'))
    {
        result = resultArray[0];
    }
    else if ((resultArray[1] == resultArray[4]) && (resultArray[4] == resultArray[7]) && (resultArray[1] != 'e'))
    {
        result = resultArray[1];
    }
    else if ((resultArray[2] == resultArray[4]) && (resultArray[4] == resultArray[6]) && (resultArray[2] != 'e'))
    {
        result = resultArray[2];
    }
    else if ((resultArray[2] == resultArray[5]) && (resultArray[5] == resultArray[8]) && (resultArray[2] != 'e'))
    {
        result = resultArray[2];
    }
    else if ((resultArray[3] == resultArray[4]) && (resultArray[4] == resultArray[5]) && (resultArray[3] != 'e'))
    {
        result = resultArray[3];
    }
    else if ((resultArray[6] == resultArray[7]) && (resultArray[7] == resultArray[8]) && (resultArray[6] != 'e'))
    {
        result = resultArray[6];
    }
    return result;
}

void setUsername(char *username, const char *message)
{
    fflush(stdin);
    printf("\n%s : ", message);
    fgets(username, 30, stdin);
    if (strlen(username) > 1)
    {
        username[strlen(username) - 1] = '\0';
    }
}

void printGame(const int whichTypeGame, const char gameResult, const char *firstPlayerName, const char *secondPlayerName)
{
    char gameEnd = 'f';
    clearScreen();
    printColor(COLOR_YELLOW);
    printf("\n\n############################### Tic Tac Toe ###############################");
    printColor(COLOR_GREEN);
    printf("\n\nPlayer 1 - %s   ( O )", firstPlayerName);
    printColor(COLOR_BLUE);
    printf("\nPlayer 2 - %s   ( X )", secondPlayerName);
    if (whichTypeGame == PLAY_WITH_SMART_COMPUTER)
    {
        if (remainMove <= 4)
        {
            switch (gameResult)
            {
            case 'x':
            {
                gameEnd = 't';
                printColor(COLOR_BLUE);
                printf("\nPlayer 2 - %s   ( X ) won", secondPlayerName);
                break;
            }
            case 'o':
            {
                gameEnd = 't';
                printColor(COLOR_GREEN);
                printf("\n\nPlayer 1 - %s   ( O ) won", firstPlayerName);
                break;
            }
            case 'd':
            {
                if (isGameOver())
                {
                    gameEnd = 't';

                    printColor(COLOR_WHITE);
                    printf("\n\nGame Draw");
                }
                break;
            }
            default:
            {
                gameEnd = 'f';
            }
            }
        }
    }
    else if (whichTypeGame == PLAY_WITH_EVIL_COMPUTER)
    {
    }
    else if (whichTypeGame == PLAY_WITH_PLAYER)
    {
    }
    printColor(COLOR_YELLOW);
    printf("\n\n###########################################################################");
    if (gameEnd == 't' && askUsetToPlayAgainOrNot())
    {
        restartGame();
    }
    else
    {
        clearScreen();
        exit(0);
    }
}

void restartGame()
{
    fflush(stdin);
    remainMove = 9;
    for (int i = 0; i < 9; ++i)
    {
        resultArray[i] = 'e';
    }
    startGame();
}

int askUsetToPlayAgainOrNot()
{
    char playOrNot;
    int repeat = 0;
    do
    {
        if (repeat == 1)
        {
            printf("\nPlease enter valid input");
        }
        printf("\n\nAre you want to play again ? (y / n)  :  ");
        fflush(stdin);
        scanf("%c", &playOrNot);
        if (playOrNot == 'y' || playOrNot == 'Y')
        {
            repeat = 0;
            return 1;
        }
        else if (playOrNot == 'n' || playOrNot == 'N')
        {
            repeat = 0;
            return 0;
        }
        else
        {
            repeat = 1;
        }
    } while (repeat == 1);
    return 0;
}