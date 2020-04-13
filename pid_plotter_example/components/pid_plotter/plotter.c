#include "plotter.h"


/**
 * @brief Wrapper function to run the plotter functionality on a separate core
**/
void plotter()
{
    ESP_ERROR_CHECK(init_queue());
    init_transport();
    
    xTaskCreatePinnedToCore(pid_const_transport, "tcp_pid_receive", 4096, NULL, 1, &pid_const_transport_handle, 0);
    xTaskCreatePinnedToCore(pid_transport, "udp_pid_send", 4096, NULL, 2, &pid_transport_handle, 1);
}