
function read_file(file_name)
    local f = io.open(file_name, "r")

    if f == nil then
        print(string.format("%s: error: %s: No such file", arg[0], arg[1]))
        os.exit(1)
    end

    local content = f:read("*all")

    f:close()
    return content
end

stk = {}
pairs = {}

mem_size = 1024
line_count = 1
char_count = 1

if #arg ~= 1 and #arg ~= 2 then
    print(string.format("Usage: %s <file> [optional: memory-size, default: %d]", arg[0], mem_size))
    return 1
end

buffer = read_file(arg[1])
buffer_length = #buffer
mem_size = tonumber(arg[2]) or mem_size

tape = {}

for i = 1, mem_size do
    tape[i] = 0
end

for i = 1, buffer_length do
    local c = string.sub(buffer, i, i)

    if c == "\n" then
        line_count = line_count + 1
        char_count = 1
    elseif c == "[" then
        table.insert(stk, i)
    elseif c == "]" then
        local top = table.remove(stk)

        if top == nil then
            print(string.format("\nSyntax error: Unexpected ']' at line %d, char %d", line_count, char_count))
            return 1
        end

        pairs[top] = i
        pairs[i] = top
    end

    char_count = char_count + 1
end

if table.remove(stk) ~= nil then
    print(string.format("\nSyntax error: Uncaught '[' at line %d, char %d", line_count, char_count))
    return 1
end

i, j = 1, 1

while i < buffer_length do
    local c = string.sub(buffer, i, i)

    if c == "+" then
        tape[j] = tape[j] + 1
    elseif c == "-" then
        tape[j] = tape[j] - 1
    elseif c == ">" then
        j = (j + 1) % mem_size
    elseif c == "<" then
        j = (j - 1) % mem_size
    elseif c == "." then
        io.write(string.char(tape[j]))
    elseif c == "," then
        tape[j] = io.read(1):byte()
    elseif c == "[" then
        if tape[j] == 0 then
            i = pairs[i]
        end
    elseif c == "]" then
        if tape[j] ~= 0 then
            i = pairs[i]
        end
    end

    i = i + 1
end
