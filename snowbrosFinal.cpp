#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#include <stdlib.h>
using namespace std;
void boundry();
void gameOver();
void youWin();
void showOptions();

void gotoxy(int x, int y);

void player();
void enemy1();
void enemy2();
void enemy3();

char getCharAtXY(short int x, short int y);

void eraseShape(int x, int y, int W, int H);

void moveplayerleft();
void moveplayerright();

void createBullet(bool);
void printBullets();
void eraseBullets();
void moveBullet();
void fire1(int fire1X, int fire1Y);

void erasefire1(int fire1X, int fire1Y);

void movefire1();
bool checkfire1(int fire1X);

void fire2();
void erasefire2();
void movefire2();
bool checkfire2(int fire2X);

void enemy1Jump(int, int);
void move1enemy2(string direction);
string change1direction2(string direction);

void enemy1Jump2();
void move1enemy3(string direction);
string change1direction3(string direction);

void enemy2Jump();
void checkBulletCollision();
void removeBullet(int);

void killEnemy1();
void killEnemy2();
void killEnemy3();

int score(int fire1X, int fire2X, int e1X, int e2X, int e3X);
void lives();
void minusLife();

void reset(bool, bool, bool, bool, string, string, string, string, string);
void move1enemy(string direction);
void printScore();
string change1direction(string direction);

void move2enemy(string direction);
string change2direction(string direction);

void move3enemy(string direction);
string change3direction(string direction);

int pX = 27, pY = 15;
int e1X = 25, e1Y = 3;
int e2X = 16, e2Y = 8;
int e3X = 52, e3Y = 2;
int fire1X = pX - 1, fire1Y = pY;
int fire2X = pX + 6, fire2Y = pY;
int newFire1X, newFire2X;
int countEnemy1 = 0;
int countEnemy2 = 0;
int scoreInt = 0;
int life = 3;
int moveDir = 0;
int moveDirOne = 1;
int choice;
bool heartOfGame = false;

const int bulletCount = 100;
int currentBulletCount = 0;
int bulletX[bulletCount];
int bulletY[bulletCount];
bool isBulletActive[bulletCount];
bool isMovingLeft[bulletCount];

bool checkCollision(int x, int y, int W, int H, int bX, int bY);
bool checkCollisionForEnemy3WithPlayer(int x, int y, int W, int H, int bX, int bY, int bX2, int bX3, int bX4);

