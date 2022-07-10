#include <iostream>
#include <bitset>

#include "ECS/Scene.h"
#include "Components/Transform.h"
#include "Components/Relationship.h"

#include "Systems/Systems.h"
#include "ECS/EventHandler.h"

using namespace ECS;

int main() {
	Scene* scene = new Scene();

	auto transformSystem = std::make_unique<TransformSystem>();
	scene->addSystem(std::move(transformSystem));

	auto parent = scene->createEntity();
	scene->addComponent<TransformComponent>(parent, TransformComponent(10.0, 10.0));

	for (int i = 0; i < 50000; ++i) {
		auto child = scene->createEntity();
		scene->getComponent<Relationship>(child)->parent = parent;
		scene->addComponent<TransformComponent>(child, TransformComponent(1.0, 1.0));
	}

	std::cout << scene->getComponent<TransformComponent>(2)->x << std::endl;

	scene->init();
	scene->update(1.0f);

	std::cout << scene->getComponent<TransformComponent>(2)->x << std::endl;

	delete scene;
}

