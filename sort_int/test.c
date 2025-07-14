#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEN 20

void sort_int(int *ptr);

int main() {
    
    int arr[LEN + 1];

    srand(time(0));

    // filling an array
    for (int i = 0; i < LEN; i ++){
        arr[i] = rand() % 100; // sorting LEN numbers from 0 to 100
    }

    for (int i = 0; i < LEN; i ++){
        printf("%d ", arr[i]);
    }
    printf("\n");

    sort_int(arr);

    for (int i = 0; i < LEN; i ++){
        printf("%d ", arr[i]);
    }
    
    
}

void sort_int(int *ptr){
    
    int min, temp = 0;
    
    for (int j = 0; j < LEN; j ++){
        
        min = *(ptr + j);

        for (int i = j; i < LEN; i++){

            if (*(ptr + i) < min){
                min = *(ptr + i);
                temp = i;
            }
        }

        *(ptr + temp) = *(ptr + j);
        *(ptr + j) = min;

    }

}