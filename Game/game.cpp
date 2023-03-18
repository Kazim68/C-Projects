#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <cmath>
#include <fstream>
using namespace std;

// pre game menu and it's functionalities
void header();
void menu();
void multiplayermode();
int option(int optcount, int x, int y);
void mode(int opt);
void newgame();
void gamereset();
void continuekey(int x, int y);
bool intvalid(string);
void levelendscreen(string text);
void levelselection();
void print_by_2_character(string arr[][2], int size, string color, int x, int y);
void print_by_3_character(string arr[][3], int size, string color, int x, int y);
void print_by_4_character(string arr[][4], int size, string color, int x, int y);
void print_by_5_character(string arr[][5], int size, string color, int x, int y);

// enemies
void printenemy(int x, int y);
void printenemy2(int x, int y);
void printenemy3_right(int x, int y);
void printenemy3_left(int x, int y);
void enemy4(int, int);
void printenemy6right(int x, int y);
void printenemy6left(int x, int y);
void enemy6movement();
void enemy1movement();
void enemy2movement();
void enemy3movement();
void enemy3director();
void enemy4movement();
void enemy5movement();
void enemy5director();
void enemy6director();
int enemy6_xdistance_calculator();
void enemy3death(int x, int y);
void eraseenemy(int, int);
void eraseenemy3(int, int);
void eraseenemy4(int, int);

// enemies bullets functions
void removeenemybullet(int c, string direction);
void enemybulletinitializer();
void resetenemybullets();
void enemybullet(int x, int y, string direction);
void printenemybullet(int x, int y);
void enemybulletmovement();
void enemybulletcollision();

// player
void printplayer_right(int x, int y);
void printplayer_left(int x, int y);
void playermovement();
void printplayerwithdirection();
void erase(int, int);

// player bullet functions
void playerbulletinitializer();
void removebullet(int c, string direction);
void resetplayerbullets();
void bulletcollision();
void bulletmovement();
void bullet(int, int);
void erasebullet(int x, int y);

// on screen navigators
void gotoxy(int x, int y);
char getCharAtxy(short int x, short int y);

// basic game functions
void addscore();
void touchbulletcrate(int x, int y);
void touchhealthpill(int x, int y);
void checkitems(int x, int y);
void phealth(string name, int x, int y);
void phealthdamage(int damage, int x, int y);
void p2health(string name, int x, int y);
void p2healthdamage(int damage, int x, int y);
void e1health(int x, int y, string name);
void enemydeath(int, int);
void e1healthdamage(int damage);
void e2health(int x, int y, string name);
void e2healthdamage(int damage);
void e3health(int x, int y, string name);
void e3healthdamage(int damage);
void e5health(int x, int y, string name);
void e5healthdamage(int damage);
void e6health(int x, int y, string name);
void e6healthdamage(int damage);
void printscore();
void displayebulletcount();
void counteraser(int x, int y);
float distance(int x1, int y1, int x2, int y2);

// functions of maps
void boundary();
void headbar();
void map1();
void map2();
void map3();
void platform(int x, int y, int size);
void verticalplatform(int x, int y, int width, int height);
void objectinitiolizer();
void firstrow(int x, int y);
void innerrows(int x, int y);
void healthpill(int x, int y);
void bulletcrate(int x, int y);
void printkey(int x, int y);
void printhealthpill();

// functions of zombies
void printzombie(int, int);
void zombiemovement();
void zombieattack();
void zombiedeath();
void zombiedeathsprite(int x, int y);
void zombiereset();
void zombieresetlevel3();
void zombiemovementlevel3();
void level3zombiedeath();

// levels
void level1();
void level2();
void level3();

// Multiplayer maps
void stage1();
void stage2();

// multiplayer functions
void mpheadbar();
void mpfunctionality();
void printplayer1_right(int x, int y);
void printplayer1_left(int x, int y);
void printplayer2_right(int x, int y);
void printplayer2_left(int x, int y);
void player1movement();
void player2movement();
void printplayer1withdirection();
void printplayer2withdirection();
void mpbulletplayer1(int x, int y);
void mpbulletplayer2(int x, int y);

// sign in/up
void startscreen();
void signin();
void signup();
bool uniquename(string name);
string usernameinputscreen();
bool format(string word);

// file handling for storing player progress
void loaddata();
void loadplayerdata(string name);
string linedata(string line, int col);
bool converttobool(string value);
void writedata();

// global declarations

int px, py, ex, ey, ex2, ey2, ex3, ey3, ex4, ey4, ex5, ey5, ex6, ey6;                                  // to keep track of coordiantes of characters
int zombietimer, enemy3timer, enemy5timer, enemy6timer;                                                // to slow movement of zombies
int randomvalue, randomvalue2;                                                                         // to move enemy 3 & 5 randomly
int pbulletcountR, pbulletcountL, bulletcount, ebulletcountR, ebulletcountL;                           // counting bullets
int playerhealth, player2health, enemy1health, enemy2health, enemy3health, enemy5health, enemy6health; // health
int score;                                                                                             // score
int hpillx, hpilly, bcratex, bcratey, key_x, key_y;                                                    // coordinates of items on map

char box = 219;

string playerdirection = "right", enemy1direction = "down", enemy2direction = "down",
       enemy3direction = "right", enemy5direction = "left",
       enemy6direction = "right"; // to keep track of direction of characters

string playername1;

// level initializers
bool level1running = false, level2running = false, level3running = false;          // to keep track of levels
bool enemy1alive, enemy2alive, enemy3alive, playeralive, enemy5alive, enemy6alive; // to check whether character is alive or not
bool level1complete, level2complete, level3complete;                               // to keep track of level completion
bool startenemy6;                                                                  // movement of enemy 6 starts when player first time matches y coordinate with them
bool zombiealive[10], level3zombiealive[5];
bool multiplayer, mprunning = false; // multiplayer checking and loop

// bullets
int rightbulletsX[1000] = {-1}, rightbulletsY[1000] = {-1}, leftbulletsX[1000] = {-1}, leftbulletsY[1000] = {-1}; // player bullets
bool is_player_right_bullet_active[1000], is_player_left_bullet_active[1000];
int enemyrightbulletsX[10000], enemyrightbulletsY[10000], enemyleftbulletsX[10000], enemyleftbulletsY[10000]; // enemy bullets
bool is_enemy_right_bullet_active[10000], is_enemy_left_bullet_active[10000];

// players status data
string playersdata[100][5];
int counter = 0, playercount = 0;
bool foundplayer = false;

// zombies
int zombiex[10], zombiey[10]; // level 2 zombies xy coordinates
int level3zombiesx[5], level3zombiesy[5];

// multiplayer variables
int px1, py1, px2, py2;                                       // players coordinates
int jump, jump2;                                              // a counter for making jump realistic
bool player1alive, player2alive;                              // for keeping track of winner
bool mp_mode = false;                                         // true when multiplayer is running
string player1direction = "right", player2direction = "left"; // to keep track of player direction while moving up and down

int main()
{
    loaddata();
    startscreen();
}

void screenframe() // main set screen interface of each level
{
    playername1 = "Player";
    system("cls");
    headbar();
    boundary();
}

void level1() // functionality of level 1
{
    int timer = 0;       // to let enemy 3 stick to a random direction for a moment
    int bullettimer = 0; // bullet remove timer of player

    // asssignments of global variables
    hpillx = 108, hpilly = 12, bcratex = 136, bcratey = 26, key_x = 1, key_y = 1;
    pbulletcountR = 0, pbulletcountL = 0, bulletcount = 100, ebulletcountR = 0, ebulletcountL = 0;
    playerhealth = 100, enemy1health = 100, enemy2health = 100, enemy3health = 100, score = 0, enemy3timer = 0;
    px = 10, py = 38, ex = 30, ey = 10, ex2 = 160, ey2 = 10, ex3 = 90, ey3 = 25;
    enemy1alive = true, enemy2alive = true, enemy3alive = true, playeralive = true;
    level1running = true;

    // interface
    screenframe();
    map1();
    printenemy(ex, ey);
    printenemy2(ex2, ey2);
    printenemy3_right(ex3, ey3);
    printplayer_right(px, py);
    playerbulletinitializer();
    enemybulletinitializer();

    // game loop
    while (level1running)
    {
        if (playerhealth > 0)
        {
            playermovement();
        }
        else
        {
            level1running = false;
            playeralive = false;
            levelendscreen("  You Died!");
        }
        if (enemy1health > 0)
        {
            enemy1movement();
        }
        else
        {
            enemydeath(ex, ey);
            enemy1alive = false;
        }
        if (enemy2health > 0)
        {
            enemy2movement();
        }
        else
        {
            enemydeath(ex2, ey2);
            enemy2alive = false;
        }
        if (enemy3health > 0)
        {
            if (timer == 5)
            {
                randomvalue = rand() % 4;
                timer = 0;
            }
            enemy3director();
        }
        else
        {
            enemy3death(ex3, ey3);
            enemy3alive = false;
            key_x = 5, key_y = 22;
            printkey(key_x, key_y);
        }
        if (enemy3timer == 120)
        {
            enemy3timer = 0;
        }
        if (bullettimer == 20)
        {
            resetplayerbullets();
            resetenemybullets();
            bullettimer = 0;
        }
        e1health(1, 2, "Enemy 1");
        e2health(1, 3, "Enemy 2");
        e3health(1, 4, "Enemy 3");
        bulletmovement();
        bulletcollision();
        enemybulletmovement();
        enemybulletcollision();
        timer++;
        enemy3timer++;
        bullettimer++;
        Sleep(50);
    }
    level1running = false;
}

void level2()
{
    int timer = 0; // to slow movement of zombies
    int keytimer = 0;
    // assignments
    hpillx = 140, hpilly = 14, bcratex = 119, bcratey = 36, key_x = 1, key_y = 1;
    pbulletcountR = 0, pbulletcountL = 0, bulletcount = 100, ebulletcountR = 0, ebulletcountL = 0;
    playerhealth = 100, score = 0;
    px = 73, py = 21, ex4 = 25, ey4 = 32;
    playeralive = true;
    level2running = true;

    // zombie coordinate reset
    zombiereset();

    // screen interface
    screenframe();
    map2();
    printplayer_right(px, py);
    enemy4(ex4, ey4);
    playerbulletinitializer();
    enemybulletinitializer();
    for (int i = 0; i < 10; i++)
    {
        printzombie(zombiex[i], zombiey[i]);
    }

    // game loop
    while (level2running)
    {
        if (playerhealth > 0)
        {
            playermovement();
        }
        else
        {
            level2running = false;
            playeralive = false;
            levelendscreen("  You Died!");
        }

        if (timer == 3)
        {
            zombiemovement();
            timer = 0;
            zombieattack();
        }
        if (keytimer == 600)
        {
            key_x = 42, key_y = 32;
            printkey(key_x, key_y);
        }
        bulletmovement();
        bulletcollision();
        enemybulletmovement();
        enemybulletcollision();
        zombiedeath();
        enemy4movement();
        timer++;
        keytimer++;
        Sleep(50);
    }
    level2running = false;
}

