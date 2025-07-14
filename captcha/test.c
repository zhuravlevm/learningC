#include <stdio.h>
#include <stdlib.h>

#define MPL 42
#define PLUS 43
#define COMMA 44
#define MINUS 45

int main() {
    
    printf("CAPTCHA\n" 
    "Solve it: ");

    unsigned int arg1, arg2, op;
    
    while (1){

        srand(time(0));

        arg1 = rand() % 10; arg2 = rand() % 10;

        op = 42 + rand() % 4;
        while (op == COMMA) 
            op = 42 + rand() % 4;
    
        printf("%d %c %d = ", arg1, op ,arg2);
        
        int user_ans, ans;

        switch (op){
            case MPL: ans = arg1 * arg2; break;
            case PLUS: ans = arg1 + arg2; break;
            case MINUS: ans = arg1 - arg2; break;
        }

        scanf("%d", &user_ans);

        if (user_ans == ans){
            printf("Good boy");
            break;
        }
        else{
            printf("Try again, robocop\n", ans, op);
        }
    }

}