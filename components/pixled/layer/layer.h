#ifndef LAYER_H
#define LAYER_H

#define LAYER_T std::shared_ptr<Layer>
#define LAYER(...) LAYER_T(new Layer(__VA_ARGS__))

#include <memory>
#include "layer.h"
#include "operators.h"
#include "numeric.h"
#include "color.h"
#include "scope.h"

class Layer {
	public:
		Layer(uint16_t width, uint16_t height);
		uint16_t getWidth();
		uint16_t getHeight();
		void setPosition(std::shared_ptr<Operator> x, std::shared_ptr<Operator> y);
		void setX(std::shared_ptr<Operator> x);
		void setY(std::shared_ptr<Operator> y);
		std::shared_ptr<Operator> getX();
		std::shared_ptr<Operator> getY();
		std::shared_ptr<Integer> getXIndex();
		std::shared_ptr<Integer> getYIndex();
		std::shared_ptr<Point> pointIndex();
		void setColor(std::shared_ptr<hsb> color);
		std::shared_ptr<hsb> getColor();
	
	protected:
		uint16_t width;
		uint16_t height;
		std::shared_ptr<Operator> x;
		std::shared_ptr<Operator> y;
		std::shared_ptr<hsb> color;
		std::shared_ptr<Integer> xIndex;
		std::shared_ptr<Integer> yIndex;
};

class RenderingLayer {
	public:
		RenderingLayer(uint16_t width, uint16_t height, Strip* strip);
		void render();
		void show();
		void merge(Layer* layer);
		uint16_t getWidth();
		uint16_t getHeight();
		uint16_t** getMapping();
		~RenderingLayer();

	protected:
		uint16_t pixelCount;
		uint16_t width;
		uint16_t height;
		uint16_t** mapping;
		rgb_pixel* pixels;
		Strip* strip;
};

class LayerScope : public Scope<std::shared_ptr<Layer>> {

};

#endif //LAYER_H
