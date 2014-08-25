#include "main_menu.h"
#include <pebble.h>

#include "question_manager.h"
    
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *main_menu_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // main_menu_layer
  main_menu_layer = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(main_menu_layer, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)main_menu_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(main_menu_layer);
}
// END AUTO-GENERATED UI CODE

static void menu_draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *callback_context) {
    menu_cell_basic_header_draw(ctx, cell_layer, "PebbleVote");
}

static void menu_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
    switch(cell_index->row) {
        case 0: {
            menu_cell_basic_draw(ctx, cell_layer, "Random", NULL, NULL);
            break;
        }
        case 1: {
            menu_cell_basic_draw(ctx, cell_layer, "Voted", NULL, NULL);
            break;
        }
        case 2: {
            menu_cell_basic_draw(ctx, cell_layer, "Statistics", NULL, NULL);
            break;
        }
    }
}

static int16_t menu_get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static uint16_t menu_get_num_rows_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
    return 3;
}

static void menu_select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data ) {
    switch(cell_index->row) {
        case 0: {
            start_questions();
            break;
        }
        case 1: {
            break;
        }
        case 2: {
            break;
        }
    }
}

static void handle_window_load(Window *window) {
    menu_layer_set_callbacks(main_menu_layer, NULL, (MenuLayerCallbacks) {
        .draw_header = menu_draw_header_callback,
        .draw_row = menu_draw_row_callback,
        .get_header_height = menu_get_header_height_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .select_click = menu_select_click_callback,
    });
}

static void handle_window_unload(Window* window) {
    destroy_ui();
}

void show_main_menu(void) {
    initialise_ui();
    window_set_window_handlers(s_window, (WindowHandlers) {
        .load = handle_window_load,
        .unload = handle_window_unload,
    });
    window_stack_push(s_window, true);
}

void hide_main_menu(void) {
    window_stack_remove(s_window, true);
}
