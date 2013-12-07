#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <algorithm>
using namespace std;

/*
Balanced Partition. You have a set of n integers each in the range 0 ... K. Partition these integers into two subsets such that you minimize |S1 - S2|, where S1 and S2 denote the sums of the elements in each of the two subsets.
*/

class Solution {
public:
	int dp(int w[], int n) {
		int sum = 0;
		for (int i = 0; i < n; ++i)
			sum += w[i];

		int dp[n+1][sum+1];
		cout << "table: " << endl;
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= sum; ++j) {
				if (i == 0 || j == 0) {
					dp[i][j] = 0;
				} else if (w[i-1] > j) {
					dp[i][j] = dp[i-1][j];
				} else if (w[i-1] == j) {
					dp[i][j] = 1;
				} else {
					dp[i][j] = dp[i-1][j] || dp[i-1][j-w[i-1]];
				}
				cout << setw(1) << dp[i][j] << " ";
			}
			cout << endl;
		}

		// get start point
		int c = sum/2;
		int dist = 0;
		int i = 0;
		while (1) {
			i = 0;
			while (i <= n) {
				if (dp[i][c-dist] == 1) 
					break;
				++i;
			}
			if (dp[i][c-dist] == 1) break;
			++dist;
		}

		cout << "sum1: " << c-dist << endl;
		cout << "pick: ";
		c -= dist;
		while (i > 0) {
			if (dp[i][c] != dp[i-1][c]) {
				cout << w[i-1] << " ";
				c -= w[i-1];
			}
			--i;
		}
		cout << endl;

		return 1;
	}
};

int main()
{
	Solution sol;
	int w[5];
	int n = sizeof(w) / sizeof(w[0]);

	srand(time(NULL));

	for (int i = 0; i < n; ++i) {
		w[i] = rand()%10+1;
	}

	cout << "input: ";
	for (int i = 0; i < n; ++i)
		cout << w[i] << " ";
	cout << endl;

	sol.dp(w, n);

	return 0;
}
