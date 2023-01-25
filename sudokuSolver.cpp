#include <iostream>
#include <vector>

// this file includes an implementation of sudoku solver for an 9 by 9 board
// Recursive backtracking technique was used to solve the sudoku board
// Note: I used zero to mean that the cell is empty
// Note: If you have a debugger, debug the program to understand how backtracking works
// If you don't have one, just take a piece of paper and solve the sudoku board by following
// this program

// a structrue for cell
struct cell
{
    int row, col;
    cell(int row, int col) : row(row), col(col) {}
};

// check the safety of a row when inserting a new number
bool isRowSafe(std::vector<std::vector<int>> board, int row, int num)
{
    for (int i = 0; i < board[0].size(); i++)
    {
        if (board[row][i] == num)
            return false;
    }
    return true;
}

// check the safety of a column when inserting a new number
bool isColumnSafe(std::vector<std::vector<int>> board, int col, int num)
{
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i][col] == num)
            return false;
    }
    return true;
}

// check if a subgrid is safe to insert a new number
bool isSubGridSafe(std::vector<std::vector<int>> board, int row, int col, int num)
{
    for (int i = row / 3 * 3; i < row / 3 * 3 + 3; i++)
    {
        for (int j = col / 3 * 3; j < col / 3 * 3 + 3; j++)
        {
            if (board[i][j] == num)
                return false;
        }
    }
    return true;
}

// check if an empty cell is safe to insert a new number
bool isCellSafe(std::vector<std::vector<int>> &board, int row, int col, int num)
{
    // for an emtpy cell to be safe to insert a new number, we have to make sure
    // that the number we will insert to that cell does not already appear in respective row, column and subgrid.
    if (isRowSafe(board, row, num) && isColumnSafe(board, col, num) && isSubGridSafe(board, row, col, num))
        return true;
    return false;
}

// Find an empty cell in the board
cell findEmptyCell(std::vector<std::vector<int>> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == 0)
            {
                return cell(i, j);
            }
        }
    }
    return cell(-1, -1);
}

bool solveSudokuBoard(std::vector<std::vector<int>> &board)
{
    cell emptyCell = findEmptyCell(board); // get a empty cell
    if (emptyCell.row == -1)               // if an empty cell was not found (in which case row and col of cell is -1)
        return true;                       // return true, because board is fully solved

    int row = emptyCell.row, col = emptyCell.col; // get the row and column of the cell

    for (int num = 1; num <= 9; num++) // try all numbers 1 through 9
    {
        if (isCellSafe(board, row, col, num)) // if The cell is safe to insert a new number, insert it
        {
            board[row][col] = num;       // inserting a new number
            if (solveSudokuBoard(board)) // Solve the rest of the board recursively, and then check if the board was solved properly
                return true;             // if yes, return true
            board[row][col] = 0;         // otherwise remove the last number we inserted because it didn't lead us to a solution
            // repeat the process for other numbers
        }
    }
    // If we could not insert any number, return false and backtrack to the last cell we inserted a number to try other numbers
    return false;
}

void printSudokuBoard(std::vector<std::vector<int>> board)
{
    for (int i = 0; i < board.size(); i++)
    {
        if (i % 3 == 0)
        {
            std::cout << "**********************************" << std::endl;
        }
        for (int j = 0; j < board[0].size(); j++)
        {
            if (j % 3 == 0)
                std::cout << "| ";
            std::cout << board[i][j] << "  ";
        }
        std::cout << "*" << std::endl;
    }
    std::cout << "**********************************" << std::endl;
}

int main()
{
    std::vector<std::vector<int>> board1 = {{2, 3, 0, 4, 1, 5, 0, 6, 8},
                                            {0, 8, 0, 2, 3, 6, 5, 1, 9},
                                            {1, 6, 0, 9, 8, 7, 2, 3, 4},
                                            {3, 1, 7, 0, 9, 4, 0, 2, 5},
                                            {4, 5, 8, 1, 2, 0, 6, 9, 7},
                                            {9, 2, 6, 0, 5, 8, 3, 0, 1},
                                            {0, 0, 0, 5, 0, 0, 1, 0, 2},
                                            {0, 0, 0, 8, 4, 2, 9, 0, 3},
                                            {5, 9, 2, 3, 7, 1, 4, 8, 6}};

    std::vector<std::vector<int>> board2 = {{5, 3, 0, 0, 7, 0, 0, 0, 0},
                                            {6, 0, 0, 1, 9, 5, 0, 0, 0},
                                            {0, 9, 8, 0, 0, 0, 0, 6, 0},
                                            {8, 0, 0, 0, 6, 0, 0, 0, 3},
                                            {4, 0, 0, 8, 0, 3, 0, 0, 1},
                                            {7, 0, 0, 0, 2, 0, 0, 0, 6},
                                            {0, 6, 0, 0, 0, 0, 2, 8, 0},
                                            {0, 0, 0, 4, 1, 9, 0, 0, 5},
                                            {0, 0, 0, 0, 8, 0, 0, 7, 9}};

    solveSudokuBoard(board1);
    printSudokuBoard(board1);

    return 0;
}