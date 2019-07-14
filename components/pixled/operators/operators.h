#ifndef OPERATORS_H
#define OPERATORS_H

#include "LedStrip.h"
#include <cmath>

/**
 * Operator interface
 */
class Operator {
	public:
		virtual float yield()=0;
};

class FirstOrderOperator : public Operator {
	public:
		FirstOrderOperator(Operator* p);
		virtual float yield() = 0;
	protected:
		Operator* p;
};

class SecondOrderOperator : public FirstOrderOperator {
	public:
		SecondOrderOperator(Operator* p1, Operator* p2);
		virtual float yield() = 0;
	protected:
		Operator* p2;
};
#endif //OPERATORS_H
