#include "operators.h"

/**
 * Constant float
 */
class Number : public Operator {
	public:
		Number(float value);
		float yield();
		void set(float value);
	private:
		float value;
};

/**
 * Constant integer
 */
class Integer : public Operator {
	public:
		Integer(int value);
		Integer();
		float yield();
		void increment(int value);
		int get();
		void set(int value);
	private:
		int value;
};

class Product : public SecondOrderOperator {
	public:
		Product(Operator* p1, Operator* p2);
		float yield();
};
