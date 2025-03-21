
#include "raylib.h"
#include <string>
#include <iostream>
#include <math.h>
#include <ctime>
#define SNAKE_LEN 256
#define cellSize 30

using namespace std;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

// Global variables subject to modifications


static int screenwidth = 800;
static int screenheight = 500;


static int cellX = screenwidth / cellSize;
static int cellY = screenheight / cellSize;



static int frameCounter = 0;
static bool isOver = false;



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


// random apple
//Create Food Struct:
//Create Food Class
//Initialize Random Seed:
//Create and Draw Food in Main Loop :
class Foods {

private:

    Vector2 xy;

public:

    int x, y;

    // random x and y
    void Food() {

        x = GetRandomValue(0, 30);
        y = GetRandomValue(0, 30);
    }


    srand((unsigned int)time (NULL));

    int centerX = ((screenwidth / 2) / squareSize) * squareSize;
    int centerY = ((screenheight / 2) / squareSize) * squareSize;

    for (int i = 0; i < snakeLength; i++) {
        snake[i].position = { (float)centerX - (i * (float)squareSize), (float)centerY }; 
        snake[i].size = { (float)squareSize, (float)squareSize }; 
        snake[i].speed = { (float)squareSize, 1 };
        snake[i].color = GREEN; 
    }
    snake[0].color = RED;

    // image of the food (apple)


    apple.position = {
        (float)((rand() % (screenwidth / squareSize)) * squareSize) ,
        (float)((rand() % (screenheight / squareSize)) * squareSize) 
    }; //Random x and y for now
    apple.size = { (float)squareSize, (float)squareSize };// Size of the apple
    apple.color = YELLOW; 




    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        DrawBackground();
        UpdateGame();
        //----------------------------------------------------------------------------------
    }
};

static Snake snake[SNAKE_LEN];

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


static void UpdateGame(void);
int main(void)
{    
    // Initialization
    //--------------------------------------------------------------------------------------



    InitWindow(screenwidth, screenheight, "Snake");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
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
        


        ClearBackground(LIME);

        UpdateGame();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    
    CloseWindow();       

    ClearBackground(SKYBLUE);

    for (int i = 0; i < screenwidth / squareSize + 1; i++) {
        Vector2 start = { squareSize * i + offset.x / 2.0f, offset.y / 2.0f };
        Vector2 end = { squareSize * i + offset.x / 2.0f, screenheight - offset.y / 2.0f };
        DrawLineV(start, end, LIGHTGRAY);
    }
    for (int i = 0; i < screenheight / squareSize + 1; i++) {
        Vector2 start = {offset.x / 2.0f, squareSize * i + offset.y};
        Vector2 end = { screenwidth - offset.x / 2.0f, squareSize * i + offset.y / 2.0f};
        DrawLineV(start, end, LIGHTGRAY);
    }


void MainGame(void) {
    // For our main game function to be updated
    frameCounter = 0;

}
void UpdateGame() {
    // Set up hotkeys

       
        DrawRectangle(
            (int)snake[i].position.x, (int)snake[i].position.y,
            (int)snake[i].size.x,(int) snake[i].size.y, snake[i].color);
    }

    DrawRectangleV (apple.position, apple.size, apple.color);

    
    EndDrawing();
}