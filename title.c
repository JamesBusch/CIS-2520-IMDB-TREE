/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 04/11/2019
 * Version: 0.03
 **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "title.h"
#include "binary.h"
#include "common.h"

/**************************
 * creates the array of title_basics
 * in: the file directory
 * out: the struct containg the array
 *************************/
struct title_data *getTitle(char *fileDir){
    FILE *fp;
    struct title_basics *finalArray;
    struct title_data *toReturn;
    char *directory;
    char *loopChecker;
    char holder[1000];
    char *dirHolder = "/title.basics.tsv\0";
    char stringBuffer[1000];
    int movieCount;
    int i;


    /*Opening file*/
    directory = malloc(sizeof(char) * (strlen(fileDir) + strlen(dirHolder) + 1));
    strcpy(directory, fileDir);
    strcat(directory, dirHolder);
    fp = fopen(directory, "r");

    movieCount = 0;
    do{/*Gets the amount of movies for array malloc*/
        loopChecker = fgets(stringBuffer, 1000, fp);
        getColumn(stringBuffer, holder, 2);
        if(strstr(holder, "movie")){
            getColumn(stringBuffer, holder, 5);
            if(strstr(holder, "0")){
                movieCount++;
            }
        }

    }while(loopChecker != NULL);
    
    /*Creates array to return*/
    finalArray = malloc(sizeof(struct title_basics) * movieCount);
    fseek(fp, 0, SEEK_SET);

    i = 0;
    do{/*Fills the array with the title and tconst*/
        loopChecker = fgets(stringBuffer, 1000, fp); 

        getColumn(stringBuffer, holder, 2);
        if(strstr(holder, "movie")){
            getColumn(stringBuffer, holder, 5);
            if(strstr(holder, "0")){
                getColumn(stringBuffer, holder, 1);/*Adds tconst*/
                finalArray[i].tconst = malloc(sizeof(char) * (strlen(holder)) + 1);
                reverseWord(holder);
                strncpy(finalArray[i].tconst, holder, strlen(holder) + 1);

                getColumn(stringBuffer, holder, 3);/*Adds title*/
                finalArray[i].primaryTitle = malloc(sizeof(char) * (strlen(holder)) + 1);
                strncpy(finalArray[i].primaryTitle, holder, strlen(holder) + 1);
                i++;
            }
        }
    }while(loopChecker != NULL);

    toReturn = malloc(sizeof(struct title_data));
    toReturn->arrSize = movieCount;
    toReturn->treeTitle = NULL;
    toReturn->treetconst = NULL;
    toReturn->data = finalArray;

    fclose(fp);
    free(directory);
    return toReturn;

}

/**************************
 * buildPTIndex
 * builds the tree of primary titles/tconsts
 * in: the title_data struct that you want all the info placed in
 * out: void
 **************************/
void buildPTIndex(struct title_data *data){
    int i;
    struct node *root;
    root = NULL;
    for(i = 0; i < data->arrSize; i++){
        addNodePT(&root, (data->data[i]).primaryTitle, &(data->data[i]));
    }
    data->treeTitle = root;
}

/**************************
 * addNodePT
 * adds a node to the primary title tree
 * in: a root node, the wanted char to place, the adress of the array element to place
 * out: void
 *************************/
void addNodePT(struct node **root, char *key, struct title_basics *element){
    if(*root){
        if(strcmp(key, (*root)->keyPointer) > 0){
            addNodePT(&((*root)->childOne), key, element);
        }else if(strcmp(key, (*root)->keyPointer) <= 0){
            addNodePT(&((*root)->childTwo), key, element);
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
 * findPT
 * finds the occernces of the given string
 * in: the title_data struct containg the array and
 *     the wanted string
 * out: the location of array element
 *************************/
struct title_basics* findPT(struct title_data *data, char *toFind){
    struct node *toReturn;
    toReturn = find(data->treeTitle, toFind);
    if(toReturn == NULL) return NULL;
    return (struct title_basics*)(toReturn->data);
}

/**************************
 * buildTconstTree
 * builds the tree based on the 
 * reversed value of tconst
 * in: the title_data struct containing the array data
 * out: void
 *************************/
void buildTconstTree(struct title_data *data){
    int i;
    struct node *root;
    root = NULL;
    for(i = 0; i < data->arrSize; i++){
        addNodePT(&root, (data->data[i]).tconst, &(data->data[i]));
    }
    data->treetconst = root;
}

/**************************
 * findTconst
 * finds the occernces of the given tconst
 * in: the title_data struct containing the array data
 *     and the wanted tconst to find
 *************************/
struct title_basics* findTconst(struct title_data *data, char *toFind){
    struct node *toReturn;
    toReturn = find(data->treetconst, toFind);
    if(toReturn == NULL) return NULL;
    return (struct title_basics*)(toReturn->data);
}

/**************************
 * freeTitleArray
 * frees the array of title_basics and the struct
 * holding it
 * in: the wanted struct to free
 * out: void
 **************************/
void freeTitleArray(struct title_data *toFree){
    int i;
    for(i = 0; i < toFree->arrSize; i++){
        free(toFree->data[i].primaryTitle);
        free(toFree->data[i].tconst);
    }
    free(toFree->data);
    free(toFree);
}
