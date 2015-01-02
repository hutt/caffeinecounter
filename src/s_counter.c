#include <pebble.h>
#include "s_counter.h"

// Persistent Keys
#define NUM_CAFFEINE_PKEY 100
// Default
#define NUM_CAFFEINE_DEFAULT 0
// time of last caffeine intake  
#define DATE_LAST_INTAKE_PKEY 1

static Window *s_window;
static GFont s_res_bitham_30_black;
static GFont s_res_gothic_28_bold;
static TextLayer *s_heading;
static TextLayer *s_caffeine_layer;
static TextLayer *s_info_layer;

static int halflife=300;
static int caff_time0=1397412233;
static int num_caffeine;

float caffeine() {
    time_t now1 = time(NULL);
    int timer_s=now1;
    float x=-(timer_s-caff_time0)/(halflife*86.56170245);
    float term=x;
    float answer=x;		
    if (timer_s-caff_time0<172800) {
        int i=2;
        float error=0.001;				
        while (term > error || term < -error)
        {
            int work = i;
            term =  (term * x)/work;
            answer = answer + (term);
            i++;
        }
    }
    else {
        num_caffeine=0;
        caff_time0=timer_s;
    }

    answer = answer + 1.0;

    answer = num_caffeine * answer;
    if (answer<0) answer = 0;
    return(answer);
}

void update_screen(void){
  //get actual count
    
  //Update caffeine count text
  static char caffeine_count_text[40];
  snprintf(caffeine_count_text, sizeof(caffeine_count_text), "%umg", num_caffeine);
  text_layer_set_text(s_caffeine_layer, caffeine_count_text);
  
}

static void update_intake(void){
    caff_time0 = time(NULL);
}

static void long_select_click_handler(ClickRecognizerRef recognizer, void *context) {
    num_caffeine=0;
    update_intake();
    update_screen();
}

static void single_up_click_handler(ClickRecognizerRef recognizer, void *context) {
  //Increment caffeine count
  num_caffeine=num_caffeine+10;
  //Save time
  update_intake();
  //Update screen
  update_screen();
}

static void long_up_click_handler(ClickRecognizerRef recognizer, void *context) {
    num_caffeine = num_caffeine+100;
    update_intake();
    update_screen();
    
  //vibes_short_pulse();
  
}

static void single_down_click_handler(ClickRecognizerRef recognizer, void *context) {
  //Decrement caffeine count
  if (num_caffeine < 10) {
    // can't be less than 0
    return;
  }else{
    num_caffeine=num_caffeine-10;
    //vibes_long_pulse(); -- rawrr.
    update_intake();
    update_screen();   
  }
}

static void long_down_click_handler(ClickRecognizerRef recognizer, void *context) {
    if(num_caffeine < 100){
        return;
    }else{
        num_caffeine = num_caffeine-100;
        update_intake();
        update_screen();
    }
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    num_caffeine = caffeine();
    update_screen();
}

static void click_config_provider(void *context) {
  window_long_click_subscribe(BUTTON_ID_SELECT, 800, long_select_click_handler, NULL);
  window_single_click_subscribe(BUTTON_ID_UP, single_up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, single_down_click_handler);
  window_long_click_subscribe(BUTTON_ID_UP, 300, long_up_click_handler, NULL);
  window_long_click_subscribe(BUTTON_ID_DOWN, 300, long_down_click_handler, NULL);
}

void init (void){
    //Update every minute
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
    //Read caffeine count
    num_caffeine = persist_exists(NUM_CAFFEINE_PKEY) ? persist_read_int(NUM_CAFFEINE_PKEY) : NUM_CAFFEINE_DEFAULT;
    //Read last caffeine intake
    caff_time0 = persist_exists(DATE_LAST_INTAKE_PKEY) ? persist_read_int(DATE_LAST_INTAKE_PKEY) : time(NULL);
}

void end(void){
    //Things to save before exiting app
    persist_write_int(NUM_CAFFEINE_PKEY, (num_caffeine+1));
    persist_write_int(DATE_LAST_INTAKE_PKEY, caff_time0);
    tick_timer_service_unsubscribe();
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
  // text_layer_set_text(s_info_layer, "00:00 until < 5mg");
  text_layer_set_text(s_info_layer, "");
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
