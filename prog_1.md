# Q1.Write a program to check if any given mathematical expression has a balanced number of parentheses or not?

### (a)defining data structures:
```c
#define max_size 30    
char stack[max_size];   
int top = -1;
```

**Explanation:**
* `#define max_size 20` this initializes the size of the array
* `char stack[size]` sets a character array of defined size
* `top = -1` initializes the top of stack to be -1

### (b)Functions:
* `push(char x)`: push function is used to insert an item into the stack.
* `pop()`: pop function is used to remove an item from a stack.
* `check`: This function check if the opening parenthesis matches with the closing parenthesis.
* `pair(char open,char close)`: This function check if the opening parenthesis has its matching closing parenthesis and returns TRUE if the mathematical expression is balanced else FALSE.

### (c) Main Method Organization
The `main()` function serves as the interface:
1.  **Input**: It captures a string expression from the user and stores in `exp[]`;.
2.  **Processing**: It passes the string to `check`.
3.  **Output**: `check` return wether the expression is balanced or not

### (d) Sample Output / Test Cases

| Expression | Result | Reason |
| :--- | :--- | :--- |
| `a+(b-c)*(d` | **Not Balanced** | The `(` before `d` is never closed. |
| `m+[a-b*(c+d*{m)]` | **Not Balanced** | The `{` is followed by a `)` instead of a `}` (Mismatched). |
| `a+(b-c)` | **Balanced** | All opening brackets have corresponding closing brackets. |

```text
Enter the expression: a+(b-c)*(d
Given mathematical expression dosent have balanced number of parentheses

Enter the expression: m+[a-b*(c+d*{m)]
Given mathematical expression dosent have balanced number of parentheses

Enter the expression: a+(b-c)
Given mathematical expression has balanced number of parentheses
