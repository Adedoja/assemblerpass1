#include "headers.h"
#include "opcode.h"

struct opcode directive[]= {{"ADD",3}, {"ADDF",3}, {"ADDR",2}, {"AND", 3},
        {"CLEAR", 2}, {"COMP",3}, {"COMPF", 3}, {"COMPR", 2},
        {"DIV",3}, {"DIVF",3}, {"FIX", 1}, {"FLOAT", 1}, {"HIO",1},
        {"J",3},{"JET",3},{"JEQ",3}, {"JGT",3}, {"JLT",3}, {"JSUB", 3},
        {"LDA", 3}, {"LDB",3}, {"LDCH", 3}, {"LDF", 3}, {"LDL", 3},
        {"LDS", 3}, {"LDT", 3}, {"LDX", 3}, {"LPS", 3},
        {"MUL", 3}, {"MULF", 3}, {"MULR", 2}, {"OR", 3}, {"RD", 3},
        {"RMO", 2}, {"RSUB", 3}, {"SHIFTL", 2},
        {"SHIFTR", 2}, {"SSK",3}, {"STA",3}, {"STB",3},
        {"STCH",3}, {"STF",3}, {"STI",3}, {"STL",3},
        {"STS",3}, {"STSW",3}, {"STT",3}, {"STX",3},
        {"SUB", 3}, {"SUBF", 3}, {"SUBFR",2}, {"SVC",2},
        {"TD",3}, {"TIO",1}, {"TIX",3}, {"TIXR",2},{"WD",3}
};


int DirectiveLength = sizeof(directive)/ sizeof(directive[0]);

int checkForFormat(char *opcode) {

        for (int j=0; j<DirectiveLength; j++) {
                if (strcmp(opcode, directive[j].mnemonic) ==0) {
                        return directive[j].Format;
                }
        }
        return -1;
}

void convertToUpper(char *word) {
        for (int i=0; word[i] != '\0'; i++) {
                word[i]= toupper((unsigned char)word[i]);
        }
}

long Convert(const char *operand,int base , int lineNumber, const char*opcode){
char *ptr;
long convert_base=strtol(operand,&ptr,base);
if(*ptr != '\0'){
printf("ASSEMBLY ERROR: Line %d: Invalid  constant '%s'\n", lineNumber, opcode, operand);
        exit(-1);
    }
    return convert_base;
}
