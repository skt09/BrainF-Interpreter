#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "binary_search.h"
#include "stack.h"

int main(int argc, char const **argv)
{
	int64_t i, j, usable_size_of_pairs, line_count, char_count;
	int8_t *tape = NULL;
	uint64_t numbytes;
	uint64_t memsize = 1024;
	uint64_t pairsize = 1024;

	char c, *buffer = NULL;

	int64_t *open_pairs_1 = NULL;
	int64_t *end_pairs_1 = NULL;

	int64_t *open_pairs_2 = NULL;
	int64_t *end_pairs_2 = NULL;

    stack *stk = NULL, *temp = NULL;
	FILE *fp = NULL;

	if (argc != 2 && argc != 3 && argc != 4)
	{
		printf("Usage: %s <file> <optional: memory-size, default: %ld> <optional: pair-size, default: %ld>\n", argv[0], memsize, pairsize);
		return -1;
	}
	
	fp = fopen(argv[1], "rb");

	if (fp == NULL)
	{
		printf("%s: error: %s: No such file\n", argv[0], argv[1]);
		return -1;
	}

	if (argc >= 3)
		memsize = atoll(argv[2]);
	
	if (argc == 4)
		pairsize = atoll(argv[3]);

	open_pairs_1 = (int64_t*)malloc(pairsize * sizeof(int64_t));
	memset(open_pairs_1, -1, sizeof(int64_t) * pairsize);

	end_pairs_1 = (int64_t*)malloc(pairsize * sizeof(int64_t));
	memset(end_pairs_1, -1, sizeof(int64_t) * pairsize);

	open_pairs_2 = (int64_t*)malloc(pairsize * sizeof(int64_t));
	memset(open_pairs_2, -1, sizeof(int64_t) * pairsize);

	end_pairs_2 = (int64_t*)malloc(pairsize * sizeof(int64_t));
	memset(end_pairs_2, -1, sizeof(int64_t) * pairsize);

	tape = (int8_t*)calloc(memsize, sizeof(int8_t));
	
	fseek(fp, 0L, SEEK_END);
	
	numbytes = ftell(fp);

	buffer = (char*)malloc(numbytes * sizeof(char));

	rewind(fp);

	// I'm not entirely sure what is going on here, but it seems to be working
	fread(buffer, numbytes, 1, fp);

	fclose(fp);

    usable_size_of_pairs = 0;
    line_count = 1;
    char_count = 1;

	// Getting the pair indices
	for (i = 0, j = 0; (c = buffer[i]) != '\0'; i++)
	{
        if (c == '\n')
        {
            line_count++;
            char_count = 1;
        }
		else if (c == '[')
		{
            Push(CreateNode('['), &stk);
            usable_size_of_pairs++;

			while (open_pairs_1[j] != -1)
				j++;
			
			open_pairs_1[j] = i;
		}
		else if (c == ']')
		{
            temp = Pop(&stk);

            if (temp == NULL)
            {
                printf("\nSyntax error: Unexpected closing bracket in line %ld char %ld.\n", line_count, char_count);
                return -1;
            }

            free(temp);

			while (end_pairs_1[j] != -1)
				j--;
			
			end_pairs_1[j] = i;
		}

		char_count++;
	}

    if (Peek(stk) != NULL)
    {
        printf("\nSyntax error: Unclosed bracket in line %ld char %ld.\n", line_count, char_count);
		free(stk);
        return -1;
    }

	open_pairs_1 = realloc(open_pairs_1, usable_size_of_pairs * sizeof(int64_t));
    end_pairs_1 = realloc(end_pairs_1, usable_size_of_pairs * sizeof(int64_t));

	open_pairs_2 = realloc(open_pairs_2, usable_size_of_pairs * sizeof(int64_t));
    end_pairs_2 = realloc(end_pairs_2, usable_size_of_pairs * sizeof(int64_t));

	// Getting the pair indices
	for (i = numbytes - 1, j = usable_size_of_pairs - 1; i >= 0; i--)
	{
		c = buffer[i];

		if (c == ']')
		{
			while (end_pairs_2[j] != -1)
				j--;
			
			end_pairs_2[j] = i;
		}
		else if (c == '[')
		{
			while (open_pairs_2[j] != -1)
				j++;
			
			open_pairs_2[j] = i;
		}
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
					i = end_pairs_1[binary_search(i, usable_size_of_pairs, open_pairs_1)];

				break;

			case ']':
				if (tape[j] != 0)
					i = open_pairs_2[binary_search(i, usable_size_of_pairs, end_pairs_2)];

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
	
	free(open_pairs_1);
	free(end_pairs_1);

	free(open_pairs_2);
	free(end_pairs_2);

	return 0;
}
