#include <iostream>
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <string>
using namespace std;

/*
Edit Distance. Given two text strings A of length n and B of length m, you want to transform A into B with a minimum number of operations of the following types: delete a character from A, insert a character into A, or change some character in A into a new character. The minimal number of such operations required to transform A into B is called the edit distance between A and B.
*/

class Solution {
public:
	int dp(string a, string b) {
		cout << "input: " << a << ", " << b << endl;

		int n = a.length();
		int m = b.length();
		int dp[n+1][m+1];

		cout << "table: " << endl;
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= m; ++j) {
				if (i == 0 || j == 0)
					dp[i][j] = max(i, j);
				else
					dp[i][j] = min( min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1] + (a[i-1] != b[i-1]) );
				cout << setw(2) << dp[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;

		return dp[n][m];
	}
};

int main()
{
	Solution sol;
	string a = "abcdefg";
	string b = "hahdck";

	cout << sol.dp(a, b) << endl;

	return 0;
}
