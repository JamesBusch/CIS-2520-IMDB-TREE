/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 03/11/2019
 * Version: 0.04
 **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "name.h"
#include "common.h"

/**************************
 * getName
 * creates the array with all the name info
 * in: the file directory
 * out: a struct name_data with all the data
 *************************/
struct name_data *getName(char *fileDir){
    FILE *fp;
    struct name_basics *finalArray;
    struct name_data *toReturn;
    char *directory;
    char *loopChecker;
    char holder[256];
    char *dirHolder = "/name.basics.tsv\0";
    char stringBuffer[256];
    int actorCount;
    int i;

    /*Opening file*/
    directory = malloc(sizeof(char) * (strlen(fileDir) + strlen(dirHolder) + 1));
    strcpy(directory, fileDir);
    strcat(directory, dirHolder);
    fp = fopen(directory, "r");

    actorCount = 0;
    do{/*Gets the amount of actors/actress for array malloc*/
        loopChecker = fgets(stringBuffer, 255, fp);
        getColumn(stringBuffer, holder, 5);

        if(strstr(holder, "actor") || strstr(holder, "actress")){
            actorCount++;
        }
    }while(loopChecker != NULL);

    /*Creating struct array and reseting file*/
    finalArray = malloc(sizeof(struct name_basics) * actorCount);
    fseek(fp, 0, SEEK_SET);

    i = 0;
    do{/*Gets the nconst and primary name for each actor/actress in the file*/
        loopChecker = fgets(stringBuffer, 255, fp); 

        getColumn(stringBuffer, holder, 5);
        if(strstr(holder, "actor") || strstr(holder, "actress")){
            /*gets nconst*/
            getColumn(stringBuffer, holder, 1);
            finalArray[i].nconst = malloc(sizeof(char) * (strlen(holder)) + 1);
            reverseWord(holder);
            strncpy(finalArray[i].nconst, holder, strlen(holder) + 1);

            /*gets primary name*/
            getColumn(stringBuffer, holder, 2);
            finalArray[i].primaryName = malloc(sizeof(char) * (strlen(holder)) + 1);
            strncpy(finalArray[i].primaryName, holder, strlen(holder) + 1);
            i++;
        }
    }while(loopChecker != NULL);

    toReturn = malloc(sizeof(struct name_data));
    toReturn->arrSize = actorCount;
    toReturn->treeName = NULL;
    toReturn->treenconst = NULL;
    toReturn->data = finalArray;

    fclose(fp);
    free(directory);
    return toReturn;
}

/**************************
 * buildNameIndex
 * creates the name tree
 * in: a struct name_data with the array data
 * out: void
 *************************/
void buildNameIndex(struct name_data *data){
    int i;
    struct node *root;
    root = NULL;
    for(i = 0; i < data->arrSize; i++){
        addNodeName(&root, (data->data[i]).primaryName, &(data->data[i]));
    }
    fflush(stdout);
    data->treeName = root;
}

/**************************
 * addNodeName
 * adds a node into the tree based on the key given
 * in: the wanted root node, the key to compare,
 *     a struct name_basics of the array element location
 * out: void
 *************************/
void addNodeName(struct node **root, char *key, struct name_basics *element){
    if(*root){
        if(strcmp(key, (*root)->keyPointer) > 0){
            addNodeName(&((*root)->childOne), key, element);
        }else if(strcmp(key, (*root)->keyPointer) <= 0){
            addNodeName(&((*root)->childTwo), key, element);
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
 * findName
 * finds the wanted name in the tree
 * in: a struct name_data with the array data
 * out: a struct name_baiscs pointing at the array element
 *************************/
struct name_basics* findName(struct name_data *data, char *toFind){
    struct node *toReturn;
    toReturn = find(data->treeName, toFind);
    if(toReturn == NULL) return NULL;
    return (struct name_basics*)(toReturn->data);
}

/**************************
 * buildNconstIndex
 * builds a tree based on the nconst
 * in: a struct name_data with the array data
 * out: void
 *************************/
void buildNconstIndex(struct name_data *data){
    int i;
    struct node *root;
    root = NULL;
    for(i = 0; i < data->arrSize; i++){
        addNodeName(&root, (data->data[i]).nconst, &(data->data[i]));
    }
    data->treenconst = root;
}

/**************************
 * findTconst
 * finds the element with the wanted Tconst
 * in: a struct name_data with the array data, the wanted key
 * out: a struct name_basics pointing at the array element
 *************************/
struct name_basics* findNconst(struct name_data *data, char *toFind){
    struct node *toReturn;
    toReturn = find(data->treenconst, toFind);
    if(toReturn == NULL) return NULL;
    return (struct name_basics*)(toReturn->data);
}

/**************************
 * freeNameArray
 * frees the array of struct name_basics
 * in: struct name_data with the array data
 * out: void
 *************************/
void freeNameArray(struct name_data *toFree){
    int i;
    for(i = 0; i < toFree->arrSize; i++){
        free(toFree->data[i].nconst);
        free(toFree->data[i].primaryName);
    }
    free(toFree->data);
    free(toFree);
    
}
