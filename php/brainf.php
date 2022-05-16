<?php

$mem_size = 1024;

if ($argc != 2 && $argc != 3) {
    echo "Usage: php " . $argv[0] . " <file> [optional: memory size, default: " . $mem_size . "]\n";
    exit(1);
}

$file_name = $argv[1];

$file = fopen($file_name, "r");

if (!$file) {
    echo $argv[0] . ": error: " . $file_name . ": No such file\n";
    exit(1);
}

$code_len = filesize($file_name);
$code = fread($file, $code_len);
fclose($file);

if ($argc == 3) {
    $mem_size = $argv[2];
}

$stk = new SplStack();
$tape = array_fill(0, $mem_size, 0);

$line_count = 1;
$char_count = 1;

for ($i = 0; $i < $code_len; $i++) {
    $char = $code[$i];

    if ($char == "\n") {
        $line_count++;
        $char_count = 1;
    } else if ($char == "[") {
        $stk->push($i);
    } else if ($char == "]") {
        if ($stk->isEmpty()) {
            echo $argv[0] . ": error: " . $file_name . ": Unmatched ] at line " . $line_count . ", char " . $char_count . "\n";
            exit(1);
        }

        $jmp_to = $stk->pop();
        $map[$jmp_to] = $i;
        $map[$i] = $jmp_to;
    }
}

if (!$stk->isEmpty()) {
    echo $argv[0] . ": error: " . $file_name . ": Unmatched [ at line " . $line_count . ", char " . $char_count . "\n";
    exit(1);
}

$ptr = 0;

for ($i = 0; $i < $code_len; $i++) {
    $char = $code[$i];

    switch ($char) {
        case '+':
            $tape[$ptr] = ($tape[$ptr] + 1) % 256;
            break;

        case '-':
            $tape[$ptr] = $tape[$ptr] == 0 ? 255 : $tape[$ptr] - 1;
            break;

        case '>':
            $ptr = ($ptr + 1) % $mem_size;
            break;

        case '<':
            $ptr = $ptr == 0 ? $mem_size - 1 : $ptr - 1;
            break;

        case '.':
            echo chr($tape[$ptr]);
            break;

        case ',':
            $tape[$ptr] = ord(fgetc(STDIN));
            break;

        case '[':
            if ($tape[$ptr] == 0) {
                $i = $map[$i];
            }
            break;

        case ']':
            if ($tape[$ptr] != 0) {
                $i = $map[$i];
            }
            break;
    }
}
