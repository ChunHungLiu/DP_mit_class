#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

/*
Optimal Strategy for a Game. Consider a row of n coins of values v(1) ... v(n), where n is even. We play a game against an opponent by alternating turns. In each turn, a player selects either the first or last coin from the row, removes it from the row permanently, and receives the value of the coin. Determine the maximum possible amount of money we can definitely win if we move first.
*/

class Solution {
public:
	int dp(int c[], int n) {
		int sum = 0;
		cout << "input: ";
		for (int i = 0; i < n; ++i) {
			cout << c[i] << ", ";
			sum += c[i];
		}
		cout << endl;
		cout << "sum: " << sum << endl;

		int dp[n][n];
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				dp[i][j] = 0;

		for (int len = 0; len < n; ++len) {
			for (int i = 0; i < n-len; ++i) {
				if (len == 0)
					dp[i][i+len] = c[i];
				else if (len == 1)
					dp[i][i+len] = max(c[i], c[i+1]);
				else {
					int j = i+len;
					int val_1 = c[i] + min(dp[i+2][j], dp[i+1][j-1]);
					int val_2 = c[j] + min(dp[i+1][j-1], dp[i][j-2]);
					dp[i][i+len] = max(val_1, val_2);
				}
			}
		}

		cout << "table: " << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cout << setw(3) << dp[i][j] << " ";
			cout << endl;
		}
		cout << endl;

		cout << "You win by: " << dp[0][n-1]*2 - sum << endl;

		return dp[0][n-1];
	}
};

int main()
{
	Solution sol;
	int c[5];
	int n = sizeof(c) / sizeof(c[0]);
	srand(time(NULL));

	for (int i = 0; i < n; ++i)
		c[i] = rand()%20+1;

	cout << sol.dp(c, n) << endl;

	return 0;
}
