#include "statistics_detail.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static TextLayer *either_text_layer;
static TextLayer *or_text_layer;
static TextLayer *either_count_text_layer;
static TextLayer *or_count_text_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  // either_text_layer
  either_text_layer = text_layer_create(GRect(5, 5, 100, 45));
  text_layer_set_text(either_text_layer, "EITHER_EITHER EITHER_EITHER EITHER_EITHER");
  layer_add_child(window_get_root_layer(s_window), (Layer *)either_text_layer);
  
  // or_text_layer
  or_text_layer = text_layer_create(GRect(5, 55, 100, 45));
  text_layer_set_text(or_text_layer, "OR_OR_OR_OR OR_OR_OR_OR OR_OR_OR_OR");
  layer_add_child(window_get_root_layer(s_window), (Layer *)or_text_layer);
  
  // either_count_text_layer
  either_count_text_layer = text_layer_create(GRect(110, 5, 30, 15));
  text_layer_set_text(either_count_text_layer, "1000");
  layer_add_child(window_get_root_layer(s_window), (Layer *)either_count_text_layer);
  
  // or_count_text_layer
  or_count_text_layer = text_layer_create(GRect(110, 55, 30, 15));
  text_layer_set_text(or_count_text_layer, "1000");
  layer_add_child(window_get_root_layer(s_window), (Layer *)or_count_text_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(either_text_layer);
  text_layer_destroy(or_text_layer);
  text_layer_destroy(either_count_text_layer);
  text_layer_destroy(or_count_text_layer);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
    destroy_ui();
}

void show_statistics_detail(const char *either, const char *or, const char *either_count, const char *or_count) {
    initialise_ui();
    
    text_layer_set_text(either_text_layer, either);
    text_layer_set_text(either_count_text_layer, either_count);
    
    text_layer_set_text(or_text_layer, or);
    text_layer_set_text(or_count_text_layer, or_count);
    
    window_set_window_handlers(s_window, (WindowHandlers) {
        .unload = handle_window_unload,
    });
    window_stack_push(s_window, true);
}

void hide_statistics_detail(void) {
    window_stack_remove(s_window, true);
}
