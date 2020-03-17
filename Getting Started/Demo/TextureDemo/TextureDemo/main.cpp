#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#define GLEW_STATIC
#include <GL/glew.h> // window management library
#include <GL/glfw3.h>
#include <glm/glm.hpp>
//#include <GL/glut.h> //Library for displaying text on screen
#include <glm/gtc/matrix_transform.hpp> //
#include <SOIL/SOIL.h> // read image file
#include <chrono>
#include <thread>
#include <fstream>

#include "Shader.h"
#include "Window.h"
#include "PlayerGameObject.h"
#include "UIObject.h"
#include "HealthUI.h"
#include "WeaponUI.h"
#include "CoinUI.h"
#include "ProjectileGameObject.h"
#include "WallGameObject.h"
#include "VortexGameObject.h"
#include "PowerUpGameObject.h"
#include "TurretGameObject.h"

#define NUM_GAME_OBJECTS 6
#define NUM_UI_TEXTURES 4
#define NUM_WEAPON_TEXTURES 4
#define NUM_BULLET_TEXTURES 3
#define NUM_WALL_TEXTURES 3
#define NUM_POWERUP_TEXTURES 5
#define NUM_NUMBERS 10
#define NUM_OBJECTS NUM_GAME_OBJECTS + NUM_UI_TEXTURES + NUM_WEAPON_TEXTURES + NUM_BULLET_TEXTURES + NUM_WALL_TEXTURES + NUM_POWERUP_TEXTURES + NUM_NUMBERS

// Macro for printing exceptions
#define PrintException(exception_object)\
	std::cerr << exception_object.what() << std::endl

// Globals that define the OpenGL window and viewport
const std::string window_title_g = "Transform Demo";
const unsigned int window_width_g = 800;
const unsigned int window_height_g = 600;
const glm::vec3 viewport_background_color_g(1.0, 1.0, 1.0);
int currentStage = 0;

// Allows system to build a map based on inputted text file
void buildMap(std::string map);

// Allows the transition to the next level from making contact with the portal
void nextLevel();

//Allows the player to hit walls and return to the map safely
void playerRelocate(PlayerGameObject *player);

// Global texture info
GLuint tex[NUM_OBJECTS];

// Global game object info
std::vector<GameObject*> gameObjects;
std::vector<UIObject*> dynamicUIObjects;
std::vector<UIObject*> staticUIObjects;
std::vector<GameObject*> MapObjects;
std::vector<GLuint*> numberTextures;


// Create the geometry for a square (with two triangles)
// Return the number of array elements that form the square
int CreateSquare(void) {
	// The face of the square is defined by four vertices and two triangles

	// Number of attributes for vertices and faces
//	const int vertex_att = 7;  // 7 attributes per vertex: 2D (or 3D) position (2), RGB color (3), 2D texture coordinates (2)
//	const int face_att = 3; // Vertex indices (3)

	GLfloat vertex[]  = {
		//  square (two triangles)
		   //  Position      Color             Texcoords
		-0.5f, 0.5f,	 1.0f, 0.0f, 0.0f,		0.0f, 0.0f, // Top-left
		0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,		1.0f, 0.0f, // Top-right
		0.5f, -0.5f,	 0.0f, 0.0f, 1.0f,		1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f,	 1.0f, 1.0f, 1.0f,		0.0f, 1.0f  // Bottom-left
	};


	GLuint face[] = {
		0, 1, 2, // t1
		2, 3, 0  //t2
	};

	GLuint vbo, ebo;

	// Create buffer for vertices
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	// Create buffer for faces (index buffer)
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);

	// Return number of elements in array buffer (6 in this case)
	return sizeof(face) / sizeof(GLuint);
}


