#pragma once

#include "GameObject.h"

#define MAX_VEL_X 3
#define MIN_VEL_X -3
#define MAX_VEL_Y 3
#define MIN_VEL_Y -3
#define FRICTION 0.1f

// Inherits from GameObject
class PlayerGameObject : public GameObject {
public:
	PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, std::vector<GLuint*> extraTextures);
	~PlayerGameObject();

	// Overrides
	void update(double deltaTime);
	void render(Shader &shader);

	// Getters
	inline Weapon* getEquippedWeapon() { return equipped; }

	// Setters
	void giveWeapon(Weapon& weap);
	
	// Member functions
	void changeAcceleration(glm::vec3 newAcceleration);
	void equip(int index);
	inline void freeze(double time) { lastTimeFrozen = glfwGetTime(); timeFrozen = time; }
	char* whatIs();

	// Static data members
	static int numWeapons;
private:
	// Weapons
	Weapon* equipped;
	std::vector<Weapon*>* weapons;

	// Extra textures
	std::vector<GLuint*> extraTextures;

	// Data members
	double lastTimeFrozen;
	double timeFrozen;
};
