#include "color.h"

// Color
hsb::hsb(std::shared_ptr<Operator> h, std::shared_ptr<Operator> s, std::shared_ptr<Operator> b) {
	this->h = h;
	this->s = s;
	this->b = b;
}

rgb_pixel hsb::yield() {
	return HSBtoRGB(abs((int) this->h->yield()) % 360, this->s->yield(), this->b->yield());
}
