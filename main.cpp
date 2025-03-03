
#include "raylib.h"
#include <string>
#include <iostream>
#define SNAKE_LEN 256
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------


static int screenwidth = 800;
static int screenheight = 500;

static int frameCounter = 0;
static bool isOver = false;

static int cellSize = 30;
static int cellcount = 25;



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

static Snake snake[SNAKE_LEN]{ 0 };
Vector2 offset = { 0 };

void InitGame() {

    //offset.x = screenwidth % cellSize;
    //offset.y = screenheight % cellSize;


    for (int i = 0; i < SNAKE_LEN; i++) {
        snake[i].position.x = { 0 };
        snake[i].position.y = { 0 };
        snake[i].size = { (float)cellSize, (float)cellSize };
        snake[i].speed = Vector2{ (float)1, 0 };
    }
    


}




int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------


    InitWindow(screenwidth, screenheight, "Snake");

    InitGame();

    SetTargetFPS(30);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);




        snake[0].position.x += snake[0].speed.x;
        snake[0].position.y += snake[0].speed.y;

        DrawRectangle(snake[0].position.x, snake[0].position.y, 30, 30, RED);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    
    CloseWindow();       

    return 0;
}
