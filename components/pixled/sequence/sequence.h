#include "layer.h"

class Sequence {
	public:
		Sequence(int duration, Layer** layers, int layerCount);
		Integer* getLocalTime();
		void run(Strip* strip);
	private:
		Integer localTime;
		int duration;
		Layer** layers;
		int layerCount;
};
