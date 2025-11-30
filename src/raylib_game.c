#include "raylib.h"
#include "math.h"

// --- 구조체 정의 : 공 ---
typedef struct 
{
    Vector2 position;
    Vector2 speed;
    float radius;
} Ball;

// --- 구조체 정의 : 채 ---
typedef struct
{
    Rectangle rect; // x y w h
    float speed;
    int score;
} Paddle;




int main(void)
{
    // 1. 초기화 (Initialization)
    const int screenWidth = 800;
    const int screenHeight = 450;
  
    InitWindow(screenWidth, screenHeight, "Pong Step 4. Scoring");
    SetTargetFPS(60); 

    Ball ball = {
        .position = {screenWidth / 2.0f, screenHeight / 2.0f},
        .speed = {300.0f, 300.0f},
        .radius = screenWidth / 40.0f
    };

    Paddle player1 = {
        .rect = { screenWidth/10.0f, screenHeight/2.0f - screenHeight/9.0f, screenWidth/40.0f ,screenHeight/4.5f},
        .speed = 420.0f
    };

    Paddle player2 = {
        .rect = { screenWidth - screenWidth/10.0f, screenHeight/2.0f - screenHeight/9.0f, screenWidth/40.0f ,screenHeight/4.5f},
        .speed = 420.0f
    };

    player1.score = 0;
    player2.score = 0;

    // 2. 게임 루프
    while (!WindowShouldClose())
    {
        // -- Update -- Change: Delta Time implemented
        float dt = GetFrameTime();
        ball.position.x += ball.speed.x * dt;
        ball.position.y += ball.speed.y * dt;
        if (IsKeyDown(KEY_S)) player1.rect.y += player1.speed * dt;
        if (IsKeyDown(KEY_W)) player1.rect.y -= player1.speed * dt;

        if (IsKeyDown(KEY_DOWN)) player2.rect.y += player2.speed * dt;
        if (IsKeyDown(KEY_UP)) player2.rect.y -= player2.speed * dt;

        // 공 벽 충돌 처리
        if ((ball.position.y + ball.radius >= screenHeight) || (ball.position.y - ball.radius <= 0)) ball.speed.y *= -1.0f;

        // 패들 벽 충돌 처리
        if (player1.rect.y >= screenHeight - player1.rect.height ) player1.rect.y = screenHeight - player1.rect.height;
        if (player1.rect.y <= 0.0f) player1.rect.y = 0.0f;

        if (player2.rect.y >= screenHeight - player2.rect.height ) player2.rect.y = screenHeight - player2.rect.height;
        if (player2.rect.y <= 0.0f) player2.rect.y = 0.0f;

        // 패들 공 충돌 처리
        // only consider ball coming from right side for player1
        if (CheckCollisionCircleRec(ball.position, ball.radius, player1.rect) &&
            ball.speed.x < 0)
        {
            ball.speed.x *= -1.0f;

            // for excitement, increase ball speed by 7% every collision
            ball.speed.x *= 1.035f;
            ball.speed.y *= 1.035f;
        }    

        // only consider ball coming from left side for player2
        if (CheckCollisionCircleRec(ball.position, ball.radius, player2.rect) &&
            ball.speed.x > 0)
        {
            ball.speed.x *= -1.0f;

            // for excitement, increase ball speed by 7% every collision
            ball.speed.x *= 1.035f;
            ball.speed.y *= 1.035f;
        } 

        //Scoring Condition and State Reset
        if(ball.position.x < 0) 
        {
            player2.score += 1;
            ball.position = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
            WaitTime(0.1);
            ball.speed = (Vector2){300.0f, 300.0f};
        }

        if(ball.position.x > screenWidth) 
        {
            player1.score += 1;
            ball.position = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
            WaitTime(0.1);
            ball.speed = (Vector2){-300.0f, 300.0f};
        }


        // --- Draw ---
        BeginDrawing();
            ClearBackground(BLACK);

            DrawCircle((int)ball.position.x, (int)ball.position.y, ball.radius, RAYWHITE);

            DrawRectangleRec(player1.rect, WHITE);
            DrawRectangleRec(player2.rect, WHITE);

            if((int)GetTime() < 10.0){ //for some reason, gettime starts from 5
                DrawText("W/S", (int)player1.rect.x-30, screenHeight-100, 40, RAYWHITE);
                DrawText("^/v", (int)player2.rect.x-30, screenHeight-100, 40, RAYWHITE);
            }


            DrawText(TextFormat("%d", player1.score), player1.rect.x, 10, 40, RAYWHITE);
            DrawText(TextFormat("%d", player2.score), player2.rect.x, 10, 40, RAYWHITE);


        EndDrawing();
    }

    // 3. 종료
    CloseWindow();
    return 0;
}