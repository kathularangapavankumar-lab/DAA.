#include <iostream>
#include <climits>
using namespace std;

// Function to print the optimal parenthesization
void printOptimal(int s[][100], int i, int j) {
    if (i == j) {
        cout << "A" << i;
        return;
    }

    cout << "(";

    printOptimal(s, i, s[i][j]);
    printOptimal(s, s[i][j] + 1, j);

    cout << ")";
}

int main() {
    int n;

    cout << "Enter number of matrices: ";
    cin >> n;

    int p[100];

    cout << "Enter dimensions:\n";
    cout << "For " << n << " matrices, enter " << n + 1 << " dimensions:\n";

    for (int i = 0; i <= n; i++) {
        cin >> p[i];
    }

    int m[100][100];
    int s[100][100];

    // Initialize diagonal elements
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;
    }

    // Chain length
    for (int length = 2; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            m[i][j] = INT_MAX;

            // Find minimum cost
            for (int k = i; k < j; k++) {

                int cost = m[i][k]
                         + m[k + 1][j]
                         + p[i - 1] * p[k] * p[j];

                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }

    cout << "\nMinimum number of scalar multiplications = "
         << m[1][n] << endl;

    cout << "Optimal Parenthesization = ";
    printOptimal(s, 1, n);
    cout << endl;

    return 0;
}
