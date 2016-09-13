/**
** Project: Project1
** Name: Dong Sun
** Class: CMSC 341
** Date: 9/30/2014

**/




#ifndef LINKED_LIST_H
#define LINKED_LIST_H
using namespace std;
#include <iostream>
class Node{
private:
	char vehicle;
	Node* next;
public:
	Node();
	char setVehicle(char veh);
	void setNext(Node*aNext);
	char getvehicle();
	Node*getnext();

};
class List{
private:
	Node*head;
public:
	List();
	void print();
	void Append(char veh);
	void Delete(char veh);

};




#endif