/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 04/11/2019
 * Version: 0.04
 **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "principals.h"
#include "binary.h"

/**************************
 * getPrincipals
 * Creates the array of struct principals_basics
 * in: the file directory
 * out: a struct principals data with the array info
 *************************/
struct principals_data *getPrincipals(char *fileDir){
    FILE *fp;
    struct title_principals *finalArray;
    struct principals_data *toReturn;
    char *directory;
    char *loopChecker;
    char holder[10000];
    char *dirHolder = "/title.principals.tsv\0";
    char stringBuffer[10000];
    int actorCount;
    int i;


    /*Opening file*/
    directory = malloc(sizeof(char) * (strlen(fileDir) + strlen(dirHolder) + 1));
    strcpy(directory, fileDir);
    strcat(directory, dirHolder);
    fp = fopen(directory, "r");

    actorCount = 0;
    do{/*Gets the amount of actors/actress for array malloc*/
        loopChecker = fgets(stringBuffer, 10000, fp);
        getColumn(stringBuffer, holder, 4);

        if(strstr(holder, "actor") || strstr(holder, "actress")){
            actorCount++;
        }
    }while(loopChecker != NULL);

    /*Creating struct array and reseting file*/
    finalArray = malloc(sizeof(struct title_principals) * actorCount);
    fseek(fp, 0, SEEK_SET);

    i = 0;
    do{/*Gets the tconst, nconst, and characters from the file*/
        loopChecker = fgets(stringBuffer, 255, fp); 

        getColumn(stringBuffer, holder, 4);
        if(strstr(holder, "actor") || strstr(holder, "actress")){
            /*Adds tconst*/
            getColumn(stringBuffer, holder, 1);
            finalArray[i].tconst = malloc(sizeof(char) * (strlen(holder) + 1));
            reverseWord(holder);
            strncpy(finalArray[i].tconst, holder, strlen(holder) + 1);

            /*Adds nconst*/
            getColumn(stringBuffer, holder, 3);
            finalArray[i].nconst = malloc(sizeof(char) * (strlen(holder) + 1));
            reverseWord(holder);
            strncpy(finalArray[i].nconst, holder, strlen(holder) + 1);

            /*Adds characters*/
            getColumn(stringBuffer, holder, 6);
            finalArray[i].characters = malloc(sizeof(char) * (strlen(holder) + 1));
            strncpy(finalArray[i].characters, holder, strlen(holder) + 1);
            
            i++;
        }
    }while(loopChecker != NULL);

    toReturn = malloc(sizeof(struct principals_data));
    toReturn->arrSize = actorCount;
    toReturn->treenconst = NULL;
    toReturn->treetconst = NULL;
    toReturn->data = finalArray;

    fclose(fp);
    free(directory);
    return toReturn;
}

/**************************
 * buildPrincipalsTconstTree
 * builds a tree based off of tConst data
 * in: a struct principals_data with the array data
 * out: void
 *************************/
void buildPrincipalsTconstTree(struct principals_data *data){
    int i;
    struct node *root;
    root = NULL;
    for(i = 0; i < data->arrSize; i++){
        addNodePrincipals(&root, (data->data[i]).tconst, &(data->data[i]));
    }
    data->treetconst = root;
}

/**************************
 * buildPrincipalsNconstTree
 * builds a tree based off of nConst data
 * in: a struct principals_data with the array data
 * out: void
 *************************/
void buildPrincipalsNconstTree(struct principals_data *data){
    int i;
    struct node *root;
    root = NULL;
    for(i = 0; i < data->arrSize; i++){
        addNodePrincipals(&root, (data->data[i]).nconst, &(data->data[i]));
    }
    data->treenconst = root;
}

/**************************
 * addNodePrincipals
 * adds a node to the tree
 * in: the wanted root, the wanted key and
 *     a struct title_principals with the array data
 * out: void
 *************************/
void addNodePrincipals(struct node **root, char *key, struct title_principals *element){
    if(*root){
        if(strcmp(key, (*root)->keyPointer) > 0){
            addNodePrincipals(&((*root)->childOne), key, element);
        }else if(strcmp(key, (*root)->keyPointer) <= 0){
            addNodePrincipals(&((*root)->childTwo), key, element);
        }
    }else{
        (*root) = malloc(sizeof(struct node));
        (*root)->keyPointer = key;
        (*root)->data = element;
        (*root)->childOne = NULL;
        (*root)->childTwo = NULL;
    }
}

/**************************
 * findPrinTconst
 * finds the array element(s) containing the wanted key
 * in: a struct principals_data with the array data and the key
 * out: the location of the struct title_principals
 *************************/
struct title_principals* findPrinTconst(struct principals_data *data, char *toFind){
    struct node *toReturn;
    toReturn = find(data->treetconst, toFind);
    if(toReturn == NULL) return NULL;
    return (struct title_principals*)(toReturn->data);
}

/**************************
 * findPrinTconstNODE
 * finds the node containing the first occerance of the key
 * in: a struct principals data with the array data and the key
 * out: a struct node pointing to the first occerance
 *************************/
struct node* findPrinTconstNODE(struct principals_data *data, char *toFind){
    struct node *toReturn;
    toReturn = find(data->treetconst, toFind);
    return toReturn;
}

/**************************
 * findPrinNconst
 * finds the array element containg the wanted key
 * in: a struct principals_data with the array data and the key
 * out: the location of the struct title_principals
 *************************/
struct title_principals* findPrinNconst(struct principals_data *data, char *toFind){
    struct node *toReturn;
    toReturn = find(data->treenconst, toFind);
    if(toReturn == NULL) return NULL;
    return (struct title_principals*)(toReturn->data);
}

/**************************
 * findPrinNconstNODE
 * finds the node containing the first occerance of the key
 * in: a struct principals_data with the array data and the key
 * out: a struct node pointing to the first occerance
 *************************/
struct node* findPrinNconstNODE(struct principals_data *data, char *toFind){
    struct node *toReturn;
    toReturn = find(data->treenconst, toFind);
    return toReturn;
}


/**************************
 * freePrincipalsArray
 * frees the array for struct principals_basics
 * in: a struct principals_data with the array data
 * out: void
 *************************/
void freePrincipalsArray(struct principals_data *toFree){
    int i;
    for(i = 0; i < toFree->arrSize; i++){
        free(toFree->data[i].characters);
        free(toFree->data[i].nconst);
        free(toFree->data[i].tconst);
    }
    free(toFree->data);
    free(toFree);
}
