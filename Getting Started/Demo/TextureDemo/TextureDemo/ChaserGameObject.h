#pragma once

#include "GameObject.h"

class ChaserGameObject : public GameObject {
public:
	ChaserGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, GameObject& ref);

	// Overrides
	void update(double deltaTime);
	void render(Shader& shader);
	inline int getType() { return 11; }

private:
	int health = 3;
	GameObject& player;
};