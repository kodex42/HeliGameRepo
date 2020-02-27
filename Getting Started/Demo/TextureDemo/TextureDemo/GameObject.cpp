#include "GameObject.h"

/*
	GameObject is responsible for handling the rendering and updating of objects in the game world
	The update method is virtual, so you can inherit from GameObject and override the update functionality (see PlayerGameObject for reference)
*/

GameObject::GameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements) {
	position = entityPosition;
	texture = entityTexture;
	numElements = entityNumElements;
	velocity = glm::vec3(0.0f, 0.0f, 0.0f); // starts out stationary
	acceleration = glm::vec3(0.0f, 0.0f, 0.0f); // starts without acceleration
	offset = glm::vec2(0, 0);
	angle = 90;
	aimAngle = 0;
	speed = 0;
	isAlive = true;
	isFriendly = false;
	objectSize = 1.0f;
	maxHealth = 5;
	health = maxHealth;
	damageInvincibiltyTime = 0.1f;
	lastDamageTime = -damageInvincibiltyTime;
}

void GameObject::changeDirection(double diff) {
	angle = fmod(angle + diff, 360);
}

void GameObject::changeSpeed(double diff) {
	speed += diff;
	if (speed > MAX_SPEED)	speed = MAX_SPEED;
	if (speed < MIN_SPEED)	speed = MIN_SPEED;
}

// Updates the GameObject's state
void GameObject::update(double deltaTime) {

	// Update velocity based on current angle
	double rad = glm::radians(angle);
	velocity.x = speed * cos(rad);
	velocity.y = speed * sin(rad);

	// Update object position with Euler integration
	position += velocity * (float)deltaTime;
}

void GameObject::transform(Shader &shader) {
	// Setup the transformation matrix for the shader
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), (float)(angle - 90), glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize, objectSize, 1));

	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
}

bool GameObject::isDamaged()
{
	return lastDamageTime + damageInvincibiltyTime >= glfwGetTime();
}

void GameObject::damage()
{
	if (!isDamaged()) {
		lastDamageTime = glfwGetTime();
		health -= 1;
		if (health <= 0) kill();
	}
}

char * GameObject::pickUp() {
	//This will be re-written by subclasses to determine what is being picked up. 
	//However, the object being picked up usually will always disappear for power ups and entering portals anyways.
	//But for now to be safe it will do nothing. It would be pretty silly for bullets to delete themselves.
	//kill();
	return "object";
}

// Renders the GameObject using the shader
void GameObject::render(Shader &shader) {
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	transform(shader);

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}