void level3()
{
    int timer = 0, timer2 = 0, timer3 = 0;
    // variable assignments
    hpillx = 160, hpilly = 41, bcratex = 84, bcratey = 27, key_x = 50, key_y = 5;
    pbulletcountR = 0, pbulletcountL = 0, bulletcount = 100, ebulletcountR = 0, ebulletcountL = 0;
    px = 90, py = 41, ex3 = 7, ey3 = 39, ex4 = 144, ey4 = 35, ex5 = 150, ey5 = 18, ex6 = 120, ey6 = 13;
    playerhealth = 100, enemy3health = 100, score = 0, enemy3timer = 0, enemy5timer = 0, enemy5health = 100, enemy6health = 100;
    playeralive = true, enemy3alive = true, enemy5alive = true, enemy6alive = true;
    level3running = true, startenemy6 = false;

    // zombie reset
    zombieresetlevel3();

    // screen interface
    screenframe();
    map3();
    printplayer_right(px, py);
    printenemy3_right(ex3, ey3);
    printenemy3_left(ex5, ey5);
    enemy4(ex4, ey4);
    printenemy6left(ex6, ey6);
    playerbulletinitializer();
    enemybulletinitializer();
    for (int i = 0; i < 5; i++)
    {
        printzombie(level3zombiesx[i], level3zombiesy[i]);
    }

    // game loop
    while (level3running)
    {
        if (playerhealth > 0)
        {
            playermovement();
        }
        else
        {
            level3running = false;
            playeralive = false;
            levelendscreen("  You Died!");
        }
        if (timer == 3)
        {
            zombiemovementlevel3();
            timer = 0;
            zombieattack();
        }
        if (enemy3health > 0)
        {
            if (timer2 == 5)
            {
                randomvalue = rand() % 4;
                timer2 = 0;
            }
            enemy3director();
        }
        else
        {
            enemy3death(ex3, ey3);
            enemy3alive = false;
            key_x = 160, key_y = 12;
            printkey(key_x, key_y);
        }
        if (enemy3timer == 120)
        {
            enemy3timer = 0;
        }
        if (enemy5health > 0)
        {
            if (timer3 == 5)
            {
                randomvalue2 = rand() % 4;
                timer3 = 0;
            }
            enemy5director();
        }
        else
        {
            enemy3death(ex5, ey5);
            enemy5alive = false;
        }
        if (enemy5timer == 120)
        {
            enemy5timer = 0;
        }
        if (py == ey6 || py == ey6 + 1 || py == ey + 2)
        {
            startenemy6 = true;
        }
        if (enemy6health > 0)
        {
            if (startenemy6)
            {
                enemy6director();
            }
        }
        else
        {
            enemy3death(ex6, ey6);
            enemy6alive = false;
        }
        e6health(1, 2, "Enemy 1");
        e3health(1, 3, "Enemy 2");
        e5health(1, 4, "Enemy 3");
        bulletmovement();
        bulletcollision();
        level3zombiedeath();
        enemy4movement();
        enemybulletmovement();
        enemybulletcollision();
        timer++;
        timer2++;
        timer3++;
        enemy3timer++;
        enemy5timer++;
        Sleep(50);
    }
    level3running = false;
}

void playermovement() // movement functionalities of player
{
    if (GetAsyncKeyState(VK_RIGHT))
    {
        checkitems(px + 3, py);
        if (getCharAtxy(px + 3, py) == ' ' && getCharAtxy(px + 3, py + 1) == ' ' && getCharAtxy(px + 3, py + 2) == ' ')
        {
            erase(px, py);
            px++;
            playerdirection = "right";
            printplayer_right(px, py);
        }
    }
    else if (GetAsyncKeyState(VK_LEFT))
    {
        checkitems(px - 1, py);
        if (getCharAtxy(px - 1, py) == ' ' && getCharAtxy(px - 1, py + 1) == ' ' && getCharAtxy(px - 1, py + 2) == ' ')
        {
            erase(px, py);
            px--;
            playerdirection = "left";
            printplayer_left(px, py);
        }
    }
    else if (GetAsyncKeyState(VK_UP))
    {
        checkitems(px, py - 1);
        if (getCharAtxy(px, py - 1) == ' ' && getCharAtxy(px + 1, py - 1) == ' ' && getCharAtxy(px + 2, py - 1) == ' ' /* && getCharAtxy(px + 3, py - 1) == ' ' && getCharAtxy(px + 4, py - 1) == ' '*/)
        {
            erase(px, py);
            py--;
            printplayerwithdirection();
        }
    }
    else if (GetAsyncKeyState(VK_DOWN))
    {
        checkitems(px, py + 3);
        if (getCharAtxy(px, py + 3) == ' ' && getCharAtxy(px + 1, py + 3) == ' ' && getCharAtxy(px + 2, py + 3) == ' ')
        {
            erase(px, py);
            py++;
            printplayerwithdirection();
        }
    }
    if (GetAsyncKeyState(VK_SPACE))
    {
        if (bulletcount > 0 && (getCharAtxy(px, py) == ' ' && getCharAtxy(px - 1, py + 1) == ' ' && getCharAtxy(px + 3, py + 1) == ' '))
        {
            bullet(px, py);
            bulletcount--;
            displayebulletcount();
        }
    }
    if (GetAsyncKeyState(VK_ESCAPE))
    {
        Sleep(500);
        menu();
    }
}

void printplayerwithdirection() // determines direction of player and calls the respective side face function
{
    if (playerdirection == "right")
    {
        printplayer_right(px, py);
    }
    else if (playerdirection == "left")
    {
        printplayer_left(px, py);
    }
}

void printplayer_right(int x, int y) // print player facing right side of the console
{
    string body[3][3] = {{" ", "0", " "}, {"(", "L", "="}, {"/", ")", " "}};
    print_by_3_character(body, 3, "\33[33m", x, y);
}

void printplayer_left(int x, int y) // print player facing left side of console
{
    string body[3][3] = {{" ", "0", " "}, {"=", "J", ")"}, {" ", "(", "\\"}};
    print_by_3_character(body, 3, "\33[33m", x, y);
}

void erase(int x, int y) // erase player sprite from console
{
    string body[3][3] = {{" ", " ", " "}, {" ", " ", " "}, {" ", " ", " "}};
    print_by_3_character(body, 3, "\33[33m", x, y);
}

void print_by_3_character(string arr[][3], int size, string color, int x, int y)
{
    int bx;
    for (int i = 0; i < size; i++)
    {
        bx = x;
        for (int j = 0; j < 3; j++)
        {
            gotoxy(bx, y);
            cout << color << arr[i][j];
            bx++;
        }
        y++;
    }
}

void print_by_4_character(string arr[][4], int size, string color, int x, int y)
{
    int bx;
    for (int i = 0; i < size; i++)
    {
        bx = x;
        for (int j = 0; j < 4; j++)
        {
            gotoxy(bx, y);
            cout << color << arr[i][j];
            bx++;
        }
        y++;
    }
}

void print_by_5_character(string arr[][5], int size, string color, int x, int y)
{
    int bx;
    for (int i = 0; i < size; i++)
    {
        bx = x;
        for (int j = 0; j < 5; j++)
        {
            gotoxy(bx, y);
            cout << color << arr[i][j];
            bx++;
        }
        y++;
    }
}

void print_by_2_character(string arr[][2], int size, string color, int x, int y)
{
    int bx;
    for (int i = 0; i < size; i++)
    {
        bx = x;
        for (int j = 0; j < 2; j++)
        {
            gotoxy(bx, y);
            cout << color << arr[i][j];
            bx++;
        }
        y++;
    }
}

void printenemy(int x, int y) // printing enemy 1 on the console
{
    string body[4][4] = {{"|", "T", " ", " "}, {"\\", "=", "=", "="}, {" ", "^", "'", " "}, {"/", " ", "|", " "}};
    print_by_4_character(body, 4, "\33[32m", x, y);
}

void eraseenemy(int x, int y) // erase enemy 1 from console
{
    string body[4][4] = {{" ", " ", " ", " "}, {" ", " ", " ", " "}, {" ", " ", " ", " "}, {" ", " ", " ", " "}};
    print_by_4_character(body, 4, "\33[32m", x, y);
}

void enemy1movement() // movement functionality of enemy 1
{
    if (enemy1direction == "down")
    {
        if (ey == 22)
        {
            enemy1direction = "up";
        }
        else if (ey == py)
        {
            enemybullet(ex + 4, ey + 1, "right");
        }
        else
        {
            if (getCharAtxy(ex, ey + 4) == ' ' && getCharAtxy(ex + 2, ey + 4) == ' ' && getCharAtxy(ex + 3, ey + 4) == ' ')
            {
                eraseenemy(ex, ey);
                ey++;
                printenemy(ex, ey);
            }
        }
    }
    else if (enemy1direction == "up")
    {
        if (ey == 10)
        {
            enemy1direction = "down";
        }
        else if (ey == py)
        {
            enemybullet(ex + 4, ey + 1, "right");
        }
        else
        {
            if (getCharAtxy(ex, ey - 1) == ' ' && getCharAtxy(ex + 3, ey - 1) == ' ')
            {
                eraseenemy(ex, ey);
                ey--;
                printenemy(ex, ey);
            }
        }
    }
}

void enemydeath(int x, int y) // enemy death sprite
{
    string body[4][4] = {{" ", " ", "X", " "}, {" ", "|", " ", "'"}, {" ", "/", "!", " "}, {" ", "'", " ", "\\"}};
    print_by_4_character(body, 4, "\33[32m", x, y);
}

void printenemy2(int x, int y) // printing enemy 2 on the console
{
    string body[4][4] = {{" ", " ", "U", "|"}, {"=", "=", "=", "/"}, {" ", "'", "^", " "}, {" ", "|", " ", "\\"}};
    print_by_4_character(body, 4, "\33[32m", x, y);
}

void eraseenemy2(int x, int y)
{
    string body[4][4] = {{" ", " ", " ", " "}, {" ", " ", " ", " "}, {" ", " ", " ", " "}, {" ", " ", " ", " "}};
    print_by_4_character(body, 4, "\33[32m", x, y);
}

void enemy2movement() // movement functionality of enemy 2
{
    if (enemy2direction == "down")
    {
        if (ey2 == 37)
        {
            enemy2direction = "up";
        }
        else if (ey2 == py)
        {
            enemybullet(ex2, ey2, "left");
        }
        else
        {
            eraseenemy2(ex2, ey2);
            ey2++;
            printenemy2(ex2, ey2);
        }
    }
    else if (enemy2direction == "up")
    {
        if (ey2 == 10)
        {
            enemy2direction = "down";
        }
        else if (ey2 == py)
        {
            enemybullet(ex2, ey2, "left");
        }
        else
        {
            eraseenemy2(ex2, ey2);
            ey2--;
            printenemy2(ex2, ey2);
        }
    }
}

