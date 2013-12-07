#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <iomanip>
using namespace std;

/*
Maximum Value Contiguous Subsequence. Given a sequence of n real numbers A(1) ... A(n), determine a contiguous subsequence A(i) ... A(j) for which the sum of elements in the subsequence is maximized.
*/

class Solution {
public:
	int best(int a[], int n) {
		int res = INT_MIN;
		int cur = 0;

		for (int i = 0; i < n; ++i) {
			cur += a[i];
			if (cur < 0) 
				cur = 0; 
			else 
				res = max(res, cur);
		}

		return res;
	}

	int dp(int a[], int n) {
		int dp[n];
		int res = 0;
		int idx = 0;

		cout << "table: ";
		for (int i = 0; i < n; ++i) {
			if (i == 0) 
				dp[i] = a[i];
			else 
				dp[i] = max(dp[i-1]+a[i], a[i]);
			
			cout << dp[i] << " ";
			if (dp[i] > res) {
				res = dp[i];
				idx = i;
			}
		}
		cout << endl;

		int sum = res;
		cout << "pick: ";
		for (int i = idx; i >= 0; --i) {
			cout << a[i] << " ";
			sum -= a[i];
			if (sum == 0)
				break;
		}
		cout << endl;

		return res;
	}
};

int main()
{
	Solution sol;
	int a[5];
	int n = sizeof(a) / sizeof(a[0]);

	srand(time(NULL));

	cout << "input: ";
	for (int i = 0; i < n; ++i) {
		a[i] = rand()%10 - 2;
		cout << a[i] << " ";
	} 
	cout << endl;
		
	cout << sol.best(a, n) << endl;
	cout << sol.dp(a, n) << endl;



	return 0;
}
