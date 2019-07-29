#ifndef NUMERIC_H
#define NUMERIC_H

#include <memory>
#include "esp_log.h"
#include "operators.h"
#include "logic.h"

class Sequence;
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
		Integer(long value);
		Integer();
		float yield();
		void increment(long value);
		long get();
		void set(long value);
	private:
		long value;
};

class Product : public SecondOrderOperator {
	public:
		Product(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		float yield();
};

class Div : public SecondOrderOperator {
	public:
		Div(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		float yield();
};

class Mod : public SecondOrderOperator {
	public:
		Mod(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		float yield();
};

class Sum : public SecondOrderOperator {
	public:
		Sum(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
		float yield();
};

class Dif : public SecondOrderOperator {
	public:
		Dif(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2);
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
		Point(){};
		Point(std::shared_ptr<Operator> x, std::shared_ptr<Operator> y);
	
		std::shared_ptr<Operator> x;
		std::shared_ptr<Operator> y;
		/*
		static std::shared_ptr<Point> Translate(
			std::shared_ptr<Point> origin,
			std::shared_ptr<Point> destination,
			std::shared_ptr<Integer> clock,
			std::shared_ptr<Integer> duration
			);
			*/

};

class TranslatedPoint : public Point {
	public:
		TranslatedPoint(std::shared_ptr<Integer> clock, std::shared_ptr<Operator> xOrigin, std::shared_ptr<Operator> yOrigin);
		void translateTo(std::shared_ptr<Operator> x, std::shared_ptr<Operator> y, std::shared_ptr<Integer> duration);
		void stop();
	
	private:
		std::shared_ptr<Integer> clock;
		std::shared_ptr<Integer> origin;
		std::shared_ptr<Integer> duration;
		std::shared_ptr<Operator> currentX;
		std::shared_ptr<Operator> currentY;
		std::shared_ptr<Sequence> xSequence;
		std::shared_ptr<Sequence> ySequence;
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
