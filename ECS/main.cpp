#include <iostream>
#include <bitset>

#include "Scene.h"
#include "Components.h"
#include "Systems.h"
#include "EventHandler.h"


int main() {
	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_shared<EventHandler>();
	Scene scene(std::move(entityManager), eventHandler);

	auto tSystem = std::make_unique<TransformSystem>();
	scene.addSystem(std::move(tSystem));

	auto combatSystem = std::make_unique<CombatSystem>();
	scene.addSystem(std::move(combatSystem));
	auto physicsSystem = std::make_unique<PhysicsSystem>();
	scene.addSystem(std::move(physicsSystem));

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
	scene.update();
}

