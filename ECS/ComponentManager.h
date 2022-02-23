#pragma once

#include "EntityMap.h"

class BaseComponentManager {
public:
	virtual ~BaseComponentManager() {}
};

template<typename ComponentType>
class ComponentManager : public BaseComponentManager {
private:
	std::array<std::unique_ptr<ComponentType>, MAX_COMPONENTS_ARRRAY> m_componentArray;
	EntityMap entityMap;
	ComponentInstance m_newInstance = 1;

public:
	void addComponent(Entity e) {
		ComponentType* c = new ComponentType();
		std::unique_ptr<ComponentType> uPtr(c);
		m_componentArray.at(m_newInstance) = std::move(uPtr);
		entityMap.add(e, m_newInstance);

		m_newInstance++;
	}

	ComponentType& getComponent(Entity e) {
		ComponentInstance instance = entityMap.getEntity(e);
		return *m_componentArray[instance];
	}

	void removeComponent(Entity e) {
		ComponentInstance instance = entityMap.getInstance(e);
		ComponentInstance lastInstance = m_newInstance - 1;
		Entity lastEntity = entityMap.getEntity(lastInstance);

		entityMap.remove(e);

		if (instance != lastInstance) {
			m_componentArray[instance] = std::move(m_componentArray[lastInstance]);
			entityMap.update(lastEntity, instance);
		}

		m_newInstance--;
	}
};
