#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

/*
Longest Increasing Subsequence. Given a sequence of n real numbers A(1) ... A(n), determine a subsequence (not necessarily contiguous) of maximum length in which the values in the subsequence form a strictly increasing sequence. [on problem set 4]
*/

class Solution {
public:
	int dp(int a[], int n) {
		int dp[n];
		dp[0] = 1;
		int res = 0;
		int res_idx = -1;
		int track[n];
		for (int i = 0; i < n; ++i)
			track[i] = 0;

		// cout << "dp   : 1 ";
		for (int i = 1; i < n; ++i) {
			int max_val = 0;
			for (int j = 0; j <= i; j++) {
				if (a[i] > a[j] && dp[j] > max_val) {
					max_val = dp[j];
					track[i] = j;
				}
			}
			dp[i] = max_val + 1;

			if (dp[i] > res) {
				res = dp[i];
				res_idx = i;
			}
			// cout << dp[i] << " ";
		}
		// cout << endl;

		cout << "pick : ";
		int count = res;
		while (res_idx > 0) {
			cout << a[res_idx] << " ";
			--count;
			res_idx = track[res_idx];
		}
		if (count != 0) cout << a[0] << " ";
		cout << endl;

		return res;
	}
};

int main()
{
	Solution sol;
	int input[9];
	int n = sizeof(input)/sizeof(input[0]);

	srand(time(NULL));

	for (int i = 0; i < n; ++i)
		input[i] = i+1;
	random_shuffle(&input[0], &input[n]);

	cout << "input: ";
	for (int i = 0; i < n; ++i) {
		cout << input[i] << " ";
	}
	cout << endl;

	cout << sol.dp(input, n) << endl;

	return 0;
}
