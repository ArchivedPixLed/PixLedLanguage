#include <memory>
#include "animation.h"

#define LOG_TAG "ANIMATION"

Animation::Animation(uint16_t width, uint16_t height) {
	this->width = width;
	this->height = height;
	this->globalTime.reset(new Integer(0));
	ESP_LOGI("ANIM", "t %p", this->globalTime.get());
}

void Animation::addScene(std::shared_ptr<Scene> scene) {
	this->scenes.push_back(scene);
}

std::shared_ptr<Integer> Animation::getGlobalTime() {
	return this->globalTime;
}
	
void Animation::run(Strip* strip) {
	RenderingLayer layer = RenderingLayer(this->width, this->height, strip);
	ESP_LOGI(LOG_TAG, "Starting animation");
	for(std::shared_ptr<Scene> scene : this->scenes) {
		ESP_LOGI("ANIM", "Time : %f", this->globalTime.get()->yield());
		scene.get()->run(&layer, this->globalTime);
	}
	ESP_LOGI(LOG_TAG, "Animation end");
}

Animation::~Animation() {
	ESP_LOGI("ANIM", "Delete animation %p", this);
}
