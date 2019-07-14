#include "color.h"

// Color
hsb::hsb(Operator* h, Operator* s, Operator* b) {
	this->h = h;
	this->s = s;
	this->b = b;
}

rgb_pixel hsb::yield() {
	return HSBtoRGB(abs((int) this->h->yield()) % 360, this->s->yield(), this->b->yield());
}
