#include "operators.h"
#include "esp_log.h"


FirstOrderOperator::FirstOrderOperator(Operator* parameter) {
	this->p = parameter;
};

/*
FirstOrderOperator::~FirstOrderOperator() {
	ESP_LOGI("OP", "Delete first order %p, %p", this, this->p);
	if(this->p) {
		ESP_LOGI("OP", "Delete");
		delete this->p;
		this->p = NULL;
		ESP_LOGI("OP", "Deleted");
		bool destroyed = true;
		if (this->p) {
			destroyed = false;
		}
		ESP_LOGI("OP", "Deleted? %i", destroyed);
	}
};
*/

SecondOrderOperator::SecondOrderOperator(Operator* p1, Operator* p2) : FirstOrderOperator(p1) {
	this->p2 = p2;
};

/*
SecondOrderOperator::~SecondOrderOperator() {
	ESP_LOGI("OP2", "Delete second order %p", this);
	if(this->p2) {
		ESP_LOGI("OP2", "Delete");
		delete this->p2;
		this->p2 = NULL;
		ESP_LOGI("OP2", "Deleted");
		bool destroyed = true;
		if (this->p2) {
			destroyed = false;
		}
		ESP_LOGI("OP2", "Deleted? %i", destroyed);
	}
};
*/
