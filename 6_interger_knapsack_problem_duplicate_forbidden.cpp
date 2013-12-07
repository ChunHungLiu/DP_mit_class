#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

/*
Integer Knapsack Problem (Duplicate Items Forbidden). This is the same problem as the example above, except here it is forbidden to use more than one instance of each type of item.
*/

class Solution {
public:
	int dp(int v[], int w[], int n, int c) {
		int dp[n+1][c+1];
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= c; ++j) {
				if (i == 0 || j == 0) {
					dp[i][j] = 0;
				} else if (w[i-1] > j) {
					dp[i][j] = dp[i-1][j];
				} else {
					dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i-1]] + v[i-1]);
				}			
			}
		}

		cout << "table: " << endl;
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= c; ++j) {
				cout << setw(2) << dp[i][j] << " ";
			}
			cout << endl;
		}

		cout << "take : ";
		int j = c;
		for (int i = n; i > 0; --i) {
			if (dp[i][j] != dp[i-1][j]) {
				cout << "(" << w[i-1] << "," << v[i-1] << "), ";
				j -= w[i-1];
				if (j == 0) break;
			}
		}		
		cout << endl;

		return dp[n][c];
	}

	int dp2(int v[], int w[], int n, int c) {
		int dp[c+1];
		for (int i = 0; i <= c; ++i)
			dp[i] = 0;

		for (int i = 1; i <= n; ++i) {
			for (int j = c; j >= w[i-1]; --j) {
				int val = dp[j-w[i-1]] + v[i-1];
				dp[j] = max(dp[j], val);
			}
		}

		cout << "table: " << endl;
		for (int i = 0; i <= c; ++i) {
			cout << dp[i] << " ";
		}
		cout << endl;

		return dp[c];
	}
};

int main()
{
	Solution sol;
	int v[10];
	int n = sizeof(v) / sizeof(v[0]);
	int w[n];

	srand(time(NULL));

	for (int i = 0; i < n; ++i) {
		v[i] = rand()%10+1;
		w[i] = rand()%20+1;
	}

	cout << "weight: ";
	for (int i = 0; i < n; ++i) {
		cout << setw(2) << w[i] << " ";
	}
	cout << endl;
	cout << "value:  ";
	for (int i = 0; i < n; ++i) {
		cout << setw(2) << v[i] << " ";
	}
	cout << endl;

	cout << endl << sol.dp(v, w, n, 15) << endl;
	cout << endl;
	cout << endl << sol.dp2(v, w, n, 15) << endl;

	return 0;
}