void printenemy3_right(int x, int y) // printing enemy 3 right face on the console
{
    string body[4][3] = {{"_", "U", "_"}, {"\\", "_", "="}, {" ", "H", " "}, {"/", " ", "]"}};
    print_by_3_character(body, 4, "\33[34m", x, y);
}

void printenemy3_left(int x, int y) // printing enemy 3 left face on the console
{
    string body[4][3] = {{"_", "U", "_"}, {"=", "_", "/"}, {" ", "H", " "}, {"[", " ", "\\"}};
    print_by_3_character(body, 4, "\33[34m", x, y);
}

void eraseenemy3(int x, int y) // erase enemy 3
{
    string body[4][3] = {{" ", " ", " "}, {" ", " ", " "}, {" ", " ", " "}, {" ", " ", " "}};
    print_by_3_character(body, 4, "\33[34m", x, y);
}

void enemy3death(int x, int y) // enemy 3 death sprite
{
    string body[4][3] = {{" ", "X", " "}, {"/", "!", " "}, {")", " ", "|"}, {"'", "=", "/"}};
    print_by_3_character(body, 4, "\33[34m", x, y);
}

void enemy3director() // control direction of enemy 3
{
    // for shooting player if their y coordinates match
    if ((ey3 == py || ey3 == py - 1 || ey3 == py - 2 || ey3 == py + 1 || ey3 == py + 2) && enemy3timer <= 60)
    {
        if (ex3 > px)
        {
            printenemy3_left(ex3, ey3);
            enemybullet(ex3 - 1, ey3, "left");
        }
        else if (ex3 < px)
        {
            printenemy3_right(ex3, ey3);
            enemybullet(ex3 + 3, ey3 + 1, "right");
        }
        if (enemy3timer == 60)
        {
            enemy3timer = 100;
        }
    }

    // for random movement of enemy 3 in case it is not shooting player
    else
    {
        if (randomvalue == 0)
        {
            enemy3direction = "left";
        }
        else if (randomvalue == 1)
        {
            enemy3direction = "right";
        }
        else if (randomvalue == 2)
        {
            enemy3direction = "up";
        }
        else if (randomvalue == 3)
        {
            enemy3direction = "down";
        }
        enemy3movement();
    }
}

void enemy3movement() // moves enemy 3
{
    if (enemy3direction == "right")
    {
        if (getCharAtxy(ex3 + 3, ey3) == ' ' && getCharAtxy(ex3 + 3, ey3 + 1) == ' ' && getCharAtxy(ex3 + 3, ey3 + 2) == ' ' && getCharAtxy(ex3 + 3, ey3 + 3) == ' ')
        {
            eraseenemy3(ex3, ey3);
            ex3++;
            printenemy3_right(ex3, ey3);
        }
        else
        {
            enemy3direction = "left";
        }
    }
    else if (enemy3direction == "left")
    {
        if (getCharAtxy(ex3 - 1, ey3) == ' ' && getCharAtxy(ex3 - 1, ey3 + 1) == ' ' && getCharAtxy(ex3 - 1, ey3 + 2) == ' ' && getCharAtxy(ex3 - 1, ey3 + 3) == ' ')
        {
            eraseenemy3(ex3, ey3);
            ex3--;
            printenemy3_left(ex3, ey3);
        }
        else
        {
            enemy3direction = "right";
        }
    }
    else if (enemy3direction == "up")
    {
        if (getCharAtxy(ex3, ey3 - 1) == ' ' && getCharAtxy(ex3 + 2, ey3 - 1) == ' ' && getCharAtxy(ex3 + 3, ey3 - 1) == ' ')
        {
            eraseenemy3(ex3, ey3);
            ey3--;
            printenemy3_left(ex3, ey3);
        }
        else
        {
            enemy3direction = "down";
        }
    }
    else if (enemy3direction == "down")
    {
        if (getCharAtxy(ex3, ey3 + 4) == ' ' && getCharAtxy(ex3 + 2, ey3 + 4) == ' ' && getCharAtxy(ex3 + 3, ey3 + 4) == ' ')
        {
            eraseenemy3(ex3, ey3);
            ey3++;
            printenemy3_left(ex3, ey3);
        }
        else
        {
            enemy3direction = "up";
        }
    }
}

void enemy4(int x, int y) // prints enemy 4 on the console
{
    string body[3][5] = {{"\\", "(", ".", ")", "/"}, {"{", ":", "0", ":", "}"}, {"/", "(", "^", ")", "\\"}};
    print_by_5_character(body, 3, "\33[35m", x, y);
}

void eraseenemy4(int x, int y) // erases enemy 4 from console
{
    string body[3][5] = {{" ", " ", " ", " ", " "}, {" ", " ", " ", " ", " "}, {" ", " ", " ", " ", " "}};
    print_by_5_character(body, 3, "\33[35m", x, y);
}

void enemy4movement() // enemy 4 stays stationary but fires when player is within a certain range
{
    float distance = ((px - ex4) * (px - ex4)) + ((py - ey4) * (py - ey4));
    if (sqrt(distance) <= 10)
    {
        enemybullet(ex4 - 1, ey4, "left");
        enemybullet(ex4 + 4, ey4 + 1, "right");
    }
}

void enemy5director()
{
    // for shooting player if their y coordinates match
    if ((ey5 == py || ey5 == py - 1 || ey5 == py - 2 || ey5 == py + 1 || ey5 == py + 2) && enemy5timer <= 60)
    {
        if (ex5 > px)
        {
            printenemy3_left(ex5, ey5);
            enemybullet(ex5 - 1, ey5, "left");
        }
        else if (ex5 < px)
        {
            printenemy3_right(ex5, ey5);
            enemybullet(ex5 + 3, ey5 + 1, "right");
        }
        if (enemy5timer == 60) // so that it never fires infinetly
        {
            enemy5timer = 100;
        }
    }

    // for random movement of enemy 5 in case it is not shooting player
    else
    {
        if (randomvalue2 == 0)
        {
            enemy5direction = "left";
        }
        else if (randomvalue2 == 1)
        {
            enemy5direction = "right";
        }
        else if (randomvalue2 == 2)
        {
            enemy5direction = "up";
        }
        else if (randomvalue2 == 3)
        {
            enemy5direction = "down";
        }
        enemy5movement();
    }
}

void enemy5movement() // enemy 5 movement functionality
{
    if (enemy5direction == "right")
    {
        if (getCharAtxy(ex5 + 3, ey5) == ' ' && getCharAtxy(ex5 + 3, ey5 + 1) == ' ' && getCharAtxy(ex5 + 3, ey5 + 2) == ' ' && getCharAtxy(ex5 + 3, ey5 + 3) == ' ')
        {
            eraseenemy3(ex5, ey5);
            ex5++;
            printenemy3_right(ex5, ey5);
        }
        else
        {
            enemy5direction = "left";
        }
    }
    else if (enemy5direction == "left")
    {
        if (getCharAtxy(ex5 - 1, ey5) == ' ' && getCharAtxy(ex5 - 1, ey5 + 1) == ' ' && getCharAtxy(ex5 - 1, ey5 + 2) == ' ' && getCharAtxy(ex5 - 1, ey5 + 3) == ' ')
        {
            eraseenemy3(ex5, ey5);
            ex5--;
            printenemy3_left(ex5, ey5);
        }
        else
        {
            enemy5direction = "right";
        }
    }
    else if (enemy5direction == "up")
    {
        if (getCharAtxy(ex5, ey5 - 1) == ' ' && getCharAtxy(ex5 + 2, ey5 - 1) == ' ')
        {
            eraseenemy3(ex5, ey5);
            ey5--;
            printenemy3_left(ex5, ey5);
        }
        else
        {
            enemy5direction = "down";
        }
    }
    else if (enemy5direction == "down")
    {
        if (getCharAtxy(ex5, ey5 + 4) == ' ' && getCharAtxy(ex5 + 2, ey5 + 4) == ' ')
        {
            eraseenemy3(ex5, ey5);
            ey5++;
            printenemy3_left(ex5, ey5);
        }
        else
        {
            enemy5direction = "up";
        }
    }
}

void printenemy6right(int x, int y) // print enemy 6 facing right side of the console
{
    string body[3][3] = {{" ", "9", " "}, {"(", "L", "="}, {"/", ")", " "}};
    print_by_3_character(body, 3, "\33[32m", x, y);
}

void printenemy6left(int x, int y) // print enemy 6 facing left side of console
{
    string body[3][3] = {{" ", "9", " "}, {"=", "J", ")"}, {" ", "(", "\\"}};
    print_by_3_character(body, 3, "\33[32m", x, y);
}

int enemy6_xdistance_calculator()
{
    return sqrt((px - ex6) * (px - ex6));
}

void enemy6director() // decides movement of enemy 6
{
    // for shooting player if their y coordinates match
    if ((ey6 == py || ey6 == py - 1 || ey6 == py - 2 || ey6 == py + 1 || ey6 == py + 2) && enemy6timer <= 60)
    {
        if (ex6 > px)
        {
            printenemy6left(ex6, ey6);
            enemybullet(ex6 - 1, ey6, "left");
        }
        else if (ex6 < px)
        {
            printenemy6right(ex6, ey6);
            enemybullet(ex6 + 3, ey6, "right");
        }
        if (enemy6timer == 60)
        {
            enemy6timer = 100;
        }
    }

    // incase of no shooting
    if (py > ey6)
    {
        if (getCharAtxy(ex6, ey6 + 3) == ' ')
        {
            enemy6direction = "down";
        }
        else
        {
            enemy6direction = "left";
        }
    }
    else if (py < ey6)
    {
        if (getCharAtxy(ex6, ey6 - 1) == ' ')
        {
            enemy6direction = "up";
        }
        else
        {
            enemy6direction = "left";
        }
    }
    if (enemy6_xdistance_calculator() > 30)
    {
        if (px > ex6)
        {
            if (getCharAtxy(ex6 + 3, ey6) == ' ' && getCharAtxy(ex6 + 3, ey6 + 1) == ' ' && getCharAtxy(ex6 + 3, ey6 + 2) == ' ')
            {
                enemy6direction = "right";
            }
            else if (getCharAtxy(ex6, ey6 + 3) == ' ' && getCharAtxy(ex6 + 1, ey6 + 3) == ' ' && getCharAtxy(ex6 + 2, ey6 + 3))
            {
                enemy6direction = "down";
            }
            else
            {
                enemy6direction = "up";
            }
        }
        else if (px < ex6)
        {
            if (getCharAtxy(ex6 - 1, ey6) == ' ' && getCharAtxy(ex6 - 1, ey6 + 1) == ' ' && getCharAtxy(ex6 - 1, ey6 + 2) == ' ')
            {
                enemy6direction = "left";
            }
            else if (getCharAtxy(ex6, ey6 + 3) == ' ' && getCharAtxy(ex6 + 1, ey6 + 3) == ' ' && getCharAtxy(ex6 + 2, ey6 + 3))
            {
                enemy6direction = "down";
            }
            else
            {
                enemy6direction = "up";
            }
        }
    }
    enemy6movement();
}

