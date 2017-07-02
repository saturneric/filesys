//
//  Container.c
//  filesys
//
//  Created by Saturneric on 2017/7/1.
//  Copyright © 2017年 Bakantu Eric. All rights reserved.
//

#include "Container.h"

List *items_bin = NULL;
List *defines_bin = NULL;

int define_tofile(FILE *p_file, Define *p_define){
    fprintf(p_file, "!#define\n");
    fprintf(p_file, "id:%ld\n",p_define->id);
    fprintf(p_file, "define_num:%d\n",p_define->num);
    Node *pd_node = p_define->define_list->h_node, *pt_node = p_define->type_list->h_node;
    for (int i = 0 ; i < p_define->num; i++){
        fprintf(p_file, "value[%d]:%s/%s\n",i,(char *)pd_node->value, (char *)pt_node->value);
        pd_node = pd_node->n_node;
        pt_node = pt_node->n_node;
    }
    fprintf(p_file, "END");
    return 0;
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
    fprintf(p_file, "item_num:%ld\n",p_table->num);
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
    Node *p_node = build_node();
    p_node->value = (void *)p_define;
    add_node(defines_bin, p_node);
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
    p_table->num = 0;
    p_table->avaliable = 1;
    p_table->safe = 1;
    return p_table;
}

int add_item(Table *p_table, Item *p_item,int engineer){
    if (engineer == 0){
        if(p_item->p_define->id != p_table->p_define->id){
            DEBUG_CREATE_INFO *t_deg_crt_ifo = get_degcrtifo();;
            t_deg_crt_ifo->type = ERROR;
            t_deg_crt_ifo->showvar = 1;
            t_deg_crt_ifo->variable = &p_item;
            t_deg_crt_ifo->message = "item's define is different form the table's.";
            debug_printf(t_deg_crt_ifo);
        }
    }
    Node *p_node = build_node();
    p_node->value = p_item;
    add_node(p_table->item_list,p_node);
    p_table->num++;
    return 0;
}

int free_table(Table *p_table){
    p_table->avaliable = -1;
    p_table->safe = -1;
    free(p_table);
    return 0;
}

