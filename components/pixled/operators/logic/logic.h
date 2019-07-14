#ifndef LOGIC_H
#define LOGIC_H

class Condition {
	public:
		virtual bool yield() = 0;
//		virtual ~Condition() { };
};

class ConditionLogic : public Condition {
	public:
		ConditionLogic(Condition* c1, Condition* c2);
		virtual bool yield() = 0;
//		~ConditionLogic();
	protected:
		Condition* c1;
		Condition* c2;
};

class True : public Condition {
	public:
		True();
		bool yield();
//		~True() {};
};

class False : public Condition {
	public:
		False();
		bool yield();
//		~False() {};
};

class Not : public Condition {
	public:
		Not(Condition* c);
		bool yield();
//		~Not();
	protected:
		Condition* c;
};

class And : public ConditionLogic {
	public:
		And(Condition* c1, Condition* c2);
		bool yield();
};

class Or : public ConditionLogic {
	public:
		Or(Condition* c1, Condition* c2);
		bool yield();
};

#endif //LOGIC_H
