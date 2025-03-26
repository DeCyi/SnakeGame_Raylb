
#include "raylib.h"
#include <string>
#include <iostream>
#include <stdint.h>
#define MAX_SNAKE_LENGTH 100
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define SQUARE_SIZE 30
#define DEFAULT_SNAKE_INIT_LENGTH 3


enum Speed {
	SLOW = 8,
	MEDIUM = 6,
	FAST = 3,
};

struct Snake {
    Vector2 position;
    Vector2 speed;
    Vector2 size;
    Color color;
};

struct Apple {
    Vector2 position;
    Vector2 size;
    Color color;
};

Speed speed = SLOW;
int state = 1;
int frameCounter = 0;
int gameState = 0;
int score = 0;
int high_score = 0;
Vector2 offset = { 0 };
Vector2 previousPosition = { 0 };
Snake snake[MAX_SNAKE_LENGTH] = { 0 };
Apple apple = { 0 };
int snakeLength;

static void InitGame(void);
static void UpdateGame(void);
static void CollisionLogic(void);
static void CollisionApple(void);
static void DrawElements(void);
static void RandomApple(void);
static void MainMenu(void);
static void GameStatus(void);
static void GameOver(void);

int main(void)
{    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake");
	InitAudioDevice();
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    // Initialize game variables

    Music music = LoadMusicStream("SnakeMusic.mp3");
	PlayMusicStream(music);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        switch (state) {
            case 1:
                MainMenu();
                break;
            case 2:
            UpdateMusicStream(music);
            UpdateGame();
            DrawElements();
            break;
            case 3:
            GameOver();
            break;

         
        }
    }
	UnloadMusicStream(music);
	CloseAudioDevice();
    CloseWindow();       

    return 0;
}

void InitGame() {
    snakeLength = DEFAULT_SNAKE_INIT_LENGTH;
   

    float centerX = ((SCREEN_WIDTH / 2) / SQUARE_SIZE) * SQUARE_SIZE;
    float centerY = ((SCREEN_HEIGHT / 2) / SQUARE_SIZE) * SQUARE_SIZE;

	//Initialize snake positions
    for (int i = 0; i < MAX_SNAKE_LENGTH; i++) {
        snake[i].position = { centerX - (i * (float)SQUARE_SIZE), centerY };
        snake[i].size = { (float)SQUARE_SIZE, (float)SQUARE_SIZE };
        snake[i].speed = { (float)SQUARE_SIZE, 0 };
        snake[i].color = GREEN;
    }
    snake[0].color = RED;

    //Render apple position
    RandomApple();
    apple.size = { (float)SQUARE_SIZE, (float)SQUARE_SIZE };
    apple.color = YELLOW;
}
void UpdateGame() {
    if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) && snake[0].speed.x != (float)SQUARE_SIZE)
    {
        snake[0].speed.x = (float)-SQUARE_SIZE; //If left key, move left (negative x)
        snake[0].speed.y = 0; //No y movement
    }
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) && snake[0].speed.y != (float)SQUARE_SIZE)
    {
        snake[0].speed.x = 0; //No x movement
        snake[0].speed.y = (float)-SQUARE_SIZE; //If up key, move up (negative y)
    }
    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) && snake[0].speed.y != (float)-SQUARE_SIZE)
    {
        snake[0].speed.x = 0; //No x movement
        snake[0].speed.y = (float)SQUARE_SIZE; //If down key, move down (positive y)
    }
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) && snake[0].speed.x != (float)-SQUARE_SIZE)
    {
        snake[0].speed.x = (float)SQUARE_SIZE; //If right key, move right (positive x)
        snake[0].speed.y = 0; //No y movement
    }

    // Makes sure that it remembers where the head is now
    Vector2 previousPosition = snake[0].position;

	if ((frameCounter % speed) == 0) { // Moves the snake every 5 frames
        // Moves the head in its current direction
        snake[0].position.x += snake[0].speed.x;
        snake[0].position.y += snake[0].speed.y;

        // Makes the body follow the head
        for (int i = 1; i < snakeLength; i++) {
            Vector2 temp = snake[i].position; // Saves the current body part's position
            snake[i].position = previousPosition; // Moves it to where the part in front was
            previousPosition = temp; // Update the previous position for the next part
        }
        CollisionLogic();
        CollisionApple();
    }
	frameCounter++;
	
}

