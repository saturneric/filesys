//
//  Debug.h
//  filesys
//
//  Created by Saturneric on 2017/6/25.
//  Copyright © 2017年 Bakantu Eric. All rights reserved.
//

#ifndef Debug_h
#define Debug_h

#include <stdio.h>
#include <stdlib.h>

#define STRING 1
#define INT 2
#define FLOAT 3
#define ERROR -1
#define IMPORTANT_ERROR -2
#define WARNING 0

typedef struct debug_info{
    long id;
    int type;
    int safe;
    int showvar;
    int avaliable;
    void *variable;
    char *message;
} DEBUG_CREATE_INFO;

extern int debug_printf(DEBUG_CREATE_INFO *);
extern DEBUG_CREATE_INFO *get_degcrtifo(void);

#endif /* Debug_h */
