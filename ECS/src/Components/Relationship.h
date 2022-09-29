#pragma once

#include "ECS/Component.h"
#include "ECS/Entity.h"

namespace ECS {
	struct Relationship : public Component {
		EntityID parent{};
	};
}
