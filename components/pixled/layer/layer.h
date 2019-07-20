#ifndef LAYER_H
#define LAYER_H

#include <memory>
#include "layer.h"
#include "operators.h"
#include "numeric.h"
#include "color.h"

class Layer {
public:
	Layer(uint16_t pixelCount);
	uint16_t getPixelCount();
	void setPosition(std::shared_ptr<Operator> position);
	std::shared_ptr<Operator> getPosition();
	void setColor(std::shared_ptr<hsb> color);
	std::shared_ptr<hsb> getColor();
	std::shared_ptr<Integer> getIndex();
	void initIndex();
	~Layer();

protected:
	uint16_t pixelCount;
	std::shared_ptr<Operator> position;
	std::shared_ptr<hsb> color;
	std::shared_ptr<Integer> index;
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
