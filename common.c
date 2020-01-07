/***************
 * Name: James Busch
 * ID: 1054886
 * Email: buschj@uoguelph.ca
 * Date: 27/10/2019
 * Version: 0.01
 **************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

void getColumn(char *toParse, char *dest, int columnNumber){
    int i;
    int tabCount;
    int wordLength;
    char buffer[10000];

    i = 0;
    tabCount = 0;
    wordLength = 0;
    while(tabCount < columnNumber && toParse[i] != '\0'){
        if(toParse[i] == '\t'){
            tabCount++;
        }else if(tabCount == columnNumber - 1){
            buffer[wordLength] = toParse[i];
            wordLength++;
        }
        i++;
    }

    buffer[wordLength] = '\0';
    
    strncpy(dest, buffer, wordLength + 1);
}

void reverseWord(char *toReverse){
    int front, back;
    char holder;
    front = 0;
    back = strlen(toReverse) - 1;
    while(back > front){
        holder = toReverse[front];
        toReverse[front] = toReverse[back];
        toReverse[back] = holder;
        front++;
        back--;
    }
}
