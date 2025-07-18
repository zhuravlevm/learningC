#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 20
#define RESETER 8   // number of objects to avtomaticaly call gc


// object types that will be stored
typedef enum{
    INT,
    TWIN
} ObjectType;

typedef struct sObject{
    ObjectType type;
    unsigned char marked;

    struct sObject* next;  // linking objects

    union{
        int value;

        struct {
            struct sObject* head;
            struct sObject* tail;
        };
    };
} Object;

// creating virtual memory to store objects
// contains of stack that will store all the programm objects
typedef struct{
    Object* stack[STACK_MAX_SIZE];

    int stackSize;  

    Object* prevObject;

    int objectsNum, maxObjects;

}vm;

vm* createVM(){

    vm* VM = (vm*)malloc(sizeof(vm));
    VM -> stackSize = 0;
    VM -> prevObject = NULL;
    VM -> maxObjects = RESETER;
    VM -> objectsNum = 0;

    return VM;
}

// stack instruments

void push(vm* VM, Object* value){
    if (VM -> stackSize < STACK_MAX_SIZE) VM -> stack[VM -> stackSize++] = value;
}

Object* pop(vm* VM){
    if (VM -> stackSize > 0) return VM -> stack[--VM -> stackSize];
}

Object* new_object(vm* VM, ObjectType type){

    if (VM -> objectsNum == VM -> maxObjects) gc(VM);


    Object* object = (Object*)malloc(sizeof(Object));
    object -> type = type;
    object -> next = VM -> prevObject;
    VM -> prevObject = object;
    VM ->objectsNum++;
    return object;
}

void pushInt(vm* VM, int value){
    Object* object = new_object(VM, INT);
    object -> value = value;
    push(VM, object);
}


// tail and head are popped from stack
void pushTwin(vm* VM){
    Object* object = new_object(VM, TWIN);
    if (VM -> stackSize > 1){
        object -> tail = pop(VM);
        object -> head = pop(VM);
    }
    push(VM, object);
}

// mark and sweep

void mark(Object* object){
    object -> marked = 1;

    if (object -> type == TWIN){
        mark(object -> tail);
        mark(object -> head);
    }
}


// goes through the stack looking for the
// objects that are still in use              example: push(INT, 1) push(INT, 2) pushTwin() gc() --> objects [1] and [2] will be deleted
//                                            example: push(INT, 1) pop() --> [1] will be deleted
// delete means that the memory preserved for the object will be free
void markUsed(vm* VM){
    
    for (int i = 0; i < VM -> stackSize; i++){
        mark(VM -> stack[i]);
    }
}

// checking all the objects that are in the linked list
// if they are marked they are unmarked
// if they are not then they are deleted
// linked list consists of all the objects added to the memory since last gc()
// and stack consists of all the objects that are still in use so objects that are
// not in the stack but in the list are the objects to be deleted
void markNsweep(vm* VM){

    Object** object = &VM -> prevObject; 
    while (*object){
        if (!(*object) -> marked){
            Object* unreached = *object;
            *object = unreached -> next;
            free(unreached);
            VM -> objectsNum--;
        }
        else{
            (*object) -> marked = 0;
            object = &(*object) -> next; 
        }
    }
}

void gc(vm* VM){

    int elems_before = VM -> objectsNum;

    markUsed(VM);
    markNsweep(VM);

    printf("Objects deleted: %d, %d left\n", elems_before - VM -> objectsNum, VM -> objectsNum);
}

// cleaning all the memory
void freeVM(vm* VM){
    VM -> stackSize = 0;
    gc(VM);
    free(VM);
}

int main (int argc, const char** argv){

    return 0;

}