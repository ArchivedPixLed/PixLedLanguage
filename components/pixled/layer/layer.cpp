#include "layer.h"

int max(int v1, int v2) {
	return v1 > v2 ? v1 : v2;
}

int min(int v1, int v2) {
	return v1 < v2 ? v1 : v2;
}

// Rendering Layer
RenderingLayer::RenderingLayer(uint16_t width, uint16_t height, Strip* strip) {
	this->pixels = new rgb_pixel[width * height];
	this->strip = strip;
	this->width = width;
	this->height = height;
	this->pixelCount = width * height;
	/*
	uint16_t** mapping = new uint16_t*[width];
	for(int i = 0; i < width; i++) {
		mapping[i] = new uint16_t[height];
		for(int j = 0; j < height; j++) {
			mapping[i][j] = i * width + j;
		}
	}
	*/
	uint16_t** mapping = new uint16_t*[width];
	for(int i = 0; i < width; i++) {
		mapping[i] = new uint16_t[height];
		if (i % 2 == 0) {
			for(int j = 0; j < height; j++) {
				mapping[i][j] = i * width + j;
				ESP_LOGD("MAP", "%i %i : %i", i, j, mapping[i][j]);
			}
		}
		else {
			for(int j = 0; j < height; j++) {
				mapping[i][height - 1 - j] = i * width + j;
				ESP_LOGD("MAP", "%i %i : %i", i, j, mapping[i][height - 1 - j]);
			}
		}
	}

	this->mapping = mapping;
}

void RenderingLayer::render() {
	for(int i = 0; i < this->pixelCount; i++) {
		this->strip->setPixel(i, this->pixels[i]);
	}
}

void RenderingLayer::show() {
	this->strip->show();
}

void RenderingLayer::merge(Layer* layer) {
	int layerX = (int) layer->getX()->yield();
	int min_x = max(
			0,
			layerX
			);
	int max_x = min(
			layerX + layer->getWidth(),
			this->getWidth()
			);

	int layerY = (int) layer->getY()->yield();
	int min_y = max(
			0,
			layerY
			);
	int max_y = min(
			layerY + layer->getHeight(),
			this->getHeight()
			);

	for(int x = min_x; x < max_x; x++) {
		for(int y = min_y; y < max_y; y++) {
			this->pixels[this->getMapping()[x][y]] = layer->getColor()->yield();
			layer->getYIndex().get()->increment(1);
		}
		layer->getYIndex().get()->set(0);
		layer->getXIndex().get()->increment(1);
	}
	layer->getXIndex().get()->set(0);

}

uint16_t RenderingLayer::getWidth() {
	return this->width;
}

uint16_t RenderingLayer::getHeight() {
	return this->height;
}

uint16_t** RenderingLayer::getMapping() {
	return this->mapping;
}

Layer::Layer(uint16_t width, uint16_t height) {
	this->width = width;
	this->height = height;
	this->x.reset(new Integer(0));
	this->y.reset(new Integer(0));
	this->xIndex.reset(new Integer(0));
	this->yIndex.reset(new Integer(0));
}

uint16_t Layer::getWidth() {
	return this->width;
}

uint16_t Layer::getHeight() {
	return this->height;
}

void Layer::setPosition(std::shared_ptr<Operator> x, std::shared_ptr<Operator> y) {
	this->x = x;
	this->y = y;
}

void Layer::setX(std::shared_ptr<Operator> x) {
	this->x = x;
}

void Layer::setY(std::shared_ptr<Operator> y) {
	this->y = y;
}

std::shared_ptr<Operator> Layer::getX() {
	return this->x;
}

std::shared_ptr<Operator> Layer::getY() {
	return this->y;
}

std::shared_ptr<Integer> Layer::getXIndex() {
	return this->xIndex;
}

std::shared_ptr<Integer> Layer::getYIndex() {
	return this->yIndex;
}

std::shared_ptr<Point> Layer::pointIndex() {
	return std::shared_ptr<Point>(new Point(this->xIndex, this->yIndex));
}

void Layer::setColor(std::shared_ptr<hsb> color) {
	this->color = color;
}

std::shared_ptr<hsb> Layer::getColor() {
	return this->color;
}

RenderingLayer::~RenderingLayer() {
	ESP_LOGI("LAYER", "Deleting rendering layer...");
	for(int i = 0; i < width; i++) {
		delete this->mapping[i];
	}
	delete this->mapping;
}
