# Q2. Write a program to convert an infix mathematical expression to postfix and evaluate it.

### (a) Defining Data Structures:
```c
#define size 20

char stack[size];   // char stack for infix to postfix conversion
int top = -1;       // top of char stack

int eval_stack[size]; // int stack for postfix evaluation
int eval_top = -1;    // top of int stack
```

**Explanation:**
* `#define size 20` initializes the maximum size of both stacks
* `char stack[size]` is a character array used to hold operators and parentheses during infix to postfix conversion
* `int eval_stack[size]` is an integer array used to hold operand values during postfix evaluation
* `top = -1` and `eval_top = -1` initialize both stack tops to `-1`, indicating empty stacks

---

### (b) Functions:

* `push(char a)`: Pushes a character (operator or parenthesis) onto the char stack. Prints `"Stack full"` if the stack has reached max capacity.
* `pop()`: Removes and returns the top character from the char stack. Returns `'\0'` if the stack is empty.
* `priority(char x)`: Returns the precedence level of an operator:
  * `(` → 0 (lowest, never popped over operators)
  * `+`, `-` → 1
  * `*`, `/` → 2
  * `^` → 3 (highest)
* `infix_to_postfix(char infix[], char postfix[])`: Converts the infix expression to postfix. Handles multi-digit numbers by copying consecutive digits and separating tokens with a space character.
* `eval_push(int val)`: Pushes an integer operand onto the integer evaluation stack.
* `eval_pop()`: Removes and returns the top integer from the evaluation stack.
* `evaluate_postfix(char postfix[])`: Scans the postfix string token by token. Pushes numbers onto the eval stack; on encountering an operator, pops two operands, applies the operation, and pushes the result back.

---

### (c) Main Method Organization

The `main()` function serves as the interface:
1. **Input**: Captures an infix expression string from the user using `fgets()` and strips the trailing newline.
2. **Conversion**: Passes the infix string to `infix_to_postfix()`, which fills the `postfix[]` array with the space-separated postfix expression.
3. **Evaluation**: Passes the postfix string to `evaluate_postfix()`, which computes and returns the integer result.
4. **Output**: Prints both the postfix expression and the final evaluated result.

---

### (d) Key Logic — Infix to Postfix

The conversion follows the **Shunting Yard Algorithm**:

| Character Type | Action |
| :--- | :--- |
| Digit/Operand | Copy all consecutive digits to postfix, append a space |
| `(` | Push onto stack |
| `)` | Pop and output until `(` is found, then discard `(` |
| Operator | Pop operators of greater or equal priority, then push current operator |
| End of string | Pop all remaining operators from stack to postfix |

The space separator between tokens is critical — it allows multi-digit numbers like `23` to be distinguished from two separate numbers `2` and `3`.

---

### (e) Key Logic — Postfix Evaluation

The evaluator builds multi-digit numbers using the **multiply-by-10 method**:

```c
int num = 0;
while (isdigit(postfix[i])) 
{
    num = num * 10 + (postfix[i] - '0');
    i++;
}
```

For operators, two operands are popped — `b` first (right operand), then `a` (left operand) — and the result is pushed back:

```c
int b = eval_pop();  // right operand
int a = eval_pop();  // left operand
result = a OP b;
eval_push(result);
```

> **Note:** The order of popping matters for non-commutative operations like `-`, `/`, and `^`.

---

### (f) Sample Output / Test Cases

| Expression | Postfix | Result | Reason |
| :--- | :--- | :--- | :--- |
| `3+5*2` | `3 5 2 * +` | **13** | `*` has higher priority than `+`, so `5*2=10` first, then `3+10=13` |

```text
Enter infix expression: 3+5*2
Postfix expression : 3 5 2 * +
Evaluated result   : 13
```