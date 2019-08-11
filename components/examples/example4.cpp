#include <memory>
#include "examples.h"

Animation* example4(uint16_t width, uint16_t height, uint16_t period, float intensity, uint16_t duration) {
	Animation* example4 = new Animation(width, height);

	// Background
	std::shared_ptr<Layer> background = std::shared_ptr<Layer>(new Layer(width, height));

	example4->layerScope.define("background", background);

	std::shared_ptr<Sequence> seq = std::shared_ptr<Sequence>(new Sequence());
	seq.get()->addItem(
			std::shared_ptr<TimedSequenceItem>(new TimedSequenceItem(
					std::shared_ptr<Integer>(new Integer(0)),
					example4->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(period))
					)
				)
			);
	seq.get()->addItem(
			std::shared_ptr<TimedSequenceItem>(new TimedSequenceItem(
					std::shared_ptr<Integer>(new Integer(90)),
					example4->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(period))
					)
				)
			);

	seq.get()->addItem(
			std::shared_ptr<TimedSequenceItem>(new TimedSequenceItem(
					std::shared_ptr<Integer>(new Integer(180)),
					example4->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(period))
					)
				)
			);

	seq.get()->addItem(
			std::shared_ptr<TimedSequenceItem>(new TimedSequenceItem(
					std::shared_ptr<Integer>(new Integer(270)),
					example4->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(period))
					)
				)
			);

	background.get()->setColor(
			std::shared_ptr<hsb>(
				new hsb(
					seq,
					std::shared_ptr<Number>(new Number(1)),
					std::shared_ptr<Number>(new Number(intensity))
					)
				)
			);

	std::shared_ptr<Scene> scene = std::shared_ptr<Scene>(new Scene());
	scene.get()->addLayer(example4->layerScope.get("background"));
//	scene.get()->setStopCondition(std::shared_ptr<Condition>(new False()));
	scene.get()->setStopCondition(std::shared_ptr<Sup>(new Sup(
					example4->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(duration))
					)));

	example4->addScene(scene);

	return example4;
}
