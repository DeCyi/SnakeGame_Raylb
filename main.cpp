
#include "raylib.h"
#include <string>
#include <iostream>
#include <math.h>
#define SNAKE_LEN 256
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

const int snakeMax = 100; //Max snake length
int squareSize = 32; //Size of each square

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

Vector2 offset = { 0 }; //Offset for the grid

Snake snake[snakeMax] = { 0 }; //An array of body parts of snakes
Apple apple = { 0 }; // Apple object

int snakeLength = 2; //Initial snake length
Vector2 snakePosition[snakeMax] = { 0 }; //Array of each body part position

static void UpdateGame(void);
static void DrawBackground(void);
int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------


    InitWindow(screenwidth, screenheight, "Snake");

    SetTargetFPS(10);               
    //--------------------------------------------------------------------------------------

    float centerX = ((screenwidth / 2) / squareSize) * squareSize;
    float centerY = ((screenheight / 2) / squareSize) * squareSize;
    for (int i = 0; i < snakeLength; i++) {
        snake[i].position = { centerX - (i * (float)squareSize), centerY }; 
        snake[i].size = { (float)squareSize, (float)squareSize }; 
        snake[i].speed = { (float)squareSize, 1 };
        snake[i].color = GREEN; 
    }
    snake[0].color = RED;

    //Render apple position
    

    apple.position = { (float)5 * squareSize, (float)6 * squareSize }; //Random x and y for now
	apple.size = { (float)squareSize, (float)squareSize }; // Size of the apple
    apple.color = YELLOW; 

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        DrawBackground();
        UpdateGame();
        //----------------------------------------------------------------------------------
    }

    
    CloseWindow();       

    return 0;
}


void MainGame(void) {
    // For our main game function to be updated

}
void UpdateGame() {

    if (IsKeyPressed(KEY_LEFT))
    {
		snake[0].speed.x = (float)-squareSize; //If left key, move left (negative x)
		snake[0].speed.y = 0; //No y movement
    }
    if (IsKeyPressed(KEY_UP))
    {
		snake[0].speed.x = 0; //No x movement
		snake[0].speed.y = (float)-squareSize; //If up key, move up (negative y)
    }
    if (IsKeyPressed(KEY_DOWN))
    {
		snake[0].speed.x = 0; //No x movement
		snake[0].speed.y = (float)squareSize; //If down key, move down (positive y)
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
		snake[0].speed.x = (float)squareSize; //If right key, move right (positive x)
		snake[0].speed.y = 0; //No y movement
    }

    if (IsKeyDown(KEY_SPACE)) {
		snakeLength++; //Increase snake length

		//Set the new body part to the position of the previous body part
		snake[snakeLength - 1].position = snake[snakeLength - 2].position;
		snake[snakeLength - 1].size = snake[snakeLength - 2].size;
		snake[snakeLength - 1].speed = snake[snakeLength - 2].speed;
		snake[snakeLength - 1].color = snake[snakeLength - 2].color;
    }


    for (int i = 0; i < snakeLength; i++) {
		snakePosition[i] = snake[i].position; //Store the position of each body part
		if (i == 0) { //If it's the head
			snake[0].position.x += snake[0].speed.x; //Move the head in the x direction
			snake[0].position.y += snake[0].speed.y; //Move the head in the y direction
        }
        else {
			snake[i].position = snakePosition[i - 1]; //Set the body part to the position of the previous body part
        }
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

    for (int i = 0; i < snakeLength; i++) {

       
        DrawRectangle(snake[i].position.x, snake[i].position.y,
            snake[i].size.x, snake[i].size.y, snake[i].color);
    }
    ClearBackground(SKYBLUE);
    EndDrawing();
}