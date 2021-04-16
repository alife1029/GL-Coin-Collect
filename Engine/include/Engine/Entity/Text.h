#pragma once

#include "Engine/API.h"
#include "GameObject.h"

namespace engine {

	class ENGINE_API Text : public GameObject
	{
	public:
		Text();
		void Update() override;
	};

}