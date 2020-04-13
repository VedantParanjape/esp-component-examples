#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi_logger.h"


void app_main(void)
{
    start_wifi_logger();
    
    while(1)
    {
        
        wifi_log_e("test", "%s: %d", "free heap size", esp_get_free_heap_size());
        wifi_log_w("test", "%s: %d", "free min heap size", esp_get_minimum_free_heap_size());
    
        vTaskDelay(100);
    }
}
