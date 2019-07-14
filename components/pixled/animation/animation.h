#ifndef ANIMATION_H
#define ANIMATION_H

#include "LedStrip.h"
#include "sequence.h"

class Animation {
	public:
		Animation(size_t sequencesCount);
		void setSequences(Sequence** sequences);
		Integer* getGlobalTime();
		void run(Strip* strip);
		~Animation();
	private:
		Integer globalTime;
		Sequence** sequences;
		size_t sequencesCount;
};

#endif //ANIMATION_H