void setthisTexture(GLuint w, char *fname)
{
	glBindTexture(GL_TEXTURE_2D, w);

	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	// Texture Wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Texture Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void setallTexture(void)
{
//	tex = new GLuint[4];
	glGenTextures(NUM_OBJECTS, tex);
	setthisTexture(tex[0], "player.png");
	setthisTexture(tex[1], "saw.png");
	setthisTexture(tex[2], "rock.png");
	setthisTexture(tex[3], "healthBarSegment.png");
	setthisTexture(tex[4], "healthBarMissingSegment.png");
	setthisTexture(tex[5], "bullet.png");
	setthisTexture(tex[6], "explosion.png");
	setthisTexture(tex[7], "machineGun.png");
	setthisTexture(tex[8], "rocketLauncher.png");
	setthisTexture(tex[9], "scudMissleLauncher.png");
	setthisTexture(tex[10], "laserWeapon.png");
	setthisTexture(tex[11], "propellor.png");
	setthisTexture(tex[12], "cobbleWall.png");
	setthisTexture(tex[13], "metalWall.png");
	setthisTexture(tex[14], "vortex.png");
	setthisTexture(tex[15], "laser.png");
	setthisTexture(tex[16], "weaponCooldownBar.png");
	setthisTexture(tex[17], "weaponCooldownBarSegment.png");
	setthisTexture(tex[18], "powerUpInvincibility.png");
	setthisTexture(tex[19], "powerUpHealthBoost.png");
	setthisTexture(tex[20], "powerUpQuadDmg.png");
	setthisTexture(tex[21], "powerUpFireRate.png");
	setthisTexture(tex[22], "powerUpCoin.png");
	setthisTexture(tex[23], "Consolas/0.png");
	setthisTexture(tex[24], "Consolas/1.png");
	setthisTexture(tex[25], "Consolas/2.png");
	setthisTexture(tex[26], "Consolas/3.png");
	setthisTexture(tex[27], "Consolas/4.png");
	setthisTexture(tex[28], "Consolas/5.png");
	setthisTexture(tex[29], "Consolas/6.png");
	setthisTexture(tex[30], "Consolas/7.png");
	setthisTexture(tex[31], "Consolas/8.png");
	setthisTexture(tex[32], "Consolas/9.png");
	setthisTexture(tex[33], "turretPlate.png");
	setthisTexture(tex[34], "turret.png");

	for (int i = 0; i < 10; i++) {
		numberTextures.push_back(new GLuint(tex[23+i]));
	}
}

void setup(void)
{

	// Set up z-buffer for rendering
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Enable Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int size = 6;

	// Set up the textures
	setallTexture();

	std::vector<GLuint*> extraTextures;
	extraTextures.push_back(new GLuint(tex[7])); // Machine Gun Texture
	extraTextures.push_back(new GLuint(tex[8])); // Rocket Launcher Texture
	extraTextures.push_back(new GLuint(tex[9])); // Scud Missle Launcher Texture
	extraTextures.push_back(new GLuint(tex[10])); // Laser Weapon
	extraTextures.push_back(new GLuint(tex[11])); // Propellor
	// Setup the player object (position, texture, vertex count)
	PlayerGameObject* player = new PlayerGameObject(glm::vec3(0.0f, 0.0f, 0.0f), tex[0], size, extraTextures);
	// Note, player object should always be the first object in the game object vector 
	gameObjects.push_back(player);
	
	// Setup other objects
	//**Add new enemies by modifying the 'buildMap' function below and through editing the text file called 'map1'**
	/*
	gameObjects.push_back(new GameObject(glm::vec3(-1.0f, 1.0f, 0.0f), tex[1], size));
	gameObjects.push_back(new GameObject(glm::vec3(1.0f, -0.5f, 0.0f), tex[2], size));
	*/

	//Builds the first map
	buildMap("map1.txt");
	
	//Set up UI objects
	for (int i = 0; i < gameObjects.size(); i++) {
		if (gameObjects[i]->whatIs() == "object" || gameObjects[i]->whatIs() == "player")
			dynamicUIObjects.push_back(new HealthUI(gameObjects[i]->getPosition(), tex[3], tex[4], size, *(gameObjects[i])));
	}

	staticUIObjects.push_back(new WeaponUI(glm::vec3(-1.0f, -1.875f, 0), tex[16], tex[17], size, *(gameObjects[0])));
	staticUIObjects.push_back(new CoinUI(glm::vec3(1.5f, -1.75f, 0), tex[22], size, *(gameObjects[0]), numberTextures));
}

void shoot(Weapon* w, glm::vec3 startingPos, double dx, double dy) {
	w->lastTimeShot = glfwGetTime();
	if (w->speed == -1.0f) {
		for (int i = 0; i < 11; i++) {
			ProjectileGameObject* proj = new ProjectileGameObject(startingPos + glm::vec3(w->radius * 2 * i * dx, w->radius * 2 * i * dy, 0), tex[5], 6, *w, dx, dy, tex[6], tex[15]);
			gameObjects.push_back(proj);
		}
		((PlayerGameObject*)gameObjects[0])->freeze(w->lifespan);
	} 
	else {
		ProjectileGameObject* proj = new ProjectileGameObject(startingPos, tex[5], 6, *w, dx, dy, tex[6], tex[15]);
		gameObjects.push_back(proj);
	}
}

void controls(void)
{
	PlayerGameObject *player = (PlayerGameObject*) gameObjects[0];
	glm::vec3 currAcc = player->getAcceleration();
	float ddx = currAcc.x;
	float ddy = currAcc.y;

	// MOVEMENT: Controls allow the player to move in 8 directions, but while not moving the player hovers slightly downwards
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
		ddy = 1.0f;
	}
	else if (glfwGetKey(Window::getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
		ddy = -1.0f;
	}
	else {
		ddy = -0.02f;
	}

	if (glfwGetKey(Window::getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
		ddx = 1.0f;
		if (ddy == -0.02f)
			ddy = 0.0f;
	}
	else if (glfwGetKey(Window::getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
		ddx = -1.0f;
		if (ddy == -0.02f)
			ddy = 0.0f;
	}
	else {
		ddx = 0.0f;
	}
	player->changeAcceleration(glm::vec3(ddx, ddy, 0));

	// CHANGING WEAPONS: Can only shoot in 4 cardinal directions
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_1) == GLFW_PRESS) {
		player->equip(0);
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_2) == GLFW_PRESS) {
		player->equip(1);
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_3) == GLFW_PRESS) {
		player->equip(2);
	}
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_4) == GLFW_PRESS) {
		player->equip(3);
	}

	// SHOOTING: Can only shoot in 4 cardinal directions
	double dir = -1;
	if (glfwGetKey(Window::getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		dir = 0;
	}
	else if (glfwGetKey(Window::getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
		dir = 90;
	}
	else if (glfwGetKey(Window::getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		dir = 180;
	}
	else if (glfwGetKey(Window::getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		dir = 270;
	}
	if (dir != -1) {
		player->setAimAngle(dir);
	}

	Weapon* w = player->getEquippedWeapon();
	if (w->lastTimeShot + w->cooldown < glfwGetTime() && dir != -1) {
		if (dir == 0)
			shoot(w, player->getPosition() + glm::vec3(0.5f, -0.2f, 0), 1, 0);
		else if (dir == 90)
			shoot(w, player->getPosition() + glm::vec3(0.05f, 0.5f, 0), 0, 1);
		else if (dir == 180)
			shoot(w, player->getPosition() + glm::vec3(-0.5f, -0.2f, 0), -1, 0);
		else if (dir == 270)
			shoot(w, player->getPosition() + glm::vec3(0.05f, -0.5f, 0), 0, -1);
	}
}

void gameLoop(Window& window, Shader& shader, double deltaTime)
{
	// Clear background
	window.clear(viewport_background_color_g);

	// Render static UI Elements
	float uiZoom = 0.5f;
	glm::mat4 staticUIMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(uiZoom, uiZoom, uiZoom));
	shader.setUniformMat4("viewMatrix", staticUIMatrix);
	for (int i = 0; i < staticUIObjects.size(); i++) {
		UIObject* obj = staticUIObjects[i];
		if (obj->getIsAlive()) {
			obj->update(deltaTime);
			obj->render(shader);
		}
	}

	// set view to zoom out, centred by default at 0,0
	float cameraZoom = 0.15f;
	glm::mat4 viewMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(cameraZoom, cameraZoom, cameraZoom));
	viewMatrix = glm::translate(viewMatrix, -(gameObjects[0]->getPosition()));
	shader.setUniformMat4("viewMatrix", viewMatrix);

	// Render dynamic UI Elements
	for (int i = 0; i < dynamicUIObjects.size(); i++) {
		UIObject* obj = dynamicUIObjects[i];
		if (obj->getIsAlive()) {
			obj->update(deltaTime);
			obj->render(shader);
		}
	}

	// apply user input
	controls();

	// Update and render all game objects
	for (int i = 0; i < gameObjects.size(); i++) {
		// Get the current object
		GameObject* currentGameObject = gameObjects[i];

		// Update game objects
		currentGameObject->update(deltaTime);

		//Check for collision with walls if the item is a projectile or a player
		if (i == 0 || currentGameObject->getType() == 1) {
			for (int j = 0; j < MapObjects.size(); j++) {
				GameObject* currentWall = MapObjects[j];
				PlayerGameObject* player = (PlayerGameObject*)gameObjects[0];

				//Get positions
				glm::vec3 pos1 = currentGameObject->getPosition();
				glm::vec3 pos2 = currentWall->getPosition();
				float rad1 = currentGameObject->getSize() / 2;
				float size = currentWall->getSize();
				//If the wall is solid
				if (currentWall->getType() == 1) {
					// Set tester position
					float testX = pos1.x;
					float testY = pos1.y;
					// Rebounding directions
					float dirX = 0;
					float dirY = 0;
					if (pos1.x <= pos2.x - size/2) { // Player is left from wall 
						testX = pos2.x - size/2;
						dirX = -1.0f;
					}
					else if (pos1.x >= pos2.x + size/2) { // Player is right from wall
						testX = pos2.x + size/2;
						dirX = 1.0f;
					}
					if (pos1.y <= pos2.y - size/2) { // Player is below wall
						testY = pos2.y - size/2;
						dirY = -1.0f;
					}
					else if (pos1.y >= pos2.y + size/2) { // Player is above wall
						testY = pos2.y + size/2;
						dirY = 1.0f;
					}

					// Calculate difference between test point and player position
					float diffX = pos1.x - testX;
					float diffY = pos1.y - testY;
					float distSq = pow(diffX, 2) + pow(diffY, 2);
					if (distSq <= pow(rad1,2)) { // Standard circle to point collision
						std::cout << "Touched wall" << std::endl;
						if (i == 0) {
							currentGameObject->setVelocity(glm::vec3(dirX, dirY, 0));
						}
						else {
							currentGameObject->damage(1.0f);
						}
					}

					if (testX == pos1.x && testY == pos1.y) {
						if (i == 0)
							playerRelocate(player);
						else
							currentGameObject->damage(1.0f);
					}
				}
			}
		}

		// Check for collision between game objects
		for (int j = i + 1; j < gameObjects.size(); j++) {
			GameObject* otherGameObject = gameObjects[j];

			glm::vec3 pos1 = currentGameObject->getPosition();
			glm::vec3 pos2 = otherGameObject->getPosition();
			float rad1 = currentGameObject->getSize() / 2;
			float rad2 = otherGameObject->getSize() / 2;
			float breadth = 0.1f;
			if (pow((pos2.x - pos1.x), 2) + pow((pos2.y - pos1.y), 2) <= pow((rad1 + rad2), 2) - breadth) {
				if (currentGameObject->getIsFriendly() != otherGameObject->getIsFriendly()
					&& !currentGameObject->isDamaged() && !otherGameObject->isDamaged()) {
					currentGameObject->damage(otherGameObject->getDamage());
					otherGameObject->damage(currentGameObject->getDamage());
				}

				if (otherGameObject->getIsFriendly() && (i == 0)) {
					char* touched = otherGameObject->whatIs();
					std::cout << "Touched " << touched << std::endl;

					if (strcmp("vortex", touched) == 0) {
						nextLevel();
					}

					if (strcmp("powerUp", touched) == 0) {
						PowerUpGameObject* powerUp = (PowerUpGameObject*)otherGameObject;
						PlayerGameObject* player = (PlayerGameObject*)currentGameObject;
						player->powerUp(powerUp->getPowerUpType());
						powerUp->kill();
					}
				}
			}
		}

		// Render game objects
		currentGameObject->render(shader);
	}

	//Render map
	for (int i = 0; i < MapObjects.size(); i++) {
		MapObjects[i]->render(shader);
	}

	// Update other events like input handling
	glfwPollEvents();

	// Push buffer drawn in the background onto the display
	glfwSwapBuffers(window.getWindow());

	// Is the player dead?
	if (!gameObjects[0]->getIsAlive())
		exit(0);

	// Remove dead objects from each vector
	gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(), [](GameObject* obj) {return !obj->getIsAlive(); }), gameObjects.end());
	dynamicUIObjects.erase(std::remove_if(dynamicUIObjects.begin(), dynamicUIObjects.end(), [](UIObject* obj) {return !obj->getIsAlive(); }), dynamicUIObjects.end());
	MapObjects.erase(std::remove_if(MapObjects.begin(), MapObjects.end(), [](GameObject* obj) {return !obj->getIsAlive(); }), MapObjects.end());
}

