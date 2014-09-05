#include "language_menu.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *language_menu_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // language_menu_layer
  language_menu_layer = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(language_menu_layer, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)language_menu_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(language_menu_layer);
}
// END AUTO-GENERATED UI CODE

static void menu_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
    switch(cell_index->row) {
        case 0: {
            menu_cell_basic_draw(ctx, cell_layer, "English", NULL, gbitmap_create_with_resource(RESOURCE_ID_MENU_FOOD_ICON));
            break;
        }
        case 1: {
            menu_cell_basic_draw(ctx, cell_layer, "French", NULL, gbitmap_create_with_resource(RESOURCE_ID_MENU_BREAD_ICON));
            break;
        }
        case 2: {
            menu_cell_basic_draw(ctx, cell_layer, "German", NULL, gbitmap_create_with_resource(RESOURCE_ID_MENU_BEER_ICON));
            break;
        }
        case 2: {
            menu_cell_basic_draw(ctx, cell_layer, "Italian", NULL, gbitmap_create_with_resource(RESOURCE_ID_MENU_PIZZA_ICON));
            break;
        }
    }
}

static uint16_t menu_get_num_rows_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
    return 4;
}

static void menu_select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data ) {
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet lang = TupletCString(KEY_TYPE, "language");
    dict_write_tuplet(iter, &lang);
    
    switch(cell_index->row) {
        case 0: {
            Tuplet lang_d = TupletCString(KEY_DATA, "en");
            dict_write_tuplet(iter, &lang_d);
            break;
        }
        case 1: {
            Tuplet lang_d = TupletCString(KEY_DATA, "fr");
            dict_write_tuplet(iter, &lang_d);
            break;
        }
        case 2: {
            Tuplet lang_d = TupletCString(KEY_DATA, "de");
            dict_write_tuplet(iter, &lang_d);
            break;
        }
        case 3: {
            Tuplet lang_d = TupletCString(KEY_DATA, "it");
            dict_write_tuplet(iter, &lang_d);
            break;
        }
    }
    
    dict_write_end(iter);
    
    app_message_outbox_send();
    
    window_stack_pop(true);
}

static void handle_window_load(Window *window) {
    menu_layer_set_callbacks(main_menu_layer, NULL, (MenuLayerCallbacks) {
        .draw_row = menu_draw_row_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .select_click = menu_select_click_callback,
    });
}

static void handle_window_unload(Window* window) {
    destroy_ui();
}

void show_language_menu(void) {
    initialise_ui();
    window_set_window_handlers(s_window, (WindowHandlers) {
        .load = handle_window_load,
        .unload = handle_window_unload,
    });
    window_stack_push(s_window, true);
}

void hide_language_menu(void) {
    window_stack_remove(s_window, true);
}
