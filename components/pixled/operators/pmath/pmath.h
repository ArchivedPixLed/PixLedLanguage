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

class Sin : public SecondOrderOperator {
	public:
		Sin(std::shared_ptr<Operator> amplitude, std::shared_ptr<Operator> arg);
		float yield();
};

class Min : public SecondOrderOperator {
	public:
		Min(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		float yield();
};

class Max : public SecondOrderOperator {
	public:
		Max(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		float yield();
};
#endif //MATH_H
