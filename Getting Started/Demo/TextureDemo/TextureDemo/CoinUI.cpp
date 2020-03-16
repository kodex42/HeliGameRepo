#include "CoinUI.h"

CoinUI::CoinUI(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, GameObject& ref, const std::vector<GLuint*>& vect) : UIObject(entityPos, entityTexture, entityNumElements), player((PlayerGameObject&)ref){
	objectSize = 0.5f;
	numbers = vect;
}

void CoinUI::update(double deltaTime) {
	if (!player.getIsAlive()) kill();
}

void CoinUI::render(Shader& shader) {
	// Setup the transformation matrix for the shader
	glm::vec3 tempPosition = position;
	GLuint tempTexture = texture;
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), tempPosition);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize, objectSize, 1));

	// Set the transformation matrix
	glm::mat4 transformationMatrix = translationMatrix * scaleMatrix;

	// Draw a coin to have the text placed beside it
	// Bind the entities texture
	glBindTexture(GL_TEXTURE_2D, tempTexture);
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
	shader.setUniform4f("color_base", glm::vec4(0, 0, 0, 0));
	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);

	//Display # of coins
	int numCoins = player.getWallet();
	//Values used for conversions and things
	int coinDigit;
	std::string stringDigit;
	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(objectSize/2, objectSize/2, 1));
	std::string s = std::to_string(numCoins);

	for (int i = 0; i < s.length(); i++) {
		//Converting individual digits to characters to display and getting associated textures
		stringDigit = s.at(i);
		coinDigit = stoi(stringDigit);
		tempTexture = *numbers[coinDigit];
		glBindTexture(GL_TEXTURE_2D, tempTexture);

		//Determining the position of these values and putting them on screen
		tempPosition = position + glm::vec3(0.35f+0.2f*i, 0.0f, 0.0f);
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), tempPosition);
		glm::mat4 transformationMatrix = translationMatrix * scaleMatrix;
		shader.setUniformMat4("transformationMatrix", transformationMatrix);
		shader.setUniform4f("color_base", glm::vec4(0, 0, 0, 0));
		// Draw the entity
		glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
	}


	// Bind the entities texture
	/*glBindTexture(GL_TEXTURE_2D, backgroundSegment);
	shader.setUniformMat4("transformationMatrix", glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0, 0))
		* glm::translate(glm::mat4(1.0f), glm::vec3(cooldown * 2, 0, 0))
		* transformationMatrix);
	shader.setUniform4f("color_base", glm::vec4(0, 0, 0, 0));*/
	// Draw the entity
	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}
