#include <iostream>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y);
void map3();
void boundary();
void firstrow(int x, int y);
void innerrows(int x, int y);
void platform(int x, int y, int size);

int main()
{
    system("cls");
    boundary();
    map3();
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
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

void map3()
{
    platform(50, 23, 60);
    platform(37, 27, 15);
    platform(108, 27, 15);
    platform(24, 31, 15);
    platform(121, 31, 15);
    platform(37, 35, 15);
    platform(108, 35, 15);
    platform(50, 39, 60);
}