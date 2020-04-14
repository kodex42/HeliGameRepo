#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "Shader.h"
#include "Node.h"
#include "GameObject.h"

class LiquidatorGameObject : public GameObject {
public:
	LiquidatorGameObject(glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements);

	// Updates the GameObject's state. Can be overriden for children
	virtual void update(double deltaTime);

	// Renders the GameObject using a shader
	void render(Shader& shader);
	bool arrival(Node n);



	// Getters
	inline glm::vec3& getPosition() { return position; }
	inline glm::vec3& getVelocity() { return velocity; }

	// Setters
	inline void setPosition(glm::vec3& newPosition) { position = newPosition; }
	inline void setVelocity(glm::vec3& newVelocity) { velocity = newVelocity; }
	inline void setVelocityX(double newX) { velocity.x = newX; }
	inline void setVelocityY(double newY) { velocity.y = newY; }
protected:
	// Object's Transform Variables
	// TODO: Add more transformation variables
	glm::vec3 position;
	glm::vec3 velocity;

	// Object's details
	GLint numElements;
	float objectSize; // Not currently being used (will be needed for collision detection when objects have a different scale)

	// Object's texture
	GLuint texture;
};