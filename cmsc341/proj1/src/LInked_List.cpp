/*
** Project: Project1
** Name : Dong Sun
** Class : CMSC 341
** Date : 9 / 24 / 2014

*/


#include"Linked_List.h"

Node::Node()
{
}
char Node::setVehicle(char veh)
{
	vehicle = veh;
}
void Node::setNext(Node*aNext)
{
	next = aNext;
}
char Node::getvehicle()
{
	return vehicle;
}
Node* Node::getnext()
{
	return next;
}

List::List()
{
	head = NULL;
}

void List::Append(char veh)
{
	
	Node* nNode = new Node();
	nNode->setVehicle(veh);
	nNode->setNext(NULL);

	
	Node *tmp = head;

	if (tmp != NULL) 
	{
		while (tmp->getnext() != NULL) {
			tmp = tmp->getnext();
		}

		tmp->setNext(nNode);
	}
	else 
	{
		head = nNode;
	}
}

void List :: Delete(char veh)
{
	Node *tmp = head;

	
	if (tmp == NULL)
		return;

	if (tmp->getnext() == NULL) {
		delete tmp;
		head = NULL;
	}
	else {
	
		Node *prev;
		do {
			if (tmp->getvehicle() == veh) 
			break;
			prev = tmp;
			tmp = tmp->getnext();
		} while (tmp != NULL);
		prev->setNext(tmp->getnext());

		delete tmp;
	}
}

void List::print()
{

}