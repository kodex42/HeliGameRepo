#include "HitBoxGameObject.h"

HitBoxGameObject::HitBoxGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, float ttl) : GameObject(entityPos, entityTexture, entityNumElements), lifeSpan(ttl) {
}

void HitBoxGameObject::update(double deltaTime) {
	GameObject::update(deltaTime);

	if (lifeSpan < 0)
		kill();
	lifeSpan -= deltaTime;
}

void HitBoxGameObject::render(Shader& shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	transform(shader);

	// Draw the entity : Uncomment to show hitboxes
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}
