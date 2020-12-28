#include <menu_kubra.h>


void list(main_menu *node){

printf("IKONX\n");
while(node!=NULL){

        printf("%d ",node->id);
        printf("%s\n\n",node->menu_name);
        while(node->sub!=NULL){
            printf("     %d ",node->sub->sub_id);
            printf("      %s\n\n",node->sub->sub_name);
            node->sub = node->sub->next;

        while(node->sub->sub_sub != NULL){
          printf("         %d ",node->sub->sub_sub->sub_sub_id);
            printf("         %s\n\n",node -> sub ->sub_sub ->sub_sub_name);
                node->sub->sub_sub = node->sub->sub_sub->next;

            }
            node->sub = node->sub->next;
        }
        node = node->next;
    }

}

main_menu *add_menu_item(main_menu * r){

//////////////////////////////ADRESSING//////////////////////////////////////////
            if(r==NULL){
                 r = (main_menu*)malloc(sizeof(main_menu));
                 r->id = 100;
                 r->menu_name = "ADRESSING";
            }


            main_menu * root = (main_menu*)malloc(sizeof(main_menu));
            r->next = root;
            root->sub = (sub_menu*)malloc(sizeof(sub_menu));
            root->sub->sub_id =110;
            root->sub->sub_name = " START ADDR: ###\0";
            root->sub->sub_sub = NULL;
            root->sub->next = (sub_menu*)malloc(sizeof(sub_menu));
            root->sub = root->sub->next;
            root->sub->sub_id = 120;
            root->sub->sub_sub = NULL;
            root->sub->sub_name = " MODE    RGBW\0";
            root->sub->next = (sub_menu*)malloc(sizeof(sub_menu));
            root->sub = root->sub->next;
            root->sub->sub_id = 130;
            root->sub->sub_name = "  WRITE ADDRESS\0";
            root->sub->sub_sub = NULL;
            root->sub->next=NULL;

/////////////////////////////TEST MODE/////////////////////////////////////////



            root->next=(main_menu*)malloc(sizeof(main_menu));
            root = root->next;
            root->menu_name = "TEST MODE";
            root->id = 200;
            root->sub = (sub_menu*)malloc(sizeof(sub_menu));


            root->sub->sub_id = 210;
            root->sub->sub_name = " ANIMATION \0";

            root->sub->sub_sub = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));

            root->sub->sub_sub->sub_sub_id = 211;
            root->sub->sub_sub->sub_sub_name = " ANIMATION:  \0";
            root->sub->sub_sub->next = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));
            root->sub->sub_sub = root->sub->sub_sub->next;

            root->sub->sub_sub->sub_sub_id = 212;
            root->sub->sub_sub->sub_sub_name = " START \0";

///////////////////////////////////////////////////////////////////////////////
            root->sub->next = (sub_menu*)malloc(sizeof(sub_menu));
            root->sub = root->sub->next;
            root->sub->sub_id = 220;
            root->sub->sub_name = " CHASER CHANNEL\0";

            root->sub->sub_sub = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));

            root->sub->sub_sub->sub_sub_id = 221;
            root->sub->sub_sub->sub_sub_name = " CHASER CH\0";
            root->sub->sub_sub->next = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));
            root->sub->sub_sub = root->sub->sub_sub->next;

            root->sub->sub_sub->sub_sub_id = 222;
            root->sub->sub_sub->sub_sub_name = " FIRST CHANNEL:\0";
            root->sub->sub_sub->next = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));

            root->sub->sub_sub = root->sub->sub_sub->next;

            root->sub->sub_sub->sub_sub_id = 223;
            root->sub->sub_sub->sub_sub_name = " LAST CHANNEL:\0";

            root->sub->sub_sub->next = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));

            root->sub->sub_sub = root->sub->sub_sub->next;

            root->sub->sub_sub->sub_sub_id = 224;
            root->sub->sub_sub->sub_sub_name = " DELAY: ###x10ms\0";

             root->sub->sub_sub->next = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));

            root->sub->sub_sub = root->sub->sub_sub->next;

            root->sub->sub_sub->sub_sub_id = 225;
            root->sub->sub_sub->sub_sub_name = " START\0";
////////////////////////////////////////////////////////////////////////////////////
            root->sub->next = (sub_menu*)malloc(sizeof(sub_menu));
            root->sub = root->sub->next;
            root->sub->sub_id = 230;
            root->sub->sub_name = " UNITARY CONTROL \0";
            root->sub->next = (sub_menu*)malloc(sizeof(sub_menu));
            root->sub = root->sub->next;
            root->sub->sub_sub = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));

            root->sub->sub_sub->sub_sub_id = 231;
            root->sub->sub_sub->sub_sub_name = " UNITART CONTR\0";
            root->sub->sub_sub->next = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));
            root->sub->sub_sub = root->sub->sub_sub->next;

            root->sub->sub_sub->sub_sub_id = 232;
            root->sub->sub_sub->sub_sub_name = " CHANNEL:\0";
            root->sub->sub_sub->next = (sub_sub_menu*)malloc(sizeof(sub_sub_menu));

            root->sub->sub_sub = root->sub->sub_sub->next;

            root->sub->sub_sub->sub_sub_id = 233;
            root->sub->sub_sub->sub_sub_name = " VALUE:\0";

           ///////////////////////////////ABOUT////////////////////////////////
            root->next=(main_menu*)malloc(sizeof(main_menu));
            root = root->next;
            root->menu_name = "ABOUT";
            root->id = 300;
            root->sub = (sub_menu*)malloc(sizeof(sub_menu));


            root->sub->sub_id = 310;
            root->sub->sub_name = " ABOUT \0";

           root->next = NULL;

return r;

}


//int main(void){
//
//    main_menu * menu_root;
//    main_menu * result;
//    result = add_menu_item(menu_root);
//    list(menu_root);
//
//return 0;
//
//
//}


