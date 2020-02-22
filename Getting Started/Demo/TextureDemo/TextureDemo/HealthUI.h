#pragma once

#include "UIObject.h"
#include "GameObject.h"

// Inherits from UIObjects
class HealthUI : public UIObject {
public:
	HealthUI(glm::vec3 &entityPos, GLuint entityTexture, GLuint backgroundTexture, GLint entityNumElements, GameObject &ref);

	void render(Shader &shader);
private:
	GameObject &obj;
	GLuint backgroundSegment;
};