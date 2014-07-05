//
//  main.c
//  Project3
//
//  Authors:
//  - Stratton Aguilar
//  - Ciaran Downey
//
//  Some rights reserved. See the included LICENSE file.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "process.h"

// global constants
const int TIME_MAX = 100000;

// function prototypes
void getInput(int *mem, int * page);
int getNumProcess(FILE* filePtr);
void assignProcessList(const char* filePath);
void assignFrameList(FRAME* frameList, int pageSize, int numPage);

int main() {
    int pageSize = 0;
    int memSize = 0;
    int numPage = 0;

    char* filePath = "./in1.txt";

    getInput(&memSize, &pageSize);

    //assign values to processes from file
    assignProcessList(filePath);

    // get number of pages
    numPage = memSize / pageSize;

    // create frames
    FRAME* framelist = malloc(numPage * sizeof(FRAME));
    // assign frames
    assignFrameList(framelist, pageSize, numPage);

    return 0;
}

int multipleOfOneHundred(int t) {
    return (t % 100) == 0 ? 1 : 0;
}

int isOneTwoOrThree(int t) {
    return (t >= 1 && t <= 3) ? 1 : 0;
}

void clearStdin(char* buf) {
    if (buf[strlen(buf) - 1] != '\n') {
        int ch;
        while (((ch = getchar()) != '\n') && (ch != EOF)) ;
    }
}

int ProcessNumericInputFromUser(const char* output, int (*func)(int)) {
    char buf[10];
    int success = 0;
    int res = 0;

    while (!success) {
        printf("%s: ", output);

        if (fgets(buf, 10, stdin) == NULL) {
            clearStdin(buf);
            printf("ERROR: You didn't enter any data!\n");

            continue;
        }

        if (sscanf(buf, "%d", &res) <= 0) {
            clearStdin(buf);
            printf("ERROR: You didn't enter a number!\n");

            continue;
        }

        if (!(success = (*func)(res))) {
            clearStdin(buf);
            printf("ERROR: That number is not a valid choice\n");
        }
    }

    return res;
}

// prompts for memory size and page size
void getInput(int* mem, int* page) {
    while (1) {
        *mem = ProcessNumericInputFromUser(
            "Memory size", multipleOfOneHundred);

        *page = ProcessNumericInputFromUser(
            "Page size (1: 100, 2: 200, 3: 400)", isOneTwoOrThree);

        switch (*page) {
        case 1: *page = 100; break;
        case 2: *page = 200; break;
        case 3: *page = 400; break;
        }

        if ((*mem) % (*page) == 0) {
            break;
        }

        printf("ERROR: Memory size must be a multiple of the page!");
        printf(" %d is not a multiple of %d, please retry.\n", *mem, *page);
    }
}

// get number of processes from file
int getNumProcess(FILE* filePtr) {
    int numProc = 0;

    fscanf(filePtr, "%d", &numProc);

    return numProc;
}

// stores values processes in process array
void assignProcessList(const char* filePath) {
    int numSpace;
    int tmp;
    int counter = 0;
    int totalSpace = 0;
    FILE* filePtr = fopen(filePath, "r");

    int numProc = getNumProcess(filePtr);
    // allocate space for process array
    PROCESS* procList = malloc(numProc * sizeof(PROCESS));

    if (!filePtr) {
        printf("ERROR: Failed to open file %s", filePath);
        exit(1);
    }

    while (!feof(filePtr) && counter < numProc) {
        // store values for processes
        fscanf(filePtr, "%d %d %d %d",
               &(procList[counter].processNum),
               &(procList[counter].arrivalTime),
               &(procList[counter].lifeTime),
               &numSpace);

        // get total memory requirements for process
        totalSpace = 0;
        for (int i = 0; i < numSpace; i++) {
            fscanf(filePtr, "%d", &tmp);
            totalSpace += tmp;
        }
        procList[counter].memReq = totalSpace;

        // for testing
        printf("%d %d %d %d\n",
               (procList[counter].processNum),
               (procList[counter].arrivalTime),
               (procList[counter].lifeTime),
               procList[counter].memReq);

        // increment for next process
        counter++;
    }

    fclose(filePtr);

    return;
}

// assigns frames to memory and sets assigned to process to false
void assignFrameList(FRAME* frameList, int pageSize, int numPage) {
    int value = 0;
    char starting[40];
    char ending[20];

    // assign the frame list to empty set the memory
    for (int i = 0; i < numPage; i++) {
        frameList[i].assigned = false;

        sprintf(starting, "%d", value);
        strcat(starting, "-");
        //setting value inclusive starting from zero
        value += pageSize - 1;

        sprintf(ending, "%d", value);
        strcat(starting, ending);
        strcpy(frameList[i].location, starting);

        value++;

        // for testing
        printf("%s\n", frameList[i].location);
    }
}

