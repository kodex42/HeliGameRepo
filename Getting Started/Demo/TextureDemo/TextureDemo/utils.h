#pragma once

#include <string>

typedef struct Weapon {
	float lifespan;	// In seconds. -1 if no lifespan
	float weight;	// 0 if unaffected by gravity
	float cooldown;	// lower = faster fire
	float speed;	// -1 if laser
	float radius;	// Damage radius when the projectile dies
	float lastTimeShot;
	float damage;	// Always 1 unless powered up
	float proficiency; // Starts at 0, increases by 1 with each shot fired and by 10*radius for each kill
	int level; // Starts at 0, increases by 1 each time proficiency surpasses the next milestone
	std::string name;
	std::string currentPowerup; // "None" unless powered up
	bool isFriendly;

	Weapon(float l, float w, float c, float s, float r, std::string n, bool f) : lifespan(l), weight(w), cooldown(c), speed(s), radius(r), lastTimeShot(-c), damage(1.0f), proficiency(0), level(0), name(n), currentPowerup("None"), isFriendly(f) {}
};

typedef enum PowerUpType {
	INVINCIBILITY,
	HEALTH_BOOST,
	DOUBLE_FIRE_RATE,
	QUAD_DAMAGE,
	COIN
};