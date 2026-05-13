#include "headers.h"



void Destroy( SYMTAB table ){
         SYMTAB temp;

       while( table != NULL){
        temp = table;
       table = temp->next;
        free(temp);
        }
       printf("The Symbol table destroyed successfully. \n");
}