void playerRelocate(PlayerGameObject* player) {
	glm::vec3 truePos = player->getPosition();
	float rad1 = player->getSize() / 2;
	bool touched;

	//Find the nearest unoccupied square and plop the player there.
	for (int i = 0; i < 8; i++) {
		touched = false;
		glm::vec3 pos1 = truePos;
		if (i == 0) {
			//To the right
			pos1.x = pos1.x + 1.0f;
		}
		else if (i == 1) {
			//To the upper right
			pos1.x = pos1.x + 1.0f;
			pos1.y = pos1.y + 1.0f;
		}
		else if (i == 2) {
			//Above
			pos1.y = pos1.y + 1.0f;
		}
		else if (i == 3) {
			//To the upper left
			pos1.x = pos1.x - 1.0f;
			pos1.y = pos1.y + 1.0f;
		}
		else if (i == 4) {
			//To the left
			pos1.x = pos1.x - 1.0f;
		}
		else if (i == 5) {
			//To the lower left
			pos1.x = pos1.x - 1.0f;
			pos1.y = pos1.y - 1.0f;
		}
		else if (i == 6) {
			//Below
			pos1.y = pos1.y - 1.0f;
		}
		else if (i == 7) {
			//To the lower right
			pos1.x = pos1.x + 1.0f;
			pos1.y = pos1.y - 1.0f;
		}
		for (int j = 0; j < MapObjects.size(); j++) {
			GameObject* currentWall = MapObjects[j];
			glm::vec3 pos2 = currentWall->getPosition();
			//If the wall is solid
			if (currentWall->getType() == 1) {
				//If they touch, try again
				if (pos1.x > pos2.x - 1.0f && pos1.x < pos2.x + 1.0f && pos1.y > pos2.y - 1.0f && pos1.y < pos2.y + 1.0f) {
					touched = true;
					continue;
				}
			}
		}
		if (!touched) {
			//Nobody touched a wall this time? This is the one.
			player->setPosition(pos1);
			return;
		}
	}
}

