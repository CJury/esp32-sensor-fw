/**
 * @file esp32_sensor_fw.h
 * @brief 
 * @author Christopher Jury
 * @version 
 * @date 2023-06-18
 */

#include "esp_http_server.h"

#ifndef ESP32_SENSOR_FW_HEADER
#define ESP32_SENSOR_FW_HEADER

httpd_handle_t start_webserver(void);
void stop_webserver(httpd_handle_t server);

#endif /* ifndef ESP32_SENSOR_FW_HEADER */
