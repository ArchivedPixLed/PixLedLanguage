#include "layer.h"

int max(int v1, int v2) {
	return v1 > v2 ? v1 : v2;
}

int min(int v1, int v2) {
	return v1 < v2 ? v1 : v2;
}

BaseLayer::BaseLayer(uint16_t pixelCount, Strip* strip) {
	this->pixelCount = pixelCount;
	this->pixels = new rgb_pixel[pixelCount];
	this->strip = strip;
}//Layer

uint16_t BaseLayer::getPixelCount() {
	return this->pixelCount;
}

void BaseLayer::render() {
	for(int i = 0; i < this->pixelCount; i++) {
		this->strip->setPixel(i, this->pixels[i]);
	}
}

void BaseLayer::merge(Layer* layer) {
	int layerPosition = (int) layer->getPosition()->yield();
	int min_i = max(
			0,
			layerPosition
			);
	int max_i = min(
			layerPosition + layer->getPixelCount(),
			this->getPixelCount()
			);

	for(int i = min_i; i < max_i; i ++) {
//		layer->initIndex();
		this->pixels[i] = layer->getColor()->yield();
	}

}

Layer::Layer(uint16_t pixelCount) {
	this->pixelCount = pixelCount;
}

uint16_t Layer::getPixelCount() {
	return this->pixelCount;
}

void Layer::setPosition(Operator* position) {
	this->position = position;
}

Operator* Layer::getPosition() {
	return this->position;
}

void Layer::setColor(hsb* color) {
	this->color = color;
}

hsb* Layer::getColor() {
	return this->color;
}

Integer Layer::getIndex() {
	return this->index;
}

void Layer::initIndex() {
	this->index.set(0);
}

Layer::~Layer() {
	ESP_LOGI("LAY", "Delete lay %p", this);
}
