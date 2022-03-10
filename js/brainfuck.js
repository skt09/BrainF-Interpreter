
var fs = require('fs');

function modulo(x, y)
{
    return x - y * Math.floor(x / y);
}

var args = process.argv.slice(2);

var memorySize = 1024;
var lineCount = 1;
var charCount = 1;

var fileName = args[0];

if (fileName == undefined)
{
    console.log('Usage: node brainfuck.js <filename> [optional: memory-size, default: %d]', 1024);
    process.exit(1);
}

if (!fs.existsSync(fileName))
{
    console.log('brainfuck.js: error: %s: No such file', fileName);
    process.exit(1);
}

if (args[1] != undefined)
{
    memorySize = parseInt(args[1]);
}

var buffer = fs.readFileSync(fileName, 'utf8');

var lines = buffer.split('\n');

var str = '';

for (var i = 0; i < lines.length; i++)
{
    str += lines[i] + '\n';
}

var stack = [];
var pairs = {};

for (var i = 0; i < str.length; i++)
{
    var c = str.charAt(i);

    if (c == '\n')
    {
        lineCount++;
        charCount = 1;
    }
    if (c == '[')
    {
        stack.push(i);
    }
    else if (c == ']')
    {
        if (stack.length == 0)
        {
            console.log('brainfuck.js: error: %s: Unmatched ] at line %d, char %d', fileName, lineCount, charCount);
            process.exit(1);
        }

        var top = stack.pop();

        pairs[top] = i;
        pairs[i] = top;
    }

    charCount++;
}

if (stack.length != 0)
{
    console.log('brainfuck.js: error: %s: Unmatched [ at line %d, char %d', fileName, lineCount, charCount);
    process.exit(1);
}

var tape = [];

for (var i = 0; i < memorySize; i++)
{
    tape.push(0);
}

var j = 0;

for (var i = 0; i < str.length; i++)
{
    var c = str.charAt(i);

    if (c == '>')
    {
        j = modulo(j + 1, memorySize);
    }
    else if (c == '<')
    {
        j = modulo(j - 1, memorySize);
    }
    else if (c == '+')
    {
        tape[j] = modulo(tape[j] + 1, 256);
    }
    else if (c == '-')
    {
        tape[j] = modulo(tape[j] - 1, 256);
    }
    else if (c == '.')
    {
        process.stdout.write(String.fromCharCode(tape[j]));
    }
    else if (c == ',')
    {
        tape[j] = parseInt(process.stdin.read(1));
    }
    else if (c == '[')
    {
        if (tape[j] == 0)
        {
            i = pairs[i];
        }
    }
    else if (c == ']')
    {
        if (tape[j] != 0)
        {
            i = pairs[i];
        }
    }
}
