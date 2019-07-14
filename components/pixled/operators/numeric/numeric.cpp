#include "numeric.h"

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
Product::Product(Operator* p1, Operator* p2) : SecondOrderOperator(p1, p2) { };

float Product::yield() {
	return this->p->yield() * this->p2->yield();
};
