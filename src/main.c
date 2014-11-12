#include <pebble.h>
#include "s_counter.h"

int main() {
    init();
    show_s_counter();
    app_event_loop();
    end();
    return 0;
}
 