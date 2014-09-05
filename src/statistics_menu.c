#include "statistics_menu.h"
#include "statistics_detail.h"
#include <pebble.h>
#include "key_mappings.h"
#include "simple_window.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *statistics_menu_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  // statistics_menu_layer
  statistics_menu_layer = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(statistics_menu_layer, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)statistics_menu_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(statistics_menu_layer);
}
// END AUTO-GENERATED UI CODE

static DictionaryIterator *receivedStatisticsData;

static void menu_draw_row_callback(GContext *ctx, const Layer *cell_layer, MenuIndex *cell_index, void *callback_context) {
    int index = (cell_index->row + 1) * 10;
    Tuple *timestamp = dict_find(receivedStatisticsData, ++index);
    Tuple *either = dict_find(receivedStatisticsData, ++index);
    Tuple *or = dict_find(receivedStatisticsData, ++index);
    Tuple *either_count = dict_find(receivedStatisticsData, ++index);
    Tuple *or_count = dict_find(receivedStatisticsData, ++index);
    Tuple *total = dict_find(receivedStatisticsData, ++index);
    menu_cell_basic_draw(ctx, cell_layer, timestamp->value->cstring, total->value->cstring, NULL);
}

static uint16_t menu_get_num_rows_callback(struct MenuLayer *menu_layer, uint16_t section_index, void *callback_context) {
    Tuple *count = dict_find(receivedStatisticsData, KEY_COUNT);
    return count->value->int8;
}

static void menu_select_click_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data ) {
    int index = (cell_index->row + 1) * 10;
    Tuple *timestamp = dict_find(receivedStatisticsData, ++index);
    Tuple *either = dict_find(receivedStatisticsData, ++index);
    Tuple *or = dict_find(receivedStatisticsData, ++index);
    Tuple *either_count = dict_find(receivedStatisticsData, ++index);
    Tuple *or_count = dict_find(receivedStatisticsData, ++index);
    Tuple *total = dict_find(receivedStatisticsData, ++index);
    
    show_statistics_detail(either->value->cstring, or->value->cstring, either_count->value->cstring, or_count->value->cstring);
}

static void handle_window_load(Window *window) {
    menu_layer_set_callbacks(statistics_menu_layer, NULL, (MenuLayerCallbacks) {
        .draw_row = menu_draw_row_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .select_click = menu_select_click_callback,
    });
}

static void handle_window_unload(Window* window) {
    destroy_ui();
}

void in_received_handler_statistics(DictionaryIterator *received, void *context) {
    Tuple *status = dict_find(received, KEY_STATUS);
    Tuple *type = dict_find(received, KEY_TYPE);
    Tuple *count = dict_find(received, KEY_COUNT);
    if (status && strcmp(status->value->cstring, "success") == 0 && type) {
        if (strcmp(type->value->cstring, "statistics") == 0 && count) {
            APP_LOG(APP_LOG_LEVEL_INFO, "Statistics received");
            if (count->value->int8 == 0) {
                window_stack_pop(true);
                show_simple_window("No questions available");
            } else {
                receivedStatisticsData = received;
                
                window_stack_pop(true);
                initialise_ui();
                window_set_window_handlers(s_window, (WindowHandlers) {
                    .unload = handle_window_unload,
                    .load = handle_window_load,
                });
                window_stack_push(s_window, true);
            }
        }
    } else {
        window_stack_pop(true);
        show_simple_window("An error occured.");
    }
}

void show_statistics_menu(int personal) {
    show_simple_window("Data is being loaded...");
    
    app_message_register_inbox_received(in_received_handler_statistics);
    
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);
    
    Tuplet type = TupletCString(KEY_TYPE, "statistics");
    dict_write_tuplet(iter, &type);
    
    if (personal == 1) {
        Tuplet subtype = TupletCString(KEY_SUBTYPE, "statistics");
        dict_write_tuplet(iter, &subtype);
    } else {
        Tuplet subtype = TupletCString(KEY_SUBTYPE, "voted");
        dict_write_tuplet(iter, &subtype);
    }
    
    
    Tuplet inbox = TupletInteger(KEY_INBOX, app_message_inbox_size_maximum());
    dict_write_tuplet(iter, &inbox);
    
    dict_write_end(iter);
    
    app_message_outbox_send();
}

void hide_statistics_menu(void) {
    window_stack_remove(s_window, true);
}
