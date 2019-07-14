#include "examples.h"

Animation* example1(uint16_t numLed) {

	Animation* example1 = new Animation(2);

	// Background
	Layer* background = new Layer(numLed);
	Integer* backPos = new Integer(0);
	background->setPosition(backPos);

	// Forward Particle
	Layer* fParticle = new Layer(1);


	Layer** layers = new Layer*[2];
	layers[0] = background;
	layers[1] = fParticle;

	Sequence* seq = new Sequence(layers, 2);

	// Background setup
	Number* speed = new Number(2);
	Product* h = new Product(speed, example1->getGlobalTime());
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

	// Backward Particle
	Layer* bParticle = new Layer(1);

	Layer** layers2 = new Layer*[2];
	layers2[0] = background;
	layers2[1] = bParticle;
	Sequence* seq2 = new Sequence(layers2, 2);


	// Backward Particle setup
	Lin* bParticleSpeed = new Lin(-0.001, 0, seq2->getLocalTime());
	Lin2* bParticlePosition = new Lin2(bParticleSpeed, numLed, seq2->getLocalTime());
	bParticle->setPosition(bParticlePosition);

	Lin* bph = new Lin(360 / numLed, 0, bParticlePosition);
	Number* bps = new Number(1);
	Number* bpb = new Number(0.9);
	hsb* bParticleColor = new hsb(bph, bps, bpb);
	bParticle->setColor(bParticleColor);

	Integer* endPos2 = new Integer(0);
	Inf* stopCondition2 = new Inf(bParticlePosition, endPos2);
	seq2->setStopCondition(stopCondition2);

	Sequence** sequences = new Sequence*[2];
	sequences[0] = seq;
	sequences[1] = seq2;

	example1->setSequences(sequences);

	return example1;
}
