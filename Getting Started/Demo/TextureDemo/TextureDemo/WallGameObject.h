#pragma once

#include "GameObject.h"

class WallGameObject : public GameObject {
public:
	//WallGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, GLint type);
	WallGameObject(glm::vec3& entityPos, GLuint entityTexture, GLuint entityTexture2, GLint entityNumElements, GLint type);

	// Overrides
	void update(double deltaTime);
	void render(Shader& shader);
	void damage(float val);
	inline int getType() { return wallType; }
	void transform(Shader& shader);


private:
	int wallType;
	int health = 5;
	GLuint backupTex;
};