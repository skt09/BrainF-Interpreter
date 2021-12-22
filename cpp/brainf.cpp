#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <cmath>
#include <unordered_map>

using namespace std;

int modulo(int x, int y)
{
	return x - floor((float)x / (float)y) * y;
}

int main(int argc, char const *argv[])
{
	char c;
	string line, buffer;

	stack<int> stk;
	unordered_map<int, int> pairs;

	int mem_size = 1024;
	int line_count = 1;
	int char_count = 1;
	int buffer_length = 0;

	int temp;

	ifstream file;

	if (argc != 2 && argc != 3)
	{
		cout << "Usage: " << argv[0] << " <file> <optional: memory-size, default: " << mem_size << ">" << endl;
		return -1;
	}

	file.open(argv[1]);

	if (!file.is_open())
	{
		cout << argv[0] << ": error: " << argv[1] << ": No such file" << endl;
		return -1;
	}

	if (argc == 3)
		mem_size = atoi(argv[2]);
	
	vector<int> tape(mem_size, 0);

	while (getline(file, line))
		buffer += line + '\n';
	
	file.close();

	buffer_length = (int)buffer.length();

	for (int i = 0; i < buffer_length; i++)
	{
		c = buffer[i];

		if (c == '\n')
		{
			line_count++;
			char_count = 1;
		}
		else if (c == '[')
		{
			stk.push(i);
		}
		else if (c == ']')
		{
			if (stk.empty())
			{
				cout << endl << "Syntax error: Unexpected closing bracket in line " << line_count << " char " << line_count << "." << endl;
                return -1;
			}

			temp = stk.top();
			stk.pop();

			pairs[temp] = i;
			pairs[i] = temp;
		}

		char_count++;
	}

	if (!stk.empty())
	{
		cout << endl << "Syntax error: Unclosed bracket in line " << line_count << " char " << line_count << "." << endl;
		return -1;
	}

	// Interpreting the string
	for (int i = 0, j = 0; i < buffer_length; i++)
	{
		c = buffer[i];

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
				j = modulo(j - 1, mem_size);
				break;

			case '>':
				j = (j + 1) % mem_size;
				break;

			case '.':
                cout << (char)tape[j];
				break;

			case ',':
				tape[j] = cin.get();
				break;
		}
	}

	return 0;
}
