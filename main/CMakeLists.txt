idf_component_register(SRCS "main.c" "http_server.c" "spiffs.c"
                    INCLUDE_DIRS ".")

spiffs_create_partition_image(spiffs "./html" FLASH_IN_PROJECT)
