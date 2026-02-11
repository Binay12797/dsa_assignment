#include <stdio.h>

#define size 20

char stack[size];
int top =-1;

void push(char a)
{
    if(top == size-1)
    {
        printf("Stack full");
        return;
    }
    stack[++top]=a;
}

char pop()
{
    if(top == -1)
    {
        printf("Stack Empty");
        return;
    }
    return stack[top--];
}

int priority(char x)
{
    if(x=='(')
        return 0;
    if(x=='+' || x=='-')
        return 1;
    if(x=='*'|| x=='/')
        return 2;
    if(x=='^')
        return 3;
    return 0;
}

void infix_to_postfix(char infix[], char postfix[])
{
    for(int i=0; i!='\0'; i++)
    {
        if(isalnum(infix[i]))       //isalnum is a function which returns 1 if given char is either number or a symbol and give 0 when is an operation or any other special character
        {
            postfix[i]=infix[i];
        }
        //check if given character is a (

        else if(infix[i]=='(')
        {
            push(infix[i]);
        }
        
    }
}

int main()
{
    char infix[20];
    


    return 0;
}