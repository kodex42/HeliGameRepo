#pragma once
#define PI 3.14159265359

#include "GameObject.h"

class TurretGameObject : public GameObject {
public:
	TurretGameObject(glm::vec3& entityPos, GLuint entityTexture, GLuint turretTexture, GLint entityNumElements, GameObject& ref);
	// Overrides
	void update(double deltaTime);
	void render(Shader& shader);
	inline int getType() { return 10; }

private:
	GLuint turretTex;
	GameObject& player;
};