#include "ProjectileGameObject.h"

ProjectileGameObject::ProjectileGameObject(glm::vec3 & entityPos, GLuint entityTexture, GLint entityNumElements, Weapon & weapon, double x, double y, GLuint explosionTex, GLuint laserTex) : GameObject(entityPos, entityTexture, entityNumElements), firedFrom(weapon), explosion(explosionTex), laser(laserTex) {
	acceleration = glm::vec3(0, -(firedFrom.weight / 40), 0);
	velocity = glm::vec3(x, y, 0);
	speed = firedFrom.speed;
	isFriendly = firedFrom.isFriendly;
	if (speed != -1.0f) objectSize = 0.2f;
	else objectSize = firedFrom.radius * 2;
	lifespan = (double) firedFrom.lifespan;
	timeFired = glfwGetTime();
	isExploding = false;

	if (x == 1) angle = angle + 0;
	if (x == -1) angle = angle + 180;
	if (y == 1) angle = angle + 90;
	if (y == -1) angle = angle + 270;
}

void ProjectileGameObject::update(double deltaTime) {
	time = glfwGetTime();

	if (isExploding) {
		objectSize += 3*deltaTime;
		velocity = glm::vec3(0, 0, 0);
		acceleration = glm::vec3(0, 0, 0);
		if (objectSize >= firedFrom.radius)
			GameObject::kill();
	}
	else if (lifespan != -1.0) {
		if (timeFired + lifespan < glfwGetTime()) {
			kill();
		}
	}

	if (speed != -1) {
		// Update velocity based on current acceleration
		velocity.x += acceleration.x;
		velocity.y += acceleration.y;

		// Update object position with Euler integration
		position += velocity * (float)speed * (float)deltaTime;
	}
}

void ProjectileGameObject::render(Shader & shader) {
	if (speed != -1.0f) GameObject::render(shader);
	else {
		glm::vec3 oldPos = glm::vec3(position);
		// Bind the entities texture
		glBindTexture(GL_TEXTURE_2D, laser);

		// Setup the transformation matrix for the shader
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), (float)(angle - 90), glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize, objectSize, 1));

		shader.setUniform4f("color_base", glm::vec4(0, 0, 0, 0));
		// Set the transformation matrix in the shader
		glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		shader.setUniformMat4("transformationMatrix", transformationMatrix);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
	}
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
