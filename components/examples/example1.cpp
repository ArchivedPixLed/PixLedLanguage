#include <memory>
#include "examples.h"

Animation* example1(uint16_t numLed) {

	Animation* example1 = new Animation(256, 1);

	// Background
	LAYER_T background = LAYER(numLed, 1);

	example1->layerScope.define("background", background);

	// Forward Particle
	LAYER_T fParticle = LAYER(1, 1);

	SCENE_T seq = SCENE();
	seq.get()->addLayer(example1->layerScope.get("background"));
	seq.get()->addLayer(fParticle);

	// Background setup
	HSB_T color = HSB(
				PRODUCT(NUM(2), example1->getGlobalTime()),
				NUM(1),
				NUM(0.01)
				);
			
	/*
	std::shared_ptr<hsb> color = std::shared_ptr<hsb>(
		new hsb(
			std::shared_ptr<Product>(new Product(NUM(2)), NUM(4)))),
			NUM(1)),
			NUM(0.01))
			)
		);
	*/
	background->setColor(color);

	// Forward Particle setup
	std::shared_ptr<Lin> fParticleSpeed = std::shared_ptr<Lin>(new Lin(0.001, 0, seq.get()->getLocalTime()));
	PRODUCT_T fParticlePosition = PRODUCT(fParticleSpeed, seq.get()->getLocalTime());
	fParticle.get()->setX(fParticlePosition);

	HSB_T fParticleColor = HSB( 
				std::shared_ptr<Lin>(new Lin(360 / numLed, 0, fParticlePosition)),
				NUM(1),
				NUM(0.9)
				);

	fParticle.get()->setColor(fParticleColor);

	INT_T endPos = INT(numLed);
	std::shared_ptr<Sup> stopCondition = std::shared_ptr<Sup>(new Sup(fParticlePosition, endPos));
	seq.get()->setStopCondition(stopCondition);

	// Backward Particle
	LAYER_T bParticle = LAYER(1, 1);

	SCENE_T seq2 = SCENE();
	seq2.get()->addLayer(background);
	seq2.get()->addLayer(bParticle);


	// Backward Particle setup
	std::shared_ptr<Lin> bParticleSpeed = std::shared_ptr<Lin>(new Lin(-0.001, 0, seq2.get()->getLocalTime()));
	std::shared_ptr<Lin2> bParticlePosition = std::shared_ptr<Lin2>(new Lin2(bParticleSpeed, numLed, seq2.get()->getLocalTime()));
	bParticle.get()->setX(bParticlePosition);

	HSB_T bParticleColor = HSB(
			std::shared_ptr<Lin>(new Lin(360 / numLed, 0, bParticlePosition)),
			NUM(1),
			NUM(0.9)
			);
	bParticle.get()->setColor(bParticleColor);

	INT_T endPos2 = INT(0);
	std::shared_ptr<Inf> stopCondition2 = std::shared_ptr<Inf>(new Inf(bParticlePosition, endPos2));
	seq2.get()->setStopCondition(stopCondition2);

	example1->addScene(seq);
	example1->addScene(seq2);

	return example1;
}
