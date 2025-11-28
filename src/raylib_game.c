#include "raylib.h"

int main(void)
{
    // 1. 초기화 (Initialization)
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Pong Step 1: Bouncing Ball");
    SetTargetFPS(60); 

    // --- 공의 상태 변수 ---
    float ballX = screenWidth / 2.0f;
    float ballY = screenHeight / 2.0f;
    float ballSpeedX = 5.0f;
    float ballSpeedY = 5.0f;
    float ballRadius = 20.0f;

    // 2. 게임 루프
    while (!WindowShouldClose())
    {
        // --- Update ---
        ballX += ballSpeedX;
        ballY += ballSpeedY;

        // 벽 충돌 처리
        if ((ballX + ballRadius >= screenWidth) || (ballX - ballRadius <= 0)) ballSpeedX *= -1.0f;
        if ((ballY + ballRadius >= screenHeight) || (ballY - ballRadius <= 0)) ballSpeedY *= -1.0f;

        // --- Draw ---
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle((int)ballX, (int)ballY, ballRadius, RAYWHITE);
            DrawText(TextFormat("Pos: (%.0f, %.0f)", ballX, ballY), 10, 10, 20, GREEN);
        EndDrawing();
    }

    // 3. 종료
    CloseWindow();
    return 0;
}