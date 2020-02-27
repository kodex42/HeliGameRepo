#pragma once

#include "GameObject.h"

class WallGameObject : public GameObject {
public:
	WallGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, GLint type);

	// Overrides
	void update(double deltaTime);
	void render(Shader& shader);
	void damage();
	void kill();

private:
	int wallType;
	int health = 5;
};