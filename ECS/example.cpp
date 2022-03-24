#include <iostream>
#include <bitset>

#include "ECS/Scene.h"
#include "Components/Components.h"
#include "Systems/Systems.h"
#include "ECS/EventHandler.h"

int main() {
	std::array<RendererComponent, 50> T1;
	for (auto& itr : T1) {
		std::cout << &itr << std::endl;
	}

	auto entityManager = std::make_unique<EntityManager>();
	auto eventHandler = std::make_unique<EventHandler>();
	Scene scene(std::move(entityManager), std::move(eventHandler));

	auto tSystem = std::make_unique<TransformSystem>();
	scene.addSystem(std::move(tSystem));

	auto combatSystem = std::make_unique<CombatSystem>();
	scene.addSystem(std::move(combatSystem));
	auto physicsSystem = std::make_unique<PhysicsSystem>();
	scene.addSystem(std::move(physicsSystem));

	auto e1 = scene.createEntity();
	auto e2 = scene.createEntity();
	auto e3 = scene.createEntity();

	scene.addComponent<RendererComponent>(e1, RendererComponent());
	scene.addComponent<TransformComponent>(e1, TransformComponent(10, 10));
	scene.addComponent<RendererComponent>(e2, RendererComponent());
	scene.addComponent<TransformComponent>(e2, TransformComponent(200, 20));
	scene.addComponent<RendererComponent>(e3, RendererComponent());
	scene.addComponent<TransformComponent>(e3, TransformComponent(300, 30));
	scene.addComponent<TransformComponent>(e3, TransformComponent(300, 30));

	scene.init();
	scene.update(1.0);
}

