#include <iostream>
#include <windows.h>
using namespace std;

char box = 219;
char tank1[6] = {box, box, box, '-', '-', '>'};
char tank2[6] = {'0', ' ', '0', ' ', ' ', ' '};

char enemy1[6] = {' ', ' ', ' ', '-', '-', '-'};
char enemy2[6] = {'<', '=', '=', '(', '-', ')'};
char enemy3[6] = {' ', ' ', ' ', '\\', '@', '/'};
char enemy4[6] = {' ', ' ', ' ', '*', '*', '*'};

int bulletX[100];
int bulletY[100];
int bulletCount = 0;

int tankX = 5;
int tankY = 5;

int enemyX = 30;
int enemyY = 10;

string enemyDirection = "Up";
int timer = 0;

int score = 0;

void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);
void printTank();
void eraseTank();
void printMaze();
void moveBullet();
void generateBullet();
void removeBulletFromArray(int index);
void moveTankUp();
void moveTankDown();
void moveTankLeft();
void moveTankRight();

void moveEnemy();
void printEnemy();
void eraseEnemy();

void addScore();
void printScore();

void bulletCollisionWithEnemy();
void printBullet(int x, int y);
void eraseBullet(int x, int y);

main()
{
    system("cls");
    printMaze();
    printTank();
    printEnemy();
    while (true)
    {
        printScore();
        if (GetAsyncKeyState(VK_LEFT))
        {
            moveTankLeft();
        }
        if (GetAsyncKeyState(VK_RIGHT))
        {
            moveTankRight();
        }
        if (GetAsyncKeyState(VK_UP))
        {
            moveTankUp();
        }
        if (GetAsyncKeyState(VK_DOWN))
        {
            moveTankDown();
        }
        if (GetAsyncKeyState(VK_SPACE))
        {
            generateBullet();
        }

        if (timer == 3)
        {
            moveEnemy();
            timer = 0;
        }
        moveBullet();
        bulletCollisionWithEnemy();
        timer++;
        Sleep(90);
    }
}

void printScore()
{
    gotoxy(45, 8);
    cout << "Score: " << score;
}

void moveEnemy()
{

    if (enemyDirection == "Up")
    {
        char next = getCharAtxy(enemyX, enemyY - 1);
        if (next == ' ')
        {
            eraseEnemy();
            enemyY--;
            printEnemy();
        }
        if (next == '#')
        {
            enemyDirection = "Down";
        }
    }
    if (enemyDirection == "Down")
    {
        char next = getCharAtxy(enemyX, enemyY + 4);
        if (next == ' ')
        {
            eraseEnemy();
            enemyY++;
            printEnemy();
        }
        if (next == '#')
        {
            enemyDirection = "Up";
        }
    }
}

void printEnemy()
{
    gotoxy(enemyX, enemyY);
    for (int index = 0; index < 6; index++)
    {
        cout << enemy1[index];
    }
    gotoxy(enemyX, enemyY + 1);
    for (int index = 0; index < 6; index++)
    {
        cout << enemy2[index];
    }
    gotoxy(enemyX, enemyY + 2);
    for (int index = 0; index < 6; index++)
    {
        cout << enemy3[index];
    }
    gotoxy(enemyX, enemyY + 3);
    for (int index = 0; index < 6; index++)
    {
        cout << enemy4[index];
    }
}
void eraseEnemy()
{
    gotoxy(enemyX, enemyY);
    for (int index = 0; index < 6; index++)
    {
        cout << " ";
    }
    gotoxy(enemyX, enemyY + 1);
    for (int index = 0; index < 6; index++)
    {
        cout << " ";
    }
    gotoxy(enemyX, enemyY + 2);
    for (int index = 0; index < 6; index++)
    {
        cout << " ";
    }
    gotoxy(enemyX, enemyY + 3);
    for (int index = 0; index < 6; index++)
    {
        cout << " ";
    }
}

void moveTankLeft()
{
    char next = getCharAtxy(tankX - 1, tankY);
    if (next == ' ')
    {
        eraseTank();
        tankX = tankX - 1;
        printTank();
    }
}

void moveTankRight()
{
    char next = getCharAtxy(tankX + 6, tankY);
    if (next == ' ')
    {
        eraseTank();
        tankX = tankX + 1;
        printTank();
    }
}

void moveTankUp()
{
    char next = getCharAtxy(tankX, tankY - 1);
    if (next == ' ')
    {
        eraseTank();
        tankY = tankY - 1;
        printTank();
    }
}

void moveTankDown()
{
    char next = getCharAtxy(tankX, tankY + 2);
    if (next == ' ')
    {
        eraseTank();
        tankY = tankY + 1;
        printTank();
    }
}

void generateBullet()
{
    bulletX[bulletCount] = tankX + 7;
    bulletY[bulletCount] = tankY;
    gotoxy(tankX + 7, tankY);
    cout << ".";
    bulletCount++;
}

void removeBulletFromArray(int index)
{
    for (int x = index; x < bulletCount - 1; x++)
    {
        bulletX[x] = bulletX[x + 1];
        bulletY[x] = bulletY[x + 1];
    }
    bulletCount--;
}

void printTank()
{
    gotoxy(tankX, tankY);
    for (int index = 0; index < 6; index++)
    {
        cout << tank1[index];
    }
    gotoxy(tankX, tankY + 1);
    for (int index = 0; index < 6; index++)
    {
        cout << tank2[index];
    }
}

void eraseTank()
{
    gotoxy(tankX, tankY);
    for (int index = 0; index < 6; index++)
    {
        cout << " ";
    }
    gotoxy(tankX, tankY + 1);
    for (int index = 0; index < 6; index++)
    {
        cout << " ";
    }
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void printMaze()
{
    cout << "#########################################" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#                                       #" << endl;
    cout << "#########################################" << endl;
}

void moveBullet()
{
    for (int x = 0; x < bulletCount; x++)
    {
        char next = getCharAtxy(bulletX[x] + 1, bulletY[x] + 1);
        if (next != ' ')
        {
            eraseBullet(bulletX[x], bulletY[x]);
            removeBulletFromArray(x);
        }
        else
        {
            eraseBullet(bulletX[x], bulletY[x]);
            bulletX[x] = bulletX[x] + 1;
            printBullet(bulletX[x], bulletY[x]);
        }
    }
}

void printBullet(int x, int y)
{
    gotoxy(x, y);
    cout << ".";
}
void eraseBullet(int x, int y)
{
    gotoxy(x, y);
    cout << " ";
}

void bulletCollisionWithEnemy()
{
    for (int x = 0; x < bulletCount; x++)
    {
        if (bulletX[x] + 1 == enemyX 
        && (bulletY[x] == enemyY || bulletY[x] == enemyY + 1 || bulletY[x] == enemyY + 2 || bulletY[x] == enemyY + 3))
        {
            addScore();
            eraseBullet(bulletX[x], bulletY[x]);
            removeBulletFromArray(x);
        }
    }
}

void addScore()
{
    score++;
}

char getCharAtxy(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}