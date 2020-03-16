#pragma once

#include "UIObject.h"
#include "PlayerGameObject.h"

// Inherits from UIObject
class CoinUI : public UIObject {
public:
	CoinUI(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, GameObject& ref, const std::vector<GLuint*>& vect);

	void render(Shader& shader);
	void update(double deltaTime);

private:
	PlayerGameObject& player;
	GLuint backgroundSegment;
	std::vector<GLuint*> numbers;
};