#pragma once

#include "GameObject.h"

// Inherits from GameObject
class PlayerGameObject : public GameObject {
public:
	PlayerGameObject(glm::vec3 &entityPos, GLuint entityTexture, GLint entityNumElements, std::vector<GLuint*> extraTextures);
	~PlayerGameObject();

	// Overrides
	void update(double deltaTime);
	void render(Shader &shader);
	void damage();

	// Getters
	inline Weapon* getEquippedWeapon() { return equipped; }

	// Setters
	void giveWeapon(Weapon& weap);
	
	// Member functions
	void changeAcceleration(glm::vec3 newAcceleration);
	void equip(int index);

	// Static data members
	static double lastDamageTime;
	static int numWeapons;
private:
	// Weapons
	Weapon* equipped;
	std::vector<Weapon*>* weapons;

	// Extra textures
	std::vector<GLuint*> extraTextures;
};
