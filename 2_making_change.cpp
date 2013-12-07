#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

/*
Making Change. You are given n types of coin denominations of values v(1) < v(2) < ... < v(n) (all integers). Assume v(1) = 1, so you can always make change for any amount of money C. Give an algorithm which makes change for an amount of money C with as few coins as possible. [on problem set 4]*/

class Solution {
public:
	vector<vector<int> > recursive(vector<int> coins, int target, int idx, vector<int> cur) {
		vector<vector<int> > res;
		
		if (idx == coins.size()-1) {
			// assume last one is always 1
			for (int i = 0; i < target; ++i) {
				cur.push_back(1);
			}
			res.push_back(cur);
			return res;
		}	

		for (int i = 0; i * coins[idx] <= target; ++i) {
			if (i != 0) cur.push_back(coins[idx]);
			vector<vector<int> > r1 = recursive(coins, target-i*coins[idx], idx+1, cur);
			for (int j = 0; j < r1.size(); ++j) {
				res.push_back(r1[j]);
			}
		}

		return res;
	}

	vector<vector<int> > recursive(vector<int> coins, int target) {
		vector<int> x;
		// sort from big to small
		sort(coins.begin(), coins.end());
		reverse(coins.begin(), coins.end());

		return recursive(coins, target, 0, x);
	}

	// find minimum number of representation of coins
	int dp(vector<int> coins, int target) {
		int dp[target+1];
		int track[target+1];

		for (int i = 0; i < target+1; ++i) {
			dp[i] = 0; track[i] = 0;
		}

		// sort from small to big
		sort(coins.begin(), coins.end());
		for (int i = 0; i < coins.size(); ++i) {
			if (coins[i] > target) break;
			dp[coins[i]] = 1;
			track[coins[i]] = coins[i];
		}

		// cout << "dp: 0 1 ";
		// we know dp[0] = 0, dp[1] = 1;
		for (int i = 2; i <= target; ++i) {
			if (dp[i] == 0) {
				// should change to int_max
				int min_val = INT_MAX;
				int idx;
				for (int j = 0; j < coins.size(); ++j) {
					if (i-coins[j] <= 0) break;
					if (dp[i-coins[j]] < min_val) {
						min_val = dp[i-coins[j]];
						idx = j;
					}
				}
				dp[i] = min_val + 1;
				track[i] = coins[idx];

				// cout << dp[i] << " ";
			}
		}
		// cout << endl;

		int sum = target;
		cout << "target: " << target << ", pick: ";
		while (sum > 0) {
			cout << track[sum] << " ";
			sum -= track[sum];
		}
		cout << endl;

		return dp[target];
	}
};

int main()
{
	Solution sol;
	vector<int> coins;
	coins.push_back(1);
	coins.push_back(5);
	coins.push_back(10);
	coins.push_back(25);

	// vector<vector<int> > res = sol.recursive(coins, 26);

	// for (int i = 0; i < res.size(); ++i) {
	// 	for (int j = 0; j < res[i].size(); ++j) {
	// 		cout << res[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	for (int i = 10; i < 20; ++i)
		sol.dp(coins, i);

	// cout << sol.dp(coins, 20) << endl;

	return 0;
}
