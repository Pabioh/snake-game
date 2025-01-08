#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 20;  // for determining weidht
const int HEIGHT = 20; // for determining heght

struct Point
{
    int x, y;
};

vector<Point> snake;
Point food;
int score = 0;
char direction = 'd'; // 'w' - up, 's' - down, 'a' - left, 'd' - right
bool gameOver = false;

void setup()
{
    snake = {{WIDTH / 2, HEIGHT / 2}};        // Initializes the snake's starting position
    food = {rand() % WIDTH, rand() % HEIGHT}; // Randomly places the food on the grid
    score = 0;
    direction = 'd';
    gameOver = false;
}

void draw()
{
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (j == 0)
                cout << "#";

            bool printed = false;
            for (const auto &s : snake)
            {
                if (s.x == j && s.y == i)
                {
                    cout << "O";
                    printed = true;
                    break;
                }
            }
            if (food.x == j && food.y == i)
            {
                cout << "F";
                printed = true;
            }
            if (!printed)
                cout << " ";

            if (j == WIDTH - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void input()
{
    if (_kbhit())
    {
        char key = _getch();
        if ((key == 'w' && direction != 's') || (key == 's' && direction != 'w') ||
            (key == 'a' && direction != 'd') || (key == 'd' && direction != 'a'))
        {
            direction = key;
        }
    }
}

void logic()
{
    Point newHead = snake.front();
    if (direction == 'w')
        newHead.y--;
    if (direction == 's')
        newHead.y++;
    if (direction == 'a')
        newHead.x--;
    if (direction == 'd')
        newHead.x++;

    if (newHead.x < 0 || newHead.x >= WIDTH || newHead.y < 0 || newHead.y >= HEIGHT)
    {
        gameOver = true;
        return;
    }

    for (const auto &s : snake)
    {
        if (newHead.x == s.x && newHead.y == s.y)
        {
            gameOver = true;
            return;
        }
    }

    snake.insert(snake.begin(), newHead);

    if (newHead.x == food.x && newHead.y == food.y)
    {
        score += 10;
        food = {rand() % WIDTH, rand() % HEIGHT};
    }
    else
    {
        snake.pop_back();
    }
}

int main()
{
    srand(time(0));
    setup();

    while (!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(100);
    }

    cout << "Game Over! Your score: " << score << endl;
    return 0;