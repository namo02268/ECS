#pragma once

#include "ECS/EntityMap.h"

class BaseComponentManager {
public:
	virtual ~BaseComponentManager() {}
};

template<typename ComponentType>
class ComponentManager : public BaseComponentManager {
private:
	std::array<ComponentType, MAX_ENTITIES> *m_componentArray;
	EntityMap m_entityMap;
	ComponentInstance m_newInstance = 0;

public:
	ComponentManager() {
		m_componentArray = static_cast<std::array<ComponentType, MAX_ENTITIES> *>(malloc(sizeof(ComponentType) * MAX_ENTITIES));
	}

	~ComponentManager() {
		free(m_componentArray);
	}

	void addComponent(Entity& e, ComponentType&& c) {
		m_componentArray->at(m_newInstance) = c;
		m_entityMap.add(e, m_newInstance);

		m_newInstance++;
	}

	void removeComponent(Entity& e) {
		ComponentInstance instance = m_entityMap.getInstance(e);
		ComponentInstance lastInstance = m_newInstance - 1;
		Entity lastEntity = m_entityMap.getEntity(lastInstance);

		m_entityMap.remove(e);

		if (instance != lastInstance) {
			m_componentArray->at(instance) = m_componentArray->at(lastInstance);
			m_entityMap.update(lastEntity, instance);
		}

		m_newInstance--;
	}

	ComponentType* getComponent(Entity& e) {
		ComponentInstance instance = m_entityMap.getInstance(e);
		return &m_componentArray->at(instance);
	}
};
