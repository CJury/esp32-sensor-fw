/**
 * @file http_server.c
 * @brief 
 * @author Christopher Jury
 * @version 
 * @date 2023-06-18
 */

#include "esp_err.h"
#include "esp_http_server.h"
#include "esp_log.h"
#include "esp32_sensor_fw.h"

const char * TAG = "http_server";
static esp_err_t serve_html_file(httpd_req_t * req, const char * file)
{
	size_t size;
	char * buf;

	if (spiffs_read_file_size(file, &size) != ESP_OK)
	{
		httpd_resp_send_500(req);
		return ESP_FAIL;
	};

	buf = malloc(size);
	if (!buf)
	{
		ESP_LOGE(TAG, "%s: malloc(%d) failed.", __FUNCTION__, size);
		httpd_resp_send_500(req);
		return ESP_FAIL;
	}

	if (spiffs_read_file(file, buf, size) != ESP_OK)
	{
		free(buf);
		httpd_resp_send_500(req);
		return ESP_FAIL;
	}

	/* Ensure buffer is null terminated */
	buf[size] = 0;
	httpd_resp_send(req, buf, HTTPD_RESP_USE_STRLEN);

	free(buf);
	return ESP_OK;
}

static esp_err_t get_index(httpd_req_t * req)
{
	return serve_html_file(req, "/spiffs/index.html");
}
httpd_uri_t root_get = {
	.uri = "/",
	.method = HTTP_GET,
	.handler = get_index,
	.user_ctx = NULL,
};
httpd_handle_t start_webserver(void)
{
	ESP_LOGI(TAG, "Starting http server");
	httpd_config_t config = HTTPD_DEFAULT_CONFIG();

	httpd_handle_t server = NULL;

	/* Setup the SPIFFS filesystem */
	spiffs_init();
	/* Start the server */
	if (httpd_start(&server, &config) == ESP_OK)
	{
		httpd_register_uri_handler(server, &root_get);
	}

	return server;
}

void stop_webserver(httpd_handle_t server)
{
	if (server)
	{
		httpd_stop(server);
	}

	spiffs_end();
	ESP_LOGI(TAG, "Stopped http server");
}
