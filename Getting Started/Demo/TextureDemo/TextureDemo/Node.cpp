#include "Node.h"

//static id, used when a new node is created.
int Node::globalId = 0;

//default constructor
Node::Node(float _x, float _y) : id(globalId++) {
	edges = std::vector<Edge>();
	x = _x;
	y = _y;
	cost = 10;
	prev = NULL;
	obstacle = false;
	visited = false;
	//onPath = false;
}

void Node::obOn() {
	obstacle = true;
	onPath = false;
	for (int i = 0; i < edges.size(); i++) {
		edges[i].cost = 1000;
	}
}

void Node::obOff() {
	obstacle = false;
	for (int i = 0; i < edges.size(); i++) {
		edges[i].cost = 10;
	}
}

//determines the opposing node on an edge.
//if the edge does not contain the current node, it will return the current node
Node Node::getOtherNode(Edge e) {
	if (e.n1.getId() == getId()) {
		return e.n2;
	}
	else if (e.n2.getId() == getId()) {
		return e.n1;
	}
	else {
		return *this;
	}
}

//links two nodes together via and edge. Updates both nodes edges vector
void Node::addNode(Node& n, int edgeCost) {
	//creates an edge corresponding to nodes
	Edge e = { *this, n, edgeCost };

	//adds the edge to the vector in both nodes.
	(*this).addEdge(e);
	n.addEdge(e);
}



