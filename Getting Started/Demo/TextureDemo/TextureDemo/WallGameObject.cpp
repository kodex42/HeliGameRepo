#include "WallGameObject.h"

WallGameObject::WallGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, GLint type) : GameObject(entityPos, entityTexture, entityNumElements) {
	wallType = type;
}

//Wall type 0 is floor
//Wall type 1 is invincible wall
//Wall type 2 is destructable wall (not yet implemented)
//Wall type 3 for portal

void WallGameObject::update(double deltaTime) {
	//Nothing yet
}

void WallGameObject::render(Shader& shader) {
	GameObject::render(shader);
}

void WallGameObject::damage() {
	if (wallType == 2) {
		GameObject::damage();
	}
}