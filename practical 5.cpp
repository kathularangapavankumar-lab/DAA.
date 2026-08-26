#include <iostream>
using namespace std;

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    int weight[n], profit[n];

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    cout << "Enter profits of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> profit[i];
    }

    cout << "Enter capacity of knapsack: ";
    cin >> capacity;

    // DP table
    int dp[n + 1][capacity + 1];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {

            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }
            else if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    profit[i - 1] + dp[i - 1][w - weight[i - 1]],
                    dp[i - 1][w]
                );
            }
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nMaximum Profit = " << dp[n][capacity] << endl;

    return 0;
}
