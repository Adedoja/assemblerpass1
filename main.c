#include "headers.h"
#include "opcode.h"
int main(int argc, char *argv[]) {
    int Location_Counter = 0;
    if (argc != 2) {
        printf("ERROR: USAGE is %s <filename>\n", argv[0]);
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error: %s cannot open file\n", argv[1]);
        return -1;
    }

    char line[1024];
    int lineNumber = 0;
    SYMTAB MySymbolTable = NULL;

    while (fgets(line, sizeof(line), fp) != NULL) {
        lineNumber++;

        if (line[0] == '#' || line[0] == '\n') {
            if (line[0] == '\n') {
                printf("ASSEMBLY ERROR:\n%s\nLine %d: Blank line detected\n", line, lineNumber);
                fclose(fp);
                Destroy(MySymbolTable);
                return -1;
            }
            continue;
        }

        char *token_array[4] = {NULL};
        char delimiter[] = " \t\n\r";
        int k = 0;
        char *token = strtok(line, delimiter);
        while (token != NULL && k < 3) {
            token_array[k] = token;
            k++;
            token = strtok(NULL, delimiter);
        }

        char label[20] = {0};
        char opcode[20] = {0};
        char operand[20] = {0};
switch (k){
case 1:
strcpy(opcode, token_array[0]);
break;


case 2:
strcpy(opcode, token_array[0]);
strcpy(operand, token_array[1]);
label[0] = '\0';
break;

case 3:
 strcpy(label, token_array[0]);
 strcpy(opcode, token_array[1]);
 strcpy(operand, token_array[2]);
 break;
default:
 printf("ASSEMBLY ERROR:\n%s\nLine %d: Invalid line format\n", line, lineNumber);
            fclose(fp);
            Destroy(MySymbolTable);
            return -1;
        }

        convertToUpper(opcode);

        if (strcmp(opcode, "START") == 0) {
            if (operand[0] == '\0') {
                printf("ASSEMBLY ERROR:\n%s\nLine %d: START missing address\n", line, lineNumber);
                fclose(fp);
                Destroy(MySymbolTable);
                return -1;
            }
                  long convert= Convert(operand, 16, lineNumber, "START");
                  if(convert >= 32768 ){
                    printf("ASSEMBLY ERROR:\n%s\nLine %d:No room left in SIC memory. '%s'\n", line, lineNumber, label);
                    fclose(fp);
                    Destroy(MySymbolTable);
                    return -1;
                     }
            Location_Counter = convert;
        } else {

             if (label[0] != '\0' && isalpha(label[0])) {
              int j;
               if(strlen(label)>6){
                 printf("ASSEMBLY ERROR:\n%s\nLine %d:Invalid stringn length '%s'\n", line, lineNumber, label);
                    fclose(fp);
                    Destroy(MySymbolTable);
                    return -1;
               }
               for(j=0; label[j]; j++){
                 if(!isalnum(label[j])){
               printf("ASSEMBLY ERROR:\n%s\nLine %d:Invalid string '%s'\n", line, lineNumber, label);
                    fclose(fp);
                    Destroy(MySymbolTable);
                    return -1;
               }

              }


                if (SymbolExists(MySymbolTable, label)) {
                    printf("ASSEMBLY ERROR:\n%s\nLine %d: Duplicate symbol '%s'\n", line, lineNumber, label);
                    fclose(fp);
                    Destroy(MySymbolTable);
                    return -1;
               }
               MySymbolTable = InsertSymbol(MySymbolTable, label, Location_Counter, lineNumber);
}


            if (strcmp(opcode, "WORD") == 0) {
                    long opcode_convert= Convert(operand, 16, lineNumber, "WORD");
                  if(opcode_convert < -8388608 || opcode_convert > 16777215 ){
                    printf("ASSEMBLY ERROR:\n%s\nLine %d: WORD Constant Exceeds 24 bit limitation '%s'\n", line, lineNumber, label);
                    fclose(fp);
                    Destroy(MySymbolTable);
                    return -1;
                     }

             Location_Counter += 3;
            }
         else if (strcmp(opcode, "RESW") == 0) {

                long value= Convert(operand, 10, lineNumber, "RESW");
                 Location_Counter += 3 * value;
}
         else if (strcmp(opcode, "RESB") == 0) {
               long value= Convert(operand, 10, lineNumber, "RESB");
                 Location_Counter += value;
            }


           else if (strcmp(opcode, "BYTE") == 0) {
if (operand[0] != 'C' && operand[0] != 'X') {
printf("ASSEMBLY ERROR:\n%s\nLine %d: Invalid BYTE constant\n", line, lineNumber);
fclose(fp);
Destroy(MySymbolTable);
return -1;
}


if (operand[1] != '\'') {
    printf("ASSEMBLY ERROR:\n%s\nLine %d: Invalid BYTE constant missing quotes\n", line, lineNumber);
    fclose(fp);
    Destroy(MySymbolTable);
    return -1;
}

int i = 2;
int counter = 0;
if (operand[0]=='C'){
while (operand[i] != '\'' && operand[i] != '\0') {
i++;
counter ++;
}
}
else{
while (operand[i] != '\'' && operand[i] != '\0') {

    if ((operand[i] >= '0' && operand[i] <= '9') ||
        (operand[i] >= 'a' && operand[i] <= 'f') ||
        (operand[i] >= 'A' && operand[i] <= 'F')) {
        i++;
        counter++;
    } else {
        printf("ASSEMBLY ERROR:\n%s\nLine %d: Invalid hex digit found\n", line, lineNumber);
        fclose(fp);
        Destroy(MySymbolTable);
        return -1;
    }
}



if ((counter % 2) != 0 && operand[0] == 'X') {
    printf("ASSEMBLY ERROR:\n%s\nLine %d: Uneven number of hex digits in BYTE constant\n", line, lineNumber);
    fclose(fp);
    Destroy(MySymbolTable);
    return -1;
}
}
int total_bytes = counter / 2;

if (operand[0] == 'C') {
    Location_Counter += counter;
} else if (operand[0] == 'X') {
    Location_Counter += total_bytes;
} else {
    printf("ASSEMBLY ERROR:\n%s\nLine %d: Unrecognized BYTE format\n", line, lineNumber);
    fclose(fp);
    Destroy(MySymbolTable);
    return -1;
}

}


          else if (strcmp(opcode, "END") == 0) {
                break;
            }
         else {
                int format = checkForFormat(opcode);
                if (format == -1) {
                    printf("ASSEMBLY ERROR:\n%s\nLine %d: Invalid opcode '%s'\n", line, lineNumber, opcode);
                    fclose(fp);
                    Destroy(MySymbolTable);
                    return -1;
                }
                Location_Counter += format;
            }
        }
    }

    fclose(fp);

   PrintSymbols(MySymbolTable);
    Destroy(MySymbolTable);

    return 0;
}
