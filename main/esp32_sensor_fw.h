/**
 * @file esp32_sensor_fw.h
 * @brief 
 * @author Christopher Jury
 * @version 
 * @date 2023-06-18
 */

#include "esp_http_server.h"
#include "esp_err.h"

#ifndef ESP32_SENSOR_FW_HEADER
#define ESP32_SENSOR_FW_HEADER

httpd_handle_t start_webserver(void);
void stop_webserver(httpd_handle_t server);

esp_err_t spiffs_init(void);
void spiffs_end(void);
esp_err_t spiffs_read_file_size(const char * file, size_t * size);
esp_err_t spiffs_read_file(const char * file, char * buf, size_t buf_size);

#endif /* ifndef ESP32_SENSOR_FW_HEADER */
