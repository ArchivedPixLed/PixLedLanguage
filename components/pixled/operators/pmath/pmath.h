#ifndef PMATH_H
#define PMATH_H

#include "operators.h"

/**
 * First order linear equation
 */
class Lin : public FirstOrderOperator {
	public:
		Lin(float alpha, float beta, Operator* x);
		float yield();
	private:
		float alpha;
		float beta;
};


class Lin2 : public SecondOrderOperator {
	public:
		Lin2(Operator* alpha, float beta, Operator* x);
		float yield();
	private:
		float beta;
};
#endif //MATH_H
