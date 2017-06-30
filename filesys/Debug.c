//
//  Debug.c
//  filesys
//
//  Created by Saturneric on 2017/6/25.
//  Copyright © 2017年 Bakantu Eric. All rights reserved.
//

#include "Debug.h"
#include "ID.h"

int debug_printf(DEBUG_CREATE_INFO *p_deg_ifo){
    if (p_deg_ifo->avaliable == 0) return -1;
    if (p_deg_ifo->safe == 0) return -1;
    if(p_deg_ifo->type == -2){
        printf("!!");
    }
    if(p_deg_ifo->type == 0){
        printf("?");
    }
    if(p_deg_ifo->type == -1){
        printf("!");
    }
    printf("Debug Message{ \n");
    printf("    message: %s\n",p_deg_ifo->message);
    if(p_deg_ifo->type > 0){
        p_deg_ifo->showvar = 1;
    }
    if(p_deg_ifo->showvar){
        if(p_deg_ifo->variable == NULL){
            printf("DEBUG_PRINTF Error : unable to get the variable\n}\n");
            return -1;
        }
    }
    if(p_deg_ifo->type == STRING){
        printf("    ------------\n    type: variable info(string)");
        if (p_deg_ifo->showvar)
            printf("%s",(char *)(p_deg_ifo->variable));
    }
    else if(p_deg_ifo->type == INT){
        printf("    ------------\n    type: variable info(integer)");
        if (p_deg_ifo->showvar)
            printf("%d",*(int *)(p_deg_ifo->variable));
    }
    else if(p_deg_ifo->type == FLOAT){
        printf("    ------------\n    type: variable info(float)");
        if (p_deg_ifo->showvar)
            printf("%f",*(double *)(p_deg_ifo->variable));
    }
    else if (p_deg_ifo->type == WARNING){
        printf("    ------------\n    type: warning");
        if (p_deg_ifo->showvar)
            printf("\n    location: %p",p_deg_ifo->variable);
    }
    else if (p_deg_ifo->type == ERROR){
        printf("    ------------\n    type: error");
        if (p_deg_ifo->showvar)
            printf("\n    location: %p",p_deg_ifo->variable);
    }
    else if (p_deg_ifo->type == IMPORTANT_ERROR){
        printf("   ------------\n   type: improtant error");
        if (p_deg_ifo->showvar)
            printf("\n    location: %p",p_deg_ifo->variable);
    }
    else printf("DEBUG_PRINTF Error : unable to get the type of the variable");
    printf("\n}\n");
    free(p_deg_ifo);
    return 0;
}

DEBUG_CREATE_INFO *get_degcrtifo(void){
    DEBUG_CREATE_INFO *p_deg_crt_ifo = NULL;
    p_deg_crt_ifo = (DEBUG_CREATE_INFO *) malloc(sizeof(DEBUG_CREATE_INFO));
    if (p_deg_crt_ifo == NULL) return NULL;
    p_deg_crt_ifo->type = 0;
    p_deg_crt_ifo->avaliable = 1;
    p_deg_crt_ifo->showvar = 0;
    p_deg_crt_ifo->variable = NULL;
    p_deg_crt_ifo->safe = 1;
    p_deg_crt_ifo->id = get_id();
    
    return p_deg_crt_ifo;
}

