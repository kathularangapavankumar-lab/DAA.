#include <iostream>
#include <climits>
using namespace std;

int main() {
    int n, amount;

    cout << "Enter number of coin denominations: ";
    cin >> n;

    int coin[n];

    cout << "Enter coin denominations:\n";
    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }

    cout << "Enter amount: ";
    cin >> amount;

    // dp[i] = minimum number of coins required to make amount i
    int dp[amount + 1];

    // Initialize
    dp[0] = 0;

    for (int i = 1; i <= amount; i++) {
        dp[i] = INT_MAX;
    }

    // Dynamic Programming
    for (int i = 1; i <= amount; i++) {

        for (int j = 0; j < n; j++) {

            if (coin[j] <= i && dp[i - coin[j]] != INT_MAX) {

                dp[i] = min(dp[i],
                            dp[i - coin[j]] + 1);
            }
        }
    }

    // Check if change is possible
    if (dp[amount] == INT_MAX) {
        cout << "\nChange cannot be made." << endl;
    }
    else {
        cout << "\nMinimum number of coins = "
             << dp[amount] << endl;
    }

    return 0;
}
