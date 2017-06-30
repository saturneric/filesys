
#include "Support.h"
#include <time.h>


int main(int argc, char *argv[]){
    list_init();
    init_id();
    Define *p_define = build_define();
    add_define(p_define, "Name", "string");
    add_define(p_define, "Age", "int");
    add_define(p_define, "Power", "float");
    Table *p_table = build_table(p_define);
    Item *items[3];
    
    items[0] = build_item(p_define);
    add_data(items[0], set_valuestring("Tim"));
    add_data(items[0], set_valueint(23));
    add_data(items[0], set_valuefloat(100.0));
    add_item(p_table, items[0]);
    
    items[1] = build_item(p_define);
    add_data(items[1], set_valuestring("Pat"));
     add_data(items[1], set_valueint(33));
    add_data(items[1], set_valuefloat(120.0));
    add_item(p_table, items[1]);
    
    items[2] = build_item(p_define);
    add_data(items[2], set_valuestring("Tom"));
    add_data(items[2], set_valueint(43));
    add_data(items[2], set_valuefloat(130.0));
    add_item(p_table, items[2]);
    
    FILE *fp = fopen("table.data", "w");
    table_tofile(fp, p_table);
    fclose(fp);
    
    FILE *dfp = fopen("define.settings", "w");
    define_tofile(dfp, p_define);
    fclose(dfp);
    
    free_define(p_define);
    free_table(p_table);
    //list_delinit();
    
    return 0;
}


