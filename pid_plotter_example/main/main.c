#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_netif.h"
#include "pid_plotter.h"
#include <math.h>


void send_to_plotter()
{
    struct pid_terms dt;

    int count = 0;
    while(1)
    {
        // output the pid_const setpoint
        logD("main", "%f", pid_const_read().setpoint); 

        // Assign various values to pid terms
        dt.current = tan((double)count/0.0001); 
	    dt.error = sin((double)count/0.0001);
	    dt.P = cos((double)count/0.0001);
	    dt.I = atan((double)count/0.0001);
	    dt.D = sin((double)count/0.0001);
        count++;

        // Send the terms to the plotter
        send_to_queue(dt);
        // Wait for 10 ms
	    vTaskDelay(10);
    }
}

void app_main(void)
{
    // Start send_to_plotter task
    xTaskCreate(send_to_plotter, "send_to_plotter", 4096, NULL, 1, NULL);
    
    // Start the task that manages the plotter 
    plotter();
}
