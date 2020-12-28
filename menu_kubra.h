/*
 * men_kubra.h
 *
 *  Created on: 23 Ara 2020
 *      Author: Dell
 */

#ifndef INC_MENU_KUBRA_H_
#define INC_MENU_KUBRA_H_


#include <stdio.h>
#include <stdlib.h>


typedef struct sub_sub_menu{

    int sub_sub_id;
    char *sub_sub_name;
    struct sub_sub_menu * next;

}sub_sub_menu;


typedef struct sub_menu{

    int sub_id;
    char *sub_name;
    struct sub_menu * next;
    sub_sub_menu *sub_sub;

}sub_menu;


typedef struct main_menu{

    int id;
    char *menu_name;
    struct main_menu *next;

    sub_menu * sub;

}main_menu;

main_menu *add_menu_item(main_menu * r);

void list(main_menu *node);






#endif /* INC_MENU_KUBRA_H_ */
