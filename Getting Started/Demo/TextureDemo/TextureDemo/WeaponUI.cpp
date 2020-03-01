#include "WeaponUI.h"

WeaponUI::WeaponUI(glm::vec3& entityPos, GLuint entityTexture, GLuint backgroundTexture, GLint entityNumElements, GameObject& ref) : UIObject(entityPos, entityTexture, entityNumElements), player((PlayerGameObject&)ref), backgroundSegment(backgroundTexture) {
	objectSize = 2.0f;
}

void WeaponUI::update(double deltaTime) {
	if (!player.getIsAlive()) kill();
}

void WeaponUI::render(Shader& shader) {
	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize, objectSize, 1));

	// Set the transformation matrix
	glm::mat4 transformationMatrix = translationMatrix * scaleMatrix;

	// Draw Cooldown Bar Border
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
	shader.setUniform4f("color_base", glm::vec4(0, 0, 0, 0));
	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	// Draw Inner Cooldown Bar
	// Calculate the currently equipped weapon's cooldown as a percentage
	Weapon *w = player.getEquippedWeapon();
	float cooldown = (glfwGetTime() - w->lastTimeShot) / w->cooldown;
	if (cooldown > 1.0f) cooldown = 1.0f;

	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, backgroundSegment);
	shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0, 0))
		* glm::translate(glm::mat4(1.0f), glm::vec3(cooldown * 2, 0, 0))
		* transformationMatrix);
	shader.setUniform4f("color_base", glm::vec4(0, 0, 0, 0));
	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}
