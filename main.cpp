#include "raylib.h"

int main() {

  InitWindow(1000, 1000, "Teste");

  int currentFps = 60;

  SetTargetFPS(currentFps);

  Vector2 deltaRetangle = {10, GetScreenHeight() / 2.0f - 100};
  Vector2 deltaRetangleSize = {20, 200};

  Vector2 deltaRetangle2 = {GetScreenWidth() - 30.0f,

                            GetScreenHeight() / 2.0f - 100};
  Vector2 deltaRetangleSize2 = {20, 200};
  while (!WindowShouldClose()) {

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRectangleV(deltaRetangle2, deltaRetangleSize2, BLUE);
    DrawRectangleV(deltaRetangle, deltaRetangleSize, RED);
    EndDrawing();
  }
  CloseWindow();

  return 0;
}
