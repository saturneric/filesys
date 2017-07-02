//
//  Container.h
//  filesys
//
//  Created by Saturneric on 2017/7/1.
//  Copyright © 2017年 Bakantu Eric. All rights reserved.
//

#ifndef Container_h
#define Container_h

#include "Debug.h"
#include "List.h"
#include "ID.h"

typedef struct define{
    long id;
    int avaliable;
    int safe;
    int num;
    List *define_list;
    List *type_list;
} Define;

typedef struct item{
    long id;
    int avaliable;
    int safe;
    Define *p_define;
    List *data_list;
    int data_num;
} Item;

typedef struct table{
    long id;
    int avaliable;
    int safe;
    Define *p_define;
    List *item_list;
    long num;
}Table;

typedef struct bin{
    long id;
    int avaliable;
    int safe;
    List *item_list;
} Bin;

typedef struct file_value{
    char head[128];
    char value[128];
    long inedx;
    int if_value;
}File_v;

typedef struct define_file_value{
    char message[128];
    char type[128];
} DFile_v;

extern int table_tofile(FILE *p_file, Table *p_table);
extern int define_tofile(FILE *p_file, Define *p_define);
extern int file_totable(FILE *, Table *);
extern int file_todefine(FILE *p_file);

extern File_v *get_filevalue(char *);
extern char * get_typeByindex(Define *, int);
extern DFile_v *get_definefilevalue(char *);

extern int  *set_valueint(int);
extern double *set_valuefloat(double);
extern char *set_valuestring(char *);

extern Item *build_item(Define *);
extern int add_data(Item *, void *);
extern int free_item(Item *);

extern Define *build_define(void);
extern int add_define(Define *, char *, char *);
extern int free_define(Define *);

extern Table *build_table(Define *p_define);
extern int add_item(Table*, Item *,int);
extern int free_table(Table *);

extern Define *find_defineByid(long id);

extern void list_init(void);
extern void list_delinit(void);

extern List *defines_bin;
extern List *items_bin;


#endif /* Container_h */
