#include <pebble.h>
#include "caffeine.h"
#include "caffeine_main.h"
#include "caffeine_settings.h"
    
int main(){
    show_caffeine_main();
    app_event_loop();
    hide_caffeine_main();
    return 0;
}