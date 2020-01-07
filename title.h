/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 04/11/2019
 * Version: 0.03
 **************/

#ifndef _TITLEH_
#define _TITLEH_

#include "binary.h"

struct title_basics{
    char *tconst;
    char *primaryTitle;
};

struct title_data{
    int arrSize;
    struct node *treeTitle;
    struct node *treetconst;
    struct title_basics *data; 
};

struct title_data *getTitle(char *fileDir);
void buildPTIndex(struct title_data *data);
void freeTitleArray(struct title_data *toFree);
void addNodePT(struct node **root, char *key, struct title_basics *element);
struct title_basics* findPT(struct title_data *data, char *toFind);
void buildTconstTree(struct title_data *data);
void addNodeTconst(struct node **root, char *key, struct title_basics *element);
struct title_basics* findTconst(struct title_data *data, char *toFind);
#endif
