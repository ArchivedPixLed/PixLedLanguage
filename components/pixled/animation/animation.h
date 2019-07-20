#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>
#include <vector>
#include "LedStrip.h"
#include "sequence.h"
#include "scope.h"

class Animation {
	public:
		Animation();
		void addSequence(std::shared_ptr<Sequence> sequence);
		std::shared_ptr<Integer> getGlobalTime();
		void run(Strip* strip);
		~Animation();
		LayerScope layerScope;
		SequenceScope sequenceScope;
		OperatorScope operatorScope;

	private:
		std::shared_ptr<Integer> globalTime;
		std::vector<std::shared_ptr<Sequence>> sequences;
};

#endif //ANIMATION_H
