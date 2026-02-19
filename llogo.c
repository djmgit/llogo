#include "include/llogo.h"

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

void show_all_paths() {
    path_node_t *t_pnode = path_node_head;
    while (t_pnode != NULL) {
        printf("(%f, %f) -> (%f, %f)\n", t_pnode->path.source.x, t_pnode->path.source.y, t_pnode->path.destination.x, t_pnode->path.destination.y);
        t_pnode = t_pnode->next;
    } 
}

int eval_fd(char *val_str) {
    char *endptr;
    if (strlen(val_str) == 0) {
        return -1;
    }
    float val = strtof(val_str, &endptr);

    errno = 0;
    if (errno != 0 || *endptr != '\0') {
        return -1;
    }

    Vector2 new_pos = {cur_pos.x + cosf(direction * DEG2RAD) * val, cur_pos.y + sinf(direction * DEG2RAD) * val};
    path_t path = create_path(cur_pos, new_pos);
    add_path(path);
    cur_pos = new_pos;

    return 0;
}

int eval_bk(char *val_str) {
    if (strlen(val_str) == 0) {
        return -1;
    }

    char *endptr;
    float val = strtof(val_str, &endptr);

    errno = 0;
    if (errno != 0 || *endptr != '\0') {
        return -1;
    }

    Vector2 new_pos = {cur_pos.x - cosf(direction * DEG2RAD) * val, cur_pos.y - sinf(direction * DEG2RAD) * val};
    path_t path = create_path(cur_pos, new_pos);
    add_path(path);
    cur_pos = new_pos;

    return 0;
}

int eval_rt(char *val_str) {
    if (strlen(val_str) == 0) {
        return -1;
    }

    char *endptr;
    float val = strtof(val_str, &endptr);

    errno = 0;
    if (errno != 0 || *endptr != '\0') {
        return -1;
    }

    direction += val;

    return 0;
}

int eval_lt(char *val_str) {
    if (strlen(val_str) == 0) {
        return -1;
    }

    char *endptr;
    float val = strtof(val_str, &endptr);

    errno = 0;
    if (errno != 0 || *endptr != '\0') {
        return -1;
    }

    direction -= val;

    return 0;
}

int eval_home() {
    cur_pos = origin;
    direction = DIRECTION_START;

    return 0;
}

int eval_setxy(char *val_xy) {
    if (strlen(val_xy) == 0) {
        return -1;
    }

    char *endptr;
    errno = 0;
    const char *delimiters = " ";

    char *val_x = strtok(NULL, delimiters);
    if (val_x  == NULL) {
        return -1;
    }

    float pos_x = strtof(val_x, &endptr);
    if (errno != 0 || *endptr != '\0') {
        return -1;
    }

    char *val_y = strtok(NULL, delimiters);
    if (val_y == NULL) {
        return -1;
    }

    float pos_y = strtof(val_y, &endptr);
    if (errno != 0 || *endptr != '\0') {
        return -1;
    }

    cur_pos.x = pos_x;
    cur_pos.y = pos_y;

    return 0;

}

command_t parse_command(char *command_str) {
    command_t command;
    memset(&command, 0, sizeof(command));

    const char *delimiters = " ";
    char *token = NULL;

    token = strtok(command_str, delimiters);
    if (token == NULL) {
        return command;
    }
    strcpy(command.op, token);

    if (strcmp(command.op, "fd") == 0 ||
        strcmp(command.op, "bk") == 0 ||
        strcmp(command.op, "rt") == 0 ||
        strcmp(command.op, "lt") == 0 ||
        strcmp(command.op, "setxy") == 0) {
            token = strtok(NULL, delimiters);
            if (token == NULL) {
                return command;
            }

            strcpy(command.val, token);
    } else if (strcmp(command.val, "home") == 0) {
        return command;
    }

    return command;
}

int evaluate_command(char *command_str) {
    command_t command = parse_command(command_str);

    if (strlen(command.op) == 0) {
        return -1;
    }

    if (strcmp(command.op, "fd") == 0) {
        return eval_fd(command.val);
    }

    if (strcmp(command.op, "bk") == 0) {
        return eval_bk(command.val);
    }

    if (strcmp(command.op, "rt") == 0) {
        return eval_rt(command.val);
    }

    if (strcmp(command.op, "lt") == 0) {
        return eval_lt(command.val);
    }

    if (strcmp(command.op, "home") == 0) {
        return eval_home(command.val);
    }

    if (strcmp(command.op, "setxy") == 0) {
        return eval_setxy(command.val);
    }

    return -1;
}
