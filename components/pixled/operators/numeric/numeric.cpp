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

// Sum
Sum::Sum(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Sum::yield() {
	return this->p.get()->yield() + this->p2.get()->yield();
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
