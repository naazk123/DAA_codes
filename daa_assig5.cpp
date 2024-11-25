#include <iostream>
#include <vector>
using namespace std;

// Check if it's safe to place a queen at board[row][col]
bool isSafe(const vector<vector<int>>& board, int row, int col, int n) {
    // Check the row on the left side
    for (int j = 0; j < col; j++)
        if (board[row][j] == 1)
            return false;

    // Check the upper diagonal on the left side
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1)
            return false;

    // Check the lower diagonal on the left side
    for (int i = row + 1, j = col - 1; i < n && j >= 0; i++, j--)
        if (board[i][j] == 1)
            return false;

    return true;
}

// Solve N-Queens problem with the first queen fixed at a given position
bool solveNQueens(vector<vector<int>>& board, int col, int n, int fixedRow, int fixedCol) {
    // All queens are placed successfully
    if (col == n)
        return true;

    // Skip the fixed queen's column
    if (col == fixedCol)
        return solveNQueens(board, col + 1, n, fixedRow, fixedCol);

    for (int row = 0; row < n; row++) {
        // Check if it's safe to place the queen in this position
        if (isSafe(board, row, col, n)) {
            board[row][col] = 1; // Place queen
            if (solveNQueens(board, col + 1, n, fixedRow, fixedCol))
                return true;  // Solution found
            board[row][col] = 0; // Backtrack
        }
    }

    return false; // No solution found
}

// Print the board configuration
void printSolution(const vector<vector<int>>& board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (board[i][j] == 1 ? "Q " : ". ");
        }
        cout << endl;
    }
}

int main() {
    int n, startRow, startCol;
    cout << "Enter the size of the chessboard (n): ";
    cin >> n;
    cout << "Enter the row and column for the first queen (0-indexed): ";
    cin >> startRow >> startCol;

    // Check if the given position is valid
    if (startRow >= n || startCol >= n || startRow < 0 || startCol < 0) {
        cout << "Invalid position for the first queen.\n";
        return 0;
    }

    // Initialize the chessboard
    vector<vector<int>> board(n, vector<int>(n, 0));
    board[startRow][startCol] = 1; // Place the fixed queen

    // Attempt to solve the N-Queens problem with the fixed queen
    if (!solveNQueens(board, 0, n, startRow, startCol)) {
        cout << "No solution exists with the first queen placed at (" << startRow << ", " << startCol << ").\n";
    } else {
        printSolution(board, n);
    }

    return 0;
}
