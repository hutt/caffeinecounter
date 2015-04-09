#include "settings.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *settings_window;
static MenuLayer *s_settings_layer;

static void click_config_provider(void *context){
  //
}

static void initialise_ui(void) {
  settings_window = window_create();
  window_set_background_color(settings_window, GColorBlack);
  window_set_fullscreen(settings_window, false);
  
  // s_settings_layer
  s_settings_layer = menu_layer_create(GRect(0, 0, 144, 152));
  menu_layer_set_click_config_onto_window(s_settings_layer, settings_window);
  layer_add_child(window_get_root_layer(settings_window), (Layer *)s_settings_layer);
  
  menu_layer_set_click_config_onto_window(s_settings_layer, settings_window);
  window_set_click_config_provider(settings_window, click_config_provider);
  
}

static void destroy_ui(void) {
  window_destroy(settings_window);
  menu_layer_destroy(s_settings_layer);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_settings(void) {
  initialise_ui();
  window_set_window_handlers(settings_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(settings_window, true);
}

void hide_settings(void) {
  window_stack_remove(settings_window, true);
}
