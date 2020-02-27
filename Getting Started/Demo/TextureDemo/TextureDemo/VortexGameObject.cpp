#include "VortexGameObject.h"

VortexGameObject::VortexGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements) : GameObject(entityPos, entityTexture, entityNumElements) {
	isFriendly = true;
	objectSize = 1.0f;
}

void VortexGameObject::damage() {
	//You cannot damage this object
}

char * VortexGameObject::pickUp() {
	//When the player touches the end teleporter, the next level is triggered.
	return "vortex";
}