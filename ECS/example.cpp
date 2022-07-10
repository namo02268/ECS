#include <iostream>
#include <bitset>

#include "ECS/Scene.h"
#include "Components/Transform.h"
#include "Systems/Systems.h"
#include "ECS/EventHandler.h"

using namespace ECS;

int main() {
	Scene* scene = new Scene();

	auto e1 = scene->createEntity();
	auto e2 = scene->createEntity();
	auto e3 = scene->createEntity();

	scene->addComponent(e1, TransformComponent(10, 10));
	scene->addComponent(e2, TransformComponent(10, 10));
	scene->addComponent(e3, TransformComponent(10, 10));

	std::cout << scene->getComponent<TransformComponent>(e1) << std::endl;
	std::cout << scene->getComponent<TransformComponent>(e2) << std::endl;
	std::cout << scene->getComponent<TransformComponent>(e3) << std::endl;

	scene->destroyEntity(e1);
	auto e4 = scene->createEntity();
	scene->addComponent(e4, TransformComponent(10, 10));

	std::cout << scene->getComponent<TransformComponent>(e1) << std::endl;
	std::cout << scene->getComponent<TransformComponent>(e2) << std::endl;
	std::cout << scene->getComponent<TransformComponent>(e4) << std::endl;

	scene->init();
	scene->update(1.0);

	delete scene;
}

