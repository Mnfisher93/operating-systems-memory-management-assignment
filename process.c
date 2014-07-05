//
//  process.h
//  Project3
//
//  Created by Stratton Aguilar on 7/3/14.
//  Copyright (c) 2014 Stratton Aguilar. All rights reserved.
//

#ifndef Project3_process_h
#define Project3_process_h

typedef struct {
    int processNum;
    int arrivalTime;
    int lifeTime;
    int memReq;
}PROCESS;

typedef struct {
    bool assigned; // true if assigned to process, otherwise false
    char location[40];
    int procAssign;
    int pageNumber;
}FRAME;
#endif
