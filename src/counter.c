#include "counter.h"
#include <pebble.h>

static Window *s_window;
static GFont s_res_bitham_30_black;
static GFont s_res_gothic_28_bold;
static TextLayer *s_heading;
static TextLayer *s_amount;
static TextLayer *s_note;


// CLICK HANDLERS
static void up_click_handler(ClickRecognizerRef, void *context){
  
}

static void select_click_handler(ClickRecognizerRef, void *context){
  
}

static void down_click_handler(ClickRecognizerRef, void *context){
  
}

static void click_config_provider(void *context){
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void initialise_ui(void) {
  s_window = window_create();
  
#ifdef PBL_COLOR
  window_set_background_color(s_window, GColorWindsorTan);
#else
  window_set_background_color(s_window, GColorBlack);
#endif
  
  window_set_fullscreen(s_window, false);
  
  // Click config provider
  window_set_click_config_provider(s_window, click_config_provider);
  
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_heading
  s_heading = text_layer_create(GRect(0, 0, 133, 37));
  text_layer_set_background_color(s_heading, GColorClear);
  text_layer_set_text_color(s_heading, GColorWhite);
  text_layer_set_text(s_heading, "Caffeine");
  text_layer_set_font(s_heading, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_heading);
  
  // s_amount
  s_amount = text_layer_create(GRect(7, 37, 113, 33));
  text_layer_set_background_color(s_amount, GColorClear);
  text_layer_set_text_color(s_amount, GColorWhite);
  text_layer_set_text(s_amount, "0000mg");
  text_layer_set_text_alignment(s_amount, GTextAlignmentRight);
  text_layer_set_font(s_amount, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_amount);
  
  // s_note
  s_note = text_layer_create(GRect(7, 111, 114, 33));
  text_layer_set_background_color(s_note, GColorClear);
  text_layer_set_text_color(s_note, GColorWhite);
  text_layer_set_text(s_note, "approximate amount of caffeine");
  text_layer_set_text_alignment(s_note, GTextAlignmentRight);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_note);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_heading);
  text_layer_destroy(s_amount);
  text_layer_destroy(s_note);
}


/*
static void update_counter(void) {
  
  int timeElapsed = getTimeElapsed(now);
  double amount   = getCaffeineAmount(timeElapsed);
}

*/

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_counter(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_counter(void) {
  window_stack_remove(s_window, true);
}
