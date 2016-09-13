/*
Class: CMSC341
Project: Project 5
File Name: Graph.h
Name: Dong Sun
Date: 12/09/2014
Email: dongsun1@umbc.edu

*/

#ifndef GRAPH_H
#define GRAPH_H



#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
enum Status {
NOT_VISITED,
VISITED
};

//forward declaration
class Node;

//An object of this class represents an edge in the graph.
class Edge
{
private:
Node *orgNode;//the originating vertex
Node *dstNode;//the destination vertex
unsigned int cost;//cost of the edge

public:
Edge(Node *firstNode, Node *secNode, unsigned int inCost);
Node* getDstNode();
Node* getOrgNode();
unsigned int getCost();
};

//An object of this class holds a vertex of the graph
class Node
{
private:
vector<Edge> adjNodeList;//list of outgoing edges for this vertex
enum Status status;//used in dfs to mark the node visited
int org, des, cap;
public:
Node(int orgC, int desC, int capC);
//do not del the adj nodes here...they will be deleted by graph destructor
~Node();
enum Status getStatus();
void setStatus(enum Status st);
void addAdjNode(Node* source,Node *adj, unsigned cost);
int getOrg();
int getDes();
int getCap();




};

class Graph
{
private:

    vector<Node*> nodeList;
    vector<Edge> adjNodelist;
    int Gsize;
    bool findCycle;
    void addNewNode(Node *nNode);


public:
    Graph(string name);
    int trips(int source, int destination, int tourists);


};
#endif
