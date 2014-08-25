#include "question_window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_action_bar_checkmark;
static GBitmap *s_res_action_bar_switch;
static GBitmap *s_res_action_bar_menu;
static MenuLayer *question_menu_layer;
static ActionBarLayer *question_action_bar_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_action_bar_checkmark = gbitmap_create_with_resource(RESOURCE_ID_ACTION_BAR_CHECKMARK);
  s_res_action_bar_switch = gbitmap_create_with_resource(RESOURCE_ID_ACTION_BAR_SWITCH);
  s_res_action_bar_menu = gbitmap_create_with_resource(RESOURCE_ID_ACTION_BAR_MENU);
  // question_menu_layer
  question_menu_layer = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(question_menu_layer, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)question_menu_layer);
  
  // question_action_bar_layer
  question_action_bar_layer = action_bar_layer_create();
  action_bar_layer_add_to_window(question_action_bar_layer, s_window);
  action_bar_layer_set_background_color(question_action_bar_layer, GColorBlack);
  action_bar_layer_set_icon(question_action_bar_layer, BUTTON_ID_UP, s_res_action_bar_menu);
  action_bar_layer_set_icon(question_action_bar_layer, BUTTON_ID_SELECT, s_res_action_bar_checkmark);
  action_bar_layer_set_icon(question_action_bar_layer, BUTTON_ID_DOWN, s_res_action_bar_switch);
  layer_add_child(window_get_root_layer(s_window), (Layer *)question_action_bar_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(question_menu_layer);
  action_bar_layer_destroy(question_action_bar_layer);
  gbitmap_destroy(s_res_action_bar_checkmark);
  gbitmap_destroy(s_res_action_bar_switch);
  gbitmap_destroy(s_res_action_bar_menu);
}
// END AUTO-GENERATED UI CODE

static void (*answer_question)(question_answer_t answer);
static const char* id;
static const char* either;
static const char* or;

static void menu_draw_header_callback(GContext *ctx, const Layer *cell_layer, uint16_t section_index, void *callback_context) {
    switch(section_index) {
        case 0: {
            menu_cell_basic_header_draw(ctx, cell_layer, "Would you rather...");
            break;
        }
        case 1: {
            menu_cell_basic_header_draw(ctx, cell_layer, "... or ...");
            break;
        }
    }
}

static void menu_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
    switch(cell_index->section) {
        case 0: {
            menu_cell_basic_draw(ctx, cell_layer, either, NULL, NULL);
            break;
        }
        case 1: {
            menu_cell_basic_draw(ctx, cell_layer, or, NULL, NULL);
            break;
        }
    }
}

static int16_t menu_get_cell_height_callback(struct MenuLayer *menu_layer, MenuIndex *cell_index, void *callback_context) {
    return 44;
}

static int16_t menu_get_header_height_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

static uint16_t menu_get_num_rows_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
    return 1;
}

static uint16_t menu_get_num_sections_callback(struct MenuLayer *menu_layer, void *callback_context) {
    return 2;
}

static void menu_select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data ) {
    switch(cell_index->row) {
        case 0: {
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
    menu_layer_set_callbacks(question_menu_layer, NULL, (MenuLayerCallbacks) {
        .draw_header = menu_draw_header_callback,
        .draw_row = menu_draw_row_callback,
        .get_cell_height = menu_get_cell_height_callback,
        .get_header_height = menu_get_header_height_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .get_num_sections = menu_get_num_sections_callback,
        .select_click = menu_select_click_callback,
    });
}

static void handle_window_unload(Window* window) {
    destroy_ui();
}

void up_click_handler(ClickRecognizerRef recognizer, void *context) {
    show_question_menu(answer_question, id, either, or);
}

void select_click_handler(ClickRecognizerRef recognizer, void *context) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "Submit answer");
    
    MenuIndex index = menu_layer_get_selected_index(question_menu_layer);
    answer_question(index.section == 0 ? QUESTION_ANSWER_EITHER : QUESTION_ANSWER_OR);
}

void down_click_handler(ClickRecognizerRef recognizer, void *context) {
    MenuIndex index = menu_layer_get_selected_index(question_menu_layer);
    menu_layer_set_selected_next(question_menu_layer, (index.section == 1), MenuRowAlignNone, true);
}

void click_config_provider(void *context) {
    window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
    window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
    window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
}

void show_question_window(void (*_answer_question)(question_answer_t answer), const char* _id, const char* _either, const char* _or) {
    answer_question = _answer_question;
    id = _id;
    either = _either;
    or = _or;
    
    initialise_ui();
    window_set_window_handlers(s_window, (WindowHandlers) {
        .load = handle_window_load,
        .unload = handle_window_unload,
    });
    window_set_click_config_provider(s_window, click_config_provider);
    window_stack_push(s_window, true);
}

void hide_question_window(void) {
    window_stack_remove(s_window, true);
}