void list_init(void){
    items_bin = build_list();
    defines_bin = build_list();
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

int file_totable(FILE *p_file, Table *p_table){
    char f_string[256];
    int table_info = 0, item_info = 0;
    int new_item = 0;
    int index_value = 0;
    Item *p_item = NULL;
    while(fscanf(p_file, "%s",f_string) != EOF){
        if (!strcmp(f_string, "!#TABLE_INFO")) {
            table_info = 1;
            item_info = 0;
            continue;
        }
        if (!strcmp(f_string, "!#ITEM_INFO")) {
            table_info = 0;
            item_info = 1;
            new_item = 1;
            index_value = 0;
            continue;
        }
        if (table_info == 1){
            File_v *p_fv = get_filevalue(f_string);
            if(!strcmp(p_fv->head, "id")){
                p_table->id = atol(p_fv->value);
            }
            else if (!strcmp(p_fv->head, "item_num")){
                p_table->num = atol(p_fv->value);
            }
            else if (!strcmp(p_fv->head, "define_id")){
                Define *p_define = find_defineByid(atol(p_fv->value));
                p_table->p_define = p_define;
            }
            else{
                
            }
            free(p_fv);
        }
        else if (item_info == 1){
            if (new_item == 1){
                p_item = build_item(NULL);
                add_item(p_table, p_item,1);
                index_value = 0;
                new_item = 0;
            }
            if (!strcmp(f_string, "END")){
                new_item = 1;
                continue;
            }
            File_v *p_fv = get_filevalue(f_string);
            if(!strcmp(p_fv->head, "id")){
                p_item->id = atol(p_fv->value);
            }
            else if (!strcmp(p_fv->head, "data_num")){
                p_item->data_num = atoi(p_fv->value);
            }
            else if (!strcmp(p_fv->head, "define_id")){
                Define *p_define = find_defineByid(atol(p_fv->value));
                p_item->p_define = p_define;
            }
            if(p_fv->if_value){
                Define *p_define = p_item->p_define;
                char *type = get_typeByindex(p_define, index_value);
                index_value++;
                if(!strcmp(type, "string")){
                    add_data(p_item, (void *)set_valuestring(p_fv->value));
                }
                else if(!strcmp(type, "int")){
                    add_data(p_item, (void *) set_valueint(atoi(p_fv->value)));
                }
                else if(!strcmp(type, "float")){
                    add_data(p_item, (void *)set_valuefloat(atof(p_fv->value)));
                }
                else{
                    
                }
            }
            free(p_fv);
        }
    }
    
    return 0;
}

File_v *get_filevalue(char *f_string){
    char p_char = '\0';
    unsigned long colon_index = 0;
    p_char = f_string[colon_index];
    unsigned long fstr_len = strlen(f_string);
    while (p_char != ':' && colon_index+1 < fstr_len){
        colon_index++;
        p_char = f_string[colon_index];
    }
    File_v *p_fv = (File_v *)malloc(sizeof(File_v));
    p_fv->if_value = 0;
    strncpy(p_fv->head, f_string, colon_index);
    strncpy(p_fv->value, f_string+colon_index+1, fstr_len-colon_index);
    char c_value[8];
    strncpy(c_value, f_string, 5);
    if(!strcmp(c_value, "value")){
        p_fv->if_value = 1;
        char c_index[16];
        long len_head = strlen(p_fv->head);
        strncpy(c_index, p_fv->head+5, len_head-1);
        p_fv->inedx = atol(c_index);
    }
    return p_fv;
}

Define *find_defineByid(long id){
    List *p_list = defines_bin;
    Node *p_node = p_list->h_node;
    Define *p_define = NULL;
    Define *ps_define = NULL;
    while(p_node != NULL){
        p_define = (Define *) p_node->value;
        if (p_define->id == id){
            ps_define = p_define;
            break;
        }
        p_node = p_node->n_node;
    }
    return ps_define;
}

char * get_typeByindex(Define *p_define,int index){
    Node * p_type = get_locationByindex(p_define->type_list, index);
    return (char *) p_type->value;
}

int file_todefine(FILE *p_file){
    Define *p_define = NULL;
    char f_string[128];
    int read_todefine = 0;
    while(fscanf(p_file,"%s",f_string) != EOF){
        if (!strcmp(f_string, "!#define")){
            read_todefine = 1;
            p_define = build_define();
            continue;
            
        }
        if (!strcmp(f_string, "END")){
            read_todefine = 0;
            continue;
        }
        if (read_todefine == 1){
            File_v *p_fv =  get_filevalue(f_string);
            
            if (!strcmp(p_fv->head, "id")){
                p_define->id = atol(p_fv->value);
            }
            else if (!strcmp(p_fv->head, "define_num")){
                p_define->num = atoi(p_fv->value);
            }
            else if (p_fv->if_value == 1){
                DFile_v *p_dfv= get_definefilevalue(p_fv->value);
                add_define(p_define, p_dfv->message, p_dfv->type);
                free(p_dfv);
            }
            free(p_fv);
        }
    }
    return 0;
}

DFile_v *get_definefilevalue(char *fv_string){
    DFile_v *p_dfv = (DFile_v *)malloc(sizeof(DFile_v));
    unsigned long fvstr_len = strlen(fv_string);
    char p_char = '\0';
    unsigned long bar_index = 0;
    p_char = fv_string[bar_index];
    while (p_char != '/' && bar_index+1 < fvstr_len){
        bar_index++;
        p_char = fv_string[bar_index];
    }
    
    strncpy(p_dfv->message, fv_string, bar_index);
    strncpy(p_dfv->type,fv_string+bar_index+1 , fvstr_len-bar_index);
    
    return p_dfv;
}
