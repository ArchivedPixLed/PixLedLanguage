#include "color.h"
#include "pmath.h"
#include "numeric.h"

// Color
hsb::hsb(std::shared_ptr<Operator> h, std::shared_ptr<Operator> s, std::shared_ptr<Operator> b) {
	this->h = std::shared_ptr<Min>(new Min(
				std::shared_ptr<Max>(new Max(
						h,
						std::shared_ptr<Integer>(new Integer(0))
						)),
				std::shared_ptr<Number>(new Number(360))
				));
	this->s = std::shared_ptr<Min>(new Min(
				std::shared_ptr<Max>(new Max(
						s,
						std::shared_ptr<Number>(new Number(0))
						)),
				std::shared_ptr<Number>(new Number(1))
				));
	this->b = std::shared_ptr<Min>(new Min(
				std::shared_ptr<Max>(new Max(
						b,
						std::shared_ptr<Number>(new Number(0))
						)),
				std::shared_ptr<Number>(new Number(1))
				));
}

rgb_pixel hsb::yield() {
	return HSBtoRGB(this->h->yield(), this->s->yield(), this->b->yield());
}
