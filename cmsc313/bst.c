/*
class: CMSC313
project: Project8
filename: bst.c
Name: Jeffery Sun
Date: 11/17/2014
Email: dongsun1@umbc.edu


*/
/*   File: bst.c
 *
 *   Implementation of binary search tree ADT.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"


//
//  Create a binary search tree node with given key
//
tnode *new_tnode(int key) {
   tnode *ptr ;

   ptr = malloc(sizeof(tnode)) ;
   if (ptr == NULL) {
      fprintf(stderr, "Out of memory in new_tnode().\n") ;
      exit(1) ;
   }

   ptr->data = key ;
   ptr->size = 1 ;
   ptr->left = NULL ;
   ptr->right = NULL ;

   return ptr ;

}


//
// Add a new node with key to BST subtree rooted at ptr.
// Returns pointer to root of modified BST.
//

tnode *bst_insert(tnode *ptr, int key) {

   if (ptr == NULL) return new_tnode(key) ;

   if ( ptr->data > key )
      ptr->left = bst_insert( ptr->left, key) ;
   else
      ptr->right = bst_insert( ptr->right, key) ;

   ptr->size++ ;	// update size
   return ptr ;

}


//
// Print out contents of BST in order
//

void bst_walk (tnode *ptr) {

   if (ptr == NULL) return ;

   // print out left subtree
   if (ptr->left != NULL) bst_walk(ptr->left) ;

   // print this node
   printf("%d [%d]\n", ptr->data, ptr->size) ;

   // print out right subtree
   if (ptr->right != NULL) bst_walk(ptr->right) ;

   return ;
}


//
// Look for key in BST subtree rooted at ptr
// Return pointer to found node.
// If not found, return NULL.
//
tnode *bst_find(tnode *ptr, int key) {

   if (ptr == NULL) return NULL ;

   if ( ptr->data == key ) {		// found?

      return ptr ;

   } else if ( ptr->data > key ) {     // look in left subtree

      return bst_find(ptr->left, key) ;

   } else {                            // look in right subtree

      return bst_find(ptr->right, key) ;
   }
}

void bst_walk_depth (tnode *ptr, int depth)
{
    if(depth == 0)
    {
        bst_walk(ptr);
    }
    else {
        printf(stderr, "The depth should be 0!!" );
    }

}

//
// Recursively delete BST tree rooted at ptr
//
void bst_destroy (tnode *ptr) {

    if (ptr == NULL) return ;

    bst_destroy(ptr->left) ;
    bst_destroy(ptr->right) ;

    ptr->left = NULL ;  //paranoid
    ptr->right = NULL ;
    free(ptr) ;

}


//
//  Remove largest item in BST subtree rooted at ptr
//  Returns pointer to modified subtree.
//  Pointer to max node found is stored in reference parameter max_pptr
//
tnode *bst_remove_max(tnode *ptr, tnode **max_pptr) {
   tnode *left ;

   // NULL pointer is an error condition
   if (ptr == NULL) {
      fprintf(stderr, "Can't remove max node from NULL pointer!\n") ;
      exit(1) ;
   }

   // If right subtree exists, max is in right subtree
   if (ptr->right != NULL) {

      ptr->right = bst_remove_max(ptr->right, max_pptr) ;
      ptr->size-- ;

      return ptr ;   // root of modified subtree is current node


   } else {   //  no right subtree

      // if no right subtree, then current node is max

      left = ptr->left ;    // save

      ptr->left = NULL ;    // clean up current node
      ptr->right = NULL ;
      ptr->size = 1 ;

      *max_pptr = ptr ;	    // max is current node

      return left ;         // modified subtree is left subtree

   }
}


//
// Remove a node with key from BST subtree rooted at ptr.
// Returns pointer to modified subtree.
// If found, reference parameter *pfound is non-zero
// If not found, *pfound is set to zero.
//

tnode *bst_remove(tnode *ptr, int key, int *pfound) {

   tnode *max_node_ptr, *temp_ptr ;

   if (ptr == NULL) {   // not in NULL tree
      *pfound = 0 ;
      return NULL ;
   }

   if (ptr->data < key) {   // too big, remove from right

      ptr->right = bst_remove(ptr->right, key, pfound) ;
      if (*pfound) ptr->size-- ;
      return ptr ;

   } else if (key < ptr->data) { // too small, remove from left

      ptr->left = bst_remove(ptr->left, key, pfound) ;
      if (*pfound) ptr->size-- ;
      return ptr ;

   } else {   // ptr->data == key

       // just right, remove current node

      *pfound = 1 ;

       // removing current node is broken down into cases
       // depending on whether current node has any subtrees.


       // Case 1: no right subtree
       // left subtree becomes root of modified subtree
       //
      if (ptr->right == NULL) {

         temp_ptr = ptr->left ;
         ptr->left = NULL ;     // paranoid
         ptr->right = NULL ;
         free(ptr) ;
         return temp_ptr ;

      // Case 2: no left subtree
      // right subtree becomes root of modified subtree
      //
      } else if (ptr->left == NULL) {

         temp_ptr = ptr->right ;
         ptr->left = NULL ;     // paranoid
         ptr->right = NULL ;
         free(ptr) ;
         return temp_ptr ;

      // Case 3: has both subtrees
      // Remove max item from left subtree and make
      // that the new root of current subtree
      //
      } else {  // neither child is NULL

         // remove max item from left subtree
         ptr->left = bst_remove_max(ptr->left, &max_node_ptr) ;

         // max item takes over as root.
         max_node_ptr->left = ptr->left ;
         max_node_ptr->right = ptr->right ;
         max_node_ptr->size = ptr->size - 1 ;

         // Remove current item
         ptr->left = NULL ;   // paranoid
         ptr->right = NULL ;
         free(ptr) ;

         return max_node_ptr ;
      }

   }

}
