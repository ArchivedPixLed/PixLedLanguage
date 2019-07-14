#ifndef NUMERIC_H
#define NUMERIC_H

#include "esp_log.h"

#include "operators.h"
#include "logic.h"

/**
 * Constant float
 */
class Number : public Operator {
	public:
		Number(float value);
		float yield();
		void set(float value);
//		~Number() { };
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
//		~Integer() { ESP_LOGI("INT", "Delete %p", this); };
	private:
		int value;
};

class Product : public SecondOrderOperator {
	public:
		Product(Operator* p1, Operator* p2);
		float yield();
};

class Sum : public SecondOrderOperator {
	public:
		Sum(Operator* p1, Operator* p2);
		float yield();
};

class Comparison : public Condition {
	public:
		Comparison(Operator* p1, Operator* p2);
		virtual bool yield() = 0;
//		~Comparison();
	protected:
		Operator* p1;
		Operator* p2;
};

class Equal : public Comparison {
	public:
	   	Equal(Operator* p1, Operator* p2);
		bool yield();
};

class Sup : public Comparison {
	public:
	   	Sup(Operator* p1, Operator* p2);
		bool yield();
};

class Inf : public Comparison {
	public:
	   	Inf(Operator* p1, Operator* p2);
		bool yield();
};

#endif //NUMERIC_H
