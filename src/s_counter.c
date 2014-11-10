#include <pebble.h>
#include "s_counter.h"
    
// Persistent Keys
#define NUM_CAFFEINE_PKEY 1
// Default
#define NUM_CAFFEINE_DEFAULT 0
// time of last caffeine intake  
    
static Window *s_window;
static GFont s_res_bitham_30_black;
static GFont s_res_gothic_28_bold;
static TextLayer *s_heading;
static TextLayer *s_caffeine_layer;
static TextLayer *s_info_layer;

static int num_caffeine;

/*
static int caffeine(void){
// Half of the initial value after 3h
   int time = localtime(time_t);
   return num_caffeine * (1/2)^(ZEIT/3);
}
*/
void get_elapsed_time(void){
    //elapsed time 
}

void update_screen(void){
  //get actual count
    
  //Update caffeine count text
  static char caffeine_count_text[40];
  snprintf(caffeine_count_text, sizeof(caffeine_count_text), "%umg", num_caffeine);
  text_layer_set_text(s_caffeine_layer, caffeine_count_text);
  
  //update time until 1mg
  if(num_caffeine>=9000){
  static char caffeine_calculator_text[40];
  snprintf(caffeine_calculator_text, sizeof(caffeine_calculator_text), "OMG it's over 9000!");
  text_layer_set_text(s_info_layer, caffeine_calculator_text);
  }
}

static void select_click_handler_long(ClickRecognizerRef recognizer, void *context) {
  num_caffeine=0;
  update_screen();
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  //Increment caffeine count
  num_caffeine=num_caffeine+10;
  //Save time
  
  //vibes_short_pulse();
  update_screen();
}

static void up_click_handler_iterate(ClickRecognizerRef recognizer, void *context) {
  //Increment caffeine count
  num_caffeine=num_caffeine+100;
  //Save time
  
  //vibes_short_pulse();
  update_screen();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  //Decrement caffeine count
  if (num_caffeine <= 0) {
    // can't be less than 0
    return;
  }
  num_caffeine=num_caffeine-10;
  //vibes_long_pulse(); -- rawrr.
  update_screen();
}

static void down_click_handler_decrement(ClickRecognizerRef recognizer, void *context) {
  //Decrement caffeine count
  if (num_caffeine <= 0) {
    // can't be less than 0
    return;
  }
  num_caffeine=num_caffeine-100;
  //vibes_long_pulse(); -- rawrr.
  update_screen();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
  window_long_click_subscribe(BUTTON_ID_SELECT, 800, select_click_handler_long, NULL);
  window_long_click_subscribe(BUTTON_ID_UP, 300, NULL, up_click_handler_iterate);
  window_long_click_subscribe(BUTTON_ID_DOWN, 300, NULL, down_click_handler_decrement);
}

void init (void){
    num_caffeine = persist_exists(NUM_CAFFEINE_PKEY) ? persist_read_int(NUM_CAFFEINE_PKEY) : NUM_CAFFEINE_DEFAULT;
}

void end(void){
    //Things to save before exiting app
    persist_write_int(NUM_CAFFEINE_PKEY, num_caffeine);
}

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, false);
  
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_heading
  s_heading = text_layer_create(GRect(0, 9, 143, 37));
  text_layer_set_background_color(s_heading, GColorClear);
  text_layer_set_text_color(s_heading, GColorWhite);
  text_layer_set_text(s_heading, "Caffeine");
  text_layer_set_text_alignment(s_heading, GTextAlignmentCenter);
  text_layer_set_font(s_heading, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_heading);
  
  // s_caffeine_layer
  s_caffeine_layer = text_layer_create(GRect(34, 67, 75, 32));
  text_layer_set_background_color(s_caffeine_layer, GColorClear);
  text_layer_set_text_color(s_caffeine_layer, GColorWhite);
  text_layer_set_text(s_caffeine_layer, "9001mg");
  text_layer_set_text_alignment(s_caffeine_layer, GTextAlignmentRight);
  text_layer_set_font(s_caffeine_layer, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_caffeine_layer);
  
  // s_info_layer
  s_info_layer = text_layer_create(GRect(3, 133, 136, 15));
  text_layer_set_background_color(s_info_layer, GColorClear);
  text_layer_set_text_color(s_info_layer, GColorWhite);
  text_layer_set_text(s_info_layer, "00:00 until < 5mg");
  text_layer_set_text_alignment(s_info_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_info_layer);
    
 //Get latest counts
  update_screen();
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(s_heading);
  text_layer_destroy(s_caffeine_layer);
  text_layer_destroy(s_info_layer);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_s_counter(void) {
  initialise_ui();
  window_set_click_config_provider(s_window, click_config_provider);
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_s_counter(void) {
  window_stack_remove(s_window, true);
}
