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
// the fruit design in the game
vector<Point> snake;
Point food;
int score = 0;        // to read the control for input navigation
char direction = 'd'; // 'w' - up, 's' - down, 'a' - left, 'd' - right
bool gameOver = false;

void setup()
{
    snake = {{WIDTH / 2, HEIGHT / 2}};        // Initializes the snake's starting position
    food = {rand() % WIDTH, rand() % HEIGHT}; // Randomly places the food on the grid
    score = 0;                                // Initializes the player's score ianze zeroo
    direction = 'd';                          // Sets the initial movement direction of the snake
    gameOver = false;
}

void draw() //  Function to draw the game screen
{
    system("cls");
    for (int i = 0; i < WIDTH + 2; i++) // Draw the top border of the game screen
        cout << "#";
    cout << endl;

    //  Loop through each row (height of the game screen)
    for (int i = 0; i < HEIGHT; i++)
    { // Loop through each column (width of the game screen)
        for (int j = 0; j < WIDTH; j++)
        { // Print left border "#" at the start of each row
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
    // Draw the bottom border of the game screen
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;

    // Display the current score
    cout << "Score: " << score << endl;
}

void input() // Function to handle user input for controlling the snake's direction
{
    if (_kbhit()) // Check if a key has been pressed
    {
        char key = _getch(); // Read the pressed key without waiting for the Enter key

        // Update the direction based on the key pressed, ensuring the snake cannot reverse direction
        if ((key == 'w' && direction != 's') || // 'w' for moving up, not allowed if currently moving down ('s')
            (key == 's' && direction != 'w') || // 's' for moving down, not allowed if currently moving up ('w')
            (key == 'a' && direction != 'd') || // 'a' for moving left, not allowed if currently moving right ('d')
            (key == 'd' && direction != 'a'))   // 'd' for moving right, not allowed if currently moving left ('a')
        {
            direction = key; // Update the snake's direction
        }
    }
}

void logic()
{ // accepting input of navigation
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
        if (newHead.x == s.x && newHead.y == s.y) // the head of the snake
        {
            gameOver = true; // kuona gameover screen
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
        snake.pop_back(); //
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

    cout << "Game Over! Your score: " << score << endl; // show the game over score
    return 0;