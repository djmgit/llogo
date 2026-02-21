#include "include/llogo.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib - Move Along Angle");
    init_llogo();
    char *log = get_command_log();
    Vector2 position = { CANVAS_WIDTH / 2.0, CANVAS_HEIGHT / 2.0 };

    char command_input[64] = "";
    bool command_box_edit_mode = false;

    int command_box_width = 180;
    int command_box_height = 40;
    int command_box_x = 40;
    int command_box_y = CANVAS_HEIGHT + 40;

    int log_box_width = 300;
    int log_box_height = 160;
    int log_box_x = CANVAS_WIDTH / 2.0;
    int log_box_y = CANVAS_HEIGHT + 40;

    int log_content_box_width = 600;
    int log_content_box_height = 800;

    Rectangle panelView = { 0 };
    Vector2 panelScroll = { 1.0, 0.0 };

    Rectangle log_rectangle = (Rectangle){log_box_x, log_box_y, log_box_width, log_box_height};
    Rectangle log_content_rectangle = (Rectangle){0, 0, log_content_box_width, log_content_box_height};


    while (!WindowShouldClose()) {

        if (command_box_edit_mode) {
            if (IsKeyPressed(KEY_ENTER)) {
                if (strlen(command_input) != 0) {
                    evaluate_command(command_input);
                    memset(command_input, 0, strlen(command_input));
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangleLinesEx((Rectangle){0, 0, CANVAS_WIDTH, CANVAS_HEIGHT}, 4.0, BLACK);

        path_node_t *t_pnode = get_path_head();
        while (t_pnode != NULL) {
            DrawLine(t_pnode->path.source.x, t_pnode->path.source.y, t_pnode->path.destination.x, t_pnode->path.destination.y, BLACK);
            t_pnode = t_pnode->next;
        } 

        DrawPoly(get_cur_pos(), 3, 10, get_cur_dir(), MAROON);

        GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
        if (GuiTextBox((Rectangle){ command_box_x, command_box_y, command_box_width, command_box_height}, command_input, 64, command_box_edit_mode)) {
            command_box_edit_mode = !command_box_edit_mode;
        };

        

        GuiScrollPanel(log_rectangle, NULL, log_content_rectangle, &panelScroll, &panelView);

        BeginScissorMode(panelView.x, panelView.y, panelView.width, panelView.height);
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_TOP);   // WARNING: Word-wrap does not work as expected in case of no-top alignment
            GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_WORD);            // WARNING: If wrap mode enabled, text editing is not supported
            GuiTextBox((Rectangle){log_rectangle.x + panelScroll.x, log_rectangle.y + panelScroll.y, log_content_rectangle.width, log_content_rectangle.height}, log, 1024*1024, false);
            GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_NONE);
            GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_MIDDLE);
        EndScissorMode();

        
        //DrawText(command_input, 10, 10, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}