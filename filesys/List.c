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

List *items_bin = NULL;

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

int table_tofile(FILE *p_file, Table *p_table){
    fprintf(p_file, "!#TABLE_INFO\n");
    fprintf(p_file, "id:%ld\n",p_table->id);
    fprintf(p_file, "item_num:%d\n",p_table->num);
    fprintf(p_file, "define_id:%ld\n", p_table->p_define->id);
    Node *pi_node = p_table->item_list->h_node;
    Item *p_item = (Item *)pi_node->value;
    fprintf(p_file, "\n");
    fprintf(p_file, "!#ITEM_INFO\n");
    while (pi_node != NULL){
        p_item = (Item *)pi_node->value;
        fprintf(p_file, "id:%ld\n",p_item->id);
        fprintf(p_file, "data_num:%d\n",p_item->data_num);
        fprintf(p_file, "define_id:%ld\n",p_item->p_define->id);
        Node *pt_node = p_item->p_define->type_list->h_node;
        Node *pd_node = p_item->data_list->h_node;
        for (int i = 0; i < (p_item->p_define->num); i++){
            if (!strcmp((char *)pt_node->value, "int")){
                fprintf(p_file, "value[%d]:%d\n",i,*((int *)pd_node->value));
            }
            else if(!strcmp((char *)pt_node->value, "string")){
                fprintf(p_file, "value[%d]:%s\n",i,((char *)pd_node->value));
            }
            else if(!strcmp((char *)pt_node->value, "float")){
                fprintf(p_file, "value[%d]:%lf\n",i,*((double *)pd_node->value));
            }
            else{
                fprintf(p_file, "vlaue[%d]:not_avaliable\n",i);
            }
            pt_node = pt_node->n_node;
            pd_node = pd_node->n_node;
        }
        fprintf(p_file, "END\n");
        pi_node = pi_node->n_node;
    }
    return 0;
}

Item *build_item(Define *p_define){
    Item *p_item = (Item *)malloc(sizeof(Item));
    p_item->id = get_id();
    p_item->data_list = build_list();
    p_item->data_num = 0;
    p_item->p_define = p_define;
    p_item->avaliable = 1;
    p_item->safe = 1;
    Node *p_node = build_node();
    p_node->value = p_item;
    add_node(items_bin,p_node);
    return p_item;
}

int add_define(Define *p_define, char *define, char *type){
    Node *pd_node = build_node();
    pd_node->value = set_valuestring(define);
    
    Node *pt_node = build_node();
    pt_node->value = set_valuestring(type);
    
    add_node(p_define->define_list, pd_node);
    add_node(p_define->type_list, pt_node);
    p_define->num++;
    return 0;
}



int add_data(Item *p_item, void *value){
    if (p_item->data_num >= p_item->p_define->num){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = ERROR;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_item;
        t_deg_crt_ifo->message = "data is more than define.";
        debug_printf(t_deg_crt_ifo);
    }
    Node *p_node = build_node();
    p_node->value = value;
    add_node(p_item->data_list, p_node);
    p_item->data_num++;
    return 0;
}

Define *build_define(void){
    Define *p_define = (Define *) malloc(sizeof(Define));
    p_define->id = get_id();
    p_define->num = 0;
    p_define->define_list = build_list();
    p_define->type_list = build_list();
    p_define->avaliable = 1;
    p_define->safe = 1;
    return p_define;
}

int free_define(Define *p_define){
    free_list(p_define->define_list);
    free_list(p_define->type_list);
    p_define->avaliable = -1;
    p_define->safe = -1;
    free(p_define);
    return 0;
}

int free_item(Item *p_item){
    p_item->avaliable = -1;
    p_item->safe = -1;
    free_list(p_item->data_list);
    free(p_item);
    return 0;
}

Table *build_table(Define *p_define){
    Table *p_table = (Table *)malloc(sizeof(Table));
    p_table->id = get_id();
    p_table->item_list = build_list();
    p_table->p_define = p_define;
    p_table->avaliable = 1;
    p_table->safe = 1;
    return p_table;
}

int add_item(Table *p_table, Item *p_item){
    if(p_item->p_define->id != p_table->p_define->id){
        DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
        t_deg_crt_ifo->type = ERROR;
        t_deg_crt_ifo->showvar = 1;
        t_deg_crt_ifo->variable = &p_item;
        t_deg_crt_ifo->message = "item's define is different form the table's.";
        debug_printf(t_deg_crt_ifo);
    }
    Node *p_node = build_node();
    p_node->value = p_item;
    add_node(p_table->item_list,p_node);
    p_table->num++;
    return 0;
}

int free_table(Table *p_table){
    free_list(p_table->item_list);
    p_table->avaliable = -1;
    p_table->safe = -1;
    free(p_table);
    return 0;
}

void list_init(void){
    items_bin = build_list();
}

void list_delinit(void){
    Node *p_node = items_bin->h_node;
    while (p_node != NULL){
        Item *p_item = (Item *)p_node->value;
        if (p_item->avaliable == 1){
            free_item(p_item);
        }
        p_node = p_node->n_node;
    }
    free_list(items_bin);
}

int define_tofile(FILE *p_file, Define *p_define){
    fprintf(p_file, "!#define\n");
    fprintf(p_file, "id:%ld\n",p_define->id);
    Node *pd_node = p_define->define_list->h_node, *pt_node = p_define->type_list->h_node;
    for (int i = 0 ; i < p_define->num; i++){
        fprintf(p_file, "%s/%s\n",(char *)pd_node->value, (char *)pt_node->value);
        pd_node = pd_node->n_node;
        pt_node = pt_node->n_node;
    }
    fprintf(p_file, "END");
    return 0;
}
