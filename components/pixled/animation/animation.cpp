#include "animation.h"

#define LOG_TAG "ANIMATION"

Animation::Animation(Sequence** sequences, size_t sequencesCount) {
	this->sequences = sequences;
	this->sequencesCount = sequencesCount;
}

void Animation::run(Strip* strip) {
	ESP_LOGI(LOG_TAG, "Starting animation");
	for(int i = 0; i < this->sequencesCount; i++) {
		this->sequences[i]->run(strip);
	}
	ESP_LOGI(LOG_TAG, "Animation end");
}

Animation::~Animation() {
	for(int i = 0; i < this->sequencesCount; i++) {
		delete this->sequences[i];
	}
	delete this->sequences;
}