int invinciblityCounter = 0;
int fireRate = 0;
int jumpTimer = 0;
bool jumping = false;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
main()
{
    bool movefire1Left = false;
    bool movefire2Right = false;
    bool enemy1HasJumped = false;
    bool enemy2HasJumped = false;
    string enemy1direction = "right";
    string enemy1direction2 = "right";
    string enemy1direction3 = "right";
    string enemy2direction = "left";
    string enemy3direction = "down";
    while (true)
    {
        showOptions();
        if (choice == 1)
        {
            heartOfGame = true;
            break;
        }
        else if (choice == 2)
        {
            heartOfGame = false;
            system("cls");
            break;
        }
        else
        {
            SetConsoleTextAttribute(h, 4);
            cout << "Invalid input!!!";
            cout << "Press any key to continue!!!";
            getch();

            SetConsoleTextAttribute(h, 10);
            continue;
        }
    }
    if (heartOfGame)
    {

        system("color 0F");
        system("cls");
        boundry();
        player();
        enemy1();
        enemy2();
        enemy3();
    }

    while (heartOfGame)
    {

        if (life > 0)
        {

            minusLife();
            if (GetAsyncKeyState(VK_LEFT))
            {
                moveplayerleft();
            }
            if (GetAsyncKeyState(VK_RIGHT))
            {
                moveplayerright();
            }
            if (GetAsyncKeyState(VK_SPACE) && jumping == false)
            {
                jumping = true;
                jumpTimer = 0;
            }
            if (GetAsyncKeyState(VK_UP) && fireRate <= 0)
            {
                createBullet(true);
                fireRate = 5;
            }
            if (GetAsyncKeyState(VK_DOWN) && fireRate <= 0)
            {
                createBullet(false);
                fireRate = 5;
            }
            if (jumping)
            {
                if (getCharAtXY(pX, pY - 1) == ' ' && getCharAtXY(pX + 1, pY - 1) == ' ' && getCharAtXY(pX + 2, pY - 1) == ' ' && getCharAtXY(pX + 3, pY - 1) == ' ' && getCharAtXY(pX + 4, pY - 1) == ' ')
                {
                    if (jumpTimer < 10)
                    {
                        eraseShape(pX, pY, 6, 3);
                        pY--;
                        jumpTimer++;
                        player();
                    }
                    else
                    {
                        jumping = false;
                    }
                }
                else
                {
                    jumping = false;
                }
            }
            if (!jumping && pX > 20)
            {
                if (getCharAtXY(pX, pY + 3) == ' ')
                {
                    eraseShape(pX, pY, 6, 3);
                    pY++;
                    player();
                }
            }
            else if (!jumping && pX < 20)
            {
                if (getCharAtXY(pX + 5, pY + 3) == ' ')
                {
                    eraseShape(pX, pY, 6, 3);
                    pY++;
                    player();
                }
            }
            fireRate--;

            eraseBullets();
            checkBulletCollision();
            moveBullet();
            printBullets();

            if (scoreInt < 30)
                move1enemy(enemy1direction);
            enemy1direction = change1direction(enemy1direction);

            if (scoreInt < 60)
                move2enemy(enemy2direction);
            enemy2direction = change2direction(enemy2direction);

            if (scoreInt < 90)
                move3enemy(enemy3direction);
            enemy3direction = change3direction(enemy3direction);
            if (scoreInt >= 90)
            {
                system("cls");
                boundry();
                youWin();
                break;
            }

            if (countEnemy1 >= 3 && countEnemy1 < 7 && !enemy1HasJumped)
            {
                eraseShape(e1X, e1Y, 6, 3);
                enemy1Jump(20, 8);
                enemy1HasJumped = !enemy1HasJumped;
            }
            if (countEnemy1 >= 7 && enemy1HasJumped)
            {
                eraseShape(e1X, e1Y, 6, 3);
                enemy1Jump(3, 15);
                enemy1HasJumped = !enemy1HasJumped;
            }
            if (countEnemy2 >= 3 && !enemy2HasJumped)
            {
                eraseShape(e2X, e2Y, 6, 3);
                enemy2Jump();
                enemy2HasJumped = !enemy2HasJumped;
            }

            printScore();
            invinciblityCounter--;
            killEnemy1();
            killEnemy2();
            killEnemy3();
            player();
            Sleep(10);
        }

        if (life <= 0)
        {
            system("cls");
            boundry();
            gotoxy(5, 7);
            gameOver();
            char c = getch();
            while (c != 'r')
            {
                c = getch();
            }
            reset(movefire1Left, movefire2Right, enemy1HasJumped, enemy2HasJumped, enemy1direction, enemy1direction2, enemy1direction3, enemy2direction, enemy3direction);
            system("cls");
            boundry();
        }
    }
}

void printScore()
{
    gotoxy(3, 20);
    cout << "score=" << scoreInt;
    gotoxy(65, 20);
    cout << "Lives : ";
    for (int i = 0; i < 3; i++)
    {
        if (i < life)
            cout << "*";
        if (i >= life)
            cout << " ";
    }
}

// new function to check collision.
bool checkCollision(int x, int y, int W, int H, int bX, int bY)
{
    return bX <= (x + W) && bX >= x && bY >= y && bY <= y + H;
}

// new function to check collision of Enemy3WithPlayer.
bool checkCollisionForEnemy3WithPlayer(int x, int y, int W, int H, int bX, int bY, int bX2, int bX3, int bX4)
{
    return bX <= (x + W) && bX >= x && bX2 <= (x + W) && bX2 >= x && bX3 <= (x + W) && bX3 >= x && bX4 <= (x + W) && bX4 >= x && bY >= y && bY <= y + H;
}

