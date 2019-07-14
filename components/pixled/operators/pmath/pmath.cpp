#include "pmath.h"

Lin::Lin(float alpha, float beta, Operator* x) : FirstOrderOperator(x){
	this->alpha = alpha;
	this->beta = beta;
};

float Lin::yield() {
	return this->beta + this->alpha * this->p->yield();
};

Lin2::Lin2(Operator* alpha, float beta, Operator* x) : SecondOrderOperator(alpha, x){
	this->beta = beta;
};

float Lin2::yield() {
	return this->beta + this->p->yield() * this->p2->yield();
};
