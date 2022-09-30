#include <iostream>

#include "ECS/ECS.h"
#include "Components/Transform.h"
#include "Components/Relationship.h"

#include "Systems/Systems.h"
#include "ECS/EventHandler.h"


int main() {
	ECS::ECS* scene = new ECS::ECS();

	auto transformSystem = std::make_unique<ECS::TransformSystem>();
	scene->AddSystem(std::move(transformSystem));

	auto parent = scene->CreateEntity();
	scene->AddComponent<ECS::TransformComponent>(parent, ECS::TransformComponent(10.0, 10.0));

	for (int i = 0; i < 50000; ++i) {
		auto child = scene->CreateEntity();
		scene->GetComponent<ECS::Relationship>(child)->parent = parent;
		scene->AddComponent<ECS::TransformComponent>(child, ECS::TransformComponent(1.0, 1.0));
	}

	std::cout << scene->GetComponent<ECS::TransformComponent>(2)->x << std::endl;

	scene->Init();
	scene->Update(1.0f);

	std::cout << scene->GetComponent<ECS::TransformComponent>(2)->x << std::endl;

	delete scene;
}

