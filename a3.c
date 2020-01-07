/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 26/10/2019
 * Version: 0.02
 **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary.h"
#include "common.h"
#include "name.h"
#include "principals.h"
#include "title.h"

int main(int argc, char **argv){

    char buffer[150];
    char *command;
    char *userInput;
    int  currChar;
    int i;
    struct name_data *holderName;
    struct name_basics *nameBasics;
    struct title_data *holderTitle;
    struct title_basics *titleBasics = NULL;
    struct principals_data *holderPrincipals;
    struct node *nodeHolder;

    if(argc != 2){
        fprintf( stderr, "Usage:  %s directory\n", argv[0] );
        return -1;
    }

    holderName = getName(argv[1]);
    buildNameIndex(holderName);
    buildNconstIndex(holderName);

    holderTitle = getTitle(argv[1]);
    buildPTIndex(holderTitle);
    buildTconstTree(holderTitle);

    holderPrincipals = getPrincipals(argv[1]);
    buildPrincipalsNconstTree(holderPrincipals);
    buildPrincipalsTconstTree(holderPrincipals);


    do{
        currChar = 149;
        printf("> ");
        fgets(buffer, 149, stdin);
        command = buffer;
        /*killing white space and new line characters*/
        while(command[0] == ' ') command++;
        while(buffer[currChar] != '\n') currChar--;
        buffer[currChar] = ' ';
        while(buffer[currChar] == ' ')currChar--;
        buffer[currChar + 1] = '\0';

        /*getting command*/
        currChar = 0;
        while(command[currChar] != ' ') currChar++;
        command[currChar] = '\0';
        currChar++;

        /*getting user title/name*/
        userInput = buffer;
        while(userInput[0] == ' ')userInput++;
        for(i = 0; i < currChar; i++){
            userInput++;
        }

        if(strcmp(command, "name") == 0){
            titleBasics = NULL;
            nameBasics = findName(holderName, userInput);
            if(nameBasics == NULL){

            }else{
                nodeHolder = findPrinNconstNODE(holderPrincipals, nameBasics->nconst);
                do{
                    titleBasics = findTconst(holderTitle, ((struct title_principals*)(nodeHolder->data))->tconst);
                    if(titleBasics == NULL){

                    }else if(strcmp(((struct title_principals*)(nodeHolder->data))->nconst,
                        nameBasics->nconst) == 0){
                        printf("%s : %s", titleBasics->primaryTitle, ((struct title_principals*)(nodeHolder->data))->characters);
                    }
                    if(nodeHolder->childOne != NULL &&
                        strcmp(((struct title_principals *)((nodeHolder->childOne)->data))->nconst, nameBasics->nconst) == 0){
                        nodeHolder = nodeHolder->childOne;
                    }else{
                        nodeHolder = nodeHolder->childTwo;
                    }
                }while(nodeHolder != NULL);
            }


        }else if(strcmp(command, "title") == 0){
            nameBasics = NULL;
            titleBasics = findPT(holderTitle, userInput);
            if(titleBasics == NULL){
                
            }else{
                nodeHolder = findPrinTconstNODE(holderPrincipals, titleBasics->tconst);
                do{
                    nameBasics = findNconst(holderName, ((struct title_principals*)(nodeHolder->data))->nconst);
                    if(nameBasics == NULL){

                    }else if(strcmp(((struct title_principals*)(nodeHolder->data))->tconst,
                        titleBasics->tconst) == 0){
                        printf("%s : %s", nameBasics->primaryName, ((struct title_principals*)(nodeHolder->data))->characters);
                    }
                    
                    nodeHolder = nodeHolder->childTwo;
                    if(nodeHolder != NULL && strcmp(((struct title_principals*)(nodeHolder->data))->tconst,
                        titleBasics->tconst) != 0){
                        nodeHolder = find(nodeHolder, titleBasics->tconst);
                    }
                    
                }while(nodeHolder != NULL);
            }


        }else if(strcmp(command, "exit") == 0){
            break;
        }else{

        }

        for(i = 0; i < 150; i++){
            buffer[i] = ' ';
        }
        
    }while(strcmp(command, "exit") != 0);


    freeTree(holderName->treeName);
    freeTree(holderName->treenconst);
    freeTree(holderPrincipals->treenconst);
    freeTree(holderPrincipals->treetconst);
    freeTree(holderTitle->treeTitle);
    freeTree(holderTitle->treetconst);
    freeNameArray(holderName);
    freePrincipalsArray(holderPrincipals);
    freeTitleArray(holderTitle);


    return 0;
}
