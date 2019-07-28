#include <memory>
#include "examples.h"

Animation* example4(uint16_t width, uint16_t height) {
	Animation* example4 = new Animation(16, 16);

	// Background
	std::shared_ptr<Layer> background = std::shared_ptr<Layer>(new Layer(16, 16));

	example4->layerScope.define("background", background);

	std::shared_ptr<Sequence> seq = std::shared_ptr<Sequence>(new Sequence());
	seq.get()->addItem(
			std::shared_ptr<TimedSequenceItem>(new TimedSequenceItem(
					std::shared_ptr<Integer>(new Integer(0)),
					example4->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(10))
					)
				)
			);
	seq.get()->addItem(
			std::shared_ptr<TimedSequenceItem>(new TimedSequenceItem(
					std::shared_ptr<Integer>(new Integer(90)),
					example4->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(10))
					)
				)
			);

	seq.get()->addItem(
			std::shared_ptr<TimedSequenceItem>(new TimedSequenceItem(
					std::shared_ptr<Integer>(new Integer(180)),
					example4->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(10))
					)
				)
			);

	seq.get()->addItem(
			std::shared_ptr<TimedSequenceItem>(new TimedSequenceItem(
					std::shared_ptr<Integer>(new Integer(270)),
					example4->getGlobalTime(),
					std::shared_ptr<Integer>(new Integer(10))
					)
				)
			);

	background.get()->setColor(
			std::shared_ptr<hsb>(
				new hsb(
					seq,
					std::shared_ptr<Number>(new Number(1)),
					std::shared_ptr<Number>(new Number(0.1))
					)
				)
			);

	std::shared_ptr<Scene> scene = std::shared_ptr<Scene>(new Scene());
	scene.get()->addLayer(example4->layerScope.get("background"));
	scene.get()->setStopCondition(std::shared_ptr<Condition>(new False()));

	example4->addScene(scene);

	return example4;
}
