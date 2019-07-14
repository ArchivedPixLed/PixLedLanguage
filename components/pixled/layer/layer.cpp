#include "layer.h"
#include "esp_log.h"

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


/*
void Layer::setPixel(uint16_t index, hsb_pixel hsb_pixel) {
	this->pixels[index] = HSBtoRGB(hsb_pixel.hue, hsb_pixel.saturation, hsb_pixel.brightness);
}

void Layer::setPixel(uint16_t index, rgb_pixel pixel) {
	this->pixels[index] = pixel;
}

rgb_pixel Layer::getPixel(uint16_t index) {
	return this->pixels[index];
}
*/

/*
void merge(Layer* layer1, Layer* layer2) {
	int min_i = max(layer1->getPosition(), layer2->getPosition());

	int max_i = min(
			layer2->getPosition() + layer2->getPixelCount(),
			layer1->getPosition() + layer1->getPixelCount()
			);

	for(int i = min_i; i < max_i; i ++) {
		layer1->setPixel(i -  layer1->getPosition(), layer2->getPixel(i - layer2->getPosition()));
	}
}
*/
