#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <memory>

#include "operators.h"
#include "numeric.h"

class SequenceItem {
	public:
		SequenceItem(std::shared_ptr<Operator> op);
		virtual void reset() = 0;
		float yield();
		virtual bool end() = 0;
	protected:
		std::shared_ptr<Operator> op;
};

class Sequence : public Operator {
	public:
		Sequence();
		Sequence(std::vector<std::shared_ptr<SequenceItem>> items);
		void addItem(std::shared_ptr<SequenceItem> item);
		float yield();
	
	private:
		int currentIndex = 0;
		std::vector<std::shared_ptr<SequenceItem>> items;
};

class ConditionSequenceItem : public SequenceItem {
	public:
		ConditionSequenceItem(std::shared_ptr<Operator> op, std::shared_ptr<Condition> stopCondition);
		void reset() {};
		bool end();
	private:
		std::shared_ptr<Condition> stopCondition;
};

class TimedSequenceItem : public SequenceItem {
	public:
		TimedSequenceItem(std::shared_ptr<Operator> op, std::shared_ptr<Integer> globalTime, std::shared_ptr<Integer> duration);
		void reset();
		bool end();
	private:
		std::shared_ptr<Integer> duration;
		std::shared_ptr<Integer> globalTime;
		uint16_t begin = 0;
};

#endif
