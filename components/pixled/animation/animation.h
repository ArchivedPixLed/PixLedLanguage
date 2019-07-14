#ifndef ANIMATION_H
#define ANIMATION_H

#include "LedStrip.h"
#include "sequence.h"

class Animation {
	public:
		Animation(Sequence** sequences, size_t sequencesCount);
		void run(Strip* strip);
		~Animation();
	private:
		Sequence** sequences;
		size_t sequencesCount;
};

#endif //ANIMATION_H
