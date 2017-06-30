//
//  List.h
//  filesys
//
//  Created by Saturneric on 2017/6/25.
//  Copyright © 2017年 Bakantu Eric. All rights reserved.
//

#ifndef List_h
#define List_h


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct node{
    long id;
    int avaliable;
    int safe;
    void *value;
    struct node *n_node;
    struct node *l_node;
} Node;

typedef struct list{
    long id;
    int avaliable;
    int safe;
    long num;
    Node *h_node;
    Node *l_node;
} List;

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
    int num;
}Table;

typedef struct bin{
    long id;
    int avaliable;
    int safe;
    List *item_list;
} Bin;

extern List *items_bin;

extern List *build_list(void);
extern Node *build_node(void);
extern int free_list(List *);
extern int free_node(Node *);
extern int add_node(List *, Node *);
extern int del_node(List *, Node *);
extern int check_list(List *);
extern int check_node(Node *);
extern Node *get_locationByindex(List *,int);
extern Node *get_locationByid(List *,long);

extern Node *get_locationBystring(List *, char *);

extern int table_tofile(FILE *p_file, Table *p_table);
extern int define_tofile(FILE *p_file, Define *p_define);
extern int file_totable(FILE *, List *);

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
extern int add_item(Table*, Item *);
extern int free_table(Table *);

extern void list_init(void);
extern void list_delinit(void);


#endif /* List_h */
