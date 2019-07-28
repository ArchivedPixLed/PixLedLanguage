#include <algorithm>

#include "pmath.h"

const double pi = std::acos(-1);

Lin::Lin(float alpha, float beta, std::shared_ptr<Operator> x) : FirstOrderOperator(x){
	this->alpha = alpha;
	this->beta = beta;
};

float Lin::yield() {
	return this->beta + this->alpha * this->p.get()->yield();
};

Lin2::Lin2(std::shared_ptr<Operator> alpha, float beta, std::shared_ptr<Operator> x) : SecondOrderOperator(alpha, x){
	this->beta = beta;
};

float Lin2::yield() {
	return this->beta + this->p.get()->yield() * this->p2.get()->yield();
};

Sin::Sin(std::shared_ptr<Operator> amplitude, std::shared_ptr<Operator> arg) : SecondOrderOperator(amplitude, arg) { };

float Sin::yield() {
	return this->p.get()->yield() * 0.5 * (1 + std::sin(pi * this->p2.get()->yield()));
}

Min::Min(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Min::yield() {
	return std::min(this->p.get()->yield(), this->p2.get()->yield());
}

Max::Max(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Max::yield() {
	return std::max(this->p.get()->yield(), this->p2.get()->yield());
}
