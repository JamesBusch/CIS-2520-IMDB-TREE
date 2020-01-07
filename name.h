/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 26/10/2019
 * Version: 0.01
 **************/

#ifndef _NAMEH_
#define _NAMEH_

#include "binary.h"

struct name_basics{
    char *nconst;
    char *primaryName;
};

struct name_data{
    int arrSize;
    struct node *treeName;
    struct node *treenconst;
    struct name_basics *data;
};

struct name_data *getName(char *fileDir);
void freeNameArray(struct name_data *toFree);
void buildNameIndex(struct name_data *data);
void addNodeName(struct node **root, char *key, struct name_basics *element);
struct name_basics* findName(struct name_data *data, char *toFind);
struct name_basics* findNconst(struct name_data *data, char *toFind);
void buildNconstIndex(struct name_data *data);

#endif
