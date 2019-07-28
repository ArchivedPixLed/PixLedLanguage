#include <memory>
#include "examples.h"
#include "out.h"

Animation* example3(uint16_t width, uint16_t height) {
	Animation* example3 = new Animation(16, 16);


	/*
	 * SEQ 1
	 */
	std::shared_ptr<Layer> bg1 = std::shared_ptr<Layer>(new Layer(16, 16));
	example3->layerScope.define("bg1", bg1);

	std::shared_ptr<Scene> seq1 = std::shared_ptr<Scene>(new Scene());

	std::shared_ptr<Integer> x0 = std::shared_ptr<Integer>(new Integer(0));
	std::shared_ptr<Integer> y0 = std::shared_ptr<Integer>(new Integer(0));

	std::shared_ptr<TranslatedPoint> center = std::shared_ptr<TranslatedPoint>(new TranslatedPoint(
			example3->getGlobalTime(),
			x0,
			y0
			));

	center.get()->translateTo(
			std::shared_ptr<Integer>(new Integer(16)),
			std::shared_ptr<Integer>(new Integer(16)),
			std::shared_ptr<Integer>(new Integer(100))
			);
	center.get()->translateTo(
			std::shared_ptr<Integer>(new Integer(0)),
			std::shared_ptr<Integer>(new Integer(16)),
			std::shared_ptr<Integer>(new Integer(100))
			);
	center.get()->translateTo(
			std::shared_ptr<Integer>(new Integer(16)),
			std::shared_ptr<Integer>(new Integer(0)),
			std::shared_ptr<Integer>(new Integer(100))
			);
	center.get()->translateTo(
			std::shared_ptr<Integer>(new Integer(0)),
			std::shared_ptr<Integer>(new Integer(0)),
			std::shared_ptr<Integer>(new Integer(100))
			);

	bg1.get()->setColor(
			std::shared_ptr<hsb>(
				new hsb(
					std::shared_ptr<Sin>(new Sin(
						std::shared_ptr<Integer>(new Integer(360)),
						std::shared_ptr<Dif>(new Dif(
							std::shared_ptr<Div>(new Div(
								std::shared_ptr<Distance>(new Distance(bg1.get()->pointIndex(), center)),
								std::shared_ptr<Number>(new Number(12))
								)
							),
							std::shared_ptr<Div>(new Div(
								example3->getGlobalTime(),
								std::shared_ptr<Number>(new Number(30))
								)
							)
						))
					)),
					std::shared_ptr<Lin2>(new Lin2(
						std::shared_ptr<Number>(new Number(-0.06)),
						1,
						std::shared_ptr<Distance>(new Distance(bg1.get()->pointIndex(), center))
					)),
					std::shared_ptr<Lin2>(new Lin2(
						std::shared_ptr<Number>(new Number(-0.09)),
						1,
						std::shared_ptr<Distance>(new Distance(bg1.get()->pointIndex(), center))
					))
					)
				)
			);

	seq1.get()->addLayer(example3->layerScope.get("bg1"));
	seq1.get()->setStopCondition(std::shared_ptr<False>(new False()));


	/*
	 * ANIMATION
	 */
	example3->addScene(seq1);

	return example3;
}
