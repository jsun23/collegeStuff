/*
class: CMSC313
project: Project8
filename: bst2.c
Name: Dong Sun
Date: 11/17/2014
Email: dongsun1@umbc.edu


*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst2.h"

tnode new_tnode(const char* nom, int freq)
{
    tnode *ptr;
    ptr = malloc(sizeof(tnode));
    if(ptr == NULL)
    {
        fprintf(stderr, "No memory!!\n");
        exit(1);
    }
    ptr->name = nom;
    ptr->frequency = freq;
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->size = 1;
    return ptr;
}

tnode bst_insert(tnode* ptr, const char* nom, int freq)
{
     if (ptr == NULL) return new_tnode(nom,freq) ;

   if ( ptr->frequency > freq )
      ptr->left = bst_insert( ptr->left, nom, freq) ;
   else
      ptr->right = bst_insert( ptr->right, nom, freq) ;

   ptr->size++ ;	// update size
   return ptr ;
}

void bst_walk(tnode* ptr)
{
    if (ptr == NULL) return ;

   // print out left subtree
   if (ptr->left != NULL) bst_walk(ptr->left) ;

   // print this node
   printf("%d [%d]\n", ptr->data, ptr->size) ;

   // print out right subtree
   if (ptr->right != NULL) bst_walk(ptr->right) ;

   return ;
}

void bst_walk_depth(tnode* ptr, int depth)
{
    if(depth == 0)
    {
        bst_walk(ptr);
    }
    else {
        printf(stderr, "The depth should be 0!!" );
    }

}

tnode bst_find(tnode* ptr, int freq)
{
      if (ptr == NULL) return NULL ;

   if ( ptr->frequency == freq ) {		// found?

      return ptr ;

   } else if ( ptr->frequency > freq ) {     // look in left subtree

      return bst_find(ptr->left, freq) ;

   } else {                            // look in right subtree

      return bst_find(ptr->right, freq) ;
   }
}

void bst_destroy(tnode* ptr)
{
       if (ptr == NULL) return ;

    bst_destroy(ptr->left) ;
    bst_destroy(ptr->right) ;

    ptr->left = NULL ;  //paranoid
    ptr->right = NULL ;
    free(ptr) ;

}

tnode bst_remove_max(tnode* ptr, tnode** max_pptr)
{
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

tnode bst_remove(tnode* ptr, int freq, int* pfound)
{
    tnode *max_node_ptr, *temp_ptr ;

   if (ptr == NULL) {   // not in NULL tree
      *pfound = 0 ;
      return NULL ;
   }

   if (ptr->frequency < freq) {   // too big, remove from right

      ptr->right = bst_remove(ptr->right, freq, pfound) ;
      if (*pfound) ptr->size-- ;
      return ptr ;

   } else if (freq < ptr->frequency) { // too small, remove from left

      ptr->left = bst_remove(ptr->left, freq, pfound) ;
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

tnode bst_find_by_rank(tnode* ptr, int rank)
{
    tnode *pptr;
    if(rank > ptr->size)
    {
        printf("No such rank: %d", rank);
    }
    else if(rank == ptr->size - 1){
        if(ptr->size == rank)
        {
            pptr = new_tnode(nom, freq);
        }
    }
    return pptr;
}

tnode bst_find_by_name(tnode* ptr, const char* nom)
{
    if(ptr->name == nom)
    {
        return ptr;
    }
}
