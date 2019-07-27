#include "sequence.h"
#include "esp_log.h"

Sequence::Sequence() {
}

Sequence::Sequence(std::vector<std::shared_ptr<SequenceItem>> items) {
	this->items = items;
}

void Sequence::addItem(std::shared_ptr<SequenceItem> item) {
	this->items.push_back(item);
}

float Sequence::yield() {
	std::shared_ptr<SequenceItem> currentItem = this->items.at(this->currentIndex);
	if(!currentItem.get()->end()) {
		return currentItem.get()->yield();
	}
	if(this->currentIndex == this->items.size() - 1) {
		this->currentIndex = 0;
	}
	else {
		this->currentIndex++;
	}
	std::shared_ptr<SequenceItem> nextItem = this->items.at(this->currentIndex);
	nextItem.get()->reset();
	return nextItem.get()->yield();
}

SequenceItem::SequenceItem(std::shared_ptr<Operator> op) {
	this->op = op;
}

float SequenceItem::yield() {
	return this->op.get()->yield();
}

TimedSequenceItem::TimedSequenceItem(std::shared_ptr<Operator> op, std::shared_ptr<Integer> globalTime, uint16_t duration)
	: SequenceItem(op) {
		this->duration = duration;
		this->globalTime = globalTime;
		this->reset();
}

void TimedSequenceItem::reset() {
	this->begin = this->globalTime.get()->yield();
}

bool TimedSequenceItem::end() {
	return (this->globalTime.get()->yield() - this->begin)>=this->duration;
}
