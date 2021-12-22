#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct stack_t
{
    int64_t data;
    struct stack_t *next;

} stack;

static inline stack* CreateNode(int64_t data)
{
    stack *n = (stack*) malloc(sizeof(stack));

    if (n == NULL)
        return NULL;

    n->data = data;
    n->next = NULL;

    return n;
}

static inline void Push(stack* insertingNode, stack **head)
{
    stack *cur = *head;

    *head = insertingNode;
    insertingNode->next = cur;
}

static inline stack* Pop(stack **head)
{
    stack *cur = *head;

    if (*head == NULL)
        return NULL;

    *head = cur->next;
    cur->next = NULL;
    return cur;
}

static inline stack* Peek(stack *head)
{
    return head;
}

static inline int64_t mod(int64_t x, int64_t y)
{
	return x - floor((float)x / (float)y) * y;
}

int main(int argc, char const **argv)
{
	int64_t i, j, line_count, char_count;
	int8_t *tape = NULL;
	uint64_t numbytes;
	uint64_t memsize = 1024;

	char c, *buffer = NULL;

	int64_t *pairs = NULL;

    stack *stk = NULL, *temp = NULL;
	FILE *fp = NULL;

	if (argc != 2 && argc != 3)
	{
		printf("Usage: %s <file> <optional: memory-size, default: %ld>\n", argv[0], memsize);
		return -1;
	}
	
	fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("%s: error: %s: No such file\n", argv[0], argv[1]);
		return -1;
	}

	if (argc == 3)
		memsize = atoll(argv[2]);

	tape = (int8_t*)calloc(memsize, sizeof(int8_t));
	
	fseek(fp, 0L, SEEK_END);
	
	numbytes = ftell(fp);

	buffer = (char*)malloc(numbytes * sizeof(char));

	rewind(fp);

	// I'm not entirely sure what is going on here, but it seems to be working
	fread(buffer, 1, numbytes, fp);

	fclose(fp);

	// In this algorithm, the time complexity is O(1) but the space complexity is O(size_of_the_file in bytes)
	pairs = (int64_t*)malloc(numbytes * sizeof(int64_t));

    line_count = 1;
    char_count = 1;

	// Getting the pair indices
	for (i = 0; (c = buffer[i]) != '\0'; i++)
	{
        if (c == '\n')
        {
            line_count++;
            char_count = 1;
        }
		else if (c == '[')
		{
			temp = CreateNode(i);

			if (temp == NULL)
			{
				printf("\n%s: error: overflow\n", argv[0]);
				return -1;
			}
			
            Push(temp, &stk);
		}
		else if (c == ']')
		{
            temp = Pop(&stk);

            if (temp == NULL)
            {
                printf("\nSyntax error: Unexpected closing bracket in line %ld char %ld.\n", line_count, char_count);
                return -1;
            }

			pairs[temp->data] = i;
			pairs[i] = temp->data;

            free(temp);
		}

		char_count++;
	}

    if (Peek(stk) != NULL)
    {
        printf("\nSyntax error: Unclosed bracket in line %ld char %ld.\n", line_count, char_count);
        return -1;
    }

	// Interpreting the string
	for (i = 0, j = 0; (c = buffer[i]) != '\0'; i++)
	{
		switch (c)
		{
			case '+':
				tape[j]++;
				break;

			case '-':
				tape[j]--;
				break;

			case '[':
				if (tape[j] == 0)
					i = pairs[i];
				
				break;

			case ']':
				if (tape[j] != 0)
					i = pairs[i];
				
				break;

			case '<':
				j = mod(j - 1, memsize);
				break;

			case '>':
				j = (j + 1) % memsize;
				break;

			case '.':
                putchar((char)tape[j]);
				break;

			case ',':
				tape[j] = (int8_t)getchar();
				break;
		}
	}

	free(buffer);
	free(tape);
	free(pairs);

	return 0;
}
