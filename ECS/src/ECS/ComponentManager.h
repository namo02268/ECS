#pragma once

#include <functional>

#include "ECS/EntityMap.h"

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
		EntityMap m_entityMap;
		ComponentInstance m_newInstance = 0;

	public:
		ComponentManager() {
			m_componentArray = static_cast<std::array<ComponentType, MAX_COMPONENTS> *>(malloc(sizeof(ComponentType) * MAX_COMPONENTS));
		}

		~ComponentManager() {
			free(m_componentArray);
		}

		void addComponent(Entity& e, ComponentType&& c) {
			m_componentArray->at(m_newInstance) = std::forward<ComponentType>(c);
			m_entityMap.add(e, m_newInstance);

			++m_newInstance;
		}

		void removeComponent(const Entity& e) {
			ComponentInstance instance = m_entityMap.getInstance(e);
			ComponentInstance lastInstance = m_newInstance - 1;
			Entity lastEntity = m_entityMap.getEntity(lastInstance);

//			m_entityMap.remove(e);

			if (instance != lastInstance) {
				m_componentArray->at(instance) = m_componentArray->at(lastInstance);
				m_entityMap.update(lastEntity, instance);
			}

			--m_newInstance;
		}

		ComponentType* getComponent(const Entity& e) {
			return &m_componentArray->at(m_entityMap.getInstance(e));
		}

		void OnDestroyEntity(Entity& e) override {
			removeComponent(e);
		}

		void iterateAll(const std::function<void(ComponentType* c)> lambda) {
			for (int i = 0; i < m_newInstance; ++i) {
				lambda(&m_componentArray->at(i));
			}
		}
	};
}
