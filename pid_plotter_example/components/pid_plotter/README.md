# PID-Plotter

* ESP-IDF component for [pid-tuning-gui](https://github.com/VedantParanjape/pid-tuning-gui). This transports data, between the plotter and esp device.

# Requirements

* [logger](https://github.com/VedantParanjape/logger)  

# Installation

    cd <your_esp_idf_project>
    mkdir components
    cd components
    git clone https://github.com/VedantParanjape/logger   
    git clone https://github.com/VedantParanjape/pid-plotter-component pid_plotter

*Change CMakeList.txt to add the line given below:*   

    set(EXTRA_COMPONENT_DIRS <path_to_component_folder>)

# How to use

* Set UDP and TCP server IP address and port in menuconfig, under component config
* Set wifi ssid and password to use.    
* include "pid_plotter.h"

* `plotter()` must be called in app_main  
* `send_to_queue(pid_data_struct)` must be used to push pid_data struct to the message queue, by passing such a struct to this function, this data will be sent to client for plotting.  
* `pid_const_read()` returns the pid_const struct received from user. 

# Working

* PID Constants (Kp, Ki, Kd, and setpoint) are received by esp32, by connecting to a tcp server.
* TCP server should send the values as a json string.
```
{
    "Kp" : 1.0,
    "Ki" : 2.0,
    "Kd" : 3.0,
    "SetPoint" : 4.0
}

PID constants json format
```
* Calculated PID values (P, I, D, current, error) are sent by esp32 through udp, sent to a udp server.
* Values are sent as a json string through UDP.
```
{
    "P" : 1.0,
    "I" : 2.0,
    "D" : 3.0,
    "current" : 4.0,
    "error" : 5.0
}

PID data json format
```
# Example Code

```C
#include "pid_plotter.h"

void broad()
{
    struct pid_terms dt;
    dt.current = 1.00;
    dt.error = 2.00;
    dt.P = 3.00;
    dt.I = 4.00;
    dt.D = 5.00;
    
    while(1)
    {
        esp_err_t err = send_to_queue(dt);
        err = send_to_queue(dt);
        logD("main", "%f", pid_const_read().setpoint);
        vTaskDelay(10);
    }
}

void app_main(void)
{
    xTaskCreate(broad, "send", 4096, NULL, 1, NULL);
    plotter();
}
```
# Detailed documentation

* https://vedantparanjape.github.io/pid-plotter-component/ 
