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
    p_node->avaliable = -1;
    p_node->safe = -1;
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
        pl_node->avaliable = -1;
        pl_node->safe = -1;
        free_node(pl_node);
    }
    p_list->avaliable = -1;
    p_list->safe = -1;
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
