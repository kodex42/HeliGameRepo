#include "ProjectileGameObject.h"

ProjectileGameObject::ProjectileGameObject(glm::vec3 & entityPos, GLuint entityTexture, GLint entityNumElements, Weapon & weapon, double x, double y, GLuint explosionTex) : GameObject(entityPos, entityTexture, entityNumElements), firedFrom(weapon), explosion(explosionTex) {
	acceleration = glm::vec3(0, -(firedFrom.weight / 40), 0);
	velocity = glm::vec3(x, y, 0);
	angle = 0;
	speed = firedFrom.speed;
	isFriendly = firedFrom.isFriendly;
	objectSize = 0.1f;
	lifespan = firedFrom.lifespan;
	timeFired = glfwGetTime();
	isExploding = false;
}

void ProjectileGameObject::update(double deltaTime) {
	if (isExploding) {
		objectSize += 3*deltaTime;
		velocity = glm::vec3(0, 0, 0);
		acceleration = glm::vec3(0, 0, 0);
		if (objectSize >= firedFrom.radius)
			GameObject::kill();
	}
	else if (lifespan != -1.0f) {
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

void ProjectileGameObject::render(Shader & shader) {
	GameObject::render(shader);
}

void ProjectileGameObject::damage() {
	if (speed != -1) {
		kill();
	}
}

void ProjectileGameObject::kill() {
	if (speed != -1) {
		isExploding = true;
		texture = explosion;
	} else {
		GameObject::kill();
	}
}
