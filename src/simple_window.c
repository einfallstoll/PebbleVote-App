#include "simple_window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_18_bold;
static TextLayer *simple_text_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, false);
  
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  // simple_text_layer
  simple_text_layer = text_layer_create(GRect(20, 40, 100, 60));
  text_layer_set_text(simple_text_layer, "Text layer");
  text_layer_set_text_alignment(simple_text_layer, GTextAlignmentCenter);
  text_layer_set_font(simple_text_layer, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)simple_text_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(simple_text_layer);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
    destroy_ui();
}

Window* show_simple_window(const char* message) {    
    initialise_ui();
    text_layer_set_text(simple_text_layer, message);
    window_set_window_handlers(s_window, (WindowHandlers) {
        .unload = handle_window_unload,
    });
    window_stack_push(s_window, true);
    return s_window;
}

void hide_simple_window(void) {
    window_stack_remove(s_window, true);
}
