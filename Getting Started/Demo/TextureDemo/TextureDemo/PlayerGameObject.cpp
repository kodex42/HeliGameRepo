#include "PlayerGameObject.h"

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player

*/

int PlayerGameObject::numWeapons = 0;

PlayerGameObject::PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, std::vector<GLuint*> extraTextures)
	: GameObject(entityPos, entityTexture, entityNumElements), extraTextures(extraTextures) {
	maxHealth = 5;
	health = maxHealth;
	isFriendly = true;
	weapons = new std::vector<Weapon*>();
	damageInvincibiltyTime = 2.0f;
	lastDamageTime = -damageInvincibiltyTime;
	timeFrozen = 0;
	lastTimeFrozen = 0;

	// Setup weapons
	numWeapons = 0;
	// { lifeSpan, weight, cooldown, speed, radius, lastTimeShot, name, isFriendly }
	Weapon machineGun = { -1.0f, 0.0f, 0.5f, 4.0f, 0.1f, -0.5f, "machineGun", true };
	Weapon rockets = { 1.0f, 0.1f, 2.5f, 3.5f, 1.0f, -2.5f, "rockets", true };
	Weapon scudMissles	= { 1.8f, 3.0f, 5.0f, 1.0f, 1.5f, -5.0f, "scudMissles", true };
	Weapon laser		= { 3.0f, 0.0f, 20.0f, -1.0f, 0.3f, -20.0f, "laser", true };
	// Give the player these weapons
	giveWeapon(machineGun);
	giveWeapon(rockets);
	giveWeapon(scudMissles);
	giveWeapon(laser);
	equip(0);
}

PlayerGameObject::~PlayerGameObject() {
	for (int i = 0; i < numWeapons; i++)
		delete (*weapons)[i];
	delete weapons;
}

void PlayerGameObject::giveWeapon(Weapon& weap) {
	Weapon* ptr = new Weapon(weap);
	weapons->push_back(ptr);
	numWeapons++;
}

void PlayerGameObject::changeAcceleration(glm::vec3 newAcceleration) {
	setAcceleration(newAcceleration);
	speed = 1.0f;
}

void PlayerGameObject::equip(int index) {
	if (index >= 0 && index < numWeapons) {
		equipped = (*weapons)[index];
	}
}

// Update function for moving the player object around
void PlayerGameObject::update(double deltaTime) {
	if (lastTimeFrozen + timeFrozen <= glfwGetTime()) {
		// Slow down speed by friction
		if (speed > 0)
			speed -= FRICTION;
		else
			speed = 0;

		// Update velocity based on current acceleration
		velocity.x += acceleration.x;
		velocity.y += acceleration.y;
		velocity.x *= speed;
		velocity.y *= speed;

		// Cap player speed
		if (velocity.x > MAX_VEL_X) velocity.x = MAX_VEL_X;
		if (velocity.y > MAX_VEL_Y) velocity.y = MAX_VEL_Y;
		if (velocity.x < MIN_VEL_X) velocity.x = MIN_VEL_X;
		if (velocity.y < MIN_VEL_Y) velocity.y = MIN_VEL_Y;

		// Change angle for rendering helicopter tilt
		angle = -(30 * (velocity.x / MAX_VEL_X));

		// Update object position with Euler integration
		position += velocity * (float)deltaTime;
	}
}

void PlayerGameObject::render(Shader &shader) {
	// Setup the transformation matrix for the shader
	glm::mat4 playerTranslation = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 playerRotation = glm::rotate(glm::mat4(1.0f), (float)(angle), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1.0f), aimAngle == 180 ? 180.0f : 0.0f, glm::vec3(0, 1, 0));
	glm::mat4 playerScale = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize, objectSize, 1));
	glm::mat4 playerDamageOffset = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
	
	if (lastDamageTime + damageInvincibiltyTime > glfwGetTime()) {
		playerDamageOffset = glm::translate(glm::mat4(1.0f), glm::vec3(cos(glfwGetTime() * 50) / 50, 0, 0));
	}

	glm::mat4 playerTransformation = playerDamageOffset * playerTranslation * playerRotation * playerScale;

	// ---------- DRAW WEAPON ----------
	if (numWeapons > 0) {
		int texIndex = 0;
		if (equipped->name == "machineGun") texIndex = 0;
		if (equipped->name == "rockets") texIndex = 1;
		if (equipped->name == "scudMissles") texIndex = 2;
		if (equipped->name == "laser") texIndex = 3;

		// Weapon transformations
		glm::mat4 weaponTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(0.3f, -0.2f, 0));
		glm::mat4 weaponRotation = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f, 0, 0)) // Translate away from axle
			* glm::rotate(glm::mat4(1.0f), (float)(aimAngle), glm::vec3(0, 0, 1)) // Aiming angle
			* glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0, 0)); // Translate to axle
		glm::mat4 weaponScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.8f, 0.7f, 0));
		glm::mat4 weaponTransformation = playerDamageOffset * playerTranslation * weaponTranslation * weaponRotation * weaponScale;

		// Bind the entities texture
		glBindTexture(GL_TEXTURE_2D, *extraTextures[texIndex]);
		shader.setUniformMat4("transformationMatrix", weaponTransformation);
		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
	}

	// ---------- DRAW PLAYER ----------
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);
	shader.setUniformMat4("transformationMatrix", playerTransformation);
	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	// ---------- DRAW PROPELLOR ----------
	glm::mat4 propellorTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.6f, 0));
	glm::mat4 propellorRotation = glm::rotate(glm::mat4(1.0f), (float)fmod(glfwGetTime()*1000, 360), glm::vec3(0, 1, 0));
	glm::mat4 propellorScale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 1.0f));
	glm::mat4 propellorTransformation = playerTransformation * propellorTranslation * propellorRotation * propellorScale;

	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, *extraTextures[4]);
	shader.setUniformMat4("transformationMatrix", propellorTransformation);
	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}