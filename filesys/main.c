
#include "Support.h"


int main(int argc, char *argv[]){
    Node *nl[50];
    List *pl = build_list();
    for(int i = 0; i < 50; i++){
        nl[i] = build_node();
        nl[i]->value = (void *)set_valueint(i);
        add_node(pl, nl[i]);
    }
    
    Node *p_node = get_locationByindex(pl, 5);
    free_list(pl);
    return 0;
}


