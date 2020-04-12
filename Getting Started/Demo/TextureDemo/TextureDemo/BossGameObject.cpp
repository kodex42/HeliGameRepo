#include "BossGameObject.h"

// Inherits from GameObject
#define FRAME_SPEED 0.1

BossGameObject::BossGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, std::vector<GLuint*> extraTextures)
	: GameObject(entityPos, entityTexture, entityNumElements), spriteSheets(extraTextures), state(IDLE) {
	objectSize = 6.0f;
	maxHealth = 100;
	health = maxHealth;
	currentStateList = onlyIdleStateList;
	activeFrame = 0;
	activeTime = 0;
}

void BossGameObject::update(double deltaTime) {
	activeTime += deltaTime;
	int frameLimit;
	switch (state) {
	case IDLE: default:
		frameLimit = 8;
		break;
	}

	if (activeTime >= FRAME_SPEED) {
		activeTime -= FRAME_SPEED;
		activeFrame++;
	}

	if (activeFrame > frameLimit) {
		activeFrame = 0;
	}

	GameObject::update(deltaTime);
}

void BossGameObject::render(Shader& shader) {
	int xDim, yDim;
	int texIndex;
	switch (state) {
		case IDLE: default:
			xDim = 1200;
			yDim = 1200;
			texIndex = 0;
			break;
	}
	texture = *spriteSheets[texIndex];

	int width = 400;
	int height = 400;
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

	transform(shader);
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
