#include <memory>
#include <stdio.h>
#include <cmath>
#include "pixled.h"
#include "examples.h"

#include "freertos/task.h"
#include "esp_heap_caps.h"

#define DATA_PIN 12
#define NUM_LED 120
#define CHASER_LENGTH 10

#include "esp_log.h"


#define PERIOD 2000
#define WIDTH 120
#define HEIGHT 1
#define INTENSITY 0.8

extern "C" {
	void app_main();
}

void app_main()
{

	WS2812 strip = WS2812((gpio_num_t) DATA_PIN, NUM_LED, RMT_CHANNEL_1);
	while(true) {
		ESP_LOGI("MEM", "Init %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
//		Animation* animation = example5(60);
//		Animation* animation = example4(60, 5, 1);
		Animation* animation1 = example2_2(WIDTH, HEIGHT, 30, 20, INTENSITY, PERIOD);
		ESP_LOGI("MEM", "Run %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
		animation1->run(&strip);
		ESP_LOGI("MEM", "End %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));

		delete animation1;

		Animation* animation2 = example2(WIDTH, HEIGHT, 50, 10, INTENSITY, PERIOD);

		ESP_LOGI("MEM", "Run %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
		animation2->run(&strip);
		ESP_LOGI("MEM", "End %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));

		delete animation2;

		Animation* animation4 = example4(WIDTH, HEIGHT, 10, INTENSITY, PERIOD);

		ESP_LOGI("MEM", "Run %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
		animation4->run(&strip);
		ESP_LOGI("MEM", "End %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));

		delete animation4;

		Animation* animation5 = example5(WIDTH, HEIGHT, PERIOD);

		ESP_LOGI("MEM", "Run %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
		animation5->run(&strip);
		ESP_LOGI("MEM", "End %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));

		delete animation5;

		ESP_LOGI("MEM", "Clear %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
	}

}
