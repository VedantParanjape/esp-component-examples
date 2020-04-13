PID Plotter examples
======================

Example app for ESP-IDF Component ![pid-plotter](https://github.com/VedantParanjape/pid-plotter-component)

## Instructions

```
idf.py menuconfig
idf.py flash
```

![](https://github.com/VedantParanjape/esp-component-examples/raw/master/assets/pid_plotter_example_edited.gif)

## Usage

### How to use

* Set UDP and TCP server IP address and port in menuconfig, under component config
* Set wifi ssid and password to use.    
* include "pid_plotter.h"

* `plotter()` must be called in app_main  
* `send_to_queue(pid_data_struct)` must be used to push pid_data struct to the message queue, by passing such a struct to this function, this data will be sent to client for plotting.  
* `pid_const_read()` returns the pid_const struct received from user. 

### Working

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

## Documentation

* ![Refer to component docs for further details](https://github.com/VedantParanjape/pid-plotter-component/blob/master/README.md)
