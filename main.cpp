
#include "raylib.h"
#include <string>
#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

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
static int screenheight = 500;

static int frameCounter = 0;
static bool isOver = false;


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
        /// tryyyyyyyyyashahsauhshauhsa
        ClearBackground(RAYWHITE);

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