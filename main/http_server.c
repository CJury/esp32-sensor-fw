/**
 * @file http_server.c
 * @brief 
 * @author Christopher Jury
 * @version 
 * @date 2023-06-18
 */

#include "esp32_sensor_fw.h"

httpd_handle_t start_webserver(void)
{
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();

	httpd_handle_t server = NULL;

	/* Start the server */
	if (httpd_start(&server, &config) == ESP_OK)
	{

	}
	return server;
}

void stop_webserver(httpd_handle_t server)
{
	if (server)
	{
		httpd_stop(server);
	}
}
