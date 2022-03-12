#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct stack_t
{
	uint64_t data;
	struct stack_t *next;

} stack;

static inline stack *CreateNode(uint64_t data)
{
	stack *n = (stack *)malloc(sizeof(stack));

	if (n == NULL)
		return NULL;

	n->data = data;
	n->next = NULL;

	return n;
}

static inline void Push(stack *insertingNode, stack **head)
{
	stack *cur = *head;

	*head = insertingNode;
	insertingNode->next = cur;
}

static inline stack *Pop(stack **head)
{
	stack *cur = *head;

	if (*head == NULL)
		return NULL;

	*head = cur->next;
	cur->next = NULL;
	return cur;
}

static inline stack *Top(stack *head)
{
	return head;
}

int main(int argc, char const **argv)
{
	uint64_t i, j, line_count, char_count;
	uint8_t *tape = NULL;
	uint64_t numbytes;
	uint64_t memsize = 1024;

	unsigned char c, *buffer = NULL;

	uint64_t *pairs = NULL;

	stack *stk = NULL, *temp = NULL;
	FILE *fp = NULL;

	if (argc != 2 && argc != 3)
	{
		printf("Usage: %s <file> [optional: memory-size, default: %ld]\n", argv[0], memsize);
		return 1;
	}

	fp = fopen(argv[1], "r");

	if (fp == NULL)
	{
		printf("%s: error: %s: No such file\n", argv[0], argv[1]);
		return 1;
	}

	if (argc == 3)
		memsize = atoll(argv[2]);

	tape = (uint8_t *)calloc(memsize, sizeof(uint8_t));

	fseek(fp, 0L, SEEK_END);

	numbytes = ftell(fp);

	buffer = (unsigned char *)malloc(numbytes * sizeof(unsigned char));

	rewind(fp);

	// I'm not entirely sure what is going on here, but it seems to be working
	fread(buffer, 1, numbytes, fp);

	fclose(fp);

	// In this algorithm, the time complexity is exactly O(1) but the space complexity is O(size_of_the_file in bytes)
	pairs = (uint64_t *)malloc(numbytes * sizeof(uint64_t));

	line_count = 1;
	char_count = 1;

	// Getting the pair indices
	for (i = 0; (c = buffer[i]) != '\0'; i++, char_count++)
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
				fprintf(stderr, "\n%s: error: overflow\n", argv[0]);
				return 1;
			}

			Push(temp, &stk);
		}
		else if (c == ']')
		{
			temp = Pop(&stk);

			if (temp == NULL)
			{
				fprintf(stderr, "\nSyntax error: Unexpected closing bracket in line %ld char %ld.\n", line_count, char_count);
				return 1;
			}

			pairs[temp->data] = i;
			pairs[i] = temp->data;

			free(temp);
		}
	}

	if (Top(stk) != NULL)
	{
		fprintf(stderr, "\nSyntax error: Unclosed bracket in line %ld char %ld.\n", line_count, char_count);
		return 1;
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
			j = j == 0 ? memsize - 1 : j - 1;
			break;

		case '>':
			j = (j + 1) % memsize;
			break;

		case '.':
			putchar(tape[j]);
			break;

		case ',':
			tape[j] = (uint8_t)getchar();
			break;
		}
	}

	free(buffer);
	free(tape);
	free(pairs);

	return 0;
}
