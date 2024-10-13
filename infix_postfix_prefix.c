#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

// Stack structure for characters
struct Stack {
    int top;
    char arr[MAX];
};

// Stack structure for integers (used for evaluation)
struct IntStack {
    int top;
    int arr[MAX];
};

// Push operation for character stack
void push(struct Stack* stack, char c) {
    if (stack->top == (MAX - 1)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = c;
}

// Pop operation for character stack
char pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

// Push operation for integer stack
void pushInt(struct IntStack* stack, int value) {
    if (stack->top == (MAX - 1)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

// Pop operation for integer stack
int popInt(struct IntStack* stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

// Function to return precedence of operators
int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

// Function to check if the character is an operand
int isOperand(char c) {
    return isalpha(c) || isdigit(c);
}

// Function to convert infix to postfix
void infixToPostfix(char* infix) {
    struct Stack stack;
    stack.top = -1;
    char postfix[MAX];
    int i = 0, j = 0;
    char ch;

    while ((ch = infix[i++]) != '\0') {
        if (isOperand(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(&stack, ch);
        } else if (ch == ')') {
            while (stack.top != -1 && stack.arr[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            pop(&stack); // Remove '('
        } else { // Operator
            while (stack.top != -1 && precedence(ch) <= precedence(stack.arr[stack.top])) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    while (stack.top != -1) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
    printf("Postfix Expression: %s\n", postfix);
}

// Function to reverse a string
void reverse(char* exp) {
    int len = strlen(exp);
    for (int i = 0; i < len / 2; i++) {
        char temp = exp[i];
        exp[i] = exp[len - 1 - i];
        exp[len - 1 - i] = temp;
    }
}

// Function to convert infix to prefix
void infixToPrefix(char* infix) {
    struct Stack stack;
    stack.top = -1;
    char prefix[MAX];
    char temp[MAX];

    // Reverse the infix expression
    strcpy(temp, infix);
    reverse(temp);

    int i = 0, j = 0;
    char ch;

    while ((ch = temp[i++]) != '\0') {
        if (isOperand(ch)) {
            prefix[j++] = ch;
        } else if (ch == ')') {
            push(&stack, ch);
        } else if (ch == '(') {
            while (stack.top != -1 && stack.arr[stack.top] != ')') {
                prefix[j++] = pop(&stack);
            }
            pop(&stack); // Remove ')'
        } else {
            while (stack.top != -1 && precedence(ch) < precedence(stack.arr[stack.top])) {
                prefix[j++] = pop(&stack);
            }
            push(&stack, ch);
        }
    }

    while (stack.top != -1) {
        prefix[j++] = pop(&stack);
    }

    prefix[j] = '\0';
    reverse(prefix);
    printf("Prefix Expression: %s\n", prefix);
}

// Function to evaluate postfix expression
int evaluatePostfix(char* postfix) {
    struct IntStack stack;
    stack.top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isdigit(c)) {
            pushInt(&stack, c - '0'); // Convert char to int and push onto stack
        } else { // Operator
            int right = popInt(&stack);
            int left = popInt(&stack);
            switch (c) {
                case '+': pushInt(&stack, left + right); break;
                case '-': pushInt(&stack, left - right); break;
                case '*': pushInt(&stack, left * right); break;
                case '/': pushInt(&stack, left / right); break;
                case '^': pushInt(&stack, (int)pow(left, right)); break; // Power operation
            }
        }
    }
    return popInt(&stack); // Return the result
}

int main() {
    int choice;
    char exp[MAX];
    do {
        printf("\n--- Stack Operations Menu ---\n");
        printf("1. Infix to Postfix\n");
        printf("2. Infix to Prefix\n");
        printf("3. Postfix Evaluation\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                printf("Enter Infix Expression: ");
                fgets(exp, MAX, stdin);
                exp[strcspn(exp, "\n")] = '\0'; // Remove trailing newline
                infixToPostfix(exp);
                break;

            case 2:
                printf("Enter Infix Expression: ");
                fgets(exp, MAX, stdin);
                exp[strcspn(exp, "\n")] = '\0'; // Remove trailing newline
                infixToPrefix(exp);
                break;

            case 3:
                printf("Enter Postfix Expression: ");
                fgets(exp, MAX, stdin);
                exp[strcspn(exp, "\n")] = '\0'; // Remove trailing newline
                printf("Postfix Evaluation Result: %d\n", evaluatePostfix(exp));
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
