#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>
#include <vector>
#include "LedStrip.h"
#include "scene.h"
#include "scope.h"

class Animation {
	public:
		Animation(uint16_t width, uint16_t height);
		void addScene(std::shared_ptr<Scene> scene);
		std::shared_ptr<Integer> getGlobalTime();
		void run(Strip* strip);
		~Animation();
		LayerScope layerScope;
		SceneScope sceneScope;
		OperatorScope operatorScope;

	private:
		uint16_t width;
		uint16_t height;
		std::shared_ptr<Integer> globalTime;
		std::vector<std::shared_ptr<Scene>> scenes;
};

#endif //ANIMATION_H
