//
//  Db.h
//  filesys
//
//  Created by Saturneric on 2017/6/30.
//  Copyright © 2017年 Bakantu Eric. All rights reserved.
//

#ifndef Db_h
#define Db_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

char *path = "data/";

typedef struct db_info{
    char name[16];
} DB_CREATE_INFO;

extern int build_database(DB_CREATE_INFO *);

#endif /* Db_h */
