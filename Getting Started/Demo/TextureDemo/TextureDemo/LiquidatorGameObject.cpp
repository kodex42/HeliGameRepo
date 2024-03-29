#include "LiquidatorGameObject.h"

/*
	GameObject is responsible for handling the rendering and updating of objects in the game world
	The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
*/

LiquidatorGameObject::LiquidatorGameObject(glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements) : GameObject(entityPosition, entityTexture, entityNumElements){
	position = entityPosition;
	texture = entityTexture;
	numElements = entityNumElements;
	velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	maxHealth = 500;
	isFriendly = false;
}

// Updates the GameObject's state. Can be overriden for children
void LiquidatorGameObject::update(double deltaTime) {
	// Update object position
	position += velocity * (float)deltaTime;
}

// Renders the GameObject using a shader
void LiquidatorGameObject::render(Shader& shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));


	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	//transformationMatrix = rotationMatrix * translationMatrix  * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
	shader.setUniform4f("color_base", glm::vec4(0,0,0,0));

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

bool LiquidatorGameObject::arrival(Node n)
{
	float rad = 0.05;
	float x = position.x;
	float y = position.y;
	float nx = n.getX();
	float ny = n.getY();

	return pow(x - nx, 2) + pow(y - ny, 2) < pow(rad, 2);
}