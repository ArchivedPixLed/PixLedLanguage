#include "out.h"

#include "esp_log.h"

Print::Print(std::shared_ptr<Operator> op, const char* tag) : FirstOrderOperator(op) {
	this->tag = tag;
};


float Print::yield() {
	float value = this->p.get()->yield();
	ESP_LOGI(tag, "%f", value);
	return value;
};
