#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include  "raymath.h"

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

path_t create_path(Vector2, Vector2);
path_node_t *create_path_node(path_t);
void add_path(path_t path);
command_t parse_command(char *);
int eval_fd(char *);
void eval_bk(char *);
void eval_rt(char *);
void eval_lt(char *);
void eval_home();
void eval_setxy(char *);

