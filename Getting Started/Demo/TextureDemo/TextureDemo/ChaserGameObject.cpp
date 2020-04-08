#include "ChaserGameObject.h"

ChaserGameObject::ChaserGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, GameObject& ref) : GameObject(entityPos, entityTexture, entityNumElements), player(ref) {
	objectSize = 0.8f;
	isFriendly = false;
}

void ChaserGameObject::render(Shader& shader) {
	GameObject::render(shader);
}

void ChaserGameObject::update(double deltaTime) {
	glm::vec3 pos = player.getPosition();
	double angle = atan2(pos.y - position.y, pos.x - position.x) * 180 / 3.1415;
	double rad = glm::radians(angle);
	float x = cos(rad);
	double y = sin(rad);
	speed = 0.7f;
	time = glfwGetTime();

	// Update velocity based on current angle
	velocity.x = speed * cos(rad);
	velocity.y = speed * sin(rad);

	// Update object position with Euler integration
	position += velocity * (float)deltaTime;
}