#include "../operators.h"

class hsb {
	public:
		hsb(Operator* h, Operator* s, Operator* b);
		rgb_pixel yield();
	private:
		Operator* h;
		Operator* s;
		Operator* b;
};

