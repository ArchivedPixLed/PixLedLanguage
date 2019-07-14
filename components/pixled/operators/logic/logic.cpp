#include "logic.h"
#include "esp_log.h"

True::True(){};

bool True::yield() {
	return true;
}

False::False(){};

bool False::yield() {
	return true;
}

ConditionLogic::ConditionLogic(Condition* c1, Condition* c2) {
	this->c1 = c1;
	this->c2 = c2;
}

/*
ConditionLogic::~ConditionLogic() {
	ESP_LOGI("CL", "Delete cl %p", this);
	if(this->c1) {
		delete this->c1;
	}
	if(this->c2) {
		delete this->c2;
	}
}
*/

And::And(Condition* c1, Condition* c2) : ConditionLogic(c1, c2) { };

bool And::yield() {
	return c1->yield() && c2->yield();
}

Or::Or(Condition* c1, Condition* c2) : ConditionLogic(c1, c2) { };

bool Or::yield() {
	return c1->yield() || c2->yield();
}

Not::Not(Condition* c) {
	this-> c = c;
}

bool Not::yield() {
	return !(this->c->yield());
}

/*
Not::~Not() {
	if(this->c) {
		delete this->c;
	}
}
*/
