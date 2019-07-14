#ifndef OPERATORS_H
#define OPERATORS_H

#include <cmath>

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
		FirstOrderOperator(Operator* p);
		virtual float yield() = 0;
//		~FirstOrderOperator();
	protected:
		Operator* p;
};

class SecondOrderOperator : public FirstOrderOperator {
	public:
		SecondOrderOperator(Operator* p1, Operator* p2);
		virtual float yield() = 0;
//		~SecondOrderOperator();
	protected:
		Operator* p2;
};
#endif //OPERATORS_H
