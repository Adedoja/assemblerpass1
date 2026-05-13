#ifndef HEADERS_H
#define HEADERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct symbol_linked_list {
        char name[7];
        int address;
        int sourceline;
        struct symbol_linked_list *next;
};

typedef struct symbol_linked_list SYMBOL;
typedef SYMBOL *SYMTAB;

SYMTAB InsertSymbol( SYMTAB table, char name[7], int addr, int srcline );
void PrintSymbols( SYMTAB table );
void Destroy( SYMTAB table );
int SymbolExists( SYMTAB table, char name[7]);
int checkForFormat(char *opcode);
void convertToUpper(char *word);
long Convert(const char *operand,int base , int lineNumber, const char*opcode);
#endif
