#ifndef PMATH_H
#define PMATH_H

#include <memory>
#include "operators.h"

/**
 * First order linear equation
 */
class Lin : public FirstOrderOperator {
	public:
		Lin(float alpha, float beta, std::shared_ptr<Operator> x);
		float yield();
	private:
		float alpha;
		float beta;
};


class Lin2 : public SecondOrderOperator {
	public:
		Lin2(std::shared_ptr<Operator> alpha, float beta, std::shared_ptr<Operator> x);
		float yield();
	private:
		float beta;
};
#endif //MATH_H
