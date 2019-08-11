#ifndef COLOR_H
#define COLOR_H

#define HSB_T std::shared_ptr<hsb>
#define HSB(...) HSB_T(new hsb(__VA_ARGS__))

#include "LedStrip.h"
#include "operators.h"

class hsb {
	public:
		hsb(std::shared_ptr<Operator> h, std::shared_ptr<Operator> s, std::shared_ptr<Operator> b);
		rgb_pixel yield();
	private:
		std::shared_ptr<Operator> h;
		std::shared_ptr<Operator> s;
		std::shared_ptr<Operator> b;
};

#endif //COLOR_H
