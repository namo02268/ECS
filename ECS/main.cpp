#include <iostream>
#include <bitset>

#include "Scene.h"
#include "Components.h"

int main() {
	auto entityManager = std::make_unique<EntityManager>();
	Scene scene(std::move(entityManager));


}