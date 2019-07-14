#include "operators.h"
#include "esp_log.h"


FirstOrderOperator::FirstOrderOperator(Operator* parameter) {
	this->p = parameter;
};

SecondOrderOperator::SecondOrderOperator(Operator* p1, Operator* p2) : FirstOrderOperator(p1) {
	this->p2 = p2;
};
