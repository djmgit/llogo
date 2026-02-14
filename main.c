#include "raylib.h"
#include  "raymath.h"
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define DIRECTION_START -90.0f
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450


typedef struct path_t {
    Vector2 source;
    Vector2 destination;
} path_t;

struct path_node {
    path_t path;
    struct path_node *next;
};

typedef struct path_node path_node_t;

typedef struct command_t {
    char op[20];
    char val[100];
} command_t;

path_node_t *path_node_head;
float direction = DIRECTION_START;
Vector2 origin = { SCREEN_WIDTH*1.0f / 2, SCREEN_HEIGHT*1.0f / 2 };
Vector2 cur_pos = { SCREEN_WIDTH*1.0f / 2, SCREEN_HEIGHT*1.0f / 2 };

path_t create_path(Vector2 source, Vector2 destination) {
    return (path_t){.source = source, .destination = destination};
}

path_node_t *create_path_node(path_t path) {
    path_node_t *p_node = (path_node_t *)malloc(sizeof(path_node_t));
    p_node->path = path;
    p_node->next = NULL;
    return p_node;
}

void add_path(path_t path) {
    if (path_node_head == NULL) {
       path_node_head = create_path_node(path);
       return;
    }

    path_node_t *t_pnode = path_node_head;
    while (t_pnode->next != NULL) {
        t_pnode = t_pnode->next;
    }

    t_pnode->next = create_path_node(path);
}

command_t parse_command(char *command_str) {
    command_t command;

    const char *delimiters = " ";
    char *token;

    token = strtok(command_str, delimiters);
    if (token == NULL) {
        return command;
    }
    strcpy(command.op, token);

    token = strtok(NULL, delimiters);
    if (token == NULL) {
        return command;
    }

    strcpy(command.val, token);

    return command;
}

void eval_fd(char *val_str) {
    char *endptr;
    float val = strtof(val_str, endptr);

    errno = 0;
    if (errno != 0 || *endptr != '\0') {
        return;
    }

    Vector2 new_pos = {cur_pos.x + cosf(direction * DEG2RAD) * val, cur_pos.y + sinf(direction * DEG2RAD) * val};
    path_t path = create_path(cur_pos, new_pos);
    add_path(path);
    cur_pos = new_pos;
}

void eval_bk(char *val_str) {
    char *endptr;
    float val = strtof(val_str, endptr);

    errno = 0;
    if (errno != 0 || *endptr != '\0') {
        return;
    }

    Vector2 new_pos = {cur_pos.x - cosf(direction * DEG2RAD) * val, cur_pos.y - sinf(direction * DEG2RAD) * val};
    path_t path = create_path(cur_pos, new_pos);
    add_path(path);
    cur_pos = new_pos;
}

void eval_rt(char *val_str) {
    char *endptr;
    float val = strtof(val_str, endptr);

    errno = 0;
    if (errno != 0 || *endptr != '\0') {
        return;
    }

    direction += val;
}

void eval_lt(char *val_str) {
    char *endptr;
    float val = strtof(val_str, endptr);

    errno = 0;
    if (errno != 0 || *endptr != '\0') {
        return;
    }

    direction -= val;
}

void eval_home() {
    cur_pos = origin;
    direction = DIRECTION_START;
}

void eval_setpos(char *val_x, char *val_y) {

}


int main()
{
    InitWindow(800, 450, "Raylib - Move Along Angle");
    Vector2 position = { 400.0f, 225.0f };
    float speed = 300.0f;
    float angle = -90.0f; // 0 is right, 90 is down
    SetTargetFPS(60);

    Vector2 position_source = { 400.0f, 225.0f };

    float length = 50.0;
    Vector2 position_destination = {position_source.x + cosf(angle * DEG2RAD) * length, position_source.y + sinf(angle * DEG2RAD) * length};


    while (!WindowShouldClose()) {
        // Update angle (rotating with arrow keys)
        if (IsKeyDown(KEY_LEFT)) angle -= 3.0f;
        if (IsKeyDown(KEY_RIGHT)) angle += 3.0f;

        position_destination.x = position_source.x + cosf(angle * DEG2RAD) * length;
        position_destination.y = position_source.y + sinf(angle * DEG2RAD) * length;

        // Move forward in the current angle direction
        if (IsKeyDown(KEY_UP)) {
            position.x += cosf(angle * DEG2RAD) * speed * GetFrameTime();
            position.y += sinf(angle * DEG2RAD) * speed * GetFrameTime();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw object (a triangle pointing right, rotated)
        DrawPoly(position, 3, 20, angle, MAROON);
        DrawText("Use Arrows to Rotate/Move", 10, 10, 20, DARKGRAY);
        DrawLineV(position_source, position_destination, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}