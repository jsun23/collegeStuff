/*
Class: CMSC341
Project: Project 5
File Name: Graph.cpp
Name: Dong Sun
Date: 12/09/2014
Email: dongsun1@umbc.edu

*/



#include "Graph.h"

Edge::Edge(Node* firstNode, Node* secNode, unsigned int inCost)
{
    orgNode = firstNode;
    dstNode = secNode;
    cost = inCost;
}

Node* Edge::getDstNode()
{
     return dstNode;
}

Node* Edge::getOrgNode()
{
    return orgNode;
}

unsigned int Edge::getCost()
{
    return cost;
}

Node::Node(int orgC, int desC, int capC)
{
    org = orgC;
    des = desC;
    cap = capC;
    status = NOT_VISITED;
}

Node::~Node()
{
    adjNodeList.clear();
}


void Node::setStatus(enum Status st)
{
    status = st;
}


void Node::addAdjNode(Node* source, Node* adj, unsigned int cost)
{
//create an edge with 'this' as the originating node and adj as the destination node
    Edge newEdge(source, adj, cost);
    adjNodeList.push_back(newEdge);
}

int Node::getOrg()
{
    return org;
}

int Node::getDes()
{
    return des;
}
int Node::getCap()
{
    return cap;
}



void Graph::addNewNode(Node* nNode)
{
    nodeList.push_back(nNode);
}

Graph::Graph(string name)
{
    findCycle = false;
    fstream myfile;
    myfile.open(name.c_str(),ios_base::in);
    if(myfile.fail( ))
	{
		cout << "The File was not successfully open." << endl;
		exit(1); // ends ENTIRE program!!!
	}


    int totalPlaces, totalLine;
    Node *src;
    Node *ds;
    int cap;
    vector<Node*> nodeLists;
    myfile>> totalPlaces;
    myfile>> totalLine;
    Gsize = totalLine;
    while(myfile >> src >> ds >> cap)
    {
        for(int i=0;i<Gsize;i++)
        {
            nodeLists[i]->addAdjNode(src,ds,cap);
        }

    }
    myfile.close();
}

/*
    trips function to find the paths that the trip need to take.
    precondition: source, destination, tourists
    postcondition: path
*/
int Graph::trips(int source, int destination, int tourists)
{
    int path=0;
    for(int i=0;i<Gsize;i++)
    {
        Edge edge = adjNodelist[i];
        if(edge.getOrgNode()->getOrg() == source)
        {
            do{
                source+=1;
                edge.getDstNode()->getDes() = source;
                tourists-=edge.getCost();
                tourists+=1;
                path++;
            }while(tourists != 0); //if the tourist not equal to 0, do the trevese
        }
    }
    return path;

}


