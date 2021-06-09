#include <stdlib.h>
#include "stack.h"

inline stack* CreateNode(char data)
{
    stack *n = (stack*) malloc(sizeof(stack));

    if (n == NULL)
        return NULL;

    n->data = data;
    n->next = NULL;

    return n;
}

inline void Push(stack* insertingNode, stack **head)
{
    stack *cur = *head;

    *head = insertingNode;
    insertingNode->next = cur;
}

inline stack* Pop(stack **head)
{
    stack *cur = *head;

    if (*head == NULL)
        return NULL;

    *head = cur->next;
    cur->next = NULL;
    return cur;
}

inline stack* Peek(stack *head)
{
    return head;
}