#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BUFSIZE 32 

enum Instruction {ACC, JMP, NOP};

typedef struct inst {
    unsigned int type;
    int val;
} inst;

int main(void)
{
    long accumulator = 0;

    inst **prog = malloc(sizeof(inst*));
    bool *has_exec = NULL;

    char buffer[BUFSIZE] = {0};
    unsigned int lines = 0;

    // Reads instructions into memory
    while (fgets(buffer, BUFSIZE, stdin) != NULL) {
        inst **temp = realloc(prog, sizeof(inst*) * (lines + 1));
        if (temp == NULL) exit (1);
        prog = temp;
        inst *new_inst = malloc(sizeof(inst));
        char *n = malloc(BUFSIZE);
        int d = 0;
        
        if (sscanf(buffer, "%s +%d\n", n, &d) != 2) {
            sscanf(buffer, "%s %d\n", n, &d);
        }
        if (strcmp(n, "acc") == 0)
            new_inst->type = ACC;
        else if (strcmp(n, "jmp") == 0)
            new_inst->type = JMP;
        else
            new_inst->type = NOP;

        new_inst->val = d; 

        prog[lines] = new_inst;
        free(n);
        lines++;
    }
    has_exec = calloc(lines, sizeof(bool));
    
    // 'i' acts as the instruction pointer here
    for (int i = 0; i < lines;) {
        if (has_exec[i])
            break;
        has_exec[i] = true;
        switch (prog[i]->type) {
            case JMP:
                i += prog[i]->val;    
                //printf("Jumping to instruction %d\n", i);
                break;
            case ACC:
                accumulator += prog[i]->val;
                //printf("Accumulator is now: %ld\n", accumulator);
            case NOP:
            default:
                i++;
                break;
        }
    }
    printf("(Part 1) The accumulator is at: %ld\n", accumulator);

    for (int i = 0; i < lines; i++) {
        free(prog[i]);
    }
    free(prog);
    free(has_exec);

    return 0;
}
