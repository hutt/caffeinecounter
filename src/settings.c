#include "settings.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static MenuLayer *s_settings_layer;
static InverterLayer *s_inverterlayer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
  
  // s_settings_layer
  s_settings_layer = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(s_settings_layer, s_window);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_settings_layer);
  
  // s_inverterlayer
  s_inverterlayer = inverter_layer_create(GRect(0, 0, 144, 152));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_inverterlayer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  menu_layer_destroy(s_settings_layer);
  inverter_layer_destroy(s_inverterlayer);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_settings(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_settings(void) {
  window_stack_remove(s_window, true);
}
