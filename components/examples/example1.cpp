#include <memory>
#include "examples.h"

Animation* example1(uint16_t numLed) {

	Animation* example1 = new Animation();

	// Background
	std::shared_ptr<Layer> background = std::shared_ptr<Layer>(new Layer(numLed));
	std::shared_ptr<Integer> backPos = std::shared_ptr<Integer>(new Integer(0));
	background.get()->setPosition(backPos);

	// Forward Particle
	std::shared_ptr<Layer> fParticle = std::shared_ptr<Layer>(new Layer(1));

	std::shared_ptr<Sequence> seq = std::shared_ptr<Sequence>(new Sequence());
	seq.get()->addLayer(background);
	seq.get()->addLayer(fParticle);

	// Background setup
	std::shared_ptr<hsb> color = std::shared_ptr<hsb>(
			new hsb(
				std::shared_ptr<Product>(new Product(std::shared_ptr<Number>(new Number(2)), example1->getGlobalTime())),
				std::shared_ptr<Number>(new Number(1)),
				std::shared_ptr<Number>(new Number(0.01))
				)
			);
	/*
	std::shared_ptr<hsb> color = std::shared_ptr<hsb>(
		new hsb(
			std::shared_ptr<Product>(new Product(std::shared_ptr<Number>(new Number(2)), std::shared_ptr<Number>(new Number(4)))),
			std::shared_ptr<Number>(new Number(1)),
			std::shared_ptr<Number>(new Number(0.01))
			)
		);
	*/
	background->setColor(color);

	// Forward Particle setup
	std::shared_ptr<Lin> fParticleSpeed = std::shared_ptr<Lin>(new Lin(0.001, 0, seq.get()->getLocalTime()));
	std::shared_ptr<Product> fParticlePosition = std::shared_ptr<Product>(new Product(fParticleSpeed, seq.get()->getLocalTime()));
	fParticle.get()->setPosition(fParticlePosition);

	std::shared_ptr<hsb> fParticleColor = std::shared_ptr<hsb>(
			new hsb(
				std::shared_ptr<Lin>(new Lin(360 / numLed, 0, fParticlePosition)),
				std::shared_ptr<Number>(new Number(1)),
				std::shared_ptr<Number>(new Number(0.9))
				)
			);

	fParticle.get()->setColor(fParticleColor);

	std::shared_ptr<Integer> endPos = std::shared_ptr<Integer>(new Integer(numLed));
	std::shared_ptr<Sup> stopCondition = std::shared_ptr<Sup>(new Sup(fParticlePosition, endPos));
	seq.get()->setStopCondition(stopCondition);

	// Backward Particle
	std::shared_ptr<Layer> bParticle = std::shared_ptr<Layer>(new Layer(1));

	std::shared_ptr<Sequence> seq2 = std::shared_ptr<Sequence>(new Sequence());
	seq2.get()->addLayer(background);
	seq2.get()->addLayer(bParticle);


	// Backward Particle setup
	std::shared_ptr<Lin> bParticleSpeed = std::shared_ptr<Lin>(new Lin(-0.001, 0, seq2.get()->getLocalTime()));
	std::shared_ptr<Lin2> bParticlePosition = std::shared_ptr<Lin2>(new Lin2(bParticleSpeed, numLed, seq2.get()->getLocalTime()));
	bParticle.get()->setPosition(bParticlePosition);

	std::shared_ptr<hsb> bParticleColor = std::shared_ptr<hsb>(
		new hsb(
			std::shared_ptr<Lin>(new Lin(360 / numLed, 0, bParticlePosition)),
			std::shared_ptr<Number>(new Number(1)),
			std::shared_ptr<Number>(new Number(0.9)))
		);
	bParticle.get()->setColor(bParticleColor);

	std::shared_ptr<Integer> endPos2 = std::shared_ptr<Integer>(new Integer(0));
	std::shared_ptr<Inf> stopCondition2 = std::shared_ptr<Inf>(new Inf(bParticlePosition, endPos2));
	seq2.get()->setStopCondition(stopCondition2);

	example1->addSequence(seq);
	example1->addSequence(seq2);

	return example1;
}
