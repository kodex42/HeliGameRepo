#pragma once

#include "GameObject.h"

class ProjectileGameObject : public GameObject {
public:
	ProjectileGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, Weapon& weapon, double x, double y, GLuint explosionTex, GLuint laserTex);

	// Overrides
	void update(double deltaTime);
	void render(Shader &shader);
	void damage(float val);
	void kill();
	inline char* whatIs() { return "Projectile"; }
	inline int getType() { return 1; }

	// Member functions
	void levelWeapon(bool isKill);

private:
	Weapon& firedFrom;
	GLuint explosion;
	GLuint laser;
	double lifespan;
	double timeFired;
	bool isExploding;
};