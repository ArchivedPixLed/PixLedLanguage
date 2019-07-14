#include "examples.h"

Animation* example1(uint16_t numLed) {

	// Background
	Layer* background = new Layer(numLed);
	Integer* backPos = new Integer(0);
	background->setPosition(backPos);

	// Particle
	Layer* fParticle = new Layer(1);


	Layer** layers = new Layer*[2];
	layers[0] = background;
	layers[1] = fParticle;

	Sequence* seq = new Sequence(layers, 2);

	// Background setup
	Number* speed = new Number(1);
	Product* h = new Product(speed, seq->getLocalTime());
	Number* s = new Number(1);
	Number* b = new Number(0.01);
	hsb* color = new hsb(h, s, b);
	background->setColor(color);

	// Forward Particle setup
	Lin* fParticleSpeed = new Lin(0.001, 0, seq->getLocalTime());
	Product* fParticlePosition = new Product(fParticleSpeed, seq->getLocalTime());
	fParticle->setPosition(fParticlePosition);

	Lin* ph = new Lin(360 / numLed, 0, fParticlePosition);
	Number* ps = new Number(1);
	Number* pb = new Number(0.9);
	hsb* fParticleColor = new hsb(ph, ps, pb);
	fParticle->setColor(fParticleColor);

	Integer* endPos = new Integer(numLed);
	Sup* stopCondition = new Sup(fParticlePosition, endPos);
	seq->setStopCondition(stopCondition);

	Layer** layers2 = new Layer*[2];
	layers2[0] = background;
	layers2[1] = fParticle;
	Sequence* seq2 = new Sequence(layers2, 2);

	Sequence** sequences = new Sequence*[1];
	sequences[0] = seq;

	return new Animation(sequences, 1);
}
