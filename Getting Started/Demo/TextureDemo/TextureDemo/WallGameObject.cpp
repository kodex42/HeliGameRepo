#include "WallGameObject.h"

WallGameObject::WallGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, GLint type) : GameObject(entityPos, entityTexture, entityNumElements) {
	wallType = type;
}

//Wall type 0 is floor
//Wall type 1 is invincible wall
//Wall type 2 is destructable wall (not yet implemented)

void WallGameObject::update(double deltaTime) {
	//No updates needed!
}

void WallGameObject::render(Shader& shader) {
	GameObject::render(shader);
}

void WallGameObject::damage() {
	if (wallType == 2) {
		GameObject::damage();
	}
}

void WallGameObject::kill() {
	if (wallType == 2) {
		GameObject::kill();
	}
}