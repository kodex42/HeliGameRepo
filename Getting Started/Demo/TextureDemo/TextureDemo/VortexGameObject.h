#pragma once

#include "GameObject.h"

class VortexGameObject : public GameObject {
public:
	VortexGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements);

	// Overrides
	void damage();
	void kill();
	char * whatIs();
};
