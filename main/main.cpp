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

	/*
	// Global time
	Integer t = Integer(0);		

	// Base layer
	// BaseLayer rendered_layer = Layer(NUM_LED, &strip);



	// Background
	Layer background = Layer(NUM_LED);
	Integer backPos = Integer(0);
	background.setPosition(&backPos);
//	Lin bh = Lin(- 0.5, 360, &t);

	// Particle
	Layer particle = Layer(1);


	Layer* layers[2] = {&background, &particle};
	Sequence seq = Sequence(layers, 2);
	Integer duration = Integer(30);

	// Background setup
	Number speed = Number(1);
	Product h = Product(&speed, seq.getLocalTime());
	Number s = Number(1);
	Number b = Number(0.01);
	hsb color = hsb(&h, &s, &b);
	background.setColor(&color);

	// Particle setup
	Lin particleSpeed = Lin(0.001, 0, seq.getLocalTime());
	Product particlePosition = Product(&particleSpeed, seq.getLocalTime());
	Lin ph = Lin(360 / NUM_LED, 0, &particlePosition);
	Number ps = Number(1);
	Number pb = Number(0.9);
	hsb particleColor = hsb(&ph, &ps, &pb);
	particle.setPosition(&particlePosition);
	particle.setColor(&particleColor);

	Integer endPos = Integer(NUM_LED);
	Sup stopCondition = Sup(&particlePosition, &endPos);
	seq.setStopCondition(&stopCondition);

	seq.run(&strip);
	*/
	ESP_LOGI("MEM", "Init %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
	Animation* animation = example1(NUM_LED);
	ESP_LOGI("MEM", "Run %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));
	animation->run(&strip);
	ESP_LOGI("MEM", "End %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));

	delete animation;
	ESP_LOGI("MEM", "Clear %i", heap_caps_get_free_size(MALLOC_CAP_8BIT));

	/*
	while(particlePosition.yield() < NUM_LED) {
		particle.setPosition(particlePosition.yield());
		particle.setPixel(0, hsb_pixel(h.yield(), 1, 0.8));

		for(int i = 0; i < background.getPixelCount(); i++) {
			background.setPixel(i, hsb_pixel(abs((int) bh.yield()) % 360, 1, 0.4));
		}

		merge(&rendered_layer, &background);
		merge(&rendered_layer, &particle);

		rendered_layer.render();

		strip.show();

		t.increment(1);
	}
	*/
}
