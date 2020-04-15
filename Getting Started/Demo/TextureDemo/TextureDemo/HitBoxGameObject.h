#pragma once

#include "GameObject.h"

// Inherits from GameObject
class HitBoxGameObject : public GameObject {
public:
	HitBoxGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float ttl);
	
	// Overrides
	void update(double deltaTime);
	void render(Shader& shader);

private:
	float lifeSpan;
	bool  display;
};