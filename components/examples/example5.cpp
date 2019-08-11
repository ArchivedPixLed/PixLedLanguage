#include "pixled.h"
#include "examples.h"

Animation* example5(uint16_t length, uint16_t branches, uint16_t duration) {
	Animation* example5 = new Animation(length, branches);

	std::vector<std::shared_ptr<Layer>>* layers = new std::vector<std::shared_ptr<Layer>>();
	for(int i = 0; i < branches; i++) {
		std::shared_ptr<Layer> layer = std::shared_ptr<Layer>(new Layer(length, 1));
		layer.get()->setPosition(
				std::shared_ptr<Integer>(new Integer(0)),
				std::shared_ptr<Integer>(new Integer(i))
				);
		layers->push_back(layer);
	}

	std::shared_ptr<Scene> seq = std::shared_ptr<Scene>(new Scene());
	for(int i = 0; i < branches; i++) {
		seq.get()->addLayer(layers->at(i));
	}

	for(int i = 0; i < branches; i++) {
		int init;
		int max;
		if(i % 2) {
			init = - length / 2;
			max = length + length / 2;
		}
		else {
			max = - length / 2;
			init = length + length / 2;
		}

		std::shared_ptr<TranslatedPoint> center = std::shared_ptr<TranslatedPoint>(new TranslatedPoint(
					example5->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(init)),
					std::shared_ptr<Integer>(new Integer(0))
					));

		center.get()->translateTo(
				std::shared_ptr<Integer>(new Integer(max)),
				std::shared_ptr<Integer>(new Integer(0)),
				std::shared_ptr<Integer>(new Integer(100))
				);

		center.get()->translateTo(
				std::shared_ptr<Integer>(new Integer(init)),
				std::shared_ptr<Integer>(new Integer(0)),
				std::shared_ptr<Integer>(new Integer(100))
				);

		layers->at(i).get()->setColor(std::shared_ptr<hsb>(
				new hsb(
					std::shared_ptr<Sin>(new Sin(
						std::shared_ptr<Integer>(new Integer(360)),
							std::shared_ptr<Div>(new Div(
								std::shared_ptr<Distance>(new Distance(layers->at(i).get()->pointIndex(), center)),
								std::shared_ptr<Number>(new Number(10))
								)
							)
					)),
					std::shared_ptr<Lin2>(new Lin2(
						std::shared_ptr<Number>(new Number(-0.03)),
						1,
						std::shared_ptr<Distance>(new Distance(layers->at(i).get()->pointIndex(), center))
					)),
					std::shared_ptr<Lin2>(new Lin2(
						std::shared_ptr<Number>(new Number(-0.03)),
						1,
						std::shared_ptr<Distance>(new Distance(layers->at(i).get()->pointIndex(), center))
					))
					)
				)
				);

	}

//	seq.get()->setStopCondition(std::shared_ptr<False>(new False()));
	seq.get()->setStopCondition(std::shared_ptr<Sup>(new Sup(
					example5->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(duration))
					)));

	example5->addScene(seq);

	return example5;
}
