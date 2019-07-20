#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <memory>
#include <vector>
#include "layer.h"
#include "logic.h"
#include "numeric.h"

class Sequence {
	public:
		Sequence();
		void addLayer(std::shared_ptr<Layer> layer);
		void setStopCondition(std::shared_ptr<Condition> stopCondition);
		std::shared_ptr<Integer> getLocalTime();
		void run(Strip* strip, std::shared_ptr<Integer> globalTime);
		~Sequence();
	private:
		std::shared_ptr<Integer> localTime;
		std::shared_ptr<Condition> stopCondition;
		std::vector<std::shared_ptr<Layer>> layers;
};

#endif //SEQUENCE_H
