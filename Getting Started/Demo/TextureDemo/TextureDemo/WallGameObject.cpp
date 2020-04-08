#include "WallGameObject.h"

WallGameObject::WallGameObject(glm::vec3& entityPos, GLuint entityTexture, GLuint entityTexture2, GLint entityNumElements, GLint type) : GameObject(entityPos, entityTexture, entityNumElements) {
	wallType = type;
	objectSize = 2.0f;
	backupTex = entityTexture2;
}

//Wall type 0 is floor
//Wall type 1 is invincible wall
//Wall type 2 is destructable wall (not yet implemented)
//Wall type 3 for portal
//Wall type 4 for new line

void WallGameObject::update(double deltaTime) {
	//Nothing yet
}

void WallGameObject::render(Shader& shader) {
	GameObject::render(shader);
}

void WallGameObject::damage(float val) {
	if (wallType == 2) {
		health -= 1.0;
		if (health <= 0) GameObject::kill();
	}
	else if (wallType == 5) {
		health -= 1.0;
		if (health <= 0) {
			health = 4;
			texture = backupTex;
			wallType = 2;
		}
	}
}

void WallGameObject::transform(Shader &shader) {
	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), (float)(angle - 90), glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize, objectSize, 1));

	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
}