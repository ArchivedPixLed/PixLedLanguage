#include "sequence.h"

Sequence::Sequence(Layer** layers, int layerCount) {
	this->layers = layers;
	this->layerCount = layerCount;
	ESP_LOGI("SEQ", "init %i", this->localTime.get());
}

Sequence::Sequence(Condition* stopCondition, Layer** layers, int layerCount)
	: Sequence(layers, layerCount) {
	this->stopCondition = stopCondition;
}

void Sequence::setStopCondition(Condition* stopCondition) {
	this->stopCondition = stopCondition;
}

Integer* Sequence::getLocalTime() {
	return &(this->localTime);
}

void Sequence::run(Strip* strip, Integer* globalTime) {
	// Base layer
	BaseLayer rendered_layer = BaseLayer(strip->pixelCount, strip);
	while(!this->stopCondition->yield()) {
		ESP_LOGD("SEQ", "%i", this->localTime.get());

		for(int i = 0; i < layerCount; i++){
			rendered_layer.merge(this->layers[i]);
		}

		rendered_layer.render();

		strip->show();

		this->localTime.increment(1);
		globalTime->increment(1);
	}
};

Sequence::~Sequence() {
	ESP_LOGI("SEQ", "Delete seq %p", this);
	/*
	for(int i = 0; i < this->layerCount; i++) {
		delete this->layers[i];
	}
	delete this->layers;
	*/
}
