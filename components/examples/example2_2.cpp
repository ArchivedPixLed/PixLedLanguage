#include <memory>
#include "examples.h"

Animation* example2_2(uint16_t width, uint16_t height, float timePeriod, float spacePeriod, float intensity, uint16_t duration) {
	Animation* example2 = new Animation(width, height);

	// Background
	std::shared_ptr<Layer> background = std::shared_ptr<Layer>(new Layer(width, height));

//	example2->layerScope.define("background", background);

	background.get()->setColor(
			std::shared_ptr<hsb>(
				new hsb(
					std::shared_ptr<Sin>(new Sin(
						std::shared_ptr<Number>(new Number(360)),
						std::shared_ptr<Dif>(new Dif(
							std::shared_ptr<Div>(new Div(
								background.get()->getXIndex(),
								std::shared_ptr<Number>(new Number(spacePeriod))
								)
							),
							std::shared_ptr<Div>(new Div(
								example2->getGlobalTime(),
								std::shared_ptr<Number>(new Number(timePeriod))
								)
							)
						))
					)),
					std::shared_ptr<Number>(new Number(1)),
					std::shared_ptr<Number>(new Number(intensity))
					)
				)
			);

	std::shared_ptr<Scene> seq = std::shared_ptr<Scene>(new Scene());
//	seq.get()->addLayer(example2->layerScope.get("background"));
	seq.get()->addLayer(background);
//	seq.get()->setStopCondition(std::shared_ptr<Condition>(new False()));
	seq.get()->setStopCondition(std::shared_ptr<Sup>(new Sup(
					example2->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(duration))
					)));
	
	example2->addScene(seq);

	return example2;
}
