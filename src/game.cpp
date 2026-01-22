#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <algorithm>

constexpr int BULLET_SPEED = 400;
constexpr int PLAYER_SPEED = 200;
const int screenWidth = 800;
const int screenHeight = 450;

void DrawAsTank(Vector2 posCenter) {

}

struct Entity {
    Vector2 pos;
    int speed;
    int width = 20;
    int height = 20;
    Vector2 direction = {0,0};

    void Draw() const {
        DrawRectangle(pos.x, pos.y, width, height, DARKPURPLE);
    } 
};

bool IsOutOfScreen(Entity entity) {
    Vector2 pos = entity.pos;
    return pos.x > screenWidth || pos.y > screenHeight 
        || pos.x + entity.width < 0 || pos.y + entity.height < 0;
}

void RemoveOutOfScreenEntities(std::vector<Entity> &entities) {
    auto new_end = std::remove_if(entities.begin(), entities.end(), IsOutOfScreen);
    if (new_end != entities.end()) {
        TraceLog(LOG_DEBUG, "Remove %d entities out of screen", entities.end() - new_end);
    }

    entities.erase(new_end, entities.end());

}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    SetTraceLogLevel(LOG_DEBUG);
    // Initialization
    //--------------------------------------------------------------------------------------

    Entity tank = {400, 200, 200};
    std::vector<Entity> bullets;

    InitWindow(screenWidth, screenHeight, "raylib simple tanks");

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
        Vector2 ds_normalized = Vector2Normalize(ds);
        ds = ds_normalized * (tank.speed * dt);     
        
        // if tank stops do not change its directio
        tank.direction = ds == Vector2Zero() ? tank.direction : ds_normalized;
        tank.pos += ds;

        // shoot!!
        if (IsKeyPressed(KEY_SPACE)) {
            Vector2 bullet_pos {
                tank.pos.x + (float)tank.width / 2 - 5,
                tank.pos.y + (float)tank.height / 2 - 5};
            Entity bullet {bullet_pos, BULLET_SPEED, 
                10, 10, 
                tank.direction};
            bullets.push_back(std::move(bullet));
        }

        RemoveOutOfScreenEntities(bullets);
        for (Entity &bullet : bullets) {
            // always move a bullet 
            bullet.pos += bullet.direction * bullet.speed * dt;
        }

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);


            tank.Draw();
            
            for (const auto &bullet: bullets) {
                bullet.Draw();
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
