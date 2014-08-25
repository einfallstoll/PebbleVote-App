#include "question_menu.h"
#include "simple_window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *question_menu_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  // question_menu_layer
  question_menu_layer = menu_layer_create(GRect(0, 0, 144, 168));
  menu_layer_set_click_config_onto_window(question_menu_layer, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)question_menu_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(question_menu_layer);
}
// END AUTO-GENERATED UI CODE

static void (*answer_question)(question_answer_t answer);
static const char* id;
static const char* either;
static const char* or;

static void menu_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
    switch(cell_index->row) {
        case 0: {
            menu_cell_basic_draw(ctx, cell_layer, "Skip", NULL, NULL);
            break;
        }
        case 1: {
            menu_cell_basic_draw(ctx, cell_layer, "Report", NULL, NULL);
            break;
        }
    }
}

static uint16_t menu_get_num_rows_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
    return 2;
}

static void menu_select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data ) {
    switch(cell_index->row) {
        case 0: {
            window_stack_pop(true);
            answer_question(QUESTION_ANSWER_SKIP);
            break;
        }
        case 1: {
            window_stack_pop(true);
            answer_question(QUESTION_ANSWER_REPORT);
            break;
        }
    }
}

static void handle_window_load(Window *window) {
    menu_layer_set_callbacks(question_menu_layer, NULL, (MenuLayerCallbacks) {
        .draw_row = menu_draw_row_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .select_click = menu_select_click_callback,
    });
}

static void handle_window_unload(Window* window) {
    destroy_ui();
}

void show_question_menu(void (*_answer_question)(question_answer_t answer), const char* _id, const char* _either, const char* _or) {
    answer_question = _answer_question;
    id = _id;
    either = _either;
    or = _or;
    
    initialise_ui();
    window_set_window_handlers(s_window, (WindowHandlers) {
        .load = handle_window_load,
        .unload = handle_window_unload,
    });
    window_stack_push(s_window, true);
}

void hide_question_menu(void) {
    window_stack_remove(s_window, true);
}
