#include "raylib.h"
#include "math.h"

int main(void)
{
    // 1. 초기화 (Initialization)
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Pong Step 2: A Paddle Added");
    SetTargetFPS(60); 

    // --- 공의 상태 변수 ---
    float ballX = screenWidth / 2.0f;
    float ballY = screenHeight / 2.0f;
    float ballSpeedX = 5.0f;
    float ballSpeedY = 5.0f;
    float ballRadius = 20.0f;

    // 패들 상태변수
    float rectHeight = 100.0f;
    float rectWidth = 20.0f;
    float rectX = screenWidth/10.0f;
    float rectY = screenHeight/2.0f - rectHeight/2.0f;
    float rectSpeed = 7.0f;

    // 2. 게임 루프
    while (!WindowShouldClose())
    {
        // --- Update ---
        ballX += ballSpeedX;
        ballY += ballSpeedY;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) rectY += rectSpeed;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) rectY -= rectSpeed;
       

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
            DrawText(TextFormat("Pos: (%.0f, %.0f)", ballX, ballY), 10, 10, 20, GREEN);
            DrawText(TextFormat("BallSpd (%.3f)", (float)sqrt((pow(ballSpeedX,2) + pow(ballSpeedY,2)))), 10, 30, 20, YELLOW);
            DrawText(TextFormat("BallSpd (%.3f, %.3f)", ballSpeedX, ballSpeedY), 10, 50, 20, MAGENTA);

            DrawRectangle((int)rectX, (int)rectY, (int)rectWidth, (int)rectHeight, WHITE);
        EndDrawing();
    }

    // 3. 종료
    CloseWindow();
    return 0;
}