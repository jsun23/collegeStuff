/*
class: CMSC313
project: Project8
filename: bst.h
Name: Dong Sun
Date: 11/17/2014
Email: dongsun1@umbc.edu


*/
#ifndef _BST_H_
#define _BST_H_

typedef struct tnode {
   int data ;			// payload
   unsigned int size ;		// # of items in subtree rooted here
   struct tnode *left ;		// pointer to left subtree
   struct tnode *right  ;	// pointer to right subtree
} tnode ;


tnode *new_tnode(int key) ;

tnode *bst_insert(tnode *ptr, int key) ;

void bst_walk (tnode *ptr) ;

tnode *bst_find (tnode *ptr, int key) ;

void bst_walk_depth (tnode *ptr, int depth) ;

void bst_destroy (tnode *ptr) ;

tnode *bst_remove_max(tnode *ptr, tnode **max_pptr) ;

tnode *bst_remove(tnode *ptr, int key, int *pfound) ;



#endif
