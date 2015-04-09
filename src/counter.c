#include <pebble.h>
#include "counter.h"
//#include "caffeine.h"
//#include "add.h"
#include "settings.h"
//#include "remove.h"

static Window *counter_window;
static GFont s_res_gothic_28_bold;
static TextLayer *s_heading;
static TextLayer *s_amount;
static TextLayer *s_note;
static ActionBarLayer *s_actionbar;
static GBitmap *action_icon_plus;
static GBitmap *action_icon_settings;
static GBitmap *action_icon_minus;

// CLICK HANDLERS
static void up_click_handler(ClickRecognizerRef recognizer, void *context){
  
}

static void select_click_handler(ClickRecognizerRef recognizer, void *context){
  show_settings();
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context){
  
}

static void click_config_provider(void *context){
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

/*
static void update_display(void) {
  
}

static void update_counter(void) {
  
  int timeElapsed = getTimeElapsed(now);
  double amount   = getCaffeineAmount(timeElapsed);
  update_display();
}

*/

static void tick_handler(struct tm *t, TimeUnits unitschanged){
  //update_counter();
}

static void initialise_ui(void) {
  counter_window = window_create();

  // define differences between platforms
  #ifdef PBL_COLOR //Basalt
    //Background color
    GColor backgroundColor = GColorWindsorTan;
  
    //Text
    GColor textColor = GColorWhite;
  
    //ActionBar
    GColor actionbarColor = GColorBlack;
  #else //Aplite
    //Background color
    GColor backgroundColor = GColorBlack;
    
    //Text
    GColor textColor = GColorWhite;
  
    //Actionbar
    GColor actionbarColor = GColorBlack;
  #endif

  window_set_background_color(counter_window, backgroundColor);
  window_set_fullscreen(counter_window, false);
  
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_heading
  s_heading = text_layer_create(GRect(6, 0, 133, 37));
  text_layer_set_background_color(s_heading, GColorClear);
  text_layer_set_text_color(s_heading, textColor);
  text_layer_set_text(s_heading, "Caffeine");
  text_layer_set_font(s_heading, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(counter_window), (Layer *)s_heading);
  
  // s_amount
  s_amount = text_layer_create(GRect(6, 40, 113, 33));
  text_layer_set_background_color(s_amount, GColorClear);
  text_layer_set_text_color(s_amount, textColor);
  text_layer_set_text(s_amount, "0000mg");
  text_layer_set_text_alignment(s_amount, GTextAlignmentLeft);
  text_layer_set_font(s_amount, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(counter_window), (Layer *)s_amount);
  
  // s_note
  s_note = text_layer_create(GRect(6, 111, 114, 33));
  text_layer_set_background_color(s_note, GColorClear);
  text_layer_set_text_color(s_note, textColor);
  text_layer_set_text(s_note, "approximate amount of caffeine");
  text_layer_set_text_alignment(s_note, GTextAlignmentLeft);
  layer_add_child(window_get_root_layer(counter_window), (Layer *)s_note);
  
  // s_actionbar

  // Icons
  action_icon_plus = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PLUS_WHITE);
  action_icon_settings = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SETTINGS_WHITE);
  action_icon_minus = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MINUS_WHITE);
  
  s_actionbar = action_bar_layer_create();
  action_bar_layer_add_to_window(s_actionbar, counter_window);
  action_bar_layer_set_click_config_provider(s_actionbar, click_config_provider);
  
  action_bar_layer_set_background_color(s_actionbar, actionbarColor);
  action_bar_layer_set_icon(s_actionbar, BUTTON_ID_UP, action_icon_plus);
  action_bar_layer_set_icon(s_actionbar, BUTTON_ID_SELECT, action_icon_settings);
  action_bar_layer_set_icon(s_actionbar, BUTTON_ID_DOWN, action_icon_minus);
  
  // Where's the time?
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void destroy_ui(void) {
  window_destroy(counter_window);
  text_layer_destroy(s_heading);
  text_layer_destroy(s_amount);
  text_layer_destroy(s_note);

  gbitmap_destroy(action_icon_plus);
  gbitmap_destroy(action_icon_settings);
  gbitmap_destroy(action_icon_minus);
  action_bar_layer_destroy(s_actionbar);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
  tick_timer_service_unsubscribe();
}

void show_counter(void) {
  initialise_ui();
  window_set_window_handlers(counter_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(counter_window, true);
}

void hide_counter(void) {
  window_stack_remove(counter_window, true);
}
