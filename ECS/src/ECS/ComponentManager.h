#pragma once

#include <functional>

#include "ECS/SparseSet.h"
#include "ECS/Pool.h"

namespace ECS {
	class IComponentManager {
	public:
		virtual ~IComponentManager() {}
		virtual void OnDestroyEntity(EntityID e) = 0;
	};

	template<typename ComponentType>
	class ComponentManager : public IComponentManager {
	private:
		Pool<ComponentType, MAX_COMPONENTS> m_pool;
		SparseSet m_sparseSet;
		std::size_t m_size;

	public:
		ComponentManager() = default;
		ComponentManager(const ComponentManager&) = delete;
		ComponentManager& operator = (const ComponentManager&) = delete;
		~ComponentManager() {
			for (int i = 0; i < m_size; ++i)
				m_pool.Destroy(i);
		}

		template<typename ... Args>
		ComponentType* Add(EntityID e, Args && ... args) {
			auto ptr = m_pool.Get(m_size);
			::new(ptr) ComponentType(std::forward<Args>(args) ...);
			m_sparseSet.Add(e, m_size);
			m_size++;
			return ptr;
		}

		inline ComponentType* Get(EntityID e) {
			assert(m_size > m_sparseSet.GetInstance(e) && "n must be smaller than current size");
			return m_pool.Get(m_sparseSet.GetInstance(e));
		}

		void Remove(EntityID e) {
			auto instance = m_sparseSet.GetInstance(e);
			auto lastInstance = m_size - 1;
			auto lastEntityID = m_sparseSet.GetEntity(lastInstance);

			assert(m_size > instance && "n must be smaller than current size");

			m_pool.Destroy(e);

			if (instance != lastInstance) {
				*(m_pool.Get(instance)) = *(m_pool.Get(lastInstance));
				m_sparseSet.Update(lastEntityID, instance);
			}
			m_size--;
		}

		void OnDestroyEntity(EntityID e) override {
			Remove(e);
		}

		void IterateAll(const std::function<void(ComponentType* c)> lambda) {
		}
	};
}
