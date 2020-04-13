#pragma once

#include "Node.h"
#include "Shader.h"
#include "GameObject.h"
#include "Window.h"
#include "common.h"

#include <queue>
#include <map>
#include <algorithm>

//struct used to rank various nodes in the priority_queue
struct QNode{
	Node *node;
	int cost;
};

class Graph {
public:
	//constructor. 
	Graph(int nodeWidth, int nodeHeight, GameObject nodeSprite, GameObject& ref);
	Graph(std::vector<Node*>&, GameObject nodeSprite, GameObject& ref);

	void formatNodes(std::vector<Node*>& nodes);
	
	//Loops through array and prints out associated data for each node.
	void printData();

	//gets mouse input, updates start and end position using that information
	void update();

	glm::vec3 getFirstLocation();

	//returns the id of a node from an x/y coordinate
	int selectNode(double x, double y);

	//returns a reference to the node with the supplied id.
	Node& getNode(int id);

	void getNext();
	Node getNextId();
	bool moving = true;

	void setObstacle(int nodeId);


	//renders all the nodes in the graph
	void render(Shader &shader);

	//creates and marks a path from start to end
	std::vector<Node*> pathfind();

	//setters
	inline void setStart(int nodeId) { startNodeId = nodeId; }
	inline void setEnd(int nodeId) { endNodeId = nodeId; }
	inline void setUpdateCD(float n) { updateCD = n; }

	//getters
	inline int getStartId() { return startNodeId; }
	inline int getEndId() { return endNodeId; }
	inline float getUpdateCD() { return updateCD; }
	inline int getNodeWid() { return nodeWid; }
	inline int getNodeHei() { return nodeHei; }

	std::vector<std::vector<Node*>*> nodeVec;



private:
	//node sprite used to draw each node.
	GameObject nodeObj;

	float updateCD = 1;

	//id of start and endnode
	int startNodeId, endNodeId;
	float start_x;
	float start_y;
	GameObject& player;
	//2d vector containing all the nodes in the graph
	//std::vector<std::vector<Node>> nodes;

	std::vector<Node*> pathNodes;

	int nodeHei;
	int nodeWid;
	int size;
	//map used for easy access to nodes via id
	std::map<int, Node*> nodeMap;
	int hover;

	float minX;
	float minY;

	int binarySearchY(std::vector<std::vector<Node*>*> vec, int l, int r, int dist);
	int binarySearchX(std::vector<Node*>* vec, int l, int r, int dist);
};