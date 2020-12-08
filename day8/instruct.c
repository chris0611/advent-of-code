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

void swap_instruction(inst *i, unsigned int type)
{
    i->type = type; 
}

void swap_jmp_nop(inst *i)
{
    if (i->type == NOP)
        swap_instruction(i, JMP);
    else
        swap_instruction(i, NOP);
}

void print_instruction(inst *i)
{
    switch(i->type) {
        case ACC:
            printf("acc ");
            break;
        case JMP:
            printf("jmp ");
            break;
        case NOP:
            printf("nop ");
            break;
        default:
            printf("Invalid Instruction\n");
            return; 
    }
    if (i->val < 0) {
        printf("%d\n", i->val);
    } else {
        printf("+%d\n", i->val);
    }
}


long execute_program(inst **prog, int length, int *last_exec, bool part1)
{
    long accumulator = 0;
    bool *has_exec = calloc(length, sizeof(bool));

    if (part1 && (last_exec == NULL)) {
        // 'i' acts as the instruction pointer here
        int i;
        for (i = 0; i < length;) {
            if (has_exec[i])
                break;
            has_exec[i] = true;
            switch (prog[i]->type) {
                case JMP:
                    i += prog[i]->val;    
                    break;
                case ACC:
                    accumulator += prog[i]->val;
                case NOP:
                default:
                    i++;
                    break;
            }
        }
        free(has_exec);
        return accumulator;
    } else if (part1 && (last_exec != NULL)) {
        int i;
        int max = 0;
        for (i = 0; i < length;) {
            if (has_exec[i])
                break;
            if (i > max) max = i;
            has_exec[i] = true;
            switch (prog[i]->type) {
                case JMP:
                    i += prog[i]->val;    
                    break;
                case ACC:
                    accumulator += prog[i]->val;
                case NOP:
                default:
                    i++;
                    break;
            }
        }
        *last_exec = max;
        free(has_exec);
        return accumulator;
        
    } else {
        // TODO: debug
        int last_index = 0;
        int i;
        for (i = 0; i < length;) {
            if (i > last_index)
                last_index = i;
            if (has_exec[i])
                break;
            has_exec[i] = true;
            switch (prog[i]->type) {
                case JMP:
                    i += prog[i]->val;    
                    break;
                case ACC:
                    accumulator += prog[i]->val;
                case NOP:
                default:
                    i++;
                    break;
            }
        } 

        for (i = 0; i <= last_index; i++) {
            if (has_exec[i] && (prog[i]->type != ACC)) {
                int test = 0;
                swap_jmp_nop(prog[i]);
                execute_program(prog, length, &test, true);
                if (test == length-1) break;
                swap_jmp_nop(prog[i]);
            }
        }

        for (i = 0; i < length; i++) {
            has_exec[i] = false;
        }
    
        // Run program with changed instruction
        accumulator = 0;
        for (i = 0; i < length;) {
            if (has_exec[i])
                break;
            has_exec[i] = true;
            switch (prog[i]->type) {
                case JMP:
                    i += prog[i]->val;    
                    break;
                case ACC:
                    accumulator += prog[i]->val;
                case NOP:
                default:
                    i++;
                    break;
            }
        } 

        free(has_exec);
        return accumulator;
    }
}

int main(void)
{
    inst **prog = malloc(sizeof(inst*));

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
    
    printf("(Part 1) The accumulator is at: %ld\n", execute_program(prog, lines, NULL, true));
    printf("(Part 2) The fixed program's accumulator is at: %ld\n", execute_program(prog, lines, NULL, false));

    for (int i = 0; i < lines; i++) {
        free(prog[i]);
    }
    free(prog);

    return 0;
}