// new function to check bullet collision.
void checkBulletCollision()
{
    for (int i = 0; i < currentBulletCount; i++)
    {
        if (checkCollision(e1X, e1Y, 6, 3, bulletX[i], bulletY[i]))
        {
            removeBullet(i);
            scoreInt += 1;
        }
        if (checkCollision(e2X, e2Y, 6, 3, bulletX[i], bulletY[i]))
        {
            removeBullet(i);
            scoreInt += 1;
        }
        if (checkCollision(e3X, e3Y, 5, 2, bulletX[i], bulletY[i]))
        {
            removeBullet(i);
            scoreInt += 1;
        }
    }
}

// new function to create bullet.
void createBullet(bool left)
{
    if (currentBulletCount < bulletCount)
    {
        bulletX[currentBulletCount] = (left) ? pX - 1 : pX + 6;
        bulletY[currentBulletCount] = pY;
        isBulletActive[currentBulletCount] = true;
        isMovingLeft[currentBulletCount] = left;
        currentBulletCount++;
    }
}

// new function to print bullet.
void printBullets()
{
    for (int i = 0; i < currentBulletCount; i++)
    {
        gotoxy(bulletX[i], bulletY[i]);
        string s = (isMovingLeft[i] == true) ? "<" : ">";
        cout << s;
    }
}

// new function to erase bullet.
void eraseBullets()
{
    for (int i = 0; i < currentBulletCount; i++)
    {
        gotoxy(bulletX[i], bulletY[i]);
        cout << " ";
    }
}

// new function to remove bullet.
void removeBullet(int i)
{
    for (int j = i; j < currentBulletCount - 1; j++)
    {
        bulletX[j] = bulletX[j + 1];
        bulletY[j] = bulletY[j + 1];
        isBulletActive[j] = isBulletActive[j + 1];
        isMovingLeft[j] = isMovingLeft[j + 1];
        currentBulletCount--;
    }
}

// new function to move bullets.
void moveBullet()
{
    for (int i = 0; i < currentBulletCount; i++)
    {
        if (isBulletActive[i] == true)
        {
            bool hasMoved = false;
            if (isMovingLeft[i] == true)
            {
                char c = getCharAtXY(bulletX[i] - 1, bulletY[i]);
                if (c == ' ')
                {
                    bulletX[i]--;
                    hasMoved = true;
                }
            }
            else
            {
                char c = getCharAtXY(bulletX[i] + 1, bulletY[i]);
                if (c == ' ')
                {
                    bulletX[i]++;
                    hasMoved = true;
                }
            }
            if (!hasMoved)
            {
                removeBullet(i);
            }
        }
    }
}

