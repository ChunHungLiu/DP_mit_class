#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// http://people.csail.mit.edu/bdean/6.046/dp/dp_9.swf
/*
Counting Boolean Parenthesizations. You are given a boolean expression consisting of a string of the symbols 'true', 'false', 'and', 'or', and 'xor'. Count the number of ways to parenthesize the expression such that it will evaluate to true. For example, there is only 1 way to parenthesize 'true and false xor true' such that it evaluates to true.
*/

class Solution {
public:
	int recursive(string input, bool target, int start, int end) {
		if (start == end) {
			if ( (input[start] == '1' && target) ||
				 (input[start] == '0' && !target) ) {
				return 1;
			} else {
				return 0;
			}
		}

		int count = 0;
		if (target) {
			for (int i = start + 1; i <= end; i += 2) {
				switch (input[i]) {
				case '&':
					count += recursive(input, true, start, i-1) * recursive(input, true, i+1, end);
					break;
				case '|':
					count += recursive(input, true, start, i-1) * recursive(input, true, i+1, end);
					count += recursive(input, false, start, i-1) * recursive(input, true, i+1, end);
					count += recursive(input, true, start, i-1) * recursive(input, false, i+1, end);
					break;
				case '^':
					count += recursive(input, true, start, i-1) * recursive(input, false, i+1, end);
					count += recursive(input, false, start, i-1) * recursive(input, true, i+1, end);
					break;
				default:
					break;
				}
			}
		} else {
			for (int i = start + 1; i <= end; i += 2) {
				switch (input[i]) {
				case '|':
					count += recursive(input, false, start, i-1) * recursive(input, false, i+1, end);
					break;
				case '&':
					count += recursive(input, false, start, i-1) * recursive(input, false, i+1, end);
					count += recursive(input, false, start, i-1) * recursive(input, true, i+1, end);
					count += recursive(input, true, start, i-1) * recursive(input, false, i+1, end);
					break;
				case '^':
					count += recursive(input, true, start, i-1) * recursive(input, true, i+1, end);
					count += recursive(input, false, start, i-1) * recursive(input, false, i+1, end);
					break;
				default:
					break;
				}
			}
		}

		return count;
	}

	int recursive(string input, bool target) {
		return recursive(input, target, 0, input.size()-1);
	}

	int dp(string input, bool target) {
		int n = input.length()/2 + 1;
		int T_val[n][n];
		int F_val[n][n];

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				T_val[i][j] = 0;
				F_val[i][j] = 0;
			}
		}

		for (int i = 0; i < n; ++i) {
			if (input[2*i] == '1') { T_val[i][i] = 1; }
			else { F_val[i][i] = 1; }
		}

		for (int len = 1; len < n; ++len) {
			for (int i = 0; i+len < n; ++i) {
				// divided into two parts, [i][j] and [j+1][i+len]
				for (int j = i; j < i+len && j < n; ++j) {
					switch (input[2*j+1]) {
					case '&':
						T_val[i][i+len] += T_val[i][j] * T_val[j+1][i+len];

						F_val[i][i+len] += F_val[i][j] * F_val[j+1][i+len];
						F_val[i][i+len] += T_val[i][j] * F_val[j+1][i+len];
						F_val[i][i+len] += F_val[i][j] * T_val[j+1][i+len];
						break;
					case '|':
						T_val[i][i+len] += T_val[i][j] * T_val[j+1][i+len];
						T_val[i][i+len] += T_val[i][j] * F_val[j+1][i+len];
						T_val[i][i+len] += F_val[i][j] * T_val[j+1][i+len];

						F_val[i][i+len] += F_val[i][j] * F_val[j+1][i+len];
						break;
					case '^':
						T_val[i][i+len] += T_val[i][j] * F_val[j+1][i+len];
						T_val[i][i+len] += F_val[i][j] * T_val[j+1][i+len];

						F_val[i][i+len] += T_val[i][j] * T_val[j+1][i+len];
						F_val[i][i+len] += F_val[i][j] * F_val[j+1][i+len];
						break;
					default :
						cout << "invalid input" << endl; 
						return 0;
					}
				}
			}
		}

		cout << "True Table: " << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cout << setw(7) << T_val[i][j] << " ";
			cout << endl;
		}

		cout << "False Table: " << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j)
				cout << setw(7) << F_val[i][j] << " ";
			cout << endl;
		}

		if (target) { return T_val[0][n-1]; }
		else { return F_val[0][n-1]; }
	}
};

int main()
{
	Solution sol;
	string input = "1^0|0|1";
	cout << input << endl;

	cout << sol.dp(input, true) << endl;

	return 0;
}
