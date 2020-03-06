#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

using namespace std;

enum eDir{STOP = 0, UP, DOWN, LEFT, RIGHT};
eDir dir;

const int width = 20, height = 20;
int x, y, foodX, foodY, nTail, score;
int tailX[55], tailY[55];
bool gameOver;


void setup();
void draw();
void input();
void logic();

int main()
{
    char choice;
    do{
         setup();
    while(!gameOver)
    {
         draw();
         input();
         logic();
         Sleep(180 - score/2);
    }
        cout << "Retry(y/n)?: ";
        choice = getch();

        }while(choice == 'y' || choice == 'Y');
}

void setup()
{
    gameOver = false;
    x = width/2;
    y = height/2;
    foodX = rand()% width;
    foodY = rand()% height;
    nTail = 0;
    dir = STOP;
    score = 0;

}

void draw()
{
    system("cls");
    for(int i = 0; i < width+2; ++i)
    {
        cout << "#";
    }
    cout << endl;

    for(int row = 0; row < height; ++row)
    {
        for(int col = 0; col < width; ++col)
        {
            if(col == 0)cout << "#";
            if(x == col && y == row)
            {
                cout << "O";
            }
            else if(foodX == col && foodY == row)
            {
                cout << "F";
            }
            else
            {
                bool print = false;
                for(int i = 0; i < nTail; ++i)
                {
                    if(tailX[i] == col && tailY[i] == row)
                    {
                        print = true;
                        cout << "o";
                    }
                }

                if(!print)
                cout << " ";
            }

            if(col == width-1)
            {
                cout << "#";
            }

        }
        cout << endl;
    }

    for(int i = 0; i < width+2; ++i)
    {
        cout << "#";
    }
    cout << endl;
    cout << "Score[" << score << "]" << endl;

}

void input()
{
    if(kbhit())
    {
        switch(getch())
        {
        case 'w':
            dir = UP;
            break;

        case 's':
            dir = DOWN;
            break;

        case 'a':
            dir = LEFT;
            break;

        case 'd':
            dir = RIGHT;
            break;
        }
    }

}

void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int tmpX, tmpY;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < nTail; ++i)
    {
        tmpX = prevX;
        tmpY = prevY;
        prevX = tailX[i];
        prevY = tailY[i];
        tailX[i] = tmpX;
        tailY[i] = tmpY;
    }

    switch(dir)
        {
        case UP:
            y--;
            break;

        case DOWN:
            y++;
            break;

        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;
        }

        if(x == foodX && y == foodY)
        {
            foodX = rand()% width;
            foodY = rand()% height;
            score += 10;
            nTail++;
        }

        if(x < 0 || x > width || y < 0 || y > height)
        {
            gameOver = true;
        }

        for(int i = 1; i < nTail; ++i)
        {
            if(tailX[i] == x && tailY[i] == y)
            {
                gameOver = true;
            }
        }

}
