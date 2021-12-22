import java.io.*;
import java.util.Dictionary;
import java.util.Hashtable;
import java.util.Stack;

public class brainf
{
    static int Modulo(int x, int y)
    {
    	return (int)(x - Math.floor((float)x / (float)y) * y);
    }

    static int memorySize = 1024;
    static int lineCount = 1;
    static int charCount = 1;

    static int[] tape;
    static String buffer;
    static Dictionary<Integer, Integer> pairs;
    static Stack<Integer> stk;

    public static void main(String[] args)
    {
        try
        {
            File file = new File(args[0]);
            BufferedReader br = new BufferedReader(new FileReader(file));
            
            String line;
            buffer = "";
            
            while((line = br.readLine()) != null)
                buffer += line;

            br.close();

            if (args.length == 2)
                memorySize = Integer.parseInt(args[1]);
            
            tape = new int[memorySize];
            stk = new Stack<Integer>();
            pairs = new Hashtable<Integer, Integer>();

            for (int i = 0, temp = 0; i < buffer.length(); i++, charCount++)
            {
                char c = buffer.charAt(i);

                switch (c)
                {
                    case '\n':
                        lineCount++;
                        charCount = 1;
                        break;
                    
                    case '[':
                        stk.push(i);
                        break;

                    case ']':
                        if (stk.empty())
                        {
                            System.out.println("Syntax error: Unexpected closing bracket in line " + lineCount + " char " + charCount + ".");
                            return;
                        }

                        temp = stk.pop();

                        pairs.put(temp, i);
                        pairs.put(i, temp);
                        break;
                }
            }

            if (!stk.empty())
            {
                System.out.println("Syntax error: Unclosed bracket in line " + lineCount + " char " + charCount + ".");
                return;
            }

            for (int i = 0, j = 0; i < buffer.length(); i++)
            {
                char c = buffer.charAt(i);

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
                            i = pairs.get(i);
                        break;

                    case ']':
                        if (tape[j] != 0)
                            i = pairs.get(i);
                        break;

                    case '<':
                        j = Modulo(j - 1, memorySize);
                        break;

                    case '>':
                        j = (j + 1) % memorySize;
                        break;

                    case '.':
                        System.out.print((char)tape[j]);
                        break;

                    case ',':
                        tape[j] = System.in.read();
                        break;
                }
            }
        }
        catch (ArrayIndexOutOfBoundsException e)
        {
            System.out.println("Usage: java brainf <file> <optional: memorySize, default: " + memorySize + ">");
        }
        catch (FileNotFoundException e)
        {
            System.out.println("brainf: error: " + args[0] + ": No such file");
        }
        catch (IOException e)
        {
            e.printStackTrace();
        }
    }
}
