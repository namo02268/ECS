#include <iostream>
#include <bitset>

#include "Scene.h"
#include "EntityHandle.h"
#include "Components.h"
#include "System.h"

int main() {
	auto entityManager = std::make_unique<EntityManager>();
	Scene scene(std::move(entityManager));

	auto e1 = scene.createEntity();
	auto e2 = scene.createEntity();
	auto e3 = scene.createEntity();
	auto e4 = scene.createEntity();
	scene.addComponent<TransformComponent>(e1);
	scene.addComponent<TransformComponent>(e2);
	scene.addComponent<TransformComponent>(e3);

	scene.removeComponent<TransformComponent>(e2);
	scene.addComponent<TransformComponent>(e4);
}