#include <iostream>
using namespace std;

const int MAX_N = 100; // Maximum number of items
const int MAX_W = 1000; // Maximum knapsack capacity

int knapsack(int W, int weights[], int values[], int n) {
    int dp[MAX_N+1][MAX_W + 1] = {0}; // Static 2D array for dp

    // Fill dp array based on knapsack conditions
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            if (weights[i - 1] <= j) {
                dp[i][j] = max(values[i - 1] + dp[i - 1][j - weights[i - 1]], dp[i - 1][j]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Retrieve the result from the dp array
    int res = dp[n][W];
    int w = W;

    // Find selected items
    int selectedItems[MAX_N]; // Array to store selected item indices
    int selectedCount = 0;
    for (int i = n; i > 0 && res > 0; i--) {
        if (res != dp[i - 1][w]) { // Item i-1 was included
            selectedItems[selectedCount++] = i - 1; // Store item index
            res -= values[i - 1];
            w -= weights[i - 1];
        }
    }

    cout << "Selected items (0-indexed): ";
    for (int i = selectedCount - 1; i >= 0; i--) {
        cout << selectedItems[i] << " ";
    }
    cout << endl;

    return dp[n][W];
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter knapsack capacity: ";
    cin >> W;

    if (n > MAX_N || W > MAX_W) {
        cout << "Exceeded maximum constraints for items or weight.\n";
        return 0;
    }

    int values[MAX_N], weights[MAX_N];

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++) cin >> values[i];

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++) cin >> weights[i];

    int maxValue = knapsack(W, weights, values, n);
    cout << "Maximum value in Knapsack = " << maxValue << endl;

    return 0;
}
