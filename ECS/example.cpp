#include <iostream>
#include <bitset>

#include "ECS/Scene.h"
#include "Components/Transform.h"
#include "Components/Relationship.h"

#include "Systems/Systems.h"
#include "ECS/EventHandler.h"

using namespace ECS;

template <class T, class Allocator >
class MyVector {
private:
	T* data_;
	std::size_t size_;
	Allocator alloc_;

public:
	MyVector(std::size_t size) {
		using traits = std::allocator_traits<Allocator>;

		size_ = size;

		data_ = traits::allocate(alloc_, size);

		for (std::size_t i = 0; i < size_; ++i) {
			traits::construct(alloc_, &data_[i]);
		}
	}

	~MyVector() {
		using traits = std::allocator_traits<Allocator>;

		for (std::size_t i = 0; i < size_; ++i) {
			traits::destroy(alloc_, &data_[i]);
		}

		traits::deallocate(alloc_, data_, size_);
	}

	int& at(std::size_t n) {
		return data_[n];
	}
};

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

