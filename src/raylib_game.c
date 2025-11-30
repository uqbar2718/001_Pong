#include "raylib.h"
#include "math.h"


int main(void)
{
    // 1. 초기화 (Initialization)
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Pong Step 2.5: Small Improvements");
    SetTargetFPS(60); 

    // --- 구조체 추가 : 공 ---


    float ballX = screenWidth / 2.0f;
    float ballY = screenHeight / 2.0f;
    float ballSpeedX = 300.0f;
    float ballSpeedY = 300.0f;
    float ballRadius = screenWidth / 40.0f;

    // 패들 상태변수
    float rectHeight = screenHeight/4.5f;
    float rectWidth = screenWidth/40.0f;
    float rectX = screenWidth/10.0f;
    float rectY = screenHeight/2.0f - rectHeight/2.0f;
    float rectSpeed = 420.0f;

    // 2. 게임 루프
    while (!WindowShouldClose())
    {
        // -- Update -- Change: Delta Time implemented
        float dt = GetFrameTime();
        ballX += ballSpeedX * dt;
        ballY += ballSpeedY * dt;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) rectY += rectSpeed * dt;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) rectY -= rectSpeed * dt;
       

        // 공 벽 충돌 처리
        if ((ballX + ballRadius >= screenWidth) || (ballX - ballRadius <= 0)) ballSpeedX *= -1.0f;
        if ((ballY + ballRadius >= screenHeight) || (ballY - ballRadius <= 0)) ballSpeedY *= -1.0f;

        // 패들 벽 충돌 처리
        if (rectY >= screenHeight - rectHeight ) rectY = screenHeight - rectHeight;
        if (rectY <= 0.0f) rectY = 0.0f;

        // 패들 공 충돌 처리
        // only consider ball coming from left side
        if (CheckCollisionCircleRec((Vector2){ballX, ballY}, ballRadius, (Rectangle){rectX, rectY, rectWidth, rectHeight}) &&
            ballSpeedX < 0)
        {
            ballSpeedX *= -1.0f;

            // for excitement, increase ball speed by 7% every collision
            ballSpeedX *= 1.035f;
            ballSpeedY *= 1.035f;
        }    

        // --- Draw ---
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle((int)ballX, (int)ballY, ballRadius, RAYWHITE);
            DrawText(TextFormat("BallPos: (%.0f, %.0f)", ballX, ballY), 10, 10, 20, GREEN);
            DrawRectangle((int)rectX, (int)rectY, (int)rectWidth, (int)rectHeight, WHITE);
            DrawFPS(10, 30);

        EndDrawing();
    }

    // 3. 종료
    CloseWindow();
    return 0;
}