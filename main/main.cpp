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

class Class1 {
	public:
		Class1(int i){this->i = i;};
		int i;
		~Class1(){ESP_LOGI("TEST", "Class 1 Destroyed : %p", this);};
};

class Class2 {
	public:
		Class2(std::shared_ptr<Class1> p) {
			this->p = p;
			ESP_LOGI("TEST", "c1 use count : %li", p.use_count());
			ESP_LOGI("TEST", "this c1 use count : %li", this->p.use_count());
		};
		std::shared_ptr<Class1> p;
		~Class2(){ESP_LOGI("TEST", "Delete class 2 %p", this);};
};

Class2* buildClass2() {
	std::shared_ptr<Class1> c1 = std::shared_ptr<Class1>(new Class1(10));
	ESP_LOGI("TEST", "c1 use count : %li", c1.use_count());
	Class2* c2 = new Class2(c1);
	Class2* c2_2 = new Class2(c1);
	delete c2_2;
	return c2;
}

void app_main()
{

	WS2812 strip = WS2812((gpio_num_t) DATA_PIN, NUM_LED, RMT_CHANNEL_1);
	ESP_LOGI("MEM", "Init %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
	Animation* animation = example1(NUM_LED);
	ESP_LOGI("MEM", "Run %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
	animation->run(&strip);
	ESP_LOGI("MEM", "End %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));

	delete animation;
	ESP_LOGI("MEM", "Clear %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));

	/*
	ESP_LOGI("MEM", "Init %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
	Class2* c2 = buildClass2();
	ESP_LOGI("MEM", "Run %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
	ESP_LOGI("TEST", "%i", c2->p.get()->i);
	delete c2;
	ESP_LOGI("MEM", "End %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
	*/
}