void enemy6movement()
{
    if (enemy6direction == "right")
    {
        if (getCharAtxy(ex6 + 3, ey6) == ' ' && getCharAtxy(ex6 + 3, ey6 + 1) == ' ' && getCharAtxy(ex6 + 3, ey6 + 2) == ' ')
        {
            erase(ex6, ey6);
            ex6++;
            printenemy6right(ex6, ey6);
        }
    }
    else if (enemy6direction == "left")
    {
        if (getCharAtxy(ex6 - 1, ey6) == ' ' && getCharAtxy(ex6 - 1, ey6 + 1) == ' ' && getCharAtxy(ex6 - 1, ey6 + 2) == ' ')
        {
            erase(ex6, ey6);
            ex6--;
            printenemy6left(ex6, ey6);
        }
    }
    if (enemy6direction == "up")
    {
        if (getCharAtxy(ex6, ey6 - 1) == ' ' && getCharAtxy(ex6 + 1, ey6 - 1) == ' ' && getCharAtxy(ex6 + 2, ey6 - 1) == ' ' /* && getCharAtxy(px + 3, py - 1) == ' ' && getCharAtxy(px + 4, py - 1) == ' '*/)
        {
            erase(ex6, ey6);
            ey6--;
            printenemy6left(ex6, ey6);
        }
    }
    else if (enemy6direction == "down")
    {
        if (getCharAtxy(ex6, ey6 + 3) == ' ' && getCharAtxy(ex6 + 1, ey6 + 3) == ' ' && getCharAtxy(ex6 + 2, ey6 + 3) == ' ')
        {
            erase(ex6, ey6);
            ey6++;
            printenemy6left(ex6, ey6);
        }
    }
}

void printenemybullet(int x, int y) // prints enemy bullets
{
    gotoxy(x, y);
    cout << "\33[31m"
         << "-";
}

void enemybulletinitializer()
{
    for (int i = 0; i < 10000; i++)
    {
        is_enemy_right_bullet_active[i] = false;
        is_enemy_left_bullet_active[i] = false;
    }
}

void enemybullet(int x, int y, string direction) // generates an enemy bullet and add index in the array
{
    // generating right side bullets of enemies
    if (direction == "right")
    {
        enemyrightbulletsX[ebulletcountR] = x;
        enemyrightbulletsY[ebulletcountR] = y;
        is_enemy_right_bullet_active[ebulletcountR] = true;
        ebulletcountR++;
        printenemybullet(x, y);
    }

    // generating left side bullets of enemies
    else if (direction == "left")
    {
        enemyleftbulletsX[ebulletcountL] = x - 1;
        enemyleftbulletsY[ebulletcountL] = y + 1;
        is_enemy_left_bullet_active[ebulletcountL] = true;
        ebulletcountL++;
        printenemybullet(x - 1, y + 1);
    }
}

void enemybulletmovement() // moves all the bullets of enemies
{
    // for right hand side bullet
    for (int i = 0; i < ebulletcountR; i++)
    {
        if (is_enemy_right_bullet_active[i])
        {
            erasebullet(enemyrightbulletsX[i], enemyrightbulletsY[i]);
            enemyrightbulletsX[i] += 1;
            printenemybullet(enemyrightbulletsX[i], enemyrightbulletsY[i]);
        }
    }

    // for left hand side bullet
    for (int i = 0; i < ebulletcountL; i++)
    {
        if (is_enemy_left_bullet_active[i])
        {
            erasebullet(enemyleftbulletsX[i], enemyleftbulletsY[i]);
            enemyleftbulletsX[i] -= 1;
            printenemybullet(enemyleftbulletsX[i], enemyleftbulletsY[i]);
        }
    }
}

void enemybulletcollision() // enemy bullet collsion detection
{
    // for right hand side bullet
    for (int i = 0; i < ebulletcountR; i++)
    {
        if (is_enemy_right_bullet_active[i])
        {
            int x = enemyrightbulletsX[i], y = enemyrightbulletsY[i];
            char next = getCharAtxy(x + 1, y);
            if ((x + 1 == px + 1 && y == py) || (x + 1 == px && y == py + 1) || (x + 1 == px + 2 && y == py + 1) || (x + 1 == px && y == py + 2) || (x + 1 == px + 1 && y == py + 2) || (x + 1 == px + 2 && y == py + 2))
            {
                erasebullet(x, y);
                if (playeralive)
                {
                    phealthdamage(2, 1, 1);
                }
                removeenemybullet(i, "right");
            }
            else if (next != ' ')
            {
                erasebullet(x, y);
                removeenemybullet(i, "right");
            }
        }
    }

    // for left hand side bullet
    for (int i = 0; i < ebulletcountL; i++)
    {
        if (is_enemy_left_bullet_active[i])
        {
            int x = enemyleftbulletsX[i], y = enemyleftbulletsY[i];
            char next = getCharAtxy(x - 1, y);
            if ((x - 1 == px + 1 && y == py) || (x - 1 == px && y == py + 1) || (x - 1 == px + 2 && y == py + 1) || (x - 1 == px && y == py + 2) || (x - 1 == px + 1 && y == py + 2) || (x - 1 == px + 2 && y == py + 2))
            {
                erasebullet(x, y);
                if (playerhealth)
                {
                    phealthdamage(2, 1, 1);
                }
                removeenemybullet(i, "left");
            }
            else if (next != ' ')
            {
                erasebullet(x, y);
                removeenemybullet(i, "left");
            }
        }
    }
}

void removeenemybullet(int c, string direction) // removes enemy bullet from the arrays
{
    // for right hand side bullet
    if (direction == "right")
    {
        is_enemy_right_bullet_active[c] = false;
    }

    // for left hand side bullet
    else if (direction == "left")
    {
        is_enemy_left_bullet_active[c] = false;
    }
}

void resetenemybullets()
{
    // for right bullets
    for (int i = 0; i < ebulletcountR; i++)
    {
        if (!is_enemy_right_bullet_active[i])
        {
            for (int j = i; j < ebulletcountR - 1; j++)
            {
                enemyrightbulletsX[j] = enemyrightbulletsX[j + 1];
                enemyrightbulletsY[j] = enemyrightbulletsY[j + 1];
                is_enemy_right_bullet_active[j] = is_enemy_right_bullet_active[j + 1];
            }
            ebulletcountR--;
        }
    }

    // for left bullets
    for (int i = 0; i < ebulletcountL; i++)
    {
        if (!is_enemy_left_bullet_active[i])
        {
            for (int j = i; j < ebulletcountL - 1; j++)
            {
                enemyleftbulletsX[j] = enemyleftbulletsX[j + 1];
                enemyleftbulletsY[j] = enemyleftbulletsY[j + 1];
                is_enemy_left_bullet_active[j] = is_enemy_left_bullet_active[j + 1];
            }
            ebulletcountL--;
        }
    }
}

void erasebullet(int x, int y) // erases the bullet
{
    gotoxy(x, y);
    cout << " ";
}

void printbullet(int x, int y) // prints the bullet
{
    gotoxy(x, y);
    cout << "\33[31m"
         << ".";
}

void bullet(int x, int y) // generates a player bullet and adds bullet index in the array
{
    // generating right hand side bullet
    if (playerdirection == "right")
    {
        rightbulletsX[pbulletcountR] = x + 3;
        rightbulletsY[pbulletcountR] = y + 1;
        is_player_right_bullet_active[pbulletcountR] = true;
        pbulletcountR++;
        printbullet(x + 3, y + 1);
    }

    // generating left hand side bullet
    else if (playerdirection == "left")
    {
        leftbulletsX[pbulletcountL] = x - 1;
        leftbulletsY[pbulletcountL] = y + 1;
        is_player_left_bullet_active[pbulletcountL] = true;
        pbulletcountL++;
        printbullet(x - 1, y + 1);
    }
}

void bulletmovement() // moves all the bullets of player
{
    // for right hand side bullet
    for (int i = 0; i < pbulletcountR; i++)
    {
        if (is_player_right_bullet_active[i])
        {
            erasebullet(rightbulletsX[i], rightbulletsY[i]);
            rightbulletsX[i] += 1;
            printbullet(rightbulletsX[i], rightbulletsY[i]);
        }
    }

    // for left hand side bullet
    for (int i = 0; i < pbulletcountL; i++)
    {
        if (is_player_left_bullet_active[i])
        {
            erasebullet(leftbulletsX[i], leftbulletsY[i]);
            leftbulletsX[i] -= 1;
            printbullet(leftbulletsX[i], leftbulletsY[i]);
        }
    }
}

