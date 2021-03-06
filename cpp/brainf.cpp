#include <fstream>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
	int mem_size = 1024;

	if (argc != 2 && argc != 3)
	{
		cerr << "Usage: " << argv[0] << " <file> [optional: memory-size, default: " << mem_size << "]\n";
		return 1;
	}

	ifstream file(argv[1]);

	if (!file.is_open())
	{
		cerr << argv[0] << ": error: " << argv[1] << ": No such file\n";
		return 1;
	}

	if (argc == 3)
		mem_size = atoi(argv[2]);

	string buffer, line;

	while (getline(file, line))
		buffer += line + '\n';

	file.close();

	int buffer_length = (int)buffer.length();

	stack<int> stk;
	unordered_map<int, int> pairs;
	vector<uint8_t> tape(mem_size, 0);

	int line_count = 1;
	int char_count = 1;

	for (int i = 0; i < buffer_length; i++)
	{
		char c = buffer[i];

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
				cerr << argv[0] << ": error: " << argv[1] << ": Unmatched ']' at line " << line_count << ", char "
					 << char_count << '\n';
				return 1;
			}

			int temp = stk.top();
			stk.pop();

			pairs[temp] = i;
			pairs[i] = temp;
		}
	}

	if (!stk.empty())
	{
		cerr << argv[0] << ": error: " << argv[1] << ": Unmatched '[' at line " << line_count << ", char " << char_count
			 << '\n';
		return 1;
	}

	for (int i = 0, j = 0; i < buffer_length; i++)
	{
		char c = buffer[i];

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
			j = j == 0 ? mem_size - 1 : j - 1;
			break;

		case '>':
			j = (j + 1) % mem_size;
			break;

		case '.':
			cout << tape[j];
			break;

		case ',':
			tape[j] = cin.get();
			break;
		}
	}

	return 0;
}
