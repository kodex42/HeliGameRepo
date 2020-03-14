#include "WallGameObject.h"

WallGameObject::WallGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, GLint type) : GameObject(entityPos, entityTexture, entityNumElements) {
	wallType = type;
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
		GameObject::damage(val);
	}
}

void WallGameObject::transform(Shader &shader) {
	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), (float)(angle - 90), glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize*2, objectSize*2, 1));

	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
}