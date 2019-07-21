#include "sequence.h"

Sequence::Sequence() {
	this->localTime = std::shared_ptr<Integer>(new Integer(0));
	ESP_LOGI("SEQ", "init %i", this->localTime.get()->get());
}

void Sequence::addLayer(std::shared_ptr<Layer> layer) {
	this->layers.push_back(layer);
}

void Sequence::setStopCondition(std::shared_ptr<Condition> stopCondition) {
	this->stopCondition = stopCondition;
}

std::shared_ptr<Integer> Sequence::getLocalTime() {
	return this->localTime;
}

void Sequence::run(RenderingLayer* rendering_layer, std::shared_ptr<Integer> globalTime) {
	// Base layer
	while(!this->stopCondition.get()->yield()) {
		ESP_LOGD("SEQ", "gt: %i", globalTime.get()->get());
		ESP_LOGD("SEQ", "lt: %i", this->localTime.get()->get());

		for(std::shared_ptr<Layer> layer : this->layers) {
			ESP_LOGD("SEQ", "merging %p", layer.get());
			rendering_layer->merge(layer.get());
		}

		rendering_layer->render();

		rendering_layer->show();

		this->localTime.get()->increment(1);
		globalTime.get()->increment(1);
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
