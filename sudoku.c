#include <stdio.h>
#include <stdbool.h>

#define N 9
#define SUCCESS 1
#define FAILURE -1
#define SOLUTIONS_LIMIT 10000

void printBoard(int board[][N]);
void fillSudoku(int board[][N]);
int fillSudoku_aux(int board[][N], int number_of_full_cells0, int usedRow[][N], int usedCol[][N], int usedBox[][N], bool *is_first_solution);
int getBoard(int board[][N]);
void getUsedCol(int board[][N], int usedCol[][N]);
void getUsedBox(int board[][N], int usedBox[][N]);
void getUsedRow(int board[][N], int usedRow[][N]);
void printResult(int board[][N], int res);
void resetUsed(int arr[][N]);
bool isRowLegal(int board[][N], int row, int val);
bool isColLegal(int board[][N], int col, int val);
bool isBoxLegal(int board[][N], int row, int col, int val);
bool isBoardLegal(int board[][N]);

int main()
{
	int board[N][N] = {{0}};
	printf("Welcome to Sudoku Solver\n");
	printf("Enter board - 0 for blank space\n");
	int res = getBoard(board);
	if (res == FAILURE)
	{
		printf("Failed to recieve input - Terminating program\n");
	}
	else
	{
		printf("The Board:\n");
		printBoard(board);
		bool is_legal = isBoardLegal(board);
		if (is_legal)
			fillSudoku(board);
		else
			printResult(board, 0);
	}

	return 0;
}

//	Recieves input from the user into board variable
int getBoard(int board[][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			int num;
			if (scanf("%d", &num))
			{
				if (num >= 0 && num <= 9)
				{
					board[row][col] = num;
				}
			}
			else
			{
				return FAILURE;
			}
		}
	}
	return SUCCESS;
}

bool isBoardLegal(int board[][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			if (board[row][col] != 0)
			{
				int val = board[row][col];
				board[row][col] = 0;
				if ((!isRowLegal(board, row, val)) || (!isColLegal(board, col, val)) || (!isBoxLegal(board, row, col, val)))
				{
					return false;
				}
				board[row][col] = val;
			}
		}
	}
	return true;
}

void fillSudoku(int board[][N])
{
	int usedRow[N][N] = {{0}};
	int usedCol[N][N] = {{0}};
	int usedBox[N][N] = {{0}};
	int number_of_full_cells = 0;
	getUsedRow(board, usedRow);
	getUsedCol(board, usedCol);
	getUsedBox(board, usedBox);
	bool is_first_solution = true;
	int amount_of_solutions = fillSudoku_aux(board, number_of_full_cells, usedRow, usedCol, usedBox, &is_first_solution);
	printResult(board, amount_of_solutions);
}

void printResult(int board[][N], int amount_of_solutions)
{
	if (amount_of_solutions >= SOLUTIONS_LIMIT)
	{
		printf("There are more than 10,000 solutions! Wow! \n");
	}
	else if (amount_of_solutions)
	{
		printf("Amount Of Solutions: %d\n", amount_of_solutions);
	}
	else
	{
		printf("There is no solution\n");
	}
}

int fillSudoku_aux(int board[][N], int number_of_full_cells, int usedRow[][N], int usedCol[][N], int usedBox[][N], bool *is_first_solution)
{
	if (number_of_full_cells == 81)
	{
		if (*is_first_solution)
		{
			// if you want to print every possible solution - delete the if statement
			printf("Solution for example:\n");
			printBoard(board);
			*is_first_solution = false;
		}
		return 1;
	}
	int row = number_of_full_cells / 9;
	int col = number_of_full_cells % 9;
	int amount_of_solutions = 0;
	if (board[row][col] != 0)
	{
		amount_of_solutions += fillSudoku_aux(board, number_of_full_cells + 1, usedRow, usedCol, usedBox, is_first_solution);
	}
	else
	{
		int box = (row / 3) * 3 + col / 3;
		for (int i = 0; i < N; i++)
		{
			if (usedRow[row][i] == 1 || usedCol[col][i] == 1 || usedBox[box][i] == 1)
				continue;
			board[row][col] = i + 1;
			usedRow[row][i] = 1;
			usedCol[col][i] = 1;
			usedBox[box][i] = 1;
			amount_of_solutions += fillSudoku_aux(board, number_of_full_cells + 1, usedRow, usedCol, usedBox, is_first_solution);
			board[row][col] = 0;
			usedRow[row][i] = 0;
			usedCol[col][i] = 0;
			usedBox[box][i] = 0;

			// putting limit to amount of solutions to search for
			if (amount_of_solutions >= SOLUTIONS_LIMIT)
			{
				return amount_of_solutions;
			}
		}
	}
	return amount_of_solutions;
}

void printBoard(int board[][N])
{
	for (int i = 0; i < N; i++)
	{
		if (i % 3 == 0)
		{
			for (int k = 0; k < N + 4; k++)
			{
				printf("- ");
			}
			printf("\n");
		}
		printf("| ");
		for (int j = 0; j < N; j++)
		{
			if (j % 3 == 2)
			{
				printf("%c | ", board[i][j] == 0 ? ' ' : board[i][j] + 48);
			}
			else
			{
				printf("%c ", board[i][j] == 0 ? ' ' : board[i][j] + 48);
			}
		}
		printf("\n");
	}
	for (int k = 0; k < N + 4; k++)
	{
		printf("- ");
	}
	printf("\n");
}

//	When given board to fill, writes in usedCol which number is already used in a every col
void getUsedCol(int board[][N], int usedCol[][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			if (board[row][col] != 0)
			{
				usedCol[col][board[row][col] - 1] = 1;
			}
		}
	}
}

//	When given board to fill, writes in usedBox which number is already used in a every box
void getUsedBox(int board[][N], int usedBox[][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			if (board[row][col] != 0)
			{
				int box = (row / 3) * 3 + col / 3;
				usedBox[box][board[row][col] - 1] = 1;
			}
		}
	}
}

//	When given board to fill, writes in usedRow which number is already used in a every row
void getUsedRow(int board[][N], int usedRow[][N])
{
	for (int row = 0; row < N; row++)
	{
		for (int col = 0; col < N; col++)
		{
			if (board[row][col] != 0)
			{
				usedRow[row][board[row][col] - 1] = 1;
			}
		}
	}
}

bool isRowLegal(int board[][N], int row, int val)
{
	for (int col = 0; col < N; col++)
	{
		if (board[row][col] == val)
			return false;
	}
	return true;
}
bool isColLegal(int board[][N], int col, int val)
{
	for (int row = 0; row < N; row++)
	{
		if (board[row][col] == val)
			return false;
	}
	return true;
}
bool isBoxLegal(int board[][N], int row, int col, int val)
{
	row = row - row % 3;
	col = col - col % 3;
	for (; row < 3; row++)
	{
		for (; col < 3; col++)
		{
			if (board[row][col] == val)
				return false;
		}
	}
	return true;
}