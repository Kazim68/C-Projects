#include <iostream>
using namespace std;

bool is_space(string text)
{
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
        {
            return true;
        }
    }
    return false;
}

string spacecheck()
{
    string text;
    while (1)
    {
        cin.ignore();
        getline(cin, text);
        if (!is_space(text))
        {
            return text;
        }
        cout << "Invalid entry: ";
    }
    return text;
}

void print()
{
    cout << "hhhhhhhhhhhhhhhh" << endl;
    cout << "hhhhhhhhhhhhhhhh" << endl;
    cout << "hhhhhhhhhhhhhhhh" << endl;
    string name, password;
    cout << "Enter name: ";
    name = spacecheck();
    cout << "your name is: " << name << endl;
    cout << "enter password: ";
    password = spacecheck();
    cout << "your password is: " << password;
}

int input()
{
    int line;
    cout << "enter line: ";
    cin >> line;
    return line;
}

int main()
{
    int line = input();
    if (line)
    {
        print();
    }
}