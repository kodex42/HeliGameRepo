#pragma once

#include "UIObject.h"
#include "PlayerGameObject.h"

// Inherits from UIObject
class WeaponUI : public UIObject {
public:
	WeaponUI(glm::vec3& entityPos, GLuint entityTexture, GLuint backgroundTexture, GLint entityNumElements, GameObject& ref);

	void render(Shader& shader);
	void update(double deltaTime);

private:
	PlayerGameObject& player;
	GLuint backgroundSegment;
};