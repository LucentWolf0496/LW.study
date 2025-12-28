#include <raylib.h>

int main() {
    InitWindow(640, 480, "Raylib Test in VSCode");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello, Raylib!", 200, 200, 30, LIGHTGRAY);
        DrawCircle(GetMouseX(), GetMouseY(), 50, MAROON);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}