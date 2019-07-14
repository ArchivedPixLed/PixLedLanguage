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

/*
hsb::~hsb() {
	ESP_LOGI("COL", "Delete color %p", this);
	if(this->h) {
		delete this->h;
	}
	if(this->s) {
		delete this->s;
	}
	if(this->b) {
		delete this->b;
	}
}
*/
