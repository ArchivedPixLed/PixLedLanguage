#ifndef OUT_H
#define OUT_H
#include "operators.h"

class Print : public FirstOrderOperator {
	public:
		Print(std::shared_ptr<Operator> op, const char* tag);
		float yield();
	private:
		const char* tag;
};

#endif
