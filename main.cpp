#include "grid.h"

#include <iostream>
#include <raylib.h>

using namespace std;

const int SQUARE_SIZE = 32;
const int GRID_SIZE = 40;

Vector2 snake[GRID_SIZE * GRID_SIZE] = {{0, 0}, {0, 1}, {0, 2}};
int length = 3;
Vector2 speed = {0, 1};
bool gameover = false;

void update(Grid& grid) {
    for (int i = 0; i < length; i++) {
        int r = snake[i].x;
        int c = snake[i].y;
        grid[r][c].reborn();
    }

    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid.size(); col++) {
            int nlive = grid.live_neighour(row, col);
            if (grid[row][col].isAlive()) {
                if (nlive < 2 || nlive > 3) {
                    grid[row][col].die();
                }
            } else if (nlive == 3) {
                grid[row][col].reborn();
            }
        }
    }


    // x is row
    int r, c;
    for (int i = 1; i < length; i++ ) {
        snake[i-1] = snake[i];
    }
    snake[length -1].x += speed.x;
    snake[length -1].y += speed.y;

    r = snake[length-1].x;
    c = snake[length-1].y;

    if (r >= GRID_SIZE || c >= GRID_SIZE || r < 0 || c < 0) {
        gameover = true;
        return;
    }

    if (grid[r][c].isAlive()) {
        snake[length].x = r;
        snake[length].y = c;
        length++;
    }
}

int main() {
    cout << "Hello World!" << endl;

    Grid grid(GRID_SIZE);

    InitWindow(GRID_SIZE * SQUARE_SIZE, GRID_SIZE * SQUARE_SIZE, "");

    SetTargetFPS(10);

    bool pause = false;
    bool allowPress = true;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (IsKeyPressed(KEY_SPACE)) {
            pause = !pause;
        } else if (gameover && IsKeyPressed(KEY_R)) {
            gameover = false;
            grid.clear();

            speed = {0, 1};
            snake[0] = {0, 0};
            snake[1] = {0, 1};
            snake[2] = {0, 2};
            length = 3;
        }

        if (!pause && !gameover) {
            if (IsKeyPressed(KEY_DOWN) && speed.x != -1 && speed.y != 0) {
                speed = {1, 0};
            } else if (IsKeyPressed(KEY_LEFT) && speed.x != 0 && speed.y != 1) {
                speed = {0, -1};
            } else if (IsKeyPressed(KEY_RIGHT) && speed.x != 0 && speed.y != -1) {
                speed = {0, 1};
            } else if (IsKeyPressed(KEY_UP) && speed.x != 1 && speed.y != 0) {
                speed = {-1, 0};
            }

            update(grid);
        }

        if (gameover) {
            DrawText("Game Over", 190, 200, 40, LIGHTGRAY);
        } else {
            for (int row = 0; row < grid.size(); row++) {
                for (int col = 0; col < grid.size(); col++) {
                    int posX = col * SQUARE_SIZE;
                    int posY = row * SQUARE_SIZE;
                    Color color = LIGHTGRAY;
                    if (grid[row][col].isAlive()) {
                        color = BLACK;
                        color.a = 100;
                        DrawRectangle(posX, posY, SQUARE_SIZE, SQUARE_SIZE, color);
                    } else {
                        DrawRectangleLines(posX, posY, SQUARE_SIZE, SQUARE_SIZE, color);
                    }
                }
            }

            for (int i = 0; i < length; i++ ) {
                int posX = snake[i].y * SQUARE_SIZE;
                int posY = snake[i].x * SQUARE_SIZE;
                Color snake_color = PURPLE;
                if (i == length - 1) {
                    snake_color = RED;
                }
                snake_color.a = 100;
                DrawRectangle(posX, posY, SQUARE_SIZE, SQUARE_SIZE, snake_color);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
