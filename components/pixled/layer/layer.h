#ifndef LAYER_H
#define LAYER_H

#include "layer.h"
#include "operators.h"
#include "numeric.h"
#include "color.h"

class Layer {
public:
	Layer(uint16_t pixelCount);
	uint16_t getPixelCount();
	void setPosition(Operator* position);
	Operator* getPosition();
	void setColor(hsb* color);
	hsb* getColor();
	Integer getIndex();
	void initIndex();
	~Layer();

protected:
	uint16_t pixelCount;
	Operator* position;
	hsb* color;
	Integer index;
};

class BaseLayer {
	public:
		BaseLayer(uint16_t pixelCount, Strip* strip);
		uint16_t getPixelCount();
		void merge(Layer* layer);
		void render();
	protected:
		uint16_t pixelCount;
		rgb_pixel* pixels;
		Strip* strip;
};

#endif //LAYER_H