// new function for reset all values when game restart.
void reset(bool movefire1Left, bool movefire2Right, bool enemy1HasJumped, bool enemy2HasJumped, string enemy1direction,
           string enemy1direction2, string enemy1direction3, string enemy2direction, string enemy3direction)
{
    pX = 27, pY = 15;
    e1X = 25, e1Y = 3;
    e2X = 16, e2Y = 8;
    e3X = 52, e3Y = 2;
    fire1X = pX - 1, fire1Y = pY;
    fire2X = pX + 6, fire2Y = pY;
    newFire1X, newFire2X;
    countEnemy1 = 0;
    countEnemy2 = 0;
    scoreInt = 0;
    life = 3;
    moveDir = 0;
    moveDirOne = 1;
    movefire1Left = false;
    movefire2Right = false;
    enemy1HasJumped = false;
    enemy2HasJumped = false;
    enemy1direction = "right";
    enemy1direction2 = "right";
    enemy1direction3 = "right";
    enemy2direction = "left";
    enemy3direction = "down";
}
char getCharAtXY(short int x, short int y)
{
    CHAR_INFO ci;
    COORD xy = {0, 0};
    SMALL_RECT rect = {x, y, x, y};
    COORD coordBufSize;
    coordBufSize.X = 1;
    coordBufSize.Y = 1;
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar : ' ';
}
void boundry()
{
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "@|----------------------------------------------------------------------------|@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|               ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|~~~~~~~~~~~~~~~~~~~~~~~~~                                                   |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|                                                                            |@" << endl;
    cout << "@|----------------------------------------------------------------------------|@" << endl;
    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
    cout << "|                                                                              |" << endl;
    cout << "|------------------------------------------------------------------------------|" << endl;
}
void showOptions()
{
    SetConsoleTextAttribute(h, 10);
    system("cls");
    gotoxy(4, 5);
    cout << "#############################" << endl;
    gotoxy(4, 6);

    cout << "        GAME OPTIONS         " << endl;
    gotoxy(4, 7);

    cout << "#############################" << endl;
    SetConsoleTextAttribute(h, 9);
    gotoxy(4, 8);

    cout << "1. Play Game" << endl;
    gotoxy(4, 9);

    cout << "2. Exit Game" << endl;
    gotoxy(4, 10);

    cout << "#############################" << endl;

    gotoxy(4, 11);

    cout << "Enter your choice (1-2): ";
    cin >> choice;
}

void gameOver()
{
    SetConsoleTextAttribute(h, 4);
    gotoxy(5, 7);
    cout << " gggggg   aa aa mm mm mmmm    eee      oooo  vv   vv   eee  rr rr " << endl;
    gotoxy(5, 8);
    cout << "gg   gg  aa aaa mmm  mm  mm ee   e    oo  oo  vv vv  ee   e rrr  r" << endl;
    gotoxy(5, 9);

    cout << "ggggggg aa  aaa mmm  mm  mm eeeee     oo  oo   vvv   eeeee  rr    " << endl;
    gotoxy(5, 10);

    cout << "     gg  aaa aa mmm  mm  mm  eeeee     oooo     v     eeeee rr    " << endl;
    gotoxy(5, 11);

    cout << "  ggggg                                                            " << endl;
    SetConsoleTextAttribute(h, 9);
    gotoxy(10, 16);
    cout << "Press 'r' key to restart";
    SetConsoleTextAttribute(h, 7);
}
void youWin()
{
    SetConsoleTextAttribute(h, 6);
    gotoxy(5, 7);
    cout << "db    db  .d88b.  db    db      db   d8b   db d888888b d8b   db" << endl;
    gotoxy(5, 8);
    cout << "`8b  d8' .8P  Y8. 88    88      88   I8I   88   `88'   888o  88" << endl;
    gotoxy(5, 9);
    cout << " `8bd8'  88    88 88    88      88   I8I   88    88    88V8o 88" << endl;
    gotoxy(5, 10);
    cout << "   88    88    88 88    88      Y8   I8I   88    88    88 V8o88" << endl;
    gotoxy(5, 11);
    cout << "   88    `8b  d8' 88b  d88      `8b d8'8b d8'   .88.   88  V888" << endl;
    gotoxy(5, 12);
    cout << "   YP     `Y88P'  ~Y8888P'       `8b8' `8d8'  Y888888P VP   V8P" << endl;
    gotoxy(5,30);
}

void player()
{
    SetConsoleTextAttribute(h, 1);
    gotoxy(pX, pY);
    cout << " /---\\" << endl;
    gotoxy(pX, pY + 1);
    cout << " \\---/" << endl;
    gotoxy(pX, pY + 2);
    cout << " _|^|_" << endl;
    SetConsoleTextAttribute(h, 15);
}

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;

    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
    return;
}
void enemy1()
{
    gotoxy(e1X, e1Y);
    cout << " (-)" << endl;
    gotoxy(e1X, e1Y + 1);
    cout << "/---\\" << endl;
    gotoxy(e1X, e1Y + 2);
    cout << "|'''|" << endl;
}

