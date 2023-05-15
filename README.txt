Welcome to Sudoku Solver!

Instructions:

1.  Compile with the next line: "gcc -std=c99 -Wall -g -pedantic-errors -Werror -DNDEBUG sudoku.c -o sudoku"
2.  To run exe: write "./sudoku"
3.  There are two ways to enter input:
    a. with command line:
        Enter every line of the board in seperate line of input - 0 is for empty cell in the board.
        For example:
        0 0 3 0 1 0 9 0 0 5 (then press Enter and write another line)

    b. alter the board_example.txt file and run "./sudoku < board_example.txt"

There are 9 lines to be submitted, and 9 numbers in each line.
if you'll write a character which is not a number, the program will end.

Output:
- a possible solution
- amount of solutions (if the amount is bigger than the SOLUTIONS_LIMIT - the program will stop searching)

*Note: The purpose of this project is to exersize on backtracking, so this might not be the most effective solution.