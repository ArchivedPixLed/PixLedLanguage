#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "layer.h"
#include "logic.h"
#include "numeric.h"

class Sequence {
	public:
		Sequence(Condition* stopCondition, Layer** layers, int layerCount);
		Sequence(Layer** layers, int layerCount);
		void setStopCondition(Condition* stopCondition);
		Integer* getLocalTime();
		void run(Strip* strip, Integer* globalTime);
		~Sequence();
	private:
		Integer localTime;
		Condition* stopCondition;
		Layer** layers;
		int layerCount;
};

#endif //SEQUENCE_H
