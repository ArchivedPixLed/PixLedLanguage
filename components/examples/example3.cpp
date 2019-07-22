#include <memory>
#include "examples.h"

Animation* example3(uint16_t width, uint16_t height) {
	Animation* example3 = new Animation(16, 16);


	/*
	 * SEQ 1
	 */
	std::shared_ptr<Layer> bg1 = std::shared_ptr<Layer>(new Layer(16, 16));
	example3->layerScope.define("bg1", bg1);

	std::shared_ptr<Sequence> seq1 = std::shared_ptr<Sequence>(new Sequence());

	std::shared_ptr<Product> xCenter = std::shared_ptr<Product>(new Product(
			std::shared_ptr<Number>(new Number(0.1)),
			seq1.get()->getLocalTime()
			)
		);

	std::shared_ptr<Point> center = std::shared_ptr<Point>(new Point(
			xCenter,
			std::shared_ptr<Integer>(new Integer(0))
			)
		);

	bg1.get()->setColor(
			std::shared_ptr<hsb>(
				new hsb(
					std::shared_ptr<Sum>(new Sum(
						std::shared_ptr<Product>(new Product(
							std::shared_ptr<Number>(new Number(5)),
							std::shared_ptr<Distance>(new Distance(bg1.get()->pointIndex(), center))
							)
						),
						std::shared_ptr<Product>(new Product(
							std::shared_ptr<Number>(new Number(-2)),
							example3->getGlobalTime()
							)
						)
					)),
					std::shared_ptr<Number>(new Number(1)),
					std::shared_ptr<Number>(new Number(0.01))
					)
				)
			);

	seq1.get()->addLayer(example3->layerScope.get("bg1"));
	seq1.get()->setStopCondition(std::shared_ptr<Sup>(new Sup(xCenter, std::shared_ptr<Integer>(new Integer(16)))));

	/*
	 * SEQ2
	 */
	std::shared_ptr<Layer> bg2 = std::shared_ptr<Layer>(new Layer(16, 16));
	example3->layerScope.define("bg2", bg2);

	std::shared_ptr<Sequence> seq2 = std::shared_ptr<Sequence>(new Sequence());

	std::shared_ptr<Product> yCenter2 = std::shared_ptr<Product>(new Product(
			std::shared_ptr<Number>(new Number(0.1)),
			seq2.get()->getLocalTime()
			)
		);

	std::shared_ptr<Point> center2 = std::shared_ptr<Point>(new Point(
			std::shared_ptr<Integer>(new Integer(16)),
			yCenter2
			)
		);

	bg2.get()->setColor(
			std::shared_ptr<hsb>(
				new hsb(
					std::shared_ptr<Sum>(new Sum(
						std::shared_ptr<Product>(new Product(
							std::shared_ptr<Number>(new Number(5)),
							std::shared_ptr<Distance>(new Distance(bg2.get()->pointIndex(), center2))
							)
						),
						std::shared_ptr<Product>(new Product(
							std::shared_ptr<Number>(new Number(-2)),
							example3->getGlobalTime()
							)
						)
					)),
					std::shared_ptr<Number>(new Number(1)),
					std::shared_ptr<Number>(new Number(0.01))
					)
				)
			);

	seq2.get()->addLayer(example3->layerScope.get("bg2"));
	seq2.get()->setStopCondition(std::shared_ptr<Sup>(new Sup(yCenter2, std::shared_ptr<Integer>(new Integer(16)))));

	/*
	 * SEQ3
	 */
	std::shared_ptr<Layer> bg3 = std::shared_ptr<Layer>(new Layer(16, 16));
	example3->layerScope.define("bg3", bg3);

	std::shared_ptr<Sequence> seq3 = std::shared_ptr<Sequence>(new Sequence());

	std::shared_ptr<Sum> xCenter3 = std::shared_ptr<Sum>(new Sum(
				std::shared_ptr<Integer>(new Integer(16)),
				std::shared_ptr<Product>(new Product(
					std::shared_ptr<Number>(new Number(-0.1)),
					seq3.get()->getLocalTime()
					)
				)
		));

	std::shared_ptr<Point> center3 = std::shared_ptr<Point>(new Point(
			xCenter3,
			std::shared_ptr<Integer>(new Integer(16))
			)
		);

	bg3.get()->setColor(
			std::shared_ptr<hsb>(
				new hsb(
					std::shared_ptr<Sum>(new Sum(
						std::shared_ptr<Product>(new Product(
							std::shared_ptr<Number>(new Number(5)),
							std::shared_ptr<Distance>(new Distance(bg3.get()->pointIndex(), center3))
							)
						),
						std::shared_ptr<Product>(new Product(
							std::shared_ptr<Number>(new Number(-2)),
							example3->getGlobalTime()
							)
						)
					)),
					std::shared_ptr<Number>(new Number(1)),
					std::shared_ptr<Number>(new Number(0.01))
					)
				)
			);

	seq3.get()->addLayer(example3->layerScope.get("bg3"));
	seq3.get()->setStopCondition(std::shared_ptr<Inf>(new Inf(xCenter3, std::shared_ptr<Integer>(new Integer(0)))));

	/*
	 * SEQ4
	 */
	std::shared_ptr<Layer> bg4 = std::shared_ptr<Layer>(new Layer(16, 16));
	example3->layerScope.define("bg4", bg4);

	std::shared_ptr<Sequence> seq4 = std::shared_ptr<Sequence>(new Sequence());

	std::shared_ptr<Sum> yCenter4 = std::shared_ptr<Sum>(new Sum(
				std::shared_ptr<Integer>(new Integer(16)),
				std::shared_ptr<Product>(new Product(
					std::shared_ptr<Number>(new Number(-0.1)),
					seq4.get()->getLocalTime()
					)
				)
		));

	std::shared_ptr<Point> center4 = std::shared_ptr<Point>(new Point(
			std::shared_ptr<Integer>(new Integer(0)),
			yCenter4
			)
		);

	bg4.get()->setColor(
			std::shared_ptr<hsb>(
				new hsb(
					std::shared_ptr<Sum>(new Sum(
						std::shared_ptr<Product>(new Product(
							std::shared_ptr<Number>(new Number(5)),
							std::shared_ptr<Distance>(new Distance(bg4.get()->pointIndex(), center4))
							)
						),
						std::shared_ptr<Product>(new Product(
							std::shared_ptr<Number>(new Number(-2)),
							example3->getGlobalTime()
							)
						)
					)),
					std::shared_ptr<Number>(new Number(1)),
					std::shared_ptr<Number>(new Number(0.01))
					)
				)
			);

	seq4.get()->addLayer(example3->layerScope.get("bg4"));
	seq4.get()->setStopCondition(std::shared_ptr<Inf>(new Inf(yCenter4, std::shared_ptr<Integer>(new Integer(0)))));

	/*
	 * ANIMATION
	 */
	example3->addSequence(seq1);
	example3->addSequence(seq2);
	example3->addSequence(seq3);
	example3->addSequence(seq4);

	return example3;
}
