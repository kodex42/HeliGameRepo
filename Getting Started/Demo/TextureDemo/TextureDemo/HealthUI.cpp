#include "HealthUI.h"

HealthUI::HealthUI(glm::vec3 &entityPos, GLuint entityTexture, GLuint backgroundTexture, GLint entityNumElements, GameObject &ref)
	: UIObject(entityPos, entityTexture, entityNumElements), obj(ref), backgroundSegment(backgroundTexture) {
	objectSize = 0.25f;
}

void HealthUI::update(double deltaTime) {
	if (!obj.getIsAlive()) kill();
	position = obj.getPosition();
}

void HealthUI::render(Shader &shader) {
	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position)
		* glm::translate(glm::mat4(1.0f), glm::vec3((-(obj.getMaxHealth() / 2) * objectSize) + objectSize/2, 0.75f * obj.getSize(), 0));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize, objectSize, 1));

	// Set the transformation matrix
	glm::mat4 transformationMatrix = translationMatrix * scaleMatrix;

	shader.setUniform4f("color_base", glm::vec4(0, 0, 0, 0));

	// Draw active green segments of health
	for (int i = 0; i < obj.getHealth(); i++) {
		// Bind the entities texture
		glBindTexture(GL_TEXTURE_2D, texture);

		glm::mat4 offsetTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(objectSize * i, 0, 0));
		shader.setUniformMat4("transformationMatrix", offsetTranslation * transformationMatrix);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
	}

	// Draw red segments of health
	for (int i = 0; i < obj.getMaxHealth(); i++) {
		// Bind the entities texture
		glBindTexture(GL_TEXTURE_2D, backgroundSegment);

		glm::mat4 offsetTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(objectSize * i, 0, 0));
		shader.setUniformMat4("transformationMatrix", offsetTranslation * transformationMatrix);

		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
	}
}