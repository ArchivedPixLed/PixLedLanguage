#include "pmath.h"

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
