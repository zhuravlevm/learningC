#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define CLOCK 1                         // 1s
#define MEMORY_CELLS 256
#define INSTRUCTIONS_NUMBER 3 
#define INSTRUCTIONS_LEN 80
int RAM[MEMORY_CELLS];        // 256 memory cells, cell with a 255 value is free 
char* instructionList[INSTRUCTIONS_NUMBER];

// illustrates the idea of pipelining instructions

typedef struct {
    int registers[8]; // 8 "registers", each stores 4 byte

    struct {
        ; 
    }ALU;

    struct {
        int programCounter;
        char* programAdressing;      // addres of an instruction that is being executed
        char instructionRegister[2]; // any instruction is codded by 2 bytes
        char status;                 // condition check (for branch instruction)
    }controlUnit;

}CPU;

CPU* start_session(){

    CPU *pc = (CPU*)malloc(sizeof(CPU));
    
    for (int i = 0; i < INSTRUCTIONS_NUMBER; i++){
        instructionList[i] = (char*)malloc(81);
    }

    pc -> controlUnit.programAdressing = instructionList[0];
    pc -> controlUnit.programCounter = 0;

    for (int i = 0; i < 256; i++){
        RAM[i] = 255;
    }
    
    return pc;
}

// ALLU

// takes pointers to "registers"
int add(CPU* PC, int* operand1, int* operand2, int* destination){
    
    if (operand1 - PC -> registers < 32 && operand1 - PC -> registers >= 0 && 
    operand2- PC -> registers < 32 && operand2 - PC -> registers >= 0 && 
        destination - PC -> registers < 32 && destination - PC -> registers >= 0){
            *destination = *operand1 + *operand2;
            return 0;
        }
    else
        return 1;  // means that input data is incorrect (operand1 or operand2 or destination are not in any register)
}

// instructions

// creating unsigned char object in RAM
int* create_int(CPU* PC, int value){

    int *free;
    // looking for empty slot
    for (int i = 0; i < MEMORY_CELLS; i++){
        if (RAM[i] == 255){
            RAM[i] = (int)value;
            free = RAM + i;
            return free;
        }
    }

    printf("No memory left\n");

}

// add 2 numbers from RAM
// takes pointers to RAM cells
int add_instruction(CPU* PC, int* operand1, int* operand2){

    PC -> registers[0] = *operand1;
    PC -> registers[1] = *operand2;

    add(PC, PC-> registers, PC -> registers + 1, PC -> registers + 2);

    return 0;

}

int decode_ins(CPU* PC, char* instruction){

    PC -> controlUnit.programAdressing = instructionList[PC -> controlUnit.programCounter++];

    // instruction type is being decoded by first 3 bytes
    // add: 1 mpl: branch:

    if (strncmp(instruction, "add", 3) == 0)
        return 1;

}

void execute_ins(CPU* PC, int instruction_code, char* instruction){

    // case addition 2 numbers

    if (instruction_code == 1){
        char counter = 4;
        int op1[6] = {0, 0, 0, 0, 0, 0}, op2[6] = {0, 0, 0, 0, 0, 0};
        int res1 = 0, res2 = 0;
        char flag = 0;

        // taking numbers from input string

        for (int i = 4, n_counter = 0; i < INSTRUCTIONS_LEN + 1; i++){

            if (*(instruction + i) == ' '){
                flag = 1;
                
                switch (n_counter)
                {
                case 1:
                    res1 = op1[0];
                    break;
                
                case 2:
                    res1 = op1[0] * 10 + op1[1];
                    break;
    
                case 3:
                    res1 = op1[0] * 100 + op1[1] * 10 + op1[2];
                    break;
                case 4:
                    res1 = op1[0] * 1000 + op1[1] * 100 + op1[2] * 10 + op1[3];
                    break;
                case 5:
                    res1 = op1[0] * 10000 + op1[1] * 1000 + op1[2] * 100 + op1[3] * 10 + op1[4];
                    break;
                case 6:
                    res1 = op1[0] * 100000 + op1[1] * 10000 + op1[2] * 1000 + op1[3] * 100 + op1[4] * 10 + op1[5];
                }
                n_counter = 0;
                continue;
                }
                
            if (*(instruction + i) == 10){
                switch (n_counter)
                {
                case 1:
                    res2 = op2[0];
                    break;
                
                case 2:
                    res2 = op2[0] * 10 + op2[1];
                    break;
    
                case 3:
                    res2 = op2[0] * 100 + op2[1] * 10 + op2[2];
                    break;
                case 4:
                    res2 = op2[0] * 1000 + op2[1] * 100 + op2[2] * 10 + op2[3];
                    break;
                case 5:
                    res2 = op2[0] * 10000 + op2[1] * 1000 + op2[2] * 100 + op2[3] * 10 + op2[4];
                    break;
                case 6:
                    res2 = op2[0] * 100000 + op2[1] * 10000 + op2[2] * 1000 + op2[3] * 100 + op2[4] * 10 + op2[5];
                }
                break;
                }

            if (!flag) op1[n_counter] = *(instruction + i) - 48;
            else op2[n_counter]= *(instruction + i) - 48;    
            
            n_counter++;
            }

            PC -> controlUnit.status = 1;
            add_instruction(PC, create_int(PC, res1), create_int(PC, res2));
    }
    
}

void write_ins(CPU* PC, int instruction_code){
    if (instruction_code == 1){
        printf("ALU's work result: %d\n", PC -> registers[2]);
    }
}



int main (int argc, const char** argv){


    CPU* pc = start_session(); 

    // fetching instructions separatly

    char instruction[INSTRUCTIONS_LEN + 1];

    int ins_counter = 0;
    while (ins_counter < INSTRUCTIONS_NUMBER){
        fgets(instruction, INSTRUCTIONS_LEN, stdin);
        strcpy(instructionList[ins_counter], instruction);
        ins_counter++;
    }

    // first instruction example
    // while first instruction is being executed the second one
    // is being decoded and so on

    if (INSTRUCTIONS_NUMBER > 0){
        printf("decoding %d instruction\n", pc -> controlUnit.programCounter + 1);
        int instruction1 = decode_ins(pc, pc -> controlUnit.programAdressing);
        sleep(CLOCK); // stops the whole program, just to show how it works
        printf("\nexecuting %d instruction\n", pc -> controlUnit.programCounter); 
        execute_ins(pc, instruction1, pc -> controlUnit.programAdressing);
    }

    int last_ins_code = pc -> controlUnit.status;

    while (pc ->controlUnit.programCounter < INSTRUCTIONS_NUMBER){
        printf("decoding %d instruction\n", pc -> controlUnit.programCounter + 1);
        int instruction_n = decode_ins(pc, pc ->controlUnit.programAdressing); 

        sleep(CLOCK);

        printf("\nwriting %d instruction\n", pc -> controlUnit.programCounter - 1);
        write_ins(pc, last_ins_code);
        
        printf("executing %d instruction\n", pc -> controlUnit.programCounter);
        execute_ins(pc, instruction_n, pc -> controlUnit.programAdressing);
        last_ins_code = instruction_n;
    }

    printf("writing %d instruction\n", pc -> controlUnit.programCounter);    
    write_ins(pc, last_ins_code);

    return 0;

}