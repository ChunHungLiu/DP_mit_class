#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <iomanip>
using namespace std;

/*
Two-Person Traversal of a Sequence of Cities. You are given an ordered sequence of n cities, and the distances between every pair of cities. You must partition the cities into two subsequences (not necessarily contiguous) such that person A visits all cities in the first subsequence (in order), person B visits all cities in the second subsequence (in order), and such that the sum of the total distances travelled by A and B is minimized. Assume that person A and person B start initially at the first city in their respective subsequences.
*/

// note: I don't think the sol here is correct!

class Solution {
public:
	int dp(int d[5][5], int n) {
		// means A stops at city i, B stops at city j.
		int dp[n][n];
		int min_val;
		for (int i = 0; i < n; ++i) 
			for (int j = 0; j < n; ++j)
				dp[i][j] = 0;

		for (int i = 0; i < n-1; ++i) {
			for (int j = i+1; j < n; ++j) {
				if (i == 0 ) {
					dp[i][j] = dp[i][j-1] + d[j-1][j];
					continue;
				} 

				min_val = INT_MAX;
				for (int k = 0; k < i; ++k) {
					if (dp[k][i]+d[k][j] < min_val)
						min_val = dp[k][i]+d[k][j];
				}
				dp[i][j] = min_val;
			}
		}

		cout << "table: " << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cout << setw(5) << dp[i][j] << " ";
			}
			cout << endl;
		}

		min_val = INT_MAX;
		for (int i = 0; i < n-1; ++i) {
			min_val = min(min_val, dp[i][n-1]);
		}
		
		return min_val;
	}
};

int main()
{
	Solution sol;
	int d[5][5];

	cout << "input: " << endl;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			d[i][j] = rand()%10+1;
			cout << setw(2) << d[i][j] << " ";
		}
		cout << endl;
	}

	cout << sol.dp(d, 5) << endl;

	return 0;
}
