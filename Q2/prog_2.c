#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define size 20


char stack[size];
int top = -1;

void push(char a) 
{
    if (top == size - 1) {
        printf("Stack full");
        return;
    }
    stack[++top] = a;
}

char pop() 
{
    if (top == -1) {
        printf("Stack Empty");
        return '\0';
    }
    return stack[top--];
}

int priority(char x) {
    if (x == '(') return 0;
    if (x == '+' || x == '-') return 1;
    if (x == '*' || x == '/') return 2;
    if (x == '^') return 3;
    return 0;
}

void infix_to_postfix(char infix[], char postfix[]) 
{
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {

        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(') {
            push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop(); // remove '('
        }
        else {
            while (top != -1 && stack[top] != '(' &&
                   priority(infix[i]) <= priority(stack[top])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
    }

    while (top != -1) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0';
}

//stack for evaluation

int eval_stack[size];
int eval_top = -1;

void eval_push(int val)
{
    if (eval_top == size - 1) {
        printf("Evaluation Stack full\n");
        return;
    }
    eval_stack[++eval_top] = val;
}

int eval_pop() 
{
    if (eval_top == -1) {
        printf("Evauationl Stack Empty\n");
        return -1;
    }
    return eval_stack[eval_top--];
}

//to evaluate postfix
int evaluate_postfix(char postfix[]) 
{
    for (int i = 0; postfix[i] != '\0'; i++) {

        // if digit, convert char to int and push
        if (isdigit(postfix[i])) {
            eval_push(postfix[i] - '0');
        }

    
        else {
            int b = eval_pop(); 
            int a = eval_pop(); 
            int result;

            switch (postfix[i]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/':
                    if (b == 0) {
                        printf("Error: Division by zero\n");
                        return -1;
                    }
                    result = a / b;
                    break;
                case '^': result = (int)pow(a, b); break;
                default:
                    printf("Unknown operator: %c\n", postfix[i]);
                    return -1;
            }

            eval_push(result);
        }
    }

    return eval_pop(); 
}



int main() 
{
    char infix[size];
    char postfix[size];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infix_to_postfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    printf("Evaluated result: %d\n", evaluate_postfix(postfix));

    return 0;
}