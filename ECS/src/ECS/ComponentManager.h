#pragma once

#include <functional>

#include "ECS/SparseSet.h"
#include "ECS/Pool.h"

namespace ECS {
	class IComponentManager {
	public:
		virtual ~IComponentManager() {}
		virtual void OnDestroyEntity(Entity& e) = 0;
	};

	template<typename ComponentType>
	class ComponentManager : public IComponentManager {
	private:
		Pool<ComponentType, MAX_COMPONENTS> m_componentPool;
		SparseSet m_sparseSet;

	public:
		ComponentManager() = default;
		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator = (const ComponentManager&) = delete;
		~ComponentManager() = default;

		template<typename ... Args>
		void AddComponent(Args && ... args) {
			m_componentPool.Add(std::forward<Args>(args) ...);
		}

		void RemoveComponent(const Entity& e) {
		}

		ComponentType* GetComponent(const Entity& e) {
		}

		void OnDestroyEntity(Entity& e) override {
		}

		void IterateAll(const std::function<void(ComponentType* c)> lambda) {
		}
	};
}
