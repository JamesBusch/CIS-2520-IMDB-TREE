/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 04/11/2019
 * Version: 0.02
 **************/

#ifndef _PRINCIPALSH_
#define _PRINCIPALSH_

#include "binary.h"

struct title_principals{
    char *tconst;
    char *nconst;
    char *characters;
};

struct principals_data{
    int arrSize;
    struct node *treetconst;
    struct node *treenconst;
    struct title_principals *data;
};

struct principals_data *getPrincipals(char *fileDir);
void freePrincipalsArray(struct principals_data *toFree);
void buildPrincipalsTconstTree(struct principals_data *data);
void buildPrincipalsNconstTree(struct principals_data *data);
void addNodePrincipals(struct node **root, char *key, struct title_principals *element);
struct title_principals* findPrinTconst(struct principals_data *data, char *toFind);
struct node* findPrinTconstNODE(struct principals_data *data, char *toFind);
struct title_principals* findPrinNconst(struct principals_data *data, char *toFind);
struct node* findPrinNconstNODE(struct principals_data *data, char *toFind);

#endif
