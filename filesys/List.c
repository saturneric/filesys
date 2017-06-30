//
//  List.c
//  filesys
//
//  Created by Saturneric on 2017/6/25.
//  Copyright © 2017年 Bakantu Eric. All rights reserved.
//

#include "List.h"
#include "Debug.h"
#include "ID.h"

List *build_list(void){
    List *p_list = (List *) malloc(sizeof(List));
    p_list->avaliable = 1;
    p_list->id = get_id();
    p_list->h_node = NULL;
    p_list->l_node = NULL;
    p_list->num = 0;
    p_list->safe = 1;
    return p_list;
}

Node *build_node(void){
    Node *p_node = (Node *) malloc(sizeof(Node));
    p_node->avaliable = 1;
    p_node->id = get_id();
    p_node->l_node = NULL;
    p_node->n_node = NULL;
    p_node->value = NULL;
    p_node->safe = 1;
    return p_node;
}

int add_node(List *p_list, Node *p_node){
    int pass = 1;
    if(check_list(p_list) == -1) pass = -1;
    if(check_node(p_node) == -1) pass = -1;
    if (pass == -1) return -1;
    if(p_list->h_node == NULL){
        p_list->h_node = p_node;
        p_list->l_node = p_node;
    }
    else{
        p_list->l_node->n_node = p_node;
        p_node->l_node = p_list->l_node;
        p_list->l_node = p_node;
    }
    p_list->num++;
    return 0;
}

int del_node(List *p_list, Node *p_node){
    int pass = 1;
    if(check_list(p_list) == -1) pass = -1;
    if(check_node(p_node) == -1) pass = -1;
    if (pass == -1) return -1;
    if (p_list->num <= 0) return -1;
    p_node->l_node->l_node->n_node = NULL;
    Node *pl_node = p_node->l_node->l_node;
    free_node(p_node->l_node);
    p_node->l_node = pl_node;
    p_list->num--;
    return 0;
}

int free_node(Node *p_node){
    free(p_node ->value);
    free(p_node);
    return 0;
}

int check_list(List *p_list){
    if(p_list == NULL){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = ERROR;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_list;
        t_deg_crt_ifo->message = "the list is no eist.";
        debug_printf(t_deg_crt_ifo);
        return -1;
    }
    if (!p_list->avaliable){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = WARNING;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_list;
        t_deg_crt_ifo->message = "the list is no avaliable.";
        debug_printf(t_deg_crt_ifo);
        return -1;
    }
    if (!p_list->safe){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = ERROR;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_list;
        t_deg_crt_ifo->message = "the list is no safe.";
        debug_printf(t_deg_crt_ifo);
        return -1;
    }
    return 0;
}

int check_node(Node *p_node){
    if(p_node == NULL){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = ERROR;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_node;
        t_deg_crt_ifo->message = "the node is no eist.";
        debug_printf(t_deg_crt_ifo);
        return -1;
        
    }
    if (!p_node->avaliable){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = WARNING;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_node;
        t_deg_crt_ifo->message = "the node is no avaliable.";
        debug_printf(t_deg_crt_ifo);
        return -1;
    }
    if (!p_node->safe){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = ERROR;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_node;
        t_deg_crt_ifo->message = "the node is no safe.";
        debug_printf(t_deg_crt_ifo);
        return -1;
    }
    return 0;
    
}

int free_list(List *p_list){
    if (p_list == NULL){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = WARNING;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_list;
        t_deg_crt_ifo->message = "the list is no exist.";
        debug_printf(t_deg_crt_ifo);
    }
    Node *p_node, *pl_node;
    p_node = p_list->h_node;
    while (p_node != NULL){
        pl_node = p_node;
        p_node = p_node->n_node;
        pl_node->avaliable = 0;
        pl_node->safe = 0;
        free_node(pl_node);
    }
    p_list->avaliable = 0;
    p_list->safe = 0;
    free(p_list);
    return 0;
}

Node * get_locationByindex(List *p_list,int index){
    check_list(p_list);
    if (index > p_list->num-1){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = ERROR;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_list;
        t_deg_crt_ifo->message = "the nodes in the list is not enough.";
        debug_printf(t_deg_crt_ifo);
        return NULL;
    }
    Node *p_node = p_list->h_node;
    while(--index > 0){
        p_node = p_node->n_node;
    }
    return p_node;
}

Node *get_locationByid(List *p_list,long id){
    check_list(p_list);
    Node *p_node = p_list->h_node;
    Node *s_node = NULL;
    while(s_node == NULL){
        if (p_node->id == id) s_node = p_node;
        p_node = p_node->n_node;
    }
    return s_node;
}

Node *get_locationBystring(List *p_list, char *string){
    check_list(p_list);
    Node *p_node = p_list->h_node;
    Node *s_node = NULL;
    while(s_node == NULL){
        if (!strcmp(p_node->value, string)) s_node = p_node;
        p_node = p_node->n_node;
    }
    return s_node;
}

int  *set_valueint(int integer){
    int *p_integer  = (int *) malloc(sizeof(int));
    *p_integer = integer;
    return p_integer;
}

double *set_valuefloat(double fnum){
    double *p_fnum = (double *)malloc(sizeof(double));
    *p_fnum = fnum;
    return p_fnum;
}

char *set_valuestring(char *string){
    char *p_string = (char *) malloc(sizeof(char) * 256);
    strcpy(p_string, string);
    return p_string;
}

int list_tofile(FILE *p_file, List *p_list){
    //fprintf(p_file, "%d,%d,");
    return 0;
}

Item *build_item(void){
    Item *p_item = (Item *)malloc(sizeof(Item));
    p_item->id = get_id();
    p_item->data_list = build_list();
    p_item->data_num = 0;
    p_item->type_list = build_list();
    p_item->define_list = build_list();
    p_item->define_num = 0;
    p_item->avaliable = 1;
    p_item->safe = 1;
    return p_item;
}

int add_define(Item *p_item, char *define, char *type){
    Node *pd_node = build_node();
    pd_node->value = set_valuestring(define);
    
    Node *pt_node = build_node();
    pt_node->value = set_valuestring(type);
    
    add_node(p_item->define_list, pd_node);
    add_node(p_item->type_list, pt_node);
    p_item->define_num++;
    return 0;
}

int add_data(Item *p_item, void *value){
    if (p_item->data_num >= p_item->define_num){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = ERROR;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_item;
        t_deg_crt_ifo->message = "data is more than define.";
        debug_printf(t_deg_crt_ifo);
    }
    return 0;
}


