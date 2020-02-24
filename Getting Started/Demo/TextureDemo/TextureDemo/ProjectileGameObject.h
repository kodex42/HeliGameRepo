#pragma once

#include "GameObject.h"

class ProjectileGameObject : public GameObject {
public:
	ProjectileGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, Weapon& weapon, double x, double y, GLuint explosionTex);
	
	// Overrides
	void update(double deltaTime);
	void render(Shader &shader);
	void damage();
	void kill();

private:
	Weapon& firedFrom;
	GLuint explosion;
	float lifespan;
	float timeFired;
	bool isExploding;
};