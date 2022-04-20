use std::env;
use std::process;
use std::io::stdin;
use std::io::Read;
use std::fs::File;
use std::collections::HashMap;
use std::convert::TryInto;

fn main()
{
    let mut mem_size = 1024;

    let args: Vec<String> = env::args().collect();
    let argc = args.len();

    if argc != 2 && argc != 3
    {
        eprintln!("usage: {} <file> [optional: memory-size, default: {}]", args[0], mem_size);
        process::exit(1);
    }

    if argc == 3
    {
        mem_size = args[2].parse::<i32>().unwrap();
    }

    let mut buffer = String::new();

    match File::open(&args[1])
    {
        Ok(mut file) => {
            file.read_to_string(&mut buffer).unwrap();
        },
        Err(..) => {
            eprintln!("{}: error: {}: No such file", args[0], args[1]);
            process::exit(1);
        },
    }

    let buf_len = buffer.len();

    let mut stk: Vec<i32> = Vec::new();
    let mut pairs: HashMap<i32, i32> = HashMap::new();
    let mut tape: Vec<u8> = vec![0; mem_size.try_into().unwrap()];

    let mut line_count = 1;
    let mut char_count = 1;

    let mut i = 0;

    while i < buf_len
    {
        let c = buffer.as_bytes()[i] as char;

        if c == '\n'
        {
            line_count += 1;
            char_count = 1;
        }
        else if c == '['
        {
            stk.push(i.try_into().unwrap());
        }
        else if c == ']'
        {
            if stk.is_empty()
            {
                eprintln!("{}: error: {}: Unmatched ']' at line {}, char {}", args[0], args[1], line_count, char_count);
                process::exit(1);
            }

            let temp = stk.pop().unwrap();

            pairs.insert(temp, i.try_into().unwrap());
            pairs.insert(i.try_into().unwrap(), temp);
        }

        i += 1;
    }

    if !stk.is_empty()
    {
        eprintln!("{}: error: {}: Unmatched '[' at line {}, char {}", args[0], args[1], line_count, char_count);
        process::exit(1);
    }

    i = 0;
    let mut j = 0;

    while i < buf_len
    {
        let c = buffer.as_bytes()[i] as char;

        if c == '+'
        {
            tape[j] = tape[j].wrapping_add(1);
        }
        else if c == '-'
        {
            tape[j] = tape[j].wrapping_sub(1);
        }
        else if c == '['
        {
            if tape[j] == 0
            {
                i = pairs[&i.try_into().unwrap()].try_into().unwrap();
            }
        }
        else if c == ']'
        {
            if tape[j] != 0
            {
                i = pairs[&i.try_into().unwrap()].try_into().unwrap();
            }
        }
        else if c == '<'
        {
            j = if j == 0 { (mem_size - 1).try_into().unwrap() } else { j - 1 };
        }
        else if c == '>'
        {
            j = if j == (mem_size - 1).try_into().unwrap() { 0 } else { j + 1 };
        }
        else if c == '.'
        {
            print!("{}", tape[j] as char);
        }
        else if c == ','
        {
            tape[j] = stdin().bytes().next().unwrap().unwrap();
        }

        i += 1;
    }
}
