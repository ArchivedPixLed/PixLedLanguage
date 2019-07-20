#ifndef LOGIC_H
#define LOGIC_H

#include <memory>

class Condition {
	public:
		virtual bool yield() = 0;
};

class ConditionLogic : public Condition {
	public:
		ConditionLogic(std::shared_ptr<Condition> c1, std::shared_ptr<Condition> c2);
		virtual bool yield() = 0;
	protected:
		std::shared_ptr<Condition> c1;
		std::shared_ptr<Condition> c2;
};

class True : public Condition {
	public:
		True();
		bool yield();
};

class False : public Condition {
	public:
		False();
		bool yield();
};

class Not : public Condition {
	public:
		Not(std::shared_ptr<Condition> c);
		bool yield();
	protected:
		std::shared_ptr<Condition> c;
};

class And : public ConditionLogic {
	public:
		And(std::shared_ptr<Condition> c1, std::shared_ptr<Condition> c2);
		bool yield();
};

class Or : public ConditionLogic {
	public:
		Or(std::shared_ptr<Condition> c1, std::shared_ptr<Condition> c2);
		bool yield();
};

#endif //LOGIC_H
