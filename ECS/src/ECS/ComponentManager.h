#pragma once

#include <functional>

#include "ECS/SparseSet.h"

namespace ECS {
	class IComponentManager {
	public:
		virtual ~IComponentManager() {}
		virtual void OnDestroyEntity(Entity& e) = 0;
	};

	template<typename ComponentType>
	class ComponentManager : public IComponentManager {
	private:
		std::array<ComponentType, MAX_COMPONENTS>* m_componentArray;
		SparseSet m_entityMap;
		ComponentInstance m_newInstance = 0;

	public:
		ComponentManager() {
			m_componentArray = static_cast<std::array<ComponentType, MAX_COMPONENTS> *>(malloc(sizeof(ComponentType) * MAX_COMPONENTS));
		}

		~ComponentManager() {
			free(m_componentArray);
		}

		void AddComponent(Entity& e, ComponentType&& c) {
			m_componentArray->at(m_newInstance) = std::forward<ComponentType>(c);
			m_entityMap.Add(e, m_newInstance);

			++m_newInstance;
		}

		void RemoveComponent(const Entity& e) {
			ComponentInstance instance = m_entityMap.GetInstance(e);
			ComponentInstance lastInstance = m_newInstance - 1;
			Entity lastEntity = m_entityMap.GetEntity(lastInstance);

//			m_entityMap.remove(e);

			if (instance != lastInstance) {
				m_componentArray->at(instance) = m_componentArray->at(lastInstance);
				m_entityMap.Update(lastEntity, instance);
			}

			--m_newInstance;
		}

		ComponentType* GetComponent(const Entity& e) {
			return &m_componentArray->at(m_entityMap.GetInstance(e));
		}

		void OnDestroyEntity(Entity& e) override {
			RemoveComponent(e);
		}

		void IterateAll(const std::function<void(ComponentType* c)> lambda) {
			for (int i = 0; i < m_newInstance; ++i) {
				lambda(&m_componentArray->at(i));
			}
		}
	};
}
