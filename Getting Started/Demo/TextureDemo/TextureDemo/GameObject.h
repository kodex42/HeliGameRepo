#pragma once

#include <GL/glew.h>
#include <GL/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "utils.h"

#define MIN_SPEED -2
#define MAX_SPEED 2
#define MIN_SIZE 0.5
#define MAX_SIZE 1.0

class GameObject {
public:
	GameObject(glm::vec3 &entityPosition, GLuint entityTexture, GLint entityNumElements);

	// Change the speed and bearing of the object
	void changeDirection(double diff);
	void changeSpeed(double diff);

	// Updates the GameObject's state. Can be overriden for children
	virtual void update(double deltaTime);

	// Renders the GameObject using a shader
	virtual void render(Shader &shader);
	virtual void renderParticles(Shader& shader, double deltaTime);
	virtual void transform(Shader &shader);

	// Getters
	inline glm::vec3& getPosition() { return position; }
	inline glm::vec3& getVelocity() { return velocity; }
	inline glm::vec3& getAcceleration() { return acceleration; }
	inline float getHealth() { return health; }
	inline float getMaxHealth() { return maxHealth; }
	inline float getSize() { return objectSize; }
	inline double getAngle() { return angle; }
	inline double getAimAngle() { return aimAngle; }
	inline bool getIsAlive() { return isAlive; }
	inline bool getIsFriendly() { return isFriendly; }
	inline float getDamage() { return damageVal; }

	bool isDamaged();

	// Setters
	inline void setPosition(glm::vec3 &newPosition) { position = newPosition; }
	inline void setVelocity(glm::vec3 &newVelocity) { velocity = newVelocity; }
	inline void setAcceleration(glm::vec3 &newAcceleration) { acceleration = newAcceleration; }
	inline void setFriendly() { isFriendly = true; }
	inline void setHostile() { isFriendly = false; }
	inline void setAimAngle(double angle) { aimAngle = angle; }
	virtual inline void kill() { isAlive = false; }
	virtual inline void revive() { isAlive = true; }
	virtual void damage(float val);

	// Member functions
	virtual char* whatIs();
	virtual inline int getType() { return -1; } //Returns the wall or enemy type as an int

	//Independent time for particle effects
	float myTime = 0;

protected:
	// Object's Transform Variables
	// TODO: Add more transformation variables
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	// For visual flair
	glm::vec2 offset;

	// Object's details
	GLint numElements;
	float maxHealth;
	float health;
	float objectSize;
	float damageVal;
	double damageInvincibiltyTime;
	double lastDamageTime;
	double angle;
	double aimAngle;
	double speed;
	double time;
	bool isAlive;
	bool isFriendly;

	// Object's texture
	GLuint texture;
};