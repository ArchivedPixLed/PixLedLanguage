#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include "layer.h"
#include "logic.h"
#include "numeric.h"
#include "scope.h"

class Scene {
	public:
		Scene();
		void addLayer(std::shared_ptr<Layer> layer);
		void setStopCondition(std::shared_ptr<Condition> stopCondition);
		std::shared_ptr<Integer> getLocalTime();
		void run(RenderingLayer* rendering_layer, std::shared_ptr<Integer> globalTime);
		~Scene();
		LayerScope layerScope;
		OperatorScope operatorScope;

	private:
		std::shared_ptr<Integer> localTime;
		std::shared_ptr<Condition> stopCondition;
		std::vector<std::shared_ptr<Layer>> layers;
};

class SceneScope : public Scope<std::shared_ptr<Scene>> {

};

#endif //SEQUENCE_H
