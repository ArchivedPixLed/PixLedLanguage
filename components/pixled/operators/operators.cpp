#include "operators.h"
#include "esp_log.h"


FirstOrderOperator::FirstOrderOperator(std::shared_ptr<Operator> parameter) {
	this->p = parameter;
};

SecondOrderOperator::SecondOrderOperator(
		std::shared_ptr<Operator> p1,
		std::shared_ptr<Operator> p2)
   			: FirstOrderOperator(p1) {
	this->p2 = p2;
};
