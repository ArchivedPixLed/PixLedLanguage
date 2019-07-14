#ifndef COLOR_H
#define COLOR_H

#include "LedStrip.h"
#include "operators.h"

class hsb {
	public:
		hsb(Operator* h, Operator* s, Operator* b);
		rgb_pixel yield();
//		~hsb();
	private:
		Operator* h;
		Operator* s;
		Operator* b;
};

#endif //COLOR_H
