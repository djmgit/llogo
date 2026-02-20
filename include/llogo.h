#ifndef LLOGO_HEADER_H
#define LLOGO_HEADER_H

#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "raylib.h"

#include  "raymath.h"

#define DIRECTION_START -90.0f
#define SCREEN_WIDTH 800.0f
#define SCREEN_HEIGHT 450.0f

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
int evaluate_command(char *);
int eval_fd(char *);
int eval_bk(char *);
int eval_rt(char *);
int eval_lt(char *);
int eval_home();
int eval_setxy(char *);
void show_all_paths();

#endif