void MainMenu(void) {
    BeginDrawing();
    ClearBackground(WHITE);
    Rectangle button = { 250, 200, 80, 40 };
    Color buttonColor = GREEN;

    Vector2 mouseLoc = GetMousePosition();
    bool isHover = CheckCollisionPointRec(mouseLoc, button);
    DrawRectangleRec(button, buttonColor);
    if (isHover) buttonColor = GRAY;
    
    else buttonColor = GREEN;
    
    if (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        TraceLog(LOG_INFO, "Button Clicked!");
        InitGame();
        state = 2;
    }
    DrawText("SNAKE GAME", 220, 100, 23, BLACK);
    DrawText("PLAY", 260, 210, 23, BLACK);
    EndDrawing();
   
}
void GameOver(void) {
    BeginDrawing();
    ClearBackground(WHITE);
    Rectangle button = { 350, 200, 100, 40 };
    Color buttonColor = GREEN;
    Rectangle button2 = { 350, 300, 100,40 };
    Vector2 mouseLoc = GetMousePosition();
    bool isHover = CheckCollisionPointRec(mouseLoc, button);
    bool isHover2 = CheckCollisionPointRec(mouseLoc, button2);
    DrawRectangleRec(button, buttonColor);
    DrawRectangleRec(button2, buttonColor);

    if(isHover){
    }
    if (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        TraceLog(LOG_INFO, "Button Clicked!");
        InitGame();
        state = 1;  

    }
    if (isHover2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        TraceLog(LOG_INFO, "Button Clicked!");
        InitGame();
        state = 2;
    }
    DrawText("GAME OVER", 100, 200, 36, BLACK);
    DrawText(TextFormat("Final Score: %d", score), 100, 250, 24, BLACK);
    DrawText(TextFormat("High Score: %d", high_score), 100, 280, 24, BLACK);
    DrawText("Main Menu", 360, 210, 18, BLACK);
    DrawText("Play Again", 360, 310, 18, BLACK);
    EndDrawing();
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
    DrawText(TextFormat("Score: %d", score), 50, 70, 32, BLACK);

    
    ClearBackground(SKYBLUE);
    EndDrawing();
}

void CollisionLogic(void) {
    // CASE Wall 
    if (snake[0].position.x >= SCREEN_WIDTH || snake[0].position.x < 0) {
        std::cout << "Game Over!" << std::endl;
        state = 3;
    }
    if (snake[0].position.y >= SCREEN_HEIGHT || snake[0].position.y < 0) {
        std::cout << "Game Over!" << std::endl;
        state = 3;
    }
    // CASE Self
    for (int i = 1; i < snakeLength; i++) {
        if ((snake[0].position.x == snake[i].position.x) && (snake[0].position.y == snake[i].position.y)) {
            std::cout << "Game Over!" << std::endl;
            //InitGame();
            state = 3;
        }
    }
}

void CollisionApple(void) {
	// If the head of the snake is in the same position as the apple
    if (snake[0].position.x == apple.position.x && snake[0].position.y == apple.position.y) {
        snake[snakeLength] = snake[snakeLength - 1];
        snakeLength++;
		std::cout << "Apple eaten!" << std::endl;
        score++;
		RandomApple();
    }
}

void RandomApple() {
	srand(time(NULL)); // Seed random number generator
	Vector2 previousApplePosition = apple.position;
    Vector2 newApplePosition;
    do {
        newApplePosition = { // Randomize apple position
            (float)((rand() % (SCREEN_WIDTH / SQUARE_SIZE)) * SQUARE_SIZE) ,
            (float)((rand() % (SCREEN_HEIGHT / SQUARE_SIZE)) * SQUARE_SIZE)
        };
        apple.position = { newApplePosition.x, newApplePosition.y };
	} while (previousApplePosition.x == newApplePosition.x && previousApplePosition.y == newApplePosition.y);
    std::cout << "Apple position: " << apple.position.x << " " << apple.position.y << std::endl;
}