void bulletcollision() // Remove the bullet in case of collision with the enemy
{
    // for right hand side bullet
    for (int i = 0; i < pbulletcountR; i++)
    {
        if (is_player_right_bullet_active[i])
        {
            int x = rightbulletsX[i], y = rightbulletsY[i];
            char next = getCharAtxy(x + 1, y);
            if ((x + 1 == ex && y == ey) || (x + 1 == ex + 1 && y == ey) || (x + 1 == ex && y == ey + 1) || (x + 1 == ex + 4 && y == ey + 1) || (x + 1 == ex + 1 && y == ey + 2) || (x + 1 == ex + 2 && y == ey + 2) || (x + 1 == ex && y == ey + 3) || (x + 1 == ex + 1 && y == ey + 3) || (x + 1 == ex + 2 && y == ey + 3))
            {
                erasebullet(x, y);
                if (enemy1alive)
                {
                    addscore();
                    e1healthdamage(5);
                }
                removebullet(i, "right");
            }
            else if ((x + 1 == ex2 + 2 && y == ey2) || (x + 1 == ex2 && y == ey2 + 1) || (x + 1 == ex2 + 1 && y == ey2 + 2) || (x + 1 == ex2 + 1 && y == ey2 + 2))
            {
                erasebullet(x, y);
                if (enemy2alive)
                {
                    addscore();
                    e2healthdamage(5);
                }
                removebullet(i, "right");
            }
            else if ((x + 1 == ex3 && y == ey3) || (x + 1 == ex3 + 3 && y == ey3) || (x + 1 == ex3 && y == ey3 + 1) || (x + 1 == ex3 + 3 && y == ey3 + 1) || (x + 1 == ex3 && y == ey3 + 2) || (x + 1 == ex3 + 3 && y == ey3 + 2) || (x + 1 == ex3 && y == ey3 + 3) || (x + 1 == ex3 + 3 && y == ey3 + 3))
            {
                erasebullet(x, y);
                if (enemy3alive)
                {
                    addscore();
                    e3healthdamage(5);
                }
                removebullet(i, "right");
            }
            else if ((x + 1 == ex5 && y == ey5) || (x + 1 == ex5 + 3 && y == ey5) || (x + 1 == ex5 && y == ey5 + 1) || (x + 1 == ex5 + 3 && y == ey5 + 1) || (x + 1 == ex5 && y == ey5 + 2) || (x + 1 == ex5 + 3 && y == ey5 + 2) || (x + 1 == ex5 && y == ey5 + 3) || (x + 1 == ex5 + 3 && y == ey5 + 3))
            {
                erasebullet(x, y);
                if (enemy5alive)
                {
                    addscore();
                    e5healthdamage(5);
                }
                removebullet(i, "right");
            }
            else if ((x + 1 == ex6 && y == ey6) || (x + 1 == ex6 && y == ey6 + 1) || (x + 1 == ex6 && y == ey6 + 2))
            {
                erasebullet(x, y);
                if (enemy6alive)
                {
                    addscore();
                    e6healthdamage(10);
                }
                removebullet(i, "right");
            }
            else if ((x + 1 == px1 + 1 && y == py1) || (x + 1 == px1 && y == py1 + 1) || (x + 1 == px1 + 2 && y == py1 + 1) || (x + 1 == px1 && y == py1 + 2) || (x + 1 == px1 + 1 && y == py1 + 2) || (x + 1 == px1 + 2 && y == py1 + 2))
            {
                erasebullet(x, y);
                if (player1alive)
                {
                    phealthdamage(5, 50, 4);
                }
                removebullet(i, "right");
            }
            else if ((x + 1 == px2 + 1 && y == py2) || (x + 1 == px2 && y == py2 + 1) || (x + 1 == px2 + 2 && y == py2 + 1) || (x + 1 == px2 && y == py2 + 2) || (x + 1 == px2 + 1 && y == py2 + 2) || (x + 1 == px2 + 2 && y == py2 + 2))
            {
                erasebullet(x, y);
                if (player2alive)
                {
                    p2healthdamage(5, 90, 4);
                }
                removebullet(i, "right");
            }
            else if (next != ' ')
            {
                erasebullet(x, y);
                removebullet(i, "right");
            }
        }
    }

    // for left hand side bullet
    for (int i = 0; i < pbulletcountL; i++)
    {
        if (is_player_left_bullet_active[i])
        {
            int x = leftbulletsX[i], y = leftbulletsY[i];
            char next = getCharAtxy(x - 1, y);
            if ((x - 1 == ex && y == ey) || (x - 1 == ex + 1 && y == ey) || (x - 1 == ex && y == ey + 1) || (x - 1 == ex + 4 && y == ey + 1) || (x - 1 == ex + 1 && y == ey + 2) || (x - 1 == ex + 2 && y == ey + 2) || (x - 1 == ex && y == ey + 3) || (x - 1 == ex + 1 && y == ey + 3) || (x - 1 == ex + 2 && y == ey + 3))
            {
                erasebullet(x, y);
                if (enemy1alive)
                {
                    addscore();
                    e1healthdamage(5);
                }
                removebullet(i, "left");
            }
            else if ((x - 1 == ex3 && y == ey3) || (x - 1 == ex3 + 3 && y == ey3) || (x - 1 == ex3 && y == ey3 + 1) || (x - 1 == ex3 + 3 && y == ey3 + 1) || (x - 1 == ex3 && y == ey3 + 2) || (x - 1 == ex3 + 3 && y == ey3 + 2) || (x - 1 == ex3 && y == ey3 + 3) || (x - 1 == ex3 + 3 && y == ey3 + 3))
            {
                erasebullet(x, y);
                if (enemy3alive)
                {
                    addscore();
                    e3healthdamage(5);
                }
                removebullet(i, "left");
            }
            else if ((x - 1 == ex5 && y == ey5) || (x - 1 == ex5 + 3 && y == ey5) || (x - 1 == ex5 && y == ey5 + 1) || (x - 1 == ex5 + 3 && y == ey5 + 1) || (x - 1 == ex5 && y == ey5 + 2) || (x - 1 == ex5 + 3 && y == ey5 + 2) || (x - 1 == ex5 && y == ey5 + 3) || (x - 1 == ex5 + 3 && y == ey5 + 3))
            {
                erasebullet(x, y);
                if (enemy5alive)
                {
                    addscore();
                    e5healthdamage(5);
                }
                removebullet(i, "left");
            }
            else if ((x - 1 == ex6 + 2 && y == ey6) || (x - 1 == ex6 + 2 && y == ey6 + 1) || (x - 1 == ex6 + 2 && y == ey6 + 2))
            {
                erasebullet(x, y);
                if (enemy6alive)
                {
                    addscore();
                    e6healthdamage(10);
                }
                removebullet(i, "left");
            }
            if ((x - 1 == px1 + 1 && y == py1) || (x - 1 == px1 && y == py1 + 1) || (x - 1 == px1 + 2 && y == py1 + 1) || (x - 1 == px1 && y == py1 + 2) || (x - 1 == px1 + 1 && y == py1 + 2) || (x - 1 == px1 + 2 && y == py1 + 2))
            {
                erasebullet(x, y);
                if (playerhealth)
                {
                    phealthdamage(5, 50, 4);
                }
                removeenemybullet(i, "left");
            }
            if ((x - 1 == px2 + 1 && y == py2) || (x - 1 == px2 && y == py2 + 1) || (x - 1 == px2 + 2 && y == py2 + 1) || (x - 1 == px2 && y == py2 + 2) || (x - 1 == px2 + 1 && y == py2 + 2) || (x - 1 == px2 + 2 && y == py2 + 2))
            {
                erasebullet(x, y);
                if (player2health)
                {
                    p2healthdamage(5, 90, 4);
                }
                removeenemybullet(i, "left");
            }
            else if (next != ' ')
            {
                erasebullet(x, y);
                removebullet(i, "left");
            }
        }
    }
}

void playerbulletinitializer()
{
    for (int i = 0; i < 1000; i++)
    {
        is_player_right_bullet_active[i] = false;
        is_player_left_bullet_active[i] = false;
    }
}

void removebullet(int c, string direction) // makes bullet inactive
{
    // for right hand side bullet
    if (direction == "right")
    {
        is_player_right_bullet_active[c] = false;
    }

    // for left hand side bullet
    else if (direction == "left")
    {
        is_player_left_bullet_active[c] = false;
    }
}

void resetplayerbullets() // removes inactive bullets from arrays
{
    // right side bullets
    for (int i = 0; i < pbulletcountR; i++)
    {
        if (!is_player_right_bullet_active[i])
        {
            for (int j = i; j < pbulletcountR - 1; j++)
            {
                rightbulletsX[j] = rightbulletsX[j + 1];
                rightbulletsY[j] = rightbulletsY[j + 1];
                is_player_right_bullet_active[j] = is_player_right_bullet_active[j + 1];
            }
            pbulletcountR--;
        }
    }

    // left side bullets
    for (int i = 0; i < pbulletcountL; i++)
    {
        if (!is_player_left_bullet_active[i])
        {
            for (int j = i; j < pbulletcountL - 1; j++)
            {
                leftbulletsX[j] = leftbulletsX[j + 1];
                leftbulletsY[j] = leftbulletsY[j + 1];
                is_player_left_bullet_active[j] = is_player_left_bullet_active[j + 1];
            }
            pbulletcountL--;
        }
    }
}

void phealth(string name, int x, int y) // prints player health on conscole
{
    counteraser(x, y);
    gotoxy(x, y);
    cout << "\33[33m"
         << name << " Health: " << playerhealth;
}

void phealthdamage(int damage, int x, int y) // calculates health of player after damage from enemies
{
    playerhealth -= damage;
    phealth(playername1, x, y);
}

void p2health(string name, int x, int y) // prints player health on conscole in multiplayer
{
    counteraser(x, y);
    gotoxy(x, y);
    cout << "\33[32m"
         << name << " Health: " << player2health;
}

void p2healthdamage(int damage, int x, int y) // calculates health of player after damage from enemies in multiplayer
{
    player2health -= damage;
    p2health("Player 2", x, y);
}

void e1health(int x, int y, string name) // prints health of enemy 2 on console
{
    counteraser(x, y);
    gotoxy(x, y);
    cout << "\33[32m"
         << name << " Health: " << enemy1health;
}

void e1healthdamage(int damage) // calculates enemy 1 health after damage from player bullet
{
    enemy1health -= damage;
}

void e2health(int x, int y, string name) // prints enemy 2 health on header bar
{
    counteraser(x, y);
    gotoxy(x, y);
    cout << "\33[32m"
         << name << " Health: " << enemy2health;
}

void e2healthdamage(int damage) // calcualtes health of enemy after damage by player bullet
{
    enemy2health -= damage;
}

void e3health(int x, int y, string name) // prints enemy 3 health on header bar
{
    counteraser(x, y);
    gotoxy(x, y);
    cout << "\33[34m"
         << name << " Health: " << enemy3health;
}

void e3healthdamage(int damage) // calcualtes health of enemy after damage by player bullet
{
    enemy3health -= damage;
}

void e5health(int x, int y, string name) // prints enemy 5 health on header bar
{
    counteraser(x, y);
    gotoxy(x, y);
    cout << "\33[34m"
         << name << " Health: " << enemy5health;
}

void e5healthdamage(int damage) // calcualtes health of enemy after damage by player bullet
{
    enemy5health -= damage;
}

void e6health(int x, int y, string name) // prints enemy 6 health on header bar
{
    counteraser(x, y);
    gotoxy(x, y);
    cout << "\33[32m"
         << name << " Health: " << enemy6health;
}

void e6healthdamage(int damage) // calcualtes health of enemy after damage by player bullet
{
    enemy6health -= damage;
}

void addscore() // increments score
{
    score++;
    printscore();
}

void printscore() // prints score on console
{
    gotoxy(80, 5);
    cout << "\33[37m"
         << "Score: " << score;
}

void printhealthpill() // print health pill with label on header bar
{
    gotoxy(140, 2);
    cout << "\33[35m"
         << "Health Pill -> ";
    healthpill(156, 1);
}

void counteraser(int x, int y) // erases the previous value of health and bullet count
{
    gotoxy(x, y);
    cout << "                      ";
}

void displayebulletcount() // displays bullet count on console
{
    counteraser(80, 4);
    gotoxy(80, 4);
    cout << "\33[37m"
         << "bullets: " << bulletcount;
}

void printbulletcrate() // print bullet crate with label on header bar
{
    gotoxy(140, 4);
    cout << "\33[35m"
         << "Bullet Crate -> ";
    bulletcrate(156, 4);
}

void headbar() // player, enemy, health and score bar
{
    phealth(playername1, 1, 1);
    printscore();
    displayebulletcount();
    printbulletcrate();
    printhealthpill();
}

void firstrow(int x, int y) // first & last row of map
{
    gotoxy(x, y);
    for (int i = 0; i < 166; i++)
    {
        cout << "\33[36m"
             << "#";
        x++;
        gotoxy(x, y);
    }
}

