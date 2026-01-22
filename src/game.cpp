#include "raylib.h"
#include "raymath.h"
#include <vector>


void DrawAsTank(Vector2 posCenter) {

}


struct Entity {
public:
    Vector2 pos;
    int speed;
    int width = 20;
    int height = 20;

    void Draw() {
        DrawRectangle(pos.x, pos.y, 20, 20, DARKPURPLE);
    } 
    void Shoot() {

    }
};

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    Entity tank = {400, 200, 200};
    std::vector<Entity> bullets;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        float dt = GetFrameTime();
        Vector2 ds = {0,0};
        if (IsKeyDown(KEY_LEFT)) {
            ds.x = -tank.speed * dt;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            ds.x = tank.speed * dt;
        }
        if (IsKeyDown(KEY_UP)) {
            ds.y = -tank.speed * dt;
        }
        if (IsKeyDown(KEY_DOWN)) {
            ds.y = tank.speed * dt;
        }

        ds = Vector2Normalize(ds);
        ds = Vector2Scale(ds, tank.speed * dt);
        tank.pos = Vector2Add(tank.pos, ds);
        
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            tank.Draw();
            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
