#pragma once
#define PI 3.14159265359

#include "GameObject.h"

class TurretGameObject : public GameObject {
public:
	TurretGameObject(glm::vec3& entityPos, GLuint entityTexture, GLuint turretTexture, GLint entityNumElements, GameObject& ref, void shoot(Weapon* w, glm::vec3 startingPos, double dx, double dy));
	// Overrides
	void update(double deltaTime);
	void render(Shader& shader);
	inline int getType() { return 10; }

private:
	GLuint turretTex;
	GameObject& player;
	double shotCD;
	Weapon* gun = new Weapon(-1.0f, 0.0f, 0.5f, 6.0f, 0.1f, "machineGun", false);
	void (*shootGun)(Weapon* w, glm::vec3 startingPos, double dx, double dy);
};