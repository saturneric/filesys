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

#endif /* List_h */