void buildMap(std::string map)
{
	std::string line;
	std::ifstream myfile(map);
	int j = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			std::cout << line << std::endl;
			for (int i = 0; i < line.length(); i++) {
				float len = 2.0f * i;
				float hei = 0.0f - (2.0f * j);
				switch (line[i]) {
				case 'X':
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[12], 6, 1));
					break;
				case'S':
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[13], 6, 0));
					gameObjects[0]->setPosition(glm::vec3(len, hei, 0.0f));
					break;
				case 'c': // Coin
					gameObjects.push_back(new PowerUpGameObject(glm::vec3(len, hei, 0.0f), tex[22], 6, COIN));
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[13], 6, 0));
					break;
				case 'f': // Double Fire Rate
					gameObjects.push_back(new PowerUpGameObject(glm::vec3(len, hei, 0.0f), tex[21], 6, DOUBLE_FIRE_RATE));
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[13], 6, 0));
					break;
				case 'q': // Quad Damage
					gameObjects.push_back(new PowerUpGameObject(glm::vec3(len, hei, 0.0f), tex[20], 6, QUAD_DAMAGE));
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[13], 6, 0));
					break;
				case 'h': // Health Boost
					gameObjects.push_back(new PowerUpGameObject(glm::vec3(len, hei, 0.0f), tex[19], 6, HEALTH_BOOST));
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[13], 6, 0));
					break;
				case 'i': // Invincibility
					gameObjects.push_back(new PowerUpGameObject(glm::vec3(len, hei, 0.0f), tex[18], 6, INVINCIBILITY));
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[13], 6, 0));
					break;
				case 'O':
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[13], 6, 0));
					break;
				case 'E':
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[13], 6, 0));
					//gameObjects.push_back(new GameObject(glm::vec3(len, hei, 0.0f), tex[1], 6));
					gameObjects.push_back(new TurretGameObject(glm::vec3(len, hei, 0.0f), tex[33], tex[34], 6, *gameObjects[0]));
					break;
				case 'T':
					MapObjects.push_back(new WallGameObject(glm::vec3(len, hei, 0.0f), tex[13], 6, 0));
					gameObjects.push_back(new VortexGameObject(glm::vec3(len, hei, 0.0f), tex[14], 6));
					break;
				}
			}
			j++;
		}
		myfile.close();
	}
	else std::cout << "Unable to open MAP file";
}

