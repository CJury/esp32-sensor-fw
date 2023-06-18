/**
 * @file spiffs.c
 * @brief SPIFFS filesystem handling
 *
 * Meant for serving static html with a http server so only provides read capabiity
 *
 * @author Christopher Jury
 * @version 
 * @date 2023-06-18
 */

#include <sys/stat.h> 

#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"

#include "esp32_sensor_fw.h"

static const char * TAG = "spiffs";

esp_vfs_spiffs_conf_t conf = {
	.base_path = "/spiffs",
	.partition_label = "spiffs",
	.max_files = 5,
	.format_if_mount_failed = true
};

esp_err_t spiffs_read_file_size(const char * file, size_t * size)
{
	if (!file)
	{
		ESP_LOGE(TAG, "%s: file is null", __FUNCTION__);
		return ESP_FAIL;
	}

	if (!size)
	{
		ESP_LOGE(TAG, "%s: size is null", __FUNCTION__);
		return ESP_FAIL;
	}

	FILE * fptr = fopen(file, "r");
	if (fptr == NULL)
	{
		ESP_LOGE(TAG, "%s: failed to open file %s", __FUNCTION__, file);
		return ESP_FAIL;
	}

	fseek(fptr, 0L, SEEK_END);
	*size = ftell(fptr);
	fseek(fptr, 0L, SEEK_SET);

	fclose(fptr);

	return ESP_OK;
}

esp_err_t spiffs_read_file(const char * file, char * buf, size_t buf_size) 
{
	if (!file)
	{
		ESP_LOGE(TAG, "%s: file is null", __FUNCTION__);
		return ESP_FAIL;
	}

	if (!buf)
	{
		ESP_LOGE(TAG, "%s: buf is null", __FUNCTION__);
		return ESP_FAIL;
	}

	FILE * fptr = fopen(file, "r");

	if (fptr == NULL)
	{
		ESP_LOGE(TAG, "%s: failed to open file %s", __FUNCTION__, file);
		return ESP_FAIL;
	}

	const size_t count = 1;
	const size_t ret = fread(buf, buf_size, count, fptr);

	if (ret != count) {
		if (feof(fptr))
		{
			ESP_LOGE(TAG, "%s: Unexpected end of file reading %s", __FUNCTION__, file);
		} else if (ferror(fptr)) 
		{
			ESP_LOGE(TAG, "%s: Error reading %s", __FUNCTION__, file);
		}
		fclose(fptr);
		return ESP_FAIL;
		
	}

	fclose(fptr);
	return ESP_OK;
}

esp_err_t spiffs_init(void) 
{
	ESP_LOGI(TAG, "Initializing SPIFFS");

	esp_err_t ret = esp_vfs_spiffs_register(&conf);

	if (ret == ESP_FAIL) 
	{
		ESP_LOGE(TAG, "Failed to mount or format filesystem");
	} else if (ret == ESP_ERR_NOT_FOUND) 
	{
		ESP_LOGE(TAG, "Failed to find spiffs partition");
	}

	return ret;
}

void spiffs_end(void)
{
	esp_vfs_spiffs_unregister(conf.partition_label);
	ESP_LOGI(TAG, "SPIFFS unmounted");
}
