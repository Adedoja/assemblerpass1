#include "headers.h"
void PrintSymbols(SYMTAB table) {
    SYMTAB temp = table;
    printf("\nPrinting Symbol Table\n");
    if (table == NULL) {
        printf("This table is null\n");
        return;
    }

    while(temp != NULL) {
        printf("%s\t%x\n", temp->name, temp->address);
        temp = temp->next;
    }
}