void innerrows(int x, int y) // inner rows of map
{
    gotoxy(x, y);
    cout << "\33[36m"
         << "#";
    x++;
    for (int i = 0; i < 164; i++)
    {
        gotoxy(x, y);
        cout << " ";
        x++;
    }
    gotoxy(x, y);
    cout << "\33[36m"
         << "#";
}

void boundary() // boundary of the map
{
    int x = 1, y = 8;
    firstrow(x, y);
    y++;
    for (int i = 0; i < 35; i++)
    {
        innerrows(x, y + i);
    }
    firstrow(x, y + 35);
}

void platform(int x, int y, int size) // platforms for maps
{
    char box = 219;
    for (int i = 0; i < size; i++)
    {
        gotoxy(x + i, y);
        cout << "\33[36m" << box;
    }
}

void verticalplatform(int x, int y, int width, int height) // to print vertical walls using the platform function
{
    for (int i = 0; i < height; i++)
    {
        platform(x, y + i, width);
    }
}

void objectinitiolizer() // to print crates, health pills and key on the respective map
{
    healthpill(hpillx, hpilly);
    bulletcrate(bcratex, bcratey);
}

void map1() // printing map1 of the game
{
    objectinitiolizer();
    platform(3, 24, 25);
    platform(100, 15, 20);
    platform(80, 35, 18);
    platform(85, 36, 8);
    platform(85, 34, 8);
    platform(60, 22, 13);
    platform(60, 23, 13);
    platform(60, 21, 7);
    platform(60, 20, 7);
    platform(130, 27, 12);
    platform(130, 28, 4);
    platform(138, 28, 4);
}

void map2() // printing map 2 of the game
{
    objectinitiolizer();
    platform(52, 16, 3);
    platform(52, 17, 3);
    platform(30, 18, 25);
    platform(30, 19, 3);
    platform(30, 20, 3);
    platform(20, 30, 30);
    platform(60, 25, 25);
    platform(68, 24, 10);
    platform(95, 18, 25);
    platform(135, 12, 15);
    platform(90, 38, 55);
    verticalplatform(47, 31, 3, 13);
    verticalplatform(115, 30, 3, 8);
    verticalplatform(95, 19, 2, 10);
    verticalplatform(135, 12, 2, 15);
}

void map3()
{
    objectinitiolizer();
    platform(30, 16, 135);
    platform(130, 22, 35);
    platform(3, 32, 35);
    platform(70, 24, 12);
    platform(70, 28, 24);
    platform(82, 32, 12);
    verticalplatform(70, 28, 2, 5);
    verticalplatform(81, 24, 2, 9);
    verticalplatform(92, 24, 2, 5);
    verticalplatform(36, 25, 2, 7);
    verticalplatform(145, 38, 2, 6);
}

void healthpill(int x, int y) // printing health pill sprite
{
    string body[2][2] = {{"+", "+"}, {"+", "+"}};
    print_by_2_character(body, 2, "\33[33m", x, y);
}

void erasehealthpill(int x, int y) // erases the health pill
{
    string body[2][2] = {{" ", " "}, {" ", " "}};
    print_by_2_character(body, 2, "\33[33m", x, y);
}

void bulletcrate(int x, int y) // forms a bullet crate
{
    string body[3] = {"|", "^", "|"};
    for (int i = 0; i < 3; i++)
    {
        gotoxy(x, y);
        cout << "\33[33m" << body[i];
        x++;
    }
}

void touchhealthpill(int x, int y) // determines whether player touches the health pill and resets player's health
{
    if ((x == hpillx || x + 1 == hpillx || x + 2 == hpillx || x == hpillx + 2 || x + 1 == hpillx + 2 || x + 3 == hpillx + 2) && (y == hpilly || y + 1 == hpilly || y + 2 == hpilly))
    {
        erasehealthpill(hpillx, hpilly);
        playerhealth = 100;
        phealth(playername1, 1, 1);
    }
}

void erasebulletcrate(int x, int y) // erases bullet crate
{
    string body[3] = {" ", " ", " "};
    for (int i = 0; i < 3; i++)
    {
        gotoxy(x, y);
        cout << body[i];
        x++;
    }
}

void touchbulletcrate(int x, int y) // detects if player touches bullet crate and resets bullet count
{
    if ((x == bcratex || x + 1 == bcratex || x + 2 == bcratex || x == bcratex + 3 || x + 1 == bcratex + 3 || x + 2 == bcratex + 3) && (y == bcratey || y + 1 == bcratey || y + 2 == bcratey))
    {
        erasebulletcrate(bcratex, bcratey);
        bulletcount = 100;
        displayebulletcount();
    }
}

void printkey(int x, int y) // prints the key which is used to win the level
{
    string body[3] = {"c", "=", ">"};
    for (int i = 0; i < 3; i++)
    {
        gotoxy(x, y);
        cout << "\33[37m" << body[i];
        x++;
    }
}

void touchkey(int x, int y) // determine whether player gets the key and advances to next level
{
    if ((x == key_x || x == key_x + 1 || x == key_x + 2) && (y == key_y || y + 1 == key_y || y + 2 == key_y))
    {
        erasebulletcrate(key_x, key_y); // since bullet crate and key have similar coordinate shape
        if (level1running)
        {
            level1complete = true;
            level1running = false;
            playersdata[playercount][1] = "1";
            writedata();
            levelendscreen("Level 1 Completed!");
        }
        else if (level2running)
        {
            level2complete = true;
            level2running = false;
            playersdata[playercount][2] = "1";
            writedata();
            levelendscreen("Level 2 Completed!");
        }
        else if (level3running)
        {
            level3complete = true;
            multiplayer = true;
            playersdata[playercount][3] = "1";
            playersdata[playercount][4] = "1";
            writedata();
            levelendscreen("Level 3 Completed!");
        }
    }
}

void checkitems(int x, int y) // checks whether player touches items in the map
{
    touchhealthpill(x, y);
    touchbulletcrate(x, y);
    touchkey(x, y);
}

void printzombie(int x, int y) // printing zombies on the console
{
    string body[3][3] = {{" ", "x", " "}, {"`", "!", "`"}, {"/", " l", "\\"}};
    print_by_3_character(body, 3, "\33[35m", x, y);
}

void erasezombie(int x, int y) // erase zombies from the console
{
    string body[3][3] = {{" ", " ", " "}, {" ", " ", " "}, {" ", " ", " "}};
    print_by_3_character(body, 3, "\33[35m", x, y);
}

void zombiedeathsprite(int x, int y) // zombie dies and leaves it's corpse
{
    string body[3][3] = {{" ", "!", " "}, {"\\", "|", "/"}, {" ", " ", ":"}};
    print_by_3_character(body, 3, "\33[31m", x, y);
}

void zombiemovement() // movement functionality of zombie
{
    for (int i = 0; i < 10; i++)
    {
        if (zombiealive[i] == true)
        {
            int zx = zombiex[i], zy = zombiey[i];
            if (py > zy)
            {
                if (getCharAtxy(zx, zy + 3) == ' ' && getCharAtxy(zx + 1, zy + 3) == ' ' && getCharAtxy(zx + 2, zy + 3) == ' ')
                {
                    erasezombie(zx, zy);
                    zy++;
                    zombiey[i]++;
                    printzombie(zx, zy);
                }
            }
            else if (py < zy)
            {
                if (getCharAtxy(zx, zy - 1) == ' ' && getCharAtxy(zx + 1, zy - 1) == ' ' && getCharAtxy(zx + 2, zy - 1) == ' ')
                {
                    erasezombie(zx, zy);
                    zy--;
                    zombiey[i]--;
                    printzombie(zx, zy);
                }
            }
            if (px > zx)
            {
                if (getCharAtxy(zx + 3, zy) == ' ' && getCharAtxy(zx + 3, zy + 1) == ' ' && getCharAtxy(zx + 3, zy + 2) == ' ')
                {
                    erasezombie(zx, zy);
                    zx++;
                    zombiex[i]++;
                    printzombie(zx, zy);
                }
            }
            else if (px < zx)
            {
                if (getCharAtxy(zx - 1, zy) == ' ' && getCharAtxy(zx - 1, zy + 1) == ' ' && getCharAtxy(zx - 1, zy + 2) == ' ')
                {
                    erasezombie(zx, zy);
                    zx--;
                    zombiex[i]--;
                    printzombie(zx, zy);
                }
            }
        }
    }
}

void zombieattack() // zombie attacks the player and player looses health
{
    if (getCharAtxy(px - 1, py) == '`' || getCharAtxy(px - 1, py + 1) == '`' || getCharAtxy(px - 1, py + 2) == '`' || getCharAtxy(px + 3, py) == '`' || getCharAtxy(px + 3, py + 1) == '`' || getCharAtxy(px + 3, py + 2) == '`')
    {
        playerhealth -= 10;
        phealth(playername1, 1, 1);
    }
}

void zombiedeath() // kills a zombie upon damage from player bullet
{
    for (int i = 0; i < 10; i++)
    {
        int x = zombiex[i], y = zombiey[i];
        if (getCharAtxy(x - 1, y) == '.' || getCharAtxy(x + 3, y) == '.' || getCharAtxy(x - 1, y + 1) == '.' || getCharAtxy(x + 3, y + 1) == '.' || getCharAtxy(x - 1, y + 2) == '.' || getCharAtxy(x + 3, y + 2) == '.')
        {
            zombiedeathsprite(x, y);
            zombiealive[i] = false;
            addscore();
        }
    }
}

void zombiereset() // to reset coordinates of zombies if player replays level 2
{
    int zombiextemp[10] = {10, 15, 140, 125, 115, 68, 110, 35, 150, 145};
    int zombieytemp[10] = {12, 14, 18, 34, 40, 33, 20, 26, 38, 18};

    for (int i = 0; i < 10; i++)
    {
        zombiex[i] = zombiextemp[i];
        zombiey[i] = zombieytemp[i];
        zombiealive[i] = true;
    }
}

void zombieresetlevel3() // to reset coordinates of level 3 zombies
{
    int tempx[5] = {8, 15, 19, 23, 27};
    int tempy[5] = {25, 26, 28, 24, 28};
    for (int i = 0; i < 5; i++)
    {
        level3zombiesx[i] = tempx[i];
        level3zombiesy[i] = tempy[i];
        level3zombiealive[i] = true;
    }
}

