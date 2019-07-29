#include <cmath>

#include "esp_log.h"
#include "sequence.h"

Number::Number(float value) {
	this->value = value;
};

float Number::yield() {
	return this->value;
};

void Number::set(float value) {
	this->value = value;
};

Integer::Integer(long value) {
	this->value = value;
};

Integer::Integer() : Integer(0) { };

float Integer::yield() {
	return this->value;
};

void Integer::increment(long value) {
	this->value+=value;
};

long Integer::get() {
	return this->value;
};

void Integer::set(long value) {
	this->value = value;
};

// Product
Product::Product(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Product::yield() {
	return this->p.get()->yield() * this->p2.get()->yield();
};

// Div
Div::Div(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Div::yield() {
	return this->p.get()->yield() / this->p2.get()->yield();
};

// Mod
Mod::Mod(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Mod::yield() {
	return (long) this->p.get()->yield() % (long) this->p2.get()->yield();
};

// Sum
Sum::Sum(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Sum::yield() {
	return this->p.get()->yield() + this->p2.get()->yield();
};

// Dif
Dif::Dif(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : SecondOrderOperator(p1, p2) { };

float Dif::yield() {
	return this->p.get()->yield() - this->p2.get()->yield();
};

// Comparison
Comparison::Comparison(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) {
	this->p1 = p1;
	this->p2 = p2;
};

Equal::Equal(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : Comparison(p1, p2) { };

bool Equal::yield() {
	return p1.get()->yield() == p2.get()->yield();
}

Sup::Sup(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : Comparison(p1, p2) { };

bool Sup::yield() {
	return p1.get()->yield() > p2.get()->yield();
}

Inf::Inf(std::shared_ptr<Operator> p1, std::shared_ptr<Operator> p2) : Comparison(p1, p2) { };

bool Inf::yield() {
	return p1.get()->yield() < p2.get()->yield();
}

// Point
Point::Point(std::shared_ptr<Operator> x, std::shared_ptr<Operator> y) {
	this->x = x;
	this->y = y;
}

TranslatedPoint::TranslatedPoint(std::shared_ptr<Integer> clock, std::shared_ptr<Operator> xOrigin, std::shared_ptr<Operator> yOrigin)
	: Point() {
		this->clock = clock;
		this->origin.reset(new Integer(clock.get()->yield()));
		this->duration.reset(new Integer(0));
		this->currentX = xOrigin;
		this->currentY = yOrigin;

		this->xSequence.reset(new Sequence());
		/*
		this->xSequence.get() -> addItem(std::shared_ptr<SequenceItem>(new ConditionSequenceItem(
						xOrigin,
						std::shared_ptr<Condition>(new True())
						)));
						*/

		this->ySequence.reset(new Sequence());
		/*
		this->ySequence.get() -> addItem(std::shared_ptr<SequenceItem>(new ConditionSequenceItem(
						yOrigin,
						std::shared_ptr<Condition>(new True())
						)));
						*/
	
		this->x = this->xSequence;
		this->y = this->ySequence;
}

void TranslatedPoint::translateTo(std::shared_ptr<Operator> xDestination, std::shared_ptr<Operator> yDestination, std::shared_ptr<Integer> duration) {
	this->duration.reset(new Integer((long) (duration.get()->yield() + this->duration.get()->yield())));
	std::shared_ptr<Sum> nextX = std::shared_ptr<Sum>(new Sum(
				this->currentX,
				std::shared_ptr<Product>(new Product(
					std::shared_ptr<Div>(new Div(std::shared_ptr<Dif>(new Dif(
								xDestination,
								this->currentX
								)),
								duration)),
					std::shared_ptr<Mod>(new Mod(
							std::shared_ptr<Dif>(new Dif(
									this->clock, this->origin
							)),
							std::shared_ptr<Integer>(new Integer(100))
							))
					))
				));

	this->xSequence.get()->addItem(std::shared_ptr<SequenceItem>(new TimedSequenceItem(
					nextX,
					this->clock,
					duration
					)));
			/*
					std::shared_ptr<Sup>(new Sup(
							std::shared_ptr<Dif>(new Dif(
									clock, std::shared_ptr<Integer>(new Integer(this->clock.get()->yield()))
									)),
							duration
							))
					)));
					*/
	this->currentX = xDestination;

	std::shared_ptr<Sum> nextY = std::shared_ptr<Sum>(new Sum(
			this->currentY,
			std::shared_ptr<Product>(new Product(
					std::shared_ptr<Div>(new Div(
							std::shared_ptr<Dif>(new Dif(
									yDestination, 
									this->currentY
									)),
							duration)),
					std::shared_ptr<Mod>(new Mod(
							std::shared_ptr<Dif>(new Dif(
									this->clock, this->origin 
									)),
							std::shared_ptr<Integer>(new Integer(100))
							))
					))
				));

	this->ySequence.get()->addItem(std::shared_ptr<SequenceItem>(new TimedSequenceItem(
					nextY,
					this->clock,
					duration
					)));
				/*
					std::shared_ptr<Sup>(new Sup(
							std::shared_ptr<Dif>(new Dif(
									clock, std::shared_ptr<Integer>(new Integer(this->clock.get()->yield()))
									)),
							duration
							))
					)));
					*/
	this->currentY = yDestination;

}

void TranslatedPoint::stop() {
	this->xSequence.get()->addItem(std::shared_ptr<SequenceItem>(new ConditionSequenceItem(
				this->currentX,
				std::shared_ptr<False>(new False())
				)));
	this->ySequence.get()->addItem(std::shared_ptr<SequenceItem>(new ConditionSequenceItem(
				this->currentY,
				std::shared_ptr<False>(new False())
				)));
}

// Distance
Distance::Distance(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2) {
	this->p1 = p1;
	this->p2 = p2;
}

float Distance::yield() {
	return sqrt(
		pow(p1.get()->x.get()->yield() - p2.get()->x.get()->yield(), 2) + 
		pow(p1.get()->y.get()->yield() - p2.get()->y.get()->yield(), 2) 
		);
}


