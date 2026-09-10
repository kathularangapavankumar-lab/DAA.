#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int matrixChainMultiplication(vector<int>& p, int n)
{
    // dp[i][j] = minimum cost to multiply matrices Ai to Aj
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // length is the number of matrices in the chain
    for (int length = 2; length < n; length++)
    {
        for (int i = 1; i < n - length + 1; i++)
        {
            int j = i + length - 1;

            dp[i][j] = INT_MAX;

            // Try every possible splitting point
            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k]
                         + dp[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < dp[i][j])
                {
                    dp[i][j] = cost;
                }
            }
        }
    }

    return dp[1][n - 1];
}

int main()
{
    // Matrices:
    // A1 = 10 x 20
    // A2 = 20 x 30
    // A3 = 30 x 40
    // A4 = 40 x 30

    vector<int> dimensions = {10, 20, 30, 40, 30};

    int n = dimensions.size();

    int result = matrixChainMultiplication(dimensions, n);

    cout << "Minimum number of scalar multiplications: "
         << result << endl;

    return 0;
}
