#include "ProjectileGameObject.h"

ProjectileGameObject::ProjectileGameObject(glm::vec3 & entityPos, GLuint entityTexture, GLint entityNumElements, Weapon & weapon, double x, double y) : GameObject(entityPos, entityTexture, entityNumElements), firedFrom(weapon) {
	acceleration = glm::vec3(0, -(firedFrom.weight / 40), 0);
	velocity = glm::vec3(x, y, 0);
	angle = 0;
	speed = firedFrom.speed;
	isFriendly = firedFrom.isFriendly;
	objectSize = 0.1f + firedFrom.weight;
	lifespan = firedFrom.lifespan;
	timeFired = glfwGetTime();
}

void ProjectileGameObject::update(double deltaTime)
{
	if (lifespan != -1.0f) {
		if (timeFired + lifespan < glfwGetTime()) {
			kill();
		}
	}

	// Update velocity based on current acceleration
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;

	// Update object position with Euler integration
	position += velocity * (float)speed * (float)deltaTime;
}

void ProjectileGameObject::render(Shader & shader)
{
	GameObject::render(shader);
}

void ProjectileGameObject::damage()
{
	if (speed != -1) {
		kill();
	}
}
