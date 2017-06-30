//
//  db.c
//  filesys
//
//  Created by Saturneric on 2017/6/30.
//  Copyright © 2017年 Bakantu Eric. All rights reserved.
//

#include "Db.h"
#include "List.h"

int build_database(DB_CREATE_INFO * p_db_cte_ifo){
    char db_path[64];
    int mk_return = -1;
    sprintf(db_path,"%s%s/",path,p_db_cte_ifo->name);
    printf("DEBUG: db_path = %s\n",db_path);
    
    mk_return = mkdir(db_path,S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
    return mk_return;
}
