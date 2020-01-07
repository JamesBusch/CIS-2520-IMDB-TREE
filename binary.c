/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 04/11/2019
 * Version: 0.01
 **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary.h"
#include "title.h"
#include "name.h"


/**************************
 * find
 * finds the occernce of the given key
 * in: the root node, the key of what its searching for
 * out: the node with the data
 *************************/
struct node* find(struct node *root, char *key){
    if(root){
        if(strcmp(key, root->keyPointer) > 0){
            return find(root->childOne, key);
        }else if(strcmp(key, root->keyPointer) < 0){
            return find(root->childTwo, key);
        }else{
            return root;
        }
    }else{
        return NULL;
    }
}

/**************************
 * freeTree
 * frees every node of a tree
 * in: the wanted root to free
 * out: void
 **************************/
void freeTree(struct node *root){
    if(root){
        freeTree(root->childOne);
        freeTree(root->childTwo);
        free(root);
    }
}
