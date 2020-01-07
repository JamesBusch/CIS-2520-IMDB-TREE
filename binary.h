/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 03/11/2019
 * Version: 0.01
 **************/

#ifndef _BINARYH_
#define _BINARYH_

struct node{
    char *keyPointer;
    void *data;
    struct node *childOne;
    struct node *childTwo;
};

struct node* find(struct node *root, char *key);
void freeTree(struct node *root);

#endif
