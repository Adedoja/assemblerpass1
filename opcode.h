#ifndef OPCODE_H
#define OPCODE_H

struct opcode {
        char mnemonic[7];
        int Format;
};

extern struct opcode directive[];
extern int DirectiveLength;
extern long Convert(const char *operand,int base , int lineNumber, const char*opcode);
int checkForFormat(char *opcode);
void convertToUpper(char *word);

#endif
