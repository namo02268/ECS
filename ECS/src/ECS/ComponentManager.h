#pragma once

#include "ECS/EntityComponentMap.h"

namespace ECS {
	class IComponentManager {
	public:
		virtual ~IComponentManager() {}
	};

	template<class ComponentFamily>
	class ComponentManager : public IComponentManager{
	private:
		std::array<ComponentType, MAX_COMPONENTS>* m_componentArray;
		EntityComponentMap m_ecMap;
		ComponentInstance m_newInstance = 0;
	};

}
