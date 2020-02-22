#pragma once

#include "GameObject.h"

// Inherits from GameObject
class UIObject : public GameObject {
public:
	UIObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements);

	virtual void render(Shader & shader) override;
};
