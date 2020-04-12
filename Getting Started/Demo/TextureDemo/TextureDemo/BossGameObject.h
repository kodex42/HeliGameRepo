#pragma once

#include "GameObject.h"

#define MAX_SPRITESHEET_SPRITES 20
#define NUM_NORMAL_STATES 1
#define NUM_ENRAGED_STATES 1

enum State {
	IDLE//, MELEE, SHOOT, DIE
};

class BossGameObject : public GameObject {
public:
	BossGameObject(glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements, std::vector<GLuint*> extraTextures);
	
	// Overrides
	void update(double deltaTime);
	void render(Shader& shader);

	// Member functions
	void changeState(State s);

private:
	std::vector<GLuint*> spriteSheets;
	State state;
	State onlyIdleStateList[1] = { IDLE };
	State normalStateList[NUM_NORMAL_STATES] = { IDLE };
	State enragedStateList[NUM_ENRAGED_STATES] = { IDLE };
	State* currentStateList;
	int activeFrame;
	float activeTime;
};
