package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"strconv"
	"math"
)

func main() {

	args := os.Args
	argc := len(args)

	mem_size := 1024

	if argc != 2 && argc != 3 {
		fmt.Printf("Usage: %s <file> <optional: memory-size, default: %d>\n", args[0], mem_size)
		return
	}

	file, err := os.Open(args[1])
	if err != nil {
		fmt.Printf("%s: error: %s: No such file\n", args[0], args[1])
		return
	}

	if argc == 3 {
		mem_size, err = strconv.Atoi(args[2])
	}

	if err != nil {
		fmt.Println(err)
		return
	}

	buffer, err := ioutil.ReadAll(file)
	if err != nil {
		fmt.Println(err)
		return
	}

	buffer_length := len(buffer)
	tape := make([]int, mem_size)

	line_count := 1
	char_count := 1

	var stk []int
	pairs := make(map[int]int)

	for i := 0; i < buffer_length; i++ {
		c := buffer[i]

		if c == '\n' {
			line_count++
			char_count = 1
		
		} else if c == '[' {
			stk = append(stk, i)
		
		} else if c == ']' {
			if len(stk) == 0 {
				fmt.Printf("\nSyntax error: Unexpected closing bracket in line %d char %d.\n", line_count, char_count)
				return
			}

			n := len(stk) - 1
			temp := stk[n]
			stk = stk[:n]

			pairs[temp] = i
			pairs[i] = temp
		}

		char_count++
	}

	if len(stk) != 0 {
		fmt.Printf("\nSyntax error: Unclosed bracket in line %d char %d.\n", line_count, char_count)
		return
	}

	j := 0

	for i := 0; i < buffer_length; i++ {
		c := buffer[i]

		switch c {
		case '+':
			tape[j]++
			break

		case '-':
			tape[j]--
			break

		case '[':
			if tape[j] == 0 {
				i = pairs[i]
			}
			break

		case ']':
			if tape[j] != 0 {
				i = pairs[i]
			}
			break

		case '<':
			j = modulo(j - 1, mem_size)
			break

		case '>':
			j = (j + 1) % mem_size
			break

		case '.':
			fmt.Printf("%c", tape[j])
			break

		case ',':
			fmt.Scanf("%c", &tape[j])
			break
		}
	}
}

func modulo(x, y int) int {
	return int(float64(x) - math.Floor(float64(x) / float64(y)) * float64(y))
}
