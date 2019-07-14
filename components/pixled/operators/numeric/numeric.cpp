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
Product::Product(Operator* p1, Operator* p2) : SecondOrderOperator(p1, p2) { };

float Product::yield() {
	return this->p->yield() * this->p2->yield();
};

// Comparison
Comparison::Comparison(Operator* p1, Operator* p2) {
	this->p1 = p1;
	this->p2 = p2;
};

/*
Comparison::~Comparison() {
	ESP_LOGI("NUM", "Delete comp %p", this);
	if(this->p1) {
		delete this->p1;
	}
	if(this->p2) {
		delete this->p2;
	}
}
*/

Equal::Equal(Operator* p1, Operator* p2) : Comparison(p1, p2) { };

bool Equal::yield() {
	return p1->yield() == p2->yield();
}

Sup::Sup(Operator* p1, Operator* p2) : Comparison(p1, p2) { };

bool Sup::yield() {
	return p1->yield() > p2->yield();
}

Inf::Inf(Operator* p1, Operator* p2) : Comparison(p1, p2) { };

bool Inf::yield() {
	return p1->yield() < p2->yield();
}
