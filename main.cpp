
#include "raylib.h"
#include <string>
#include <iostream>
#define MAX_SNAKE_LENGTH 100
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define SQUARE_SIZE 32
#define DEFAULT_SNAKE_INIT_LENGTH 2

struct Snake {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Color color;
};

struct Apple {
    Vector2 position;
    Vector2 size;
    bool isActive; 
    Color color;
};

int frameCounter = 0;
Vector2 offset = { 0 };
Vector2 previousPosition = { 0 };
Snake snake[MAX_SNAKE_LENGTH] = { 0 };
Apple apple = { 0 };
int snakeLength = DEFAULT_SNAKE_INIT_LENGTH;

static void InitGame(void);
static void UpdateGame(void);
static void CollisionWall(void);
static void CollisionSelf(void);
static void CollisionApple(void);
static void DrawElements(void);

int main(void)
{    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    InitGame(); // Initialize game variables

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateGame();
        DrawElements();
    }
    CloseWindow();       

    return 0;
}

void InitGame() {
    float centerX = ((SCREEN_WIDTH / 2) / SQUARE_SIZE) * SQUARE_SIZE;
    float centerY = ((SCREEN_HEIGHT / 2) / SQUARE_SIZE) * SQUARE_SIZE;

    for (int i = 0; i < MAX_SNAKE_LENGTH; i++) {
        snake[i].position = { centerX - (i * (float)SQUARE_SIZE), centerY };
        snake[i].size = { (float)SQUARE_SIZE, (float)SQUARE_SIZE };
        snake[i].speed = { (float)SQUARE_SIZE, 0 };
        snake[i].color = GREEN;
    }
    snake[0].color = RED;

    //Render apple position
    apple.position = { (float)5 * SQUARE_SIZE, (float)6 * SQUARE_SIZE }; //Random x and y for now
    apple.size = { (float)SQUARE_SIZE, (float)SQUARE_SIZE };
    apple.color = YELLOW;
}
void UpdateGame() {
    if (IsKeyPressed(KEY_LEFT) && snake[0].speed.x != (float)SQUARE_SIZE)
    {
        snake[0].speed.x = (float)-SQUARE_SIZE; //If left key, move left (negative x)
        snake[0].speed.y = 0; //No y movement
    }
    if (IsKeyPressed(KEY_UP) && snake[0].speed.y != (float)SQUARE_SIZE)
    {
        snake[0].speed.x = 0; //No x movement
        snake[0].speed.y = (float)-SQUARE_SIZE; //If up key, move up (negative y)
    }
    if (IsKeyPressed(KEY_DOWN) && snake[0].speed.y != (float)-SQUARE_SIZE)
    {
        snake[0].speed.x = 0; //No x movement
        snake[0].speed.y = (float)SQUARE_SIZE; //If down key, move down (positive y)
    }
    if (IsKeyPressed(KEY_RIGHT) && snake[0].speed.x != (float)-SQUARE_SIZE)
    {
        snake[0].speed.x = (float)SQUARE_SIZE; //If right key, move right (positive x)
        snake[0].speed.y = 0; //No y movement
    }

    // Makes sure that it remembers where the head is now
    Vector2 previousPosition = snake[0].position;

	if ((frameCounter % 5) == 0) { // Moves the snake every 5 frames
        // Moves the head in its current direction
        snake[0].position.x += snake[0].speed.x;
        snake[0].position.y += snake[0].speed.y;

        // Makes the body follow the head
        for (int i = 1; i < snakeLength; i++) {
            Vector2 temp = snake[i].position; // Saves the current body part's position
            snake[i].position = previousPosition; // Moves it to where the part in front was
            previousPosition = temp; // Update the previous position for the next part
        }
        CollisionWall();
        CollisionSelf();
        CollisionApple();
    }
	frameCounter++;
	
}

void DrawElements(void) {
    BeginDrawing(); 

    for (int i = 0; i < SCREEN_WIDTH / SQUARE_SIZE + 1; i++) {
        Vector2 start = { SQUARE_SIZE * i + offset.x / 2.0f, offset.y / 2.0f };
        Vector2 end = { SQUARE_SIZE * i + offset.x / 2.0f, SCREEN_HEIGHT - offset.y / 2.0f };
        DrawLineV(start, end, LIGHTGRAY);
    }
    for (int i = 0; i < SCREEN_HEIGHT / SQUARE_SIZE + 1; i++) {
        Vector2 start = {offset.x / 2.0f, SQUARE_SIZE * i + offset.y};
        Vector2 end = { SCREEN_WIDTH - offset.x / 2.0f, SQUARE_SIZE * i + offset.y / 2.0};
        DrawLineV(start, end, LIGHTGRAY);
    }
    for (int i = 0; i < snakeLength; i++) {
        DrawRectangle(snake[i].position.x, snake[i].position.y,
            snake[i].size.x, snake[i].size.y, snake[i].color);
    }
    DrawRectangle(apple.position.x, apple.position.y, apple.size.x, apple.size.y, apple.color);

    
    ClearBackground(SKYBLUE);
    EndDrawing();
}
void CollisionWall(void) {
    if (snake[0].position.x >= SCREEN_WIDTH || snake[0].position.x < 0) {
        std::cout << "Game Over!" << std::endl;
		exit(0);
    }
    if (snake[0].position.y >= SCREEN_HEIGHT || snake[0].position.y < 0) {
        std::cout << "Game Over!" << std::endl;
        exit(0);
    }
}
void CollisionSelf(void) {
        for (int i = 1; i < snakeLength; i++) {
            if ((snake[0].position.x == snake[i].position.x) && (snake[0].position.y == snake[i].position.y)) {
                std::cout << "Game Over!" << std::endl;
                exit(0);
            }
        }
    }

void CollisionApple(void) {
    if (snake[0].position.x == apple.position.x && snake[0].position.y == apple.position.y) {
        snake[snakeLength].position = snake[snakeLength - 1].position;
        snake[snakeLength].size = snake[snakeLength - 1].size;
        snake[snakeLength].speed = snake[snakeLength - 1].speed;
        snake[snakeLength].color = snake[snakeLength - 1].color;
        snakeLength++;
		std::cout << "Apple eaten!" << std::endl;
    }
    
}