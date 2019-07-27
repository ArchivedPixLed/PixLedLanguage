#include <memory>
#include <stdio.h>
#include <cmath>
#include "pixled.h"
#include "examples.h"

#include "freertos/task.h"
#include "esp_heap_caps.h"

#define DATA_PIN 12
#define NUM_LED 256
#define CHASER_LENGTH 10

#include "esp_log.h"

extern "C" {
	void app_main();
}

void app_main()
{

	WS2812 strip = WS2812((gpio_num_t) DATA_PIN, NUM_LED, RMT_CHANNEL_1);
	while(true) {
		ESP_LOGI("MEM", "Init %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
		Animation* animation = example4(16, 16);
		ESP_LOGI("MEM", "Run %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
		animation->run(&strip);
		ESP_LOGI("MEM", "End %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));

		delete animation;
		ESP_LOGI("MEM", "Clear %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
	}

}
