#include "logic.h"
#include "esp_log.h"

True::True(){};

bool True::yield() {
	return true;
}

False::False(){};

bool False::yield() {
	return false;
}

ConditionLogic::ConditionLogic(std::shared_ptr<Condition> c1, std::shared_ptr<Condition> c2) {
	this->c1 = c1;
	this->c2 = c2;
}

And::And(std::shared_ptr<Condition> c1, std::shared_ptr<Condition> c2) : ConditionLogic(c1, c2) { };

bool And::yield() {
	return c1->yield() && c2->yield();
}

Or::Or(std::shared_ptr<Condition> c1, std::shared_ptr<Condition> c2) : ConditionLogic(c1, c2) { };

bool Or::yield() {
	return c1->yield() || c2->yield();
}

Not::Not(std::shared_ptr<Condition> c) {
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
