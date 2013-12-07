#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <climits>
using namespace std;

/*
Bin Packing (Simplified Version). You have n1 items of size s[0], n2 items of size s2, and n3 items of size s3. You'd like to pack all of these items into bins each of capacity C, such that the total number of bins ued is minimized.
*/

class Solution {
public:
	int dp(int s[3], int n[3], int c) {
		int dp[n[0]+1][n[1]+1][n[2]+1][2];

		for (int i = 0; i <= n[0]; ++i) {
			for (int j = 0; j <= n[1]; ++j) {
				for (int k = 0; k <= n[2]; ++k) {
					if (i == 0 && j == 0 && k == 0) {
						dp[i][j][k][0] = 0;
						dp[i][j][k][1] = 0;
						continue;
					}

					int sol[3][2];
					sol[0][0] = (i == 0) ? INT_MAX : dp[i-1][j][k][0];
					sol[1][0] = (j == 0) ? INT_MAX : dp[i][j-1][k][0];
					sol[2][0] = (k == 0) ? INT_MAX : dp[i][j][k-1][0];

					bool extra_bin[3];
					extra_bin[0] = (i != 0 && dp[i-1][j][k][1]+s[0] > c) ? true : false;
					extra_bin[1] = (j != 0 && dp[i][j-1][k][1]+s[1] > c) ? true : false;
					extra_bin[2] = (k != 0 && dp[i][j][k-1][1]+s[2] > c) ? true : false;

					for (int x = 0; x < 3; ++x)
						if (extra_bin[x]) sol[x][0] += 1;

					sol[0][1] = (i == 0 || extra_bin[0]) ? s[0] : dp[i-1][j][k][1] + s[0];
					sol[1][1] = (j == 0 || extra_bin[1]) ? s[1] : dp[i][j-1][k][1] + s[1];
					sol[2][1] = (k == 0 || extra_bin[2]) ? s[2] : dp[i][j][k-1][1] + s[2];

					for (int x = 0; x < 3; ++x) {
						if (x == 0 || 
							sol[x][0] < dp[i][j][k][0] || 
							(sol[x][0] == dp[i][j][k][0] && sol[x][1] < dp[i][j][k][1])) {
							dp[i][j][k][0] = sol[x][0];
							dp[i][j][k][1] = sol[x][1];
						}
					}
				}
			}
		}

		cout << "use " << dp[n[0]][n[1]][n[2]][0]+1 << " bins, last one was: " << dp[n[0]][n[1]][n[2]][1] << endl;

		return dp[n[0]][n[1]][n[2]][0]+1;
	}
};

int main()
{
	Solution sol;
	int s[] = {4, 3, 8};
	int n[] = {5, 4, 4};

	cout << sol.dp(s, n, 10) << endl;

	return 0;
}