void enemy2()
{
    gotoxy(e2X, e2Y);
    cout << " (_)" << endl;
    gotoxy(e2X, e2Y + 1);
    cout << "/---\\" << endl;
    gotoxy(e2X, e2Y + 2);
    cout << "|'''|" << endl;
}

void moveplayerleft()
{
    if ((getCharAtXY(pX - 1, pY) == ' ') && (getCharAtXY(pX - 1, pY + 1) == ' ') && (getCharAtXY(pX - 1, pY + 2) == ' '))
    {
        eraseShape(pX, pY, 6, 3);
        pX = pX - 1;
        player();
    }
}
void moveplayerright()
{
    if ((getCharAtXY(pX + 7, pY) == ' ') && (getCharAtXY(pX + 7, pY + 1) == ' ') && (getCharAtXY(pX + 7, pY + 2) == ' '))
    {
        eraseShape(pX, pY, 6, 3);
        pX = pX + 1;
        player();
    }
}
void eraseShape(int x, int y, int W, int H)
{
    while (H > 0)
    {
        gotoxy(x, y + H - 1);
        for (int i = 0; i < W; i++)
            cout << " ";
        H--;
    }
}

void enemy3()
{
    gotoxy(e3X, e3Y);
    cout << "{*=*}";
}
string change1direction(string direction)
{
    if (direction == "right" && (getCharAtXY(e1X + 6, e1Y + 3) == ' ' || getCharAtXY(e1X + 6, e1Y + 3) == '|'))
    {
        direction = "left";
        countEnemy1++;
    }
    if (direction == "left" && (getCharAtXY(e1X - 2, e1Y + 3) == ' ' || getCharAtXY(e1X - 1, e1Y + 3) == '|'))
    {
        direction = "right";
    }
    return direction;
}
void move1enemy(string direction)
{
    eraseShape(e1X, e1Y, 6, 3);
    e1X = (direction == "right") ? e1X + 1 : e1X - 1;
    enemy1();
}
string change2direction(string direction)
{

    if (direction == "right" && getCharAtXY(e2X + 6, e2Y + 3) == ' ' || getCharAtXY(e2X + 6, e2Y + 3) == '|')
    {
        direction = "left";
        countEnemy2++;
    }
    if (direction == "left" && getCharAtXY(e2X - 1, e2Y) == '|')
    {
        direction = "right";
    }
    return direction;
}
void move2enemy(string direction)
{

    eraseShape(e2X, e2Y, 6, 3);
    if (direction == "right")
    {
        e2X = e2X + 1;
    }
    if (direction == "left")
    {
        e2X = e2X - 1;
    }
    enemy2();
}
string change3direction(string direction)
{

    if (direction == "down" && e3Y >= 17)
    {
        direction = "up";
    }
    if (direction == "up" && e3Y <= 2)
    {
        direction = "down";
    }
    return direction;
}
void move3enemy(string direction)
{

    eraseShape(e3X, e3Y, 5, 1);
    if (direction == "down")
    {
        e3Y = e3Y + 1;
        e3X = 62;
    }
    if (direction == "up")
    {
        e3Y = e3Y - 1;
        e3X = 62;
    }
    enemy3();
}
void fire1(int fire1X, int fire1Y)
{

    gotoxy(fire1X, fire1Y);
    cout << "<";
}
void erasefire1(int fire1X, int fire1Y)
{
    gotoxy(fire1X, fire1Y);
    cout << " ";
}

