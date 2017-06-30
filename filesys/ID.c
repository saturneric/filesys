//
//  ID.c
//  filesys
//
//  Created by Saturneric on 2017/6/25.
//  Copyright © 2017年 Bakantu Eric. All rights reserved.
//

#include "ID.h"

long get_id(void){
    srand((unsigned int)time(NULL));
    return (long)(rand()+rand()%1000);
}
