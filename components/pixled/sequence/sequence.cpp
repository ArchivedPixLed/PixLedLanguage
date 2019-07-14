#include "sequence.h"

Sequence::Sequence(int duration, Layer** layers, int layerCount) {
	this->duration = duration;
	this->layers = layers;
	this->layerCount = layerCount;
	ESP_LOGI("SEQ", "init %i", this->localTime.get());
}

Integer* Sequence::getLocalTime() {
	return &(this->localTime);
}

void Sequence::run(Strip* strip) {
	// Base layer
	BaseLayer rendered_layer = BaseLayer(strip->pixelCount, strip);
	while(this->localTime.get() < this->duration) {
		ESP_LOGI("SEQ", "%i", this->localTime.get());

		for(int i = 0; i < layerCount; i++){
			rendered_layer.merge(this->layers[i]);
		}

		rendered_layer.render();

		strip->show();

		this->localTime.increment(1);
	}
};
