#include "animation.h"

#define LOG_TAG "ANIMATION"

Animation::Animation(size_t sequencesCount) {
	this->sequencesCount = sequencesCount;
	//this->globalTime = new Integer();
}

void Animation::setSequences(Sequence** sequences) {
	this->sequences = sequences;
}

Integer* Animation::getGlobalTime() {
	return &(this->globalTime);
}
	
void Animation::run(Strip* strip) {
	ESP_LOGI(LOG_TAG, "Starting animation");
	for(int i = 0; i < this->sequencesCount; i++) {
		ESP_LOGI("ANIM", "Time : %f", this->globalTime.yield());
		this->sequences[i]->run(strip, &(this->globalTime));
	}
	ESP_LOGI(LOG_TAG, "Animation end");
}

Animation::~Animation() {
	for(int i = 0; i < this->sequencesCount; i++) {
		delete this->sequences[i];
	}
	delete this->sequences;
}
