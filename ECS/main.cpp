#include <iostream>
#include <bitset>

#include "Scene.h"
#include "Components.h"
#include "Systems.h"

int main() {
	auto entityManager = std::make_unique<EntityManager>();
	Scene scene(std::move(entityManager));

	auto tSystem = std::make_unique<TransformSystem>();
	scene.addSystem(std::move(tSystem));

	auto e1 = scene.createEntity();
	auto e2 = scene.createEntity();
	auto e3 = scene.createEntity();

	scene.addComponent<RendererComponent>(e1);
	scene.addComponent<TransformComponent>(e1, 10, 10);
	scene.addComponent<RendererComponent>(e2);
	scene.addComponent<TransformComponent>(e2, 200, 20);
	scene.addComponent<RendererComponent>(e3);
	scene.addComponent<TransformComponent>(e3, 300, 30);

	scene.init();
}

