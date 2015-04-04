#include <pebble.h>
#include "counter.h"
    
void handle_init(void) {
  show_counter();
}

void handle_deinit(void) {
  hide_counter();
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
