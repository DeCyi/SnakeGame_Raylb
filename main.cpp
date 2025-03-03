
#include "raylib.h"
#include <string>
#include <iostream>
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


    Vector2 vector = { (float)x, (float)y };

    // image of the food (apple)


    void Draw() {

        DrawRectangle(vector.x * cellX, vector.y * cellY, cellSize, cellSize, BLACK);

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

    return 0;
}


void MainGame(void) {
    // For our main game function to be updated
    frameCounter = 0;

}
void UpdateGame() {
    // Set up hotkeys

    
}

void UpdateDrawFrame(void) {
    // Frame update
}