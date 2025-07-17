#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 20

// type of stack data defined as T

typedef int T;

// stack is based on the array

typedef struct Stack{

    T data[STACK_MAX_SIZE];
    size_t size; // number of elements in the stack

} Stack_T;

// adding an element to the peek of the stack

T push(Stack_T *stack, T value){

    if (stack -> size < STACK_MAX_SIZE){           // owerflow check
        stack -> data[stack -> size++] = value;
        return value;}
    else
        return 0;
}

// popping the last element added

T pop(Stack_T *stack){

    if (stack -> size > 0){  
        stack -> size--;
        return stack -> data[stack -> size];
    }
    else{
        return 0;
    }

}

// returns the peek of stack

T peek (Stack_T *stack){

    if (stack -> size > 0){
        return stack -> data[stack -> size - 1];
    }
    else
        return 0;
}

// returns the pointer of the created stack
// should be assigned to a Stack_T* variable 

Stack_T* create_stack(){

    Stack_T *stack = (Stack_T*)malloc(sizeof(Stack_T));
    if (stack != NULL)
        stack -> size = 0;
    return stack;
}

int main (){

    Stack_T* stack = create_stack();

    push(stack, 5);
    pop(stack);

    for (int i = 0; i < stack -> size; i ++){
        printf("%d \n", stack -> data[i]);
    }

    push(stack, 3);
    printf("%d", peek(stack));

    pop(stack);
    
    for (int i = 0; i < stack -> size; i ++){
        printf("%d \n", stack -> data[i]);
    }

    return 0;
}


