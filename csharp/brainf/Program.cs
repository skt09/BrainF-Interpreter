int Modulus(int x, int y)
{
    return x - (x / y) * y;
}

int memorySize = 1024;
int lineCount = 1;
int charCount = 1;

int[] tape;
string buffer;
Dictionary<int, int> pairs;
Stack<int> stack;

try
{
    StreamReader sr = new StreamReader(args[0]);
    sr.BaseStream.Seek(0, SeekOrigin.Begin);
    buffer = sr.ReadToEnd();
    sr.Close();
    if (args.Length == 2)
        memorySize = Convert.ToInt32(args[1]);
    tape = new int[memorySize];
    stack = new Stack<int>();
    pairs = new Dictionary<int, int>();
    int i = 0;
    int temp;
    
    foreach (var c in buffer)
    {
        switch (c)
        {
            case '\n':
                lineCount++;
                charCount = 1;
                break;
            
            case '[':
                stack.Push(i);
                break;
            
            case ']':
                if (stack.TryPop(out temp))
                {
                    pairs.Add(temp, i);
                    pairs.Add(i, temp);
                }
                else
                {
                    Console.WriteLine($"Syntax error: Unexpected closing bracket in line {lineCount} char {charCount}.");
                    return;
                }
                break;
        }
        i++;
        charCount++;
    }
    if (stack.TryPeek(out temp))
    {
        Console.WriteLine($"Syntax error: Unclosed bracket in line {lineCount} char {charCount}.");
        return;
    }
    i = 0;
    int j = 0;
    while (i < buffer.Length)
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
            
            case '>':
                j = (j + 1) % memorySize;
                break;
            
            case '<':
                j = Modulus(j - 1, memorySize);
                break;
            
            case '[':
                if (tape[j] == 0)
                    i = pairs[i];
                break;
            
            case ']':
                if (tape[j] != 0)
                    i = pairs[i];
                break;
            
            case '.':
                Console.Write((char)tape[j]);
                break;
            
            case ',':
                tape[j] = (int)Console.Read();
                break;
        }
        i++;                    
    }
}
catch (FileNotFoundException)
{
    Console.WriteLine($"brainf: error: {args[0]}: No such file");
}
catch (Exception)
{
    Console.WriteLine($"Usage: brainf <file> <optional: memorySize, default: {memorySize}>");
}