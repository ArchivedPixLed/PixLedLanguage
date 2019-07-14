#include "LedStrip.h"
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
	/*
	void setPixel(uint16_t index, hsb_pixel pixel);
	void setPixel(uint16_t index, rgb_pixel pixel);
	rgb_pixel getPixel(uint16_t index);
	*/

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


/**
 * Merges layer2 into layer1
 */
// void merge(Layer* layer1, Layer* layer2);
