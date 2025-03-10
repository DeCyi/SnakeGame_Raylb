
#include "raylib.h"
#include <string>
#include <iostream>
#define SNAKE_LEN 256
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int snakeMax = 100;
int squareSize = 32;

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


// Global variables subject to modifications
static int screenwidth = 800;
static int screenheight = 450;

static int frameCounter = 0;
static bool isOver = false;
int cTail = 0;
Vector2 offset = { 0 };


Snake snake[100] = { 0 };
Apple apple = { 0 };
int snakeLegnth = 3;




static void UpdateGame(void);
static void DrawBackground(void);
int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------


    InitWindow(screenwidth, screenheight, "Snake");

    SetTargetFPS(30);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    float centerX = ((screenwidth / 2) / squareSize) * squareSize;
    float centerY = ((screenheight / 2) / squareSize) * squareSize;
    for (int i = 0; i < snakeLegnth; i++) {
        snake[i].position = { centerX - (i * (float)squareSize), centerY }; 
        snake[i].size = { (float)squareSize, (float)squareSize }; 
        snake[i].speed = { (float)squareSize, 0 };
        snake[i].color = GREEN; 
    }
    snake[0].color = RED;

    //Render apple position
    apple.position = { (float)5 * squareSize, (float)6 * squareSize }; //Random x and y for now
    apple.size = { (float)squareSize, (float)squareSize };
    apple.color = YELLOW;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        DrawBackground();
        DrawRectangle(apple.position.x, apple.position.y, apple.size.x, apple.size.y, apple.color);
        UpdateGame();
        //----------------------------------------------------------------------------------
    }

    
    CloseWindow();       

    return 0;
}


void MainGame(void) {
    // For our main game function to be updated
    frameCounter = 0;

}
void UpdateGame() {
  
    for (int i = 0; i < snakeMax; i++) {
        snake[i].position.x += 0.5f + snake[i].speed.x;
    }


}

void DrawBackground(void) {
    BeginDrawing(); 

    for (int i = 0; i < screenwidth / squareSize + 1; i++) {
        Vector2 start = { squareSize * i + offset.x / 2.0f, offset.y / 2.0f };
        Vector2 end = { squareSize * i + offset.x / 2.0f, screenheight - offset.y / 2.0f };
        DrawLineV(start, end, LIGHTGRAY);
    }
    for (int i = 0; i < screenheight / squareSize + 1; i++) {
        Vector2 start = {offset.x / 2.0f, squareSize * i + offset.y};
        Vector2 end = { screenwidth - offset.x / 2.0f, squareSize * i + offset.y / 2.0};
        DrawLineV(start, end, LIGHTGRAY);
    }

    for (int i = 0; i < snakeLegnth; i++) {
        DrawRectangle(snake[i].position.x, snake[i].position.y,
            snake[i].size.x, snake[i].size.y, snake[i].color);
    }
    ClearBackground(SKYBLUE);
    EndDrawing();
}