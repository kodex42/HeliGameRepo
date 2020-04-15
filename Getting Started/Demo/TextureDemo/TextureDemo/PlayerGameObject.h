#pragma once

#include "GameObject.h"

#define MAX_VEL 4
#define MAX_VEL_X MAX_VEL
#define MIN_VEL_X -MAX_VEL
#define MAX_VEL_Y MAX_VEL
#define MIN_VEL_Y -MAX_VEL
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
	inline std::vector<Weapon*>* getWeapons() { return weapons; }
	inline int getWallet() { return wallet; }
	inline double getLevelupTimer() { return levelupTimer; }
	inline bool getLevelUp() { return levelup; }
	inline int getNumWeapons() { return numWeapons; }

	// Setters
	void giveWeapon(Weapon& weap);
	inline void setLevelupTimer(double n) { levelupTimer = n; }
	inline void startLevelUp() { levelup = true; }
	inline void endLevelUp() { levelup = false; }
	
	// Member functions
	void changeAcceleration(glm::vec3 newAcceleration);
	void equip(int index);
	void powerUp(PowerUpType type);
	void damage(float val);
	char* whatIs();
	inline void freeze(double time) { lastTimeFrozen = glfwGetTime(); timeFrozen = time; }

	// Static data members
	static int numWeapons;
private:
	// Weapons
	Weapon* equipped;
	std::vector<Weapon*>* weapons;

	// Extra textures
	std::vector<GLuint*> extraTextures;

	// Data members
	int wallet;
	double lastTimeFrozen;
	double timeFrozen;
	double lastTimeMadeInvincible;
	double timeMadeInvincible;
	bool levelup = false;
	float levelupTimer;
};