void nextLevel() {
	currentStage++;
	for (int i = 0; i < MapObjects.size(); i++) {
		MapObjects[i]->kill();
	}
	for (int i = 1; i < gameObjects.size(); i++) {
		gameObjects[i]->kill();
	}
	if (currentStage == 1) {
		buildMap("map2.txt");
	}
	else if (currentStage == 2) {
		buildMap("map3.txt");
	}
	for (int i = 0; i < gameObjects.size(); i++) {
		dynamicUIObjects.push_back(new HealthUI(gameObjects[i]->getPosition(), tex[3], tex[4], 6, *(gameObjects[i])));
	}
}

// Main function that builds and runs the game
int main(void){
	try {

		// Setup window
		Window window(window_width_g, window_height_g, window_title_g);
		Shader shader("shader.vert", "shader.frag");
		shader.enable();

		setup();

		// Run the main loop
		double lastTime = glfwGetTime();
		while (!glfwWindowShouldClose(window.getWindow())) {
			
			// Calculate delta time
			double currentTime = glfwGetTime();
			double deltaTime = currentTime - lastTime;
			lastTime = currentTime;

			gameLoop(window, shader, deltaTime);
		}
	}
	catch (std::exception &e){
		// print exception and sleep so error can be read
		PrintException(e);
		std::this_thread::sleep_for(std::chrono::milliseconds(100000));
	}

	return 0;
}
