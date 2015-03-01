#include "caffeine_main.h"
#include "caffeine_settings.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_28_bold;
static GFont s_res_gothic_28;
static TextLayer *s_textlayer_1;
static TextLayer *s_textlayer_2;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, 0);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_gothic_28 = fonts_get_system_font(FONT_KEY_GOTHIC_28);
  // s_textlayer_1
  s_textlayer_1 = text_layer_create(GRect(6, 63, 104, 36));
  text_layer_set_background_color(s_textlayer_1, GColorClear);
  text_layer_set_text_color(s_textlayer_1, GColorWhite);
  text_layer_set_text(s_textlayer_1, "000mg");
  text_layer_set_text_alignment(s_textlayer_1, GTextAlignmentRight);
  text_layer_set_font(s_textlayer_1, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_1);
  
  // s_textlayer_2
  s_textlayer_2 = text_layer_create(GRect(3, 2, 87, 28));
  text_layer_set_background_color(s_textlayer_2, GColorClear);
  text_layer_set_text_color(s_textlayer_2, GColorWhite);
  text_layer_set_text(s_textlayer_2, "Caffeine");
  text_layer_set_font(s_textlayer_2, s_res_gothic_28);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_2);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_textlayer_1);
  text_layer_destroy(s_textlayer_2);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_caffeine_main(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_caffeine_main(void) {
  window_stack_remove(s_window, true);
}
