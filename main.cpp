#include "raylib.h"
#include <random>

int main() {

  InitWindow(1000, 1000, "Teste");
  static std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist(0, 1);

  int currentFps = 60;

  SetTargetFPS(currentFps);

  Vector2 deltaRetangle = {10, GetScreenHeight() / 2.0f - 100};
  Vector2 deltaRetangleSize = {20, 200};

  Vector2 deltaRetangle2 = {GetScreenWidth() - 30.0f,

                            GetScreenHeight() / 2.0f - 100};
  Vector2 deltaRetangleSize2 = {20, 200};

  Vector2 cube = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  Vector2 cubeSize = {20, 20};
  double speed = 20.0f;
  double directx = speed;
  double directy = speed;
  int score1 = 0;
  int score2 = 0;
  while (!WindowShouldClose()) {
    int pos = dist(gen);
    if ((cube.x < deltaRetangle.x + deltaRetangleSize.x &&
         cube.x + cubeSize.x > deltaRetangle.x &&
         cube.y < deltaRetangle.y + deltaRetangleSize.y &&
         cube.y + cubeSize.y > deltaRetangle.y) ||
        (cube.x < deltaRetangle2.x + deltaRetangleSize2.x &&
         cube.x + cubeSize.x > deltaRetangle2.x &&
         cube.y < deltaRetangle2.y + deltaRetangleSize2.y &&
         cube.y + cubeSize.y > deltaRetangle2.y)) {

      directx = -directx;

      if (pos) {
        directy = -directy;
      }
      cube.x += directx * GetFrameTime() * 6.0f;
      cube.y += directy * GetFrameTime() * 6.0f;
    } else if ((cube.y + cubeSize.y >= GetScreenHeight() || cube.y <= 0) &&
               !(cube.x <= 0 || cube.x + cubeSize.x >= GetScreenWidth())) {
      if (pos) {
        directx = -directx;
      }
      directy = -directy;
      cube.x += directx * GetFrameTime() * 6.0f;
      cube.y += directy * GetFrameTime() * 6.0f;
    } else if (cube.x + cubeSize.x >= GetScreenWidth()) {
      cube.x = GetScreenWidth() / 2.0f;
      cube.y = GetScreenHeight() / 2.0f;
      score1++;
    } else if (cube.x <= 0) {
      cube.x = GetScreenWidth() / 2.0f;
      cube.y = GetScreenHeight() / 2.0f;
      score2++;
    } else {
      cube.x += directx * GetFrameTime() * 6.0f;
      cube.y += directy * GetFrameTime() * 6.0f;
    }
    float step = (speed + 10) * GetFrameTime() * 6.0f;

    if (IsKeyDown(KEY_DOWN)) {
      if (deltaRetangle.y + deltaRetangleSize.y >= GetScreenHeight()) {
        deltaRetangle.y = GetScreenHeight() - deltaRetangleSize.y;
      } else {
        deltaRetangle.y += step;
      }
    }

    if (IsKeyDown(KEY_UP)) {
      if (deltaRetangle.y <= 0) { // era: y - size.y <= 0
        deltaRetangle.y = 0;      // era: GetScreenHeight() + size.y
      } else {
        deltaRetangle.y -= step;
      }
    }

    if (IsKeyDown(KEY_S)) { // era: KEY_W (W e S estavam trocados)
      if (deltaRetangle2.y + deltaRetangleSize2.y >= GetScreenHeight()) {
        deltaRetangle2.y = GetScreenHeight() - deltaRetangleSize2.y;
      } else {
        deltaRetangle2.y += step;
      }
    }

    if (IsKeyDown(KEY_W)) {        // era: KEY_S
      if (deltaRetangle2.y <= 0) { // era: y - size.y <= 0
        deltaRetangle2.y = 0;      // era: GetScreenHeight() + size.y
      } else {
        deltaRetangle2.y -= step;
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(TextFormat("%i : %i", score1, score2),
             GetScreenWidth() / (5.0f / 2.0f), 0, 100, BLUE);
    ClearBackground(RAYWHITE);
    DrawRectangleV(deltaRetangle2, deltaRetangleSize2, BLACK);
    DrawRectangleV(cube, cubeSize, BLUE);
    DrawRectangleV(deltaRetangle, deltaRetangleSize, RED);
    EndDrawing();
  }
  CloseWindow();

  return 0;
}
