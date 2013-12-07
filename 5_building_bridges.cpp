#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

/*
Building Bridges. Consider a 2-D map with a horizontal river passing through its center. There are n cities on the southern bank with x-coordinates a(1) ... a(n) and n cities on the northern bank with x-coordinates b(1) ... b(n). You want to connect as many north-south pairs of cities as possible with bridges such that no two bridges cross. When connecting cities, you can only connect city i on the northern bank to city i on the southern bank. (Note: this problem was incorrectly stated on the paper copies of the handout given in recitation.)
*/

class Solution {
public:
	int dp(int a[], int b[], int n) {
		int c[n];
		cout << "c: ";
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (a[i] == b[j]) {
					c[i] = j;
					cout << c[i] << " ";
					break;
				}
			}
		}
		cout << endl;

		int dp[n];
		for (int i = 0; i < n; ++i)
			dp[i] = 1;

		int res = 1;
		for (int i = 1; i < n; ++i) {
			for (int j = 0; j < i; ++j) {
				if (c[i] > c[j]) {
					dp[i] = max(dp[i], dp[j]+1);
				}
				res = max(res, dp[i]);
			}
		}

		return res;
	}
};

int main()
{
	Solution sol;
	int a[20];
	int n = sizeof(a) / sizeof(a[0]);
	int b[n];

	for (int i = 0; i < n; ++i) {
		a[i] = i; b[i] = i;
	}

	random_shuffle(&a[0], &a[n]);
	random_shuffle(&b[0], &b[n]);

	cout << "a: ";
	for (int i = 0; i < n; ++i) 
		cout << a[i] << " ";
	cout << endl;
	cout << "b: ";
	for (int i = 0; i < n; ++i) 
		cout << b[i] << " ";
	cout << endl;

	cout << endl << "max bridges: " << sol.dp(a, b, n) << endl;

	return 0;
}
