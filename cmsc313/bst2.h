/*
class: CMSC313
project: Project8
filename: bst2.h
Name: Dong Sun
Date: 11/17/2014
Email: dongsun1@umbc.edu


*/

#ifndef _BST2_H_
#define _BST2_H_

typedef struct tnode {
   char *name ;			// name of baby
   int frequency ;		// payload = # of occurrences
   unsigned int size ;		// # of items in subtree rooted here
   struct tnode *left ;		// pointer to left subtree
   struct tnode *right  ;	// pointer to right subtree
} tnode ;


tnode *new_tnode(const char *nom, int freq) ;

tnode *bst_insert(tnode *ptr, const char *nom, int freq) ;

void bst_walk (tnode *ptr) ;

void bst_walk_depth (tnode *ptr, int depth) ;

tnode *bst_find (tnode *ptr, int freq) ;

void bst_destroy (tnode *ptr) ;

tnode *bst_remove_max(tnode *ptr, tnode **max_pptr) ;

tnode *bst_remove(tnode *ptr, int freq, int *pfound) ;

tnode *bst_find_by_rank(tnode *ptr, int rank) ;

tnode *bst_find_by_name(tnode *ptr, const char *nom) ;


#endif
