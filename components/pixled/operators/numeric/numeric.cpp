#include <cmath>

#include "numeric.h"
#include "esp_log.h"

Number::Number(float value) {
	this->value = value;
};

float Number::yield() {
	return this->value;
};

void Number::set(float value) {
	this->value = value;
};

Integer::Integer(int value) {
	this->value = value;
};

Integer::Integer() : Integer(0) { };

float Integer::yield() {
	return this->value;
};

void Integer::increment(int value) {
	this->value+=value;
};

int Integer::get() {
	return this->value;
};

void Integer::set(int value) {
	this->value = value;
};

// Product
Product::Product(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Product::yield() {
	return this->p.get()->yield() * this->p2.get()->yield();
};

// Div
Div::Div(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Div::yield() {
	return this->p.get()->yield() / this->p2.get()->yield();
};

// Sum
Sum::Sum(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Sum::yield() {
	return this->p.get()->yield() + this->p2.get()->yield();
};

// Sum
Dif::Dif(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Dif::yield() {
	return this->p.get()->yield() - this->p2.get()->yield();
};

// Comparison
Comparison::Comparison(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) {
	this->p1 = p1;
	this->p2 = p2;
};

Equal::Equal(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : Comparison(p1, p2) { };

bool Equal::yield() {
	return p1.get()->yield() == p2.get()->yield();
}

Sup::Sup(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : Comparison(p1, p2) { };

bool Sup::yield() {
	return p1.get()->yield() > p2.get()->yield();
}

Inf::Inf(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : Comparison(p1, p2) { };

bool Inf::yield() {
	return p1.get()->yield() < p2.get()->yield();
}

// Point
Point::Point(std::shared_ptr<Operator> x, std::shared_ptr<Operator> y) {
	this->x = x;
	this->y = y;
}

// Distance
Distance::Distance(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2) {
	this->p1 = p1;
	this->p2 = p2;
}

float Distance::yield() {
	return sqrt(
		pow(p1.get()->x.get()->yield() - p2.get()->x.get()->yield(), 2) + 
		pow(p1.get()->y.get()->yield() - p2.get()->y.get()->yield(), 2) 
		);
}

// Translate
Translate::Translate(
			std::shared_ptr<Point> origin,
			std::shared_ptr<Point> destination,
			std::shared_ptr<Integer> clock,
			std::shared_ptr<Integer> duration
			)
	: Point(
		std::shared_ptr<Product>(
			new Product(
				std::shared_ptr<Div>(new Div(std::shared_ptr<Dif>(new Dif(destination.get()->x, origin.get()->x)), duration)),
				std::shared_ptr<Dif>(new Dif(clock, std::shared_ptr<Integer>(new Integer(clock.get()->yield()))))
				)
			),
		std::shared_ptr<Product>(
			new Product(
				std::shared_ptr<Div>(new Div(std::shared_ptr<Dif>(new Dif(destination.get()->y, origin.get()->y)), duration)),
				std::shared_ptr<Dif>(new Dif(clock, std::shared_ptr<Integer>(new Integer(clock.get()->yield()))))
				)
			)
		){};


