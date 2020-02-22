#pragma once

#include <string>

typedef struct Weapon {
	float lifespan;	// In seconds. -1 if no lifespan
	float weight;	// 0 if unaffected by gravity
	float cooldown;	// Shots per second
	float speed;	// -1 if laser
	float radius;	// Damage radius when the projectile dies
	float lastTimeShot;
	std::string name;
	bool isFriendly;
};