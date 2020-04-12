#include "BossGameObject.h"
#include "HitBoxGameObject.h"

// Inherits from GameObject
#define FRAME_SPEED 0.1

BossGameObject::BossGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::vector<GLuint*> extraTextures, int bossId, std::vector<GameObject*>& objs)
	: GameObject(entityPos, entityTexture, entityNumElements), spriteSheets(extraTextures), state(IDLE), objs(objs) {
	objectSize = 6.0f;
	maxHealth = 75 * bossId;
	health = maxHealth;
	activeFrame = 0;
	activeTime = 0;
	activeState = 0;
	id = bossId;
	enraged = false;
	switch (bossId) {
		case 1:
			currentStateList = new State[4]{ IDLE, IDLE, MELEE, IDLE };
			enragedStateList = new State[1]{ MELEE };
			numStates = 4;
			numEnragedStates = 1;
			break;
		case 2:
			currentStateList = new State[4]{ IDLE, IDLE, MELEE, IDLE };
			enragedStateList = new State[1]{ MELEE };
			numStates = 4;
			numEnragedStates = 1;
			break;
		case 3:
			currentStateList = new State[4]{ IDLE, IDLE, MELEE, IDLE };
			enragedStateList = new State[1]{ MELEE };
			numStates = 4;
			numEnragedStates = 1;
			break;
		default:
			currentStateList = onlyIdleStateList;
			enragedStateList = onlyIdleStateList;
			numStates = 1;
			numEnragedStates = 1;
			break;
	}
}

void BossGameObject::update(double deltaTime) {
	time = glfwGetTime();

	// Is it time for the boss to enrage?
	if (health <= maxHealth / 2 && !enraged) {
		// Swap to enraged state list
		currentStateList = enragedStateList;
		numStates = numEnragedStates;
		activeState = 0;
		nextState();
		enraged = true;
	}

	// Check state and advance animation frame
	activeTime += deltaTime;
	int frameLimit;
	switch (state) {
		case MELEE:
			frameLimit = 18;
			break;
		case IDLE: default:
			frameLimit = 9;
			break;
	}

	// Advance frame every 0.1 seconds
	if (activeTime >= FRAME_SPEED) {
		activeTime -= FRAME_SPEED;
		activeFrame++;
	}

	// Create hitboxes
	float posMod;
	if (id == 1)
		posMod = 1;
	else
		posMod = -1;
	glm::vec3 hitBoxLocation = position + glm::vec3(4.5*posMod, 0, 0);
	if (state == MELEE) {
		switch (activeFrame) {
			case 4: case 5: case 6: case 12: case 13:
				objs.push_back(new HitBoxGameObject(hitBoxLocation, *spriteSheets[2], 6, 0.1f));
				objs.push_back(new HitBoxGameObject(hitBoxLocation + glm::vec3(0, 1, 0), *spriteSheets[2], 6, 0.1f));
				break;
			case 7: case 8: case 14: case 15:
				objs.push_back(new HitBoxGameObject(hitBoxLocation, *spriteSheets[2], 6, 0.1f));
				objs.push_back(new HitBoxGameObject(hitBoxLocation + glm::vec3(0, 1, 0), *spriteSheets[2], 6, 0.1f));
				objs.push_back(new HitBoxGameObject(hitBoxLocation + glm::vec3(posMod, 0, 0), *spriteSheets[2], 6, 0.1f));
				objs.push_back(new HitBoxGameObject(hitBoxLocation + glm::vec3(posMod, 1, 0), *spriteSheets[2], 6, 0.1f));
				break;
			default:
				break;
		}
	}

	// Advance to next state if current state is complete
	if (activeFrame >= frameLimit) {
		nextState();
	}

	// Update velocity based on current angle
	double rad = glm::radians(angle);
	velocity.x = speed * cos(rad);
	velocity.y = speed * sin(rad);

	// Update object position with Euler integration
	position += velocity * (float)deltaTime;
}

void BossGameObject::render(Shader& shader) {
	int xDim, yDim, width, height;
	int texIndex;
	switch (state) {
		case MELEE:
			xDim = 1800;
			yDim = 2400;
			width = 600;
			height = 400;
			texIndex = 1;
			break;
		case IDLE: default:
			xDim = 1200;
			yDim = 1200;
			width = 400;
			height = 400;
			texIndex = 0;
			break;
	}
	texture = *spriteSheets[texIndex];

	
	float tw = float(width) / xDim;
	float th = float(height) / yDim;
	int numHorCells = xDim / width;
	float tx = (activeFrame % numHorCells) * tw;
	float ty = (activeFrame / numHorCells) * th;

	// Enable spriteSheet rendering
	shader.setUniformMat4("spriteTranslate", glm::translate(glm::mat4(1.0f), glm::vec3(tx, ty, 0)));
	shader.setUniformMat4("spriteScale", glm::scale(glm::mat4(1.0f), glm::vec3(tw, th, 1)));
	shader.setUniform1i("hasSpriteSheet", true);

	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Setup the transformation matrix for the shader
	glm::vec3 moddedPos = position;
	moddedPos.z -= 1;
	if (state == MELEE)
		if (id == 1)
			moddedPos.x += 1.5;
		else
			moddedPos.x -= 1.5;
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), moddedPos);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), (float)(angle - 90), glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize * (float(width) / 400.0), objectSize * (float(height) / 400.0), 1));

	// Set the transformation matrix in the shader
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
	shader.setUniform4f("color_base", glm::vec4(0, 0, 0, 0));

	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	// Disable spriteSheet rendering
	shader.setUniformMat4("spriteTranslate", glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)));
	shader.setUniformMat4("spriteScale", glm::scale(glm::mat4(1.0f), glm::vec3(-1, -1, -1)));
	shader.setUniform1i("hasSpriteSheet", false);
}

void BossGameObject::changeState(State s) {
	state = s;
	activeFrame = 0;
	activeTime = 0;
}

void BossGameObject::nextState() {
	changeState(currentStateList[activeState++]);
	if (activeState >= numStates) {
		activeState = 0;
	}
}