#pragma once

#include "GameObject.h"

#define MAX_SPRITESHEET_SPRITES 20

enum State {
	IDLE, MELEE//, SHOOT, DIE
};

class BossGameObject : public GameObject {
public:
	BossGameObject(glm::vec3& entityPosition, GLuint entityTexture, GLint entityNumElements, std::vector<GLuint*> extraTextures, int bossId, std::vector<GameObject*>& objs);
	
	// Overrides
	void update(double deltaTime);
	void render(Shader& shader);

	// Member functions
	void changeState(State s);
	void nextState();

private:
	std::vector<GLuint*> spriteSheets;
	std::vector<GameObject*>& objs;
	State state;
	State onlyIdleStateList[1] = { IDLE };
	State* currentStateList;
	State* enragedStateList;
	int numStates;
	int numEnragedStates;
	int activeState;
	int activeFrame;
	float activeTime;
	int id;
	bool enraged;
};
