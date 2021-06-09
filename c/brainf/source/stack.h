#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack_t
{
    char data;
    struct stack_t *next;

} stack;

stack* CreateNode(char);
void Push(stack*, stack**);
stack* Pop(stack**);
stack* Peek(stack*);

#endif