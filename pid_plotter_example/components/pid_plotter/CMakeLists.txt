idf_component_register(SRCS "json_handler.c" "udp_handler.c" "transport.c" "tcp_handler.c" "plotter.c"
                       INCLUDE_DIRS "include"
                       REQUIRES logger protocol_examples_common nvs_flash json)