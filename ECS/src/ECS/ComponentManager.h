#pragma once

#include <functional>
#include "ECS/EntityComponentMap.h"

namespace ECS {
	class IComponentManager {
	public:
		virtual ~IComponentManager() {}
	};

	template<class ComponentType>
	class ComponentManager : public IComponentManager{
	private:
		std::array<ComponentType, MAX_COMPONENTS>* m_componentArray;
		EntityComponentMap m_ecMap;
		ComponentInstanceID m_newInstance = 1;
	public:
		ComponentManager() {
			m_componentArray = static_cast<std::array<ComponentType, MAX_COMPONENTS> *>(malloc(sizeof(ComponentType) * MAX_COMPONENTS));
		}

		~ComponentManager() {
			free(m_componentArray);
		}

		void addComponent(Entity& e, ComponentType&& c) {
			m_componentArray->at(m_newInstance) = std::forward<ComponentType>(c);
			m_ecMap.add(e, m_newInstance);

			++m_newInstance;
		}

		void removeComponent(const Entity& e) {
			ComponentInstanceID instance = m_ecMap.getInstance(e);
			ComponentInstanceID lastInstance = m_newInstance - 1;
			Entity lastEntity = m_ecMap.getEntity(lastInstance);

			if (instance != lastInstance) {
				m_componentArray->at(instance) = m_componentArray->at(lastInstance);
				m_ecMap.update(lastEntity, instance);
			}

			--m_newInstance;
		}

		ComponentType* getComponent(const Entity& e) {
			return &m_componentArray->at(m_ecMap.getInstance(e));
		}

		void iterateAll(const std::function<void(ComponentType* c)> lambda) {
			for (int i = 0; i < m_newInstance; ++i) {
				lambda(&m_componentArray->at(i));
			}
		}
	};

}