void movefire1()
{
    for (int i = 3; i < 80; i++)
    {
        for (int j = 0; j < 30; j++)
        {

            if (getCharAtXY(i, j) == '<')
            {
                fire1X = i;
                fire1Y = j;
                erasefire1(fire1X, fire1Y);

                newFire1X = i - 1;

                fire1(newFire1X, fire1Y);
                if (checkfire1(newFire1X))
                {
                    erasefire1(newFire1X, fire1Y);
                }
            }
        }
    }
}
bool checkfire1(int newFire1X)
{
    if (getCharAtXY(newFire1X - 1, fire1Y) == ' ')
    {
        return false;
    }
    else
    {
        return true;
    }
}
void fire2()
{

    gotoxy(fire2X, fire2Y);
    cout << ">";
}
void erasefire2()
{
    gotoxy(fire2X, fire2Y);
    cout << " ";
}
void movefire2()
{
    for (int i = 80; i > 3; i--)
    {
        for (int j = 0; j < 30; j++)
        {

            if (getCharAtXY(i, j) == '>')
            {
                fire2X = i;
                fire2Y = j;

                erasefire2();

                fire2X = i + 1;
                fire2Y = j;

                fire2();

                if (checkfire2(fire2X))
                {
                    erasefire2();
                }
            }
        }
    }
}
bool checkfire2(int fire2X)
{
    if (getCharAtXY(fire2X + 1, fire2Y) == ' ')
    {
        return false;
    }
    else
    {
        return true;
    }
}
void enemy1Jump(int x, int y)
{
    e1X = x;
    e1Y = y;
    enemy1();
}
void move1enemy2(string direction)
{
    eraseShape(e1X, e1Y, 6, 3);
    if (direction == "right")
    {
        e1X = e1X + 1;
    }
    if (direction == "left")
    {
        e1X = e1X - 1;
    }
    enemy1();
}
string change1direction2(string direction)
{

    if (direction == "left" && e1X == 4)
    {
        direction = "right";
        countEnemy1++;
    }
    if (direction == "right" && e1X == 22)
    {
        direction = "left";
    }

    return direction;
}
void enemy1Jump2()
{
    e1X = 3;
    e1Y = 15;
    enemy1();
}
void move1enemy3(string direction)
{
    if (e1X < 72 && direction == "right")
    {
        e1X = e1X + 1;
    }
    if (e1X > 1 && direction == "left")
    {
        e1X = e1X - 1;
    }
}
string change1direction3(string direction)
{
    if (e1X == 71 && direction == "right")
    {
        direction == "left";
    }
    if (e1X == 2 && direction == "left")
    {
        direction == "right";
    }
    return direction;
}
void enemy2Jump()
{
    e2X = 3;
    e2Y = 15;
    enemy2();
}
int score(int fire1X, int fire2X, int e1X, int e2X, int e3X)
{
    if (getCharAtXY(newFire1X - 1, fire1Y) == ' ' || (getCharAtXY(newFire2X + 1, fire2Y) == ' '))
    {
        scoreInt += 0;
    }
    if (getCharAtXY(newFire1X - 1, fire1Y) == ')')
    {
        scoreInt += 10;
    }
    if (getCharAtXY(newFire2X + 2, fire2Y) == '(')
    {
        scoreInt += 10;
    }

    return scoreInt;
}

void minusLife()
{
    if (invinciblityCounter > 0)
        return;
    if (checkCollision(pX, pY, 6, 3, e1X, e1Y))
    {
        life--;
        invinciblityCounter = 10;
    }
    if (checkCollision(pX, pY, 6, 3, e2X, e2Y))
    {
        life--;
        invinciblityCounter = 10;
    }
    if (checkCollisionForEnemy3WithPlayer(pX, pY, 5, 1, e3X, e3Y, e3X + 1, e3X + 2, e3X + 3))
    {
        life--;
        invinciblityCounter = 10;
    }
}
void killEnemy1()
{
    if (scoreInt >= 30)
    {
        if (e1Y < 30)
        {
            eraseShape(e1X, e1Y, 6, 3);
            e1X = 2;
            e1Y = 30;
        }
    }
}
void killEnemy2()
{
    if (scoreInt == 60)
    {
        if (e2Y < 30)
        {
            eraseShape(e2X, e2Y, 6, 3);
            e2X = 2;
            e2Y = 30;
        }
    }
}
void killEnemy3()
{
    if (scoreInt == 90)
    {
        if (e3Y < 30)
        {
            eraseShape(e3X, e3Y, 5, 1);
            e3X = 2;
            e3Y = 30;
        }
    }
}