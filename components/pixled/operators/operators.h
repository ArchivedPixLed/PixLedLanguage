#ifndef OPERATORS_H
#define OPERATORS_H

#include <memory>
#include <cmath>
#include "scope.h"

/**
 * Operator interface
 */
class Operator {
	public:
		virtual float yield()=0;
		virtual ~Operator() { };
};

class FirstOrderOperator : public Operator {
	public:
		FirstOrderOperator(std::shared_ptr<Operator> p);
		virtual float yield() = 0;
	protected:
		std::shared_ptr<Operator> p;
};

class SecondOrderOperator : public FirstOrderOperator {
	public:
		SecondOrderOperator(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		virtual float yield() = 0;
	protected:
		std::shared_ptr<Operator> p2;
};

class OperatorScope : public Scope<std::shared_ptr<Operator>> {

};
#endif //OPERATORS_H