void zombiemovementlevel3() // movement of level 3 zombies
{
    for (int i = 0; i < 5; i++)
    {
        int zx = level3zombiesx[i], zy = level3zombiesy[i];
        if (distance(px, py, zx, zy) <= 15 && level3zombiealive[i])
        {
            if (py > zy)
            {
                if (getCharAtxy(zx, zy + 3) == ' ' && getCharAtxy(zx + 1, zy + 3) == ' ' && getCharAtxy(zx + 2, zy + 3) == ' ')
                {
                    erasezombie(zx, zy);
                    zy++;
                    level3zombiesy[i]++;
                    printzombie(zx, zy);
                }
            }
            else if (py < zy)
            {
                if (getCharAtxy(zx, zy - 1) == ' ' && getCharAtxy(zx + 1, zy - 1) == ' ' && getCharAtxy(zx + 2, zy - 1) == ' ')
                {
                    erasezombie(zx, zy);
                    zy--;
                    level3zombiesy[i]--;
                    printzombie(zx, zy);
                }
            }
            if (px > zx)
            {
                if (getCharAtxy(zx + 3, zy) == ' ' && getCharAtxy(zx + 3, zy + 1) == ' ' && getCharAtxy(zx + 3, zy + 2) == ' ')
                {
                    erasezombie(zx, zy);
                    zx++;
                    level3zombiesx[i]++;
                    printzombie(zx, zy);
                }
            }
            else if (px < zx)
            {
                if (getCharAtxy(zx - 1, zy) == ' ' && getCharAtxy(zx - 1, zy + 1) == ' ' && getCharAtxy(zx - 1, zy + 2) == ' ')
                {
                    erasezombie(zx, zy);
                    zx--;
                    level3zombiesx[i]--;
                    printzombie(zx, zy);
                }
            }
        }
    }
}

void level3zombiedeath() // kills a zombie upon damage from player bullet
{
    for (int i = 0; i < 5; i++)
    {
        int x = level3zombiesx[i], y = level3zombiesy[i];
        if (getCharAtxy(x - 1, y) == '.' || getCharAtxy(x + 3, y) == '.' || getCharAtxy(x - 1, y + 1) == '.' || getCharAtxy(x + 3, y + 1) == '.' || getCharAtxy(x - 1, y + 2) == '.' || getCharAtxy(x + 3, y + 2) == '.')
        {
            zombiedeathsprite(x, y);
            level3zombiealive[i] = false;
            addscore();
        }
    }
}

float distance(int x1, int y1, int x2, int y2) // calculates distance between two coordinates using the distance formula
{
    return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
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

void levelselection() // screen for selecting levels
{
    system("cls");
    gotoxy(60, 16);
    for (int i = 0; i < 45; i++)
    {
        cout << "\33[33m"
             << "*";
    }
    if (multiplayer)
    {
        gotoxy(70, 13);
        cout << "\33[32m"
             << "Multiplayer mode unlocked!";
    }
    gotoxy(75, 18);
    cout << "\33[33m"
         << "-> Level 1";
    if (level1complete && !level2complete)
    {
        gotoxy(75, 19);
        cout << "\33[33m"
             << "-> Level 2";
        gotoxy(75, 20);
        cout << "\33[33m"
             << "-> Back";
        int opt = option(3, 75, 21);
        if (opt == 1)
        {
            level1();
        }
        else if (opt == 2)
        {
            level2();
        }
        else
        {
            menu();
        }
    }
    else if (level2complete)
    {
        gotoxy(75, 19);
        cout << "\33[33m"
             << "-> Level 2";
        gotoxy(75, 20);
        cout << "\33[33m"
             << "-> Level 3";
        gotoxy(75, 21);
        cout << "\33[33m"
             << "-> Back";
        int opt = option(4, 75, 22);
        if (opt == 1)
        {
            level1();
        }
        else if (opt == 2)
        {
            level2();
        }
        else if (opt == 3)
        {
            level3();
        }
        else
        {
            menu();
        }
    }
    else
    {
        gotoxy(75, 19);
        cout << "\33[33m"
             << "-> Back";
        int opt = option(2, 75, 20);
        if (opt == 1)
        {
            level1();
        }
        else
        {
            menu();
        }
    }
}

void continuekey(int x, int y) // proceed program upon user input
{
    gotoxy(x, y);
    cout << "\33[35m"
         << "Press any key to continue: ";
    getch();
}

void levelendscreen(string text) // screen appears at the end of each level
{
    Sleep(1000);
    gotoxy(70, 21);
    for (int i = 0; i < 30; i++)
    {
        cout << "\33[33m"
             << "%";
    }
    gotoxy(78, 23);
    cout << "\33[33m" << text;
    gotoxy(70, 25);
    for (int i = 0; i < 30; i++)
    {
        cout << "\33[33m"
             << "%";
    }
    Sleep(3000);
    if (mp_mode)
    {
        multiplayermode();
        mp_mode = false;
    }
    else
    {
        levelselection();
    }
}

void multiplayermode() // multiplayer menu
{
    system("cls");
    if (!multiplayer)
    {
        gotoxy(70, 15);
        cout << "\33[32m"
             << "Locked!";
        continuekey(61, 20);
        menu();
    }
    else
    {
        gotoxy(50, 13);
        cout << "\33[33m"
             << "********************************************************";
        gotoxy(70, 15);
        cout << "\33[33m"
             << "Stage 1";
        gotoxy(70, 16);
        cout << "\33[33m"
             << "Stage 2";
        gotoxy(70, 17);
        cout << "\33[33m"
             << "back";
        int opt = option(3, 70, 18);
        if (opt == 1)
        {
            stage1();
            mpfunctionality();
        }
        else if (opt == 2)
        {
            stage2();
            mpfunctionality();
        }
        else
        {
            menu();
        }
    }
}

void stage1()
{
    mpheadbar();
    platform(50, 25, 25);
    platform(90, 25, 25);
    platform(70, 29, 25);
    platform(40, 29, 15);
    platform(110, 29, 15);
    platform(50, 33, 25);
    platform(90, 33, 25);
}

void stage2()
{
    mpheadbar();
    platform(50, 23, 60);
    platform(37, 27, 15);
    platform(108, 27, 15);
    platform(24, 31, 15);
    platform(121, 31, 15);
    platform(37, 35, 15);
    platform(108, 35, 15);
    platform(50, 39, 60);
}

void mpheadbar() // prints basic head bar of multiplayer mode
{
    system("cls");
    boundary();
}

void mpfunctionality()
{
    // assingments
    px1 = 60, py1 = 10, px2 = 100, py2 = 10;
    playerhealth = 100, player2health = 100;
    player1alive = true, player2alive = true;
    mprunning = true, mp_mode = true;
    playername1 = "Player 1";

    // screen interface
    phealth("Player 1", 50, 4);
    p2health("Player 2", 90, 4);
    printplayer1_right(px1, py1);
    printplayer2_left(px2, py2);
    playerbulletinitializer();

    while (mprunning)
    {
        if (playerhealth > 0)
        {
            player1movement();
        }
        else
        {
            player1alive = false;
            levelendscreen("Player 2 wins!");
        }
        if (player2health > 0)
        {
            player2movement();
        }
        else
        {
            player2alive = false;
            levelendscreen("Player 1 wins!");
        }
        bulletmovement();
        bulletcollision();
        Sleep(50);
    }
}

void printplayer1withdirection()
{
    if (player1direction == "left")
    {
        printplayer1_left(px1, py1);
    }
    else if (player1direction == "right")
    {
        printplayer1_right(px1, py1);
    }
}

void player1movement()
{
    if (jump > 0 && ((getCharAtxy(px1, py1 - 1) == ' ' && getCharAtxy(px1 + 1, py1 - 1) == ' ' && getCharAtxy(px1 + 2, py1 - 1) == ' ')))
    {
        erase(px1, py1);
        py1--;
        printplayer1withdirection();
        jump--;
        Sleep(20);
    }
    else if (getCharAtxy(px1, py1 + 3) == ' ' && getCharAtxy(px1 + 1, py1 + 3) == ' ' && getCharAtxy(px1 + 2, py1 + 3) == ' ')
    {
        erase(px1, py1);
        py1++;
        printplayer1withdirection();
    }
    if (GetAsyncKeyState(VK_RIGHT))
    {
        if (getCharAtxy(px1 + 3, py1) == ' ' && getCharAtxy(px1 + 3, py1 + 1) == ' ' && getCharAtxy(px1 + 3, py1 + 2) == ' ')
        {
            player1direction = "right";
            erase(px1, py1);
            px1++;
            printplayer1_right(px1, py1);
        }
    }
    if (GetAsyncKeyState(VK_LEFT))
    {
        if (getCharAtxy(px1 - 1, py1) == ' ' && getCharAtxy(px1 - 1, py1 + 1) == ' ' && getCharAtxy(px1 - 2, py1 + 2) == ' ')
        {
            player1direction = "left";
            erase(px1, py1);
            px1--;
            printplayer1_left(px1, py1);
        }
    }
    if (GetAsyncKeyState(VK_UP))
    {
        if (jump == 0 && (getCharAtxy(px1, py1 + 3) == box || getCharAtxy(px1 + 1, py1 + 3) == box || getCharAtxy(px1 + 2, py1 + 3) == box))
        {
            jump = 5;
        }
    }
    if (GetAsyncKeyState(VK_SPACE))
    {
        if (getCharAtxy(px1, py1) == ' ' && getCharAtxy(px1 - 1, py1 + 1) == ' ' && getCharAtxy(px1 + 3, py1 + 1) == ' ')
        {
            mpbulletplayer1(px1, py1);
        }
    }
    if (getCharAtxy(px1, py1 + 3) == '#' || getCharAtxy(px1 + 1, py1 + 3) == '#' || getCharAtxy(px1 + 2, py1 + 3) == '#')
    {
        playerhealth = 0;
    }
}

void printplayer2withdirection()
{
    if (player2direction == "left")
    {
        printplayer2_left(px2, py2);
    }
    else if (player2direction == "right")
    {
        printplayer2_right(px2, py2);
    }
}

void player2movement()
{
    if (jump2 > 0 && ((getCharAtxy(px2, py2 - 1) == ' ' && getCharAtxy(px2 + 1, py2 - 1) == ' ' && getCharAtxy(px2 + 2, py2 - 1) == ' ')))
    {
        erase(px2, py2);
        py2--;
        printplayer2withdirection();
        jump2--;
        Sleep(20);
    }
    else if (getCharAtxy(px2, py2 + 3) == ' ' && getCharAtxy(px2 + 1, py2 + 3) == ' ' && getCharAtxy(px2 + 2, py2 + 3) == ' ')
    {
        erase(px2, py2);
        py2++;
        printplayer2withdirection();
    }
    if (GetAsyncKeyState('D'))
    {
        if (getCharAtxy(px2 + 3, py2) == ' ' && getCharAtxy(px2 + 3, py2 + 1) == ' ' && getCharAtxy(px2 + 3, py2 + 2) == ' ')
        {
            player2direction = "right";
            erase(px2, py2);
            px2++;
            printplayer2_right(px2, py2);
        }
    }
    if (GetAsyncKeyState('A'))
    {
        if (getCharAtxy(px2 - 1, py2) == ' ' && getCharAtxy(px2 - 1, py2 + 1) == ' ' && getCharAtxy(px2 - 2, py2 + 2) == ' ')
        {
            player2direction = "left";
            erase(px2, py2);
            px2--;
            printplayer2_left(px2, py2);
        }
    }
    if (GetAsyncKeyState('W'))
    {
        if (jump2 == 0 && (getCharAtxy(px2, py2 + 3) == box || getCharAtxy(px2 + 1, py2 + 3) == box || getCharAtxy(px2 + 2, py2 + 3) == box))
        {
            jump2 = 5;
        }
    }
    if (GetAsyncKeyState(VK_SHIFT))
    {
        if (getCharAtxy(px2, py2) == ' ' && getCharAtxy(px2 - 1, py2 + 1) == ' ' && getCharAtxy(px2 + 3, py2 + 1) == ' ')
        {
            mpbulletplayer2(px2, py2);
        }
    }
    if (getCharAtxy(px2, py2 + 3) == '#' || getCharAtxy(px2 + 1, py2 + 3) == '#' || getCharAtxy(px2 + 2, py2 + 3) == '#')
    {
        player2health = 0;
    }
}

void mpbulletplayer1(int x, int y) // generates a player 1 bullet and adds bullet index in the array for multiplayer mode
{
    // generating right hand side bullet
    if (player1direction == "right")
    {
        rightbulletsX[pbulletcountR] = x + 3;
        rightbulletsY[pbulletcountR] = y + 1;
        is_player_right_bullet_active[pbulletcountR] = true;
        pbulletcountR++;
        printbullet(x + 3, y + 1);
    }

    // generating left hand side bullet
    else if (player1direction == "left")
    {
        leftbulletsX[pbulletcountL] = x - 1;
        leftbulletsY[pbulletcountL] = y + 1;
        is_player_left_bullet_active[pbulletcountL] = true;
        pbulletcountL++;
        printbullet(x - 1, y + 1);
    }
}

void mpbulletplayer2(int x, int y) // generates a player 2 bullet and adds bullet index in the array for multiplayer mode
{
    // generating right hand side bullet
    if (player2direction == "right")
    {
        rightbulletsX[pbulletcountR] = x + 3;
        rightbulletsY[pbulletcountR] = y + 1;
        is_player_right_bullet_active[pbulletcountR] = true;
        pbulletcountR++;
        printbullet(x + 3, y + 1);
    }

    // generating left hand side bullet
    else if (player2direction == "left")
    {
        leftbulletsX[pbulletcountL] = x - 1;
        leftbulletsY[pbulletcountL] = y + 1;
        is_player_left_bullet_active[pbulletcountL] = true;
        pbulletcountL++;
        printbullet(x - 1, y + 1);
    }
}

void printplayer1_right(int x, int y) // print player1 facing right side of the console
{
    string body[3][3] = {{" ", "1", " "}, {"(", "L", "="}, {"/", ")", " "}};
    print_by_3_character(body, 3, "\33[33m", x, y);
}

void printplayer1_left(int x, int y) // print player1 facing left side of console
{
    string body[3][3] = {{" ", "1", " "}, {"=", "J", ")"}, {" ", "(", "\\"}};
    print_by_3_character(body, 3, "\33[33m", x, y);
}

void printplayer2_right(int x, int y) // print player 2 facing right side of the console
{
    string body[3][3] = {{" ", "2", " "}, {"(", "L", "="}, {"/", ")", " "}};
    print_by_3_character(body, 3, "\33[32m", x, y);
}

void printplayer2_left(int x, int y) // print player 2 facing left side of console
{
    string body[3][3] = {{" ", "2", " "}, {"=", "J", ")"}, {" ", "(", "\\"}};
    print_by_3_character(body, 3, "\33[32m", x, y);
}

void gamereset() // erases previous record of player
{
    for (int i = 1; i < 5; i++)
    {
        playersdata[playercount][i] = "0";
    }
}

void newgame() // confirmation for starting the game from beginning
{
    system("cls");
    string choice;
    int c = 1;
    bool flag = false;
    gotoxy(75, 12);
    cout << "\33[31m"
         << "Are you sure? (Y/N): ";
    while (!flag)
    {
        getline(cin, choice);
        if (choice == "Y" || choice == "y")
        {
            flag = true;
            gamereset();
            writedata();
            level1complete = false;
            level2complete = false;
            level3complete = false;
            multiplayer = false;
            continuekey(70, 12 + c + 1);
            menu();
        }
        else if (choice == "N" || choice == "n")
        {
            flag = true;
            menu();
        }
        gotoxy(75, 12 + c);
        cout << "\33[31m"
             << "Invalid Input: ";
        c++;
    }
}

void mode(int opt) // selects mode of game
{
    if (opt == 1)
    {
        levelselection();
    }
    else if (opt == 2)
    {
        multiplayermode();
    }
    else if (opt == 3)
    {
        newgame();
    }
    else if (opt == 4)
    {
        startscreen();
    }
}

void menu() // prints main starting menu of game
{
    header();
    gotoxy(75, 20);
    cout << "\33[32m"
         << "1. Compaign" << endl;
    gotoxy(75, 21);
    cout << "\33[32m"
         << "2. Multiplayer" << endl;
    gotoxy(75, 22);
    cout << "\33[32m"
         << "3. New Game" << endl;
    gotoxy(75, 23);
    cout << "\33[32m"
         << "4. Exit" << endl;
    int opt = option(4, 75, 24);
    mode(opt);
}

void startscreen() // prints sign up/in screen
{
    system("cls");
    gotoxy(70, 10);
    for (int i = 0; i < 20; i++)
    {
        cout << "*";
    }
    gotoxy(75, 11);
    cout << "\33[33m"
         << "1. Sign in ";
    gotoxy(75, 12);
    cout << "\33[33m"
         << "2. Sign up ";
    gotoxy(75, 13);
    cout << "\33[33m"
         << "3. Quit " << endl;
    int opt = option(3, 70, 14);
    if (opt == 1)
    {
        signin();
    }
    else if (opt == 2)
    {
        signup();
    }
    else if (opt == 3)
    {
        system("cls");
        exit(0);
    }
}

void signup() // creates a new user to the game
{
    bool found = false;
    string name;
    while (!found)
    {
        name = usernameinputscreen();
        if (uniquename(name))
        {
            found = true;
            break;
        }
    }
    playercount = counter - 1;
    playersdata[playercount][0] = name;
    gamereset();
    counter++;
    writedata();
    continuekey(75, 15);
    startscreen();
}

void signin() // sign in players
{
    foundplayer = false;
    loadplayerdata(usernameinputscreen());
    if (foundplayer)
    {
        menu();
    }
    else
    {
        startscreen();
    }
}

bool uniquename(string name) // checks whether a username is already taken or not
{
    for (int i = 0; i < counter - 1; i++)
    {
        if (playersdata[i][0] == name)
        {
            return false;
        }
    }
    return true;
}

string usernameinputscreen() // inputs username
{
    system("cls");
    string name;
    bool found = false;
    while (!found)
    {
        system("cls");
        gotoxy(70, 12);
        for (int i = 0; i < 30; i++)
        {
            cout << "\33[32m"
                 << "*";
        }
        gotoxy(75, 13);
        cout << "\33[33m"
             << "Enter username: ";
        getline(cin, name);
        found = format(name);
    }
    return name;
}

bool format(string word) // validates input word based on ascii characters
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if ((word[i] < 65 || word[i] > 90) && (word[i] < 97 || word[i] > 122))
        {
            return false;
        }
    }
    return true;
}

