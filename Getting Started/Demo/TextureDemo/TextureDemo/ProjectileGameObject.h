#pragma once

#include "GameObject.h"

class ProjectileGameObject : public GameObject {
public:
	ProjectileGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, Weapon& weapon, double x, double y);
	
	// Overrides
	void update(double deltaTime);
	void render(Shader &shader);
	void damage();

private:
	Weapon& firedFrom;
	float lifespan;
	float timeFired;
};