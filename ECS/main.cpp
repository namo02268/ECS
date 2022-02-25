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

	scene.addComponent<RendererComponent>(e1);
	scene.addComponent<TransformComponent>(e1, 10);
	scene.addComponent<ColliderComponent>(e1);
	scene.addComponent<RendererComponent>(e2);
	scene.addComponent<TransformComponent>(e2, 20);

	scene.init();
}

