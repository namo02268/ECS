#pragma once

#include "Scene.h"

class Scene;

class EntityHandle {
public:
	Entity entity;
	Scene* scene;

public:
	EntityHandle(Entity entity, Scene* scene) {
		this->scene = scene;
		this->entity = entity;
	}

	template<typename ComponentType>
	void addComponent() {
		scene->addComponent(entity);
	}
};
