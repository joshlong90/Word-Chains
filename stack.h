// Stack ADT header file ... COMP9024 17s2

typedef struct StackRep *stack;

stack newStack();                 // set up empty stack
void  dropStack(stack);           // remove unwanted stack
int   StackIsEmpty(stack);        // check whether stack is empty
void  StackPush(stack, int);      // insert an int on top of stack
int   StackPop(stack);            // remove int from top of stack

// Additional functions.
void  StackPrint(stack, char **); // prints the contents of stack.
int   topStack(stack);            // returns the integer at top of stack.
int   heightStack(stack);         // return the height of a stack.