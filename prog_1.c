#include <stdio.h>
#include <conio.h>
#include <stdbool.h>

#define max_size 30

char stack[max_size];
int top=-1;

//push function defination
void push(char a)
{
    if(top == max_size -1)
        printf("Stack Overflow.");
    else
        top++;
        stack[top]=a;
}

//pop funcion defination
char pop()
{
    if(top == -1)
        printf("stack is empty.");
    else
        return stack[top--]; // top must be reduced after pop as an element is removed
}

bool pair(char open, char close)
{
    if (open=='(' && close==')')
        return true;
    else if (open=='{' && close=='}')
        return true;
    else if (open=='[' && close==']')
        return true;
    else
        return false;

}

//checks if expression has correct paranthesis or not
void check( char exp[])
{
    for(int i = 0 ; exp[i]!='\0'; i++)
    {
        char c = exp[i];

        if (c =='(' || c=='{' || c == '[')
        {
            push(c);
        }
        
        else if(c ==')' || c=='}' || c == ']')
        {
            char open = pop();
            if( !pair(open,c)  || open =='\0') //when paranthesis mismatch
            {
                printf("Given mathematical expression dosenot have balanced number of parentheses");
                return;
            }
        }
    }

    printf("Given mathematical expression has balanced number of parentheses");
    return;

}

int main()
{
    char exp[30];
    printf("Give the mathematical operation:");
    scanf("%s",exp);

    check(exp);

    return 0;
}