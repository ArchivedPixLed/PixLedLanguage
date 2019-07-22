#ifndef NUMERIC_H
#define NUMERIC_H

#include <memory>
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
		Product(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		float yield();
};

class Sum : public SecondOrderOperator {
	public:
		Sum(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		float yield();
};

class Comparison : public Condition {
	public:
		Comparison(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		virtual bool yield() = 0;
//		~Comparison();
	protected:
		std::shared_ptr<Operator> p1;
		std::shared_ptr<Operator> p2;
};

class Equal : public Comparison {
	public:
	   	Equal(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		bool yield();
};

class Sup : public Comparison {
	public:
	   	Sup(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		bool yield();
};

class Inf : public Comparison {
	public:
	   	Inf(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		bool yield();
};


class Point {
	public:
		Point(std::shared_ptr<Operator> x, std::shared_ptr<Operator> y);
	
		std::shared_ptr<Operator> x;
		std::shared_ptr<Operator> y;
};

class Distance : public Operator {
	public:
		Distance(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2);
		float yield();
	
	private:
		std::shared_ptr<Point> p1;
		std::shared_ptr<Point> p2;
};


#endif //NUMERIC_H
