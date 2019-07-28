#include <memory>
#include "examples.h"

Animation* example2(uint16_t width, uint16_t height) {
	Animation* example2 = new Animation(16, 16);

	// Background
	std::shared_ptr<Layer> background = std::shared_ptr<Layer>(new Layer(16, 16));

	example2->layerScope.define("background", background);

	background.get()->setColor(
			std::shared_ptr<hsb>(
				new hsb(
					std::shared_ptr<Sin>(new Sin(
						std::shared_ptr<Number>(new Number(360)),
						std::shared_ptr<Dif>(new Dif(
							std::shared_ptr<Div>(new Div(
								background.get()->getYIndex(),
								std::shared_ptr<Number>(new Number(20))
								)
							),
							std::shared_ptr<Div>(new Div(
								example2->getGlobalTime(),
								std::shared_ptr<Number>(new Number(30))
								)
							)
						))
					)),
					std::shared_ptr<Number>(new Number(1)),
					std::shared_ptr<Number>(new Number(0.01))
					)
				)
			);

	std::shared_ptr<Scene> seq = std::shared_ptr<Scene>(new Scene());
	seq.get()->addLayer(example2->layerScope.get("background"));
	seq.get()->setStopCondition(std::shared_ptr<Condition>(new False()));

	example2->addScene(seq);

	return example2;
}