void loaddata() // loads player status from file
{
    string line, tempname;
    fstream file;
    file.open("data.txt", ios::in);
    while (!file.eof())
    {
        getline(file, line);
        for (int i = 1; i < 6; i++)
        {
            playersdata[counter][i - 1] = linedata(line, i);
        }
        counter++;
    }
    file.close();
}

void writedata() // writes player status data
{
    fstream file;
    file.open("data.txt", ios::out);
    for (int i = 0; i < counter - 1; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            file << playersdata[i][j] << ",";
        }
        file << "\n";
    }
    file.close();
}

string linedata(string line, int col) // parse data from a line
{
    int c = 0;
    string data = "";
    for (int i = 0; line[i] != '\0'; i++)
    {
        if (line[i] == ',')
        {
            c++;
        }
        else if (c == col - 1)
        {
            data += line[i];
        }
    }
    return data;
}

void loadplayerdata(string name) // gets the data of the current player
{
    for (int i = 0; i < counter - 1; i++)
    {
        if (playersdata[i][0] == name)
        {
            foundplayer = true;
            playercount = i;
            playername1 = name;
            level1complete = converttobool(playersdata[i][1]);
            level2complete = converttobool(playersdata[i][2]);
            level3complete = converttobool(playersdata[i][3]);
            multiplayer = converttobool(playersdata[i][4]);
            break;
        }
    }
}

bool converttobool(string value) // converts string to bool
{
    if (value == "0")
    {
        return false;
    }
    else if (value == "1")
    {
        return true;
    }
}

int option(int optcount, int x, int y) // takes in user input of option
{
    bool found = false;
    string opt;
    gotoxy(x, y);
    cout << "\33[32m"
         << "Enter your choice: ";
    getline(cin, opt);
    while (!found)
    {
        if (intvalid(opt) && opt != "\0")
        {
            if (stoi(opt) > 0 && stoi(opt) <= optcount)
            {
                found = true;
                break;
            }
        }
        y++;
        gotoxy(x, y);
        cout << "\33[31m"
             << "Invalid input! Try again: ";
        getline(cin, opt);
    }
    return stoi(opt);
}

bool intvalid(string num) // validation of user input of option
{
    string digits = "0123456789";
    for (int i = 0; i < num.length(); i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (digits[j] == num[i])
            {
                break;
            }
            else if (j == 9)
            {
                return false;
            }
        }
    }
    return true;
}

void header() // header of game on main starting screen
{
    system("cls");
    gotoxy(40, 10);
    cout << "\33[33m"
         << " __________                     __      __                 __                                  " << endl;
    gotoxy(40, 11);
    cout << "\33[33m"
         << "|   _______|                   |  \\    /  |               |  |                                " << endl;
    gotoxy(40, 12);
    cout << "\33[33m"
         << "|  |   ____ __    __ __ ____   |   \\__/   | ___ _ __    __|  |____  ______ __ ____   ____     " << endl;
    gotoxy(40, 13);
    cout << "\33[33m"
         << "|  |  |__  |  |  |  |  '__  \\  |    __    |/ __` |  |  |  |   __  `| O ___|  '__  \\/__   |   " << endl;
    gotoxy(40, 14);
    cout << "\33[33m"
         << "|  \\____/  |  |__|  |  |  |  | |  |    |  | (__| |  |__|  |  |  |  |  |__ |  |  |  |  |  |    " << endl;
    gotoxy(40, 15);
    cout << "\33[33m"
         << " \\_________/\\______/|__|  |__| |__|    |__|\\___,_|\\___/  /|__|  |__|______|__|  |__|  |__| " << endl;
    gotoxy(40, 16);
    cout << "\33[33m"
         << "                                                     /  /                                      " << endl;
    gotoxy(40, 17);
    cout << "\33[33m"
         << "                                                    /__/                                       " << endl;
}
