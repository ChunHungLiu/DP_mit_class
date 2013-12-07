#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
using namespace std;

/*
Box Stacking. You are given a set of n types of rectangular 3-D boxes, where the i^th box has height h(i), width w(i) and depth d(i) (all real numbers). You want to create a stack of boxes which is as tall as possible, but you can only stack a box on top of another box if the dimensions of the 2-D base of the lower box are each strictly larger than those of the 2-D base of the higher box. Of course, you can rotate a box so that any side functions as its base. It is also allowable to use multiple instances of the same type of box.
*/

struct Box {
	int h, w, d;
};

int compare(const void *a, const void *b) {
	return (*(Box *)b).w * (*(Box *)b).d - (*(Box *)a).w * (*(Box *)a).d;
}

class Solution {
public:
	int dp(Box data[], int n) {
		// rotate the box to three dimentions;
		Box input[3*n];
		int idx = 0;
		for (int i = 0; i < n; ++i) {
			input[3*i].h = data[i].h;
			input[3*i].w = max(data[i].d, data[i].w); 
			input[3*i].d = min(data[i].d, data[i].w); 

			input[3*i+1].h = data[i].w; 
			input[3*i+1].w = max(data[i].d, data[i].h); 
			input[3*i+1].d = min(data[i].d, data[i].h); 
			
			input[3*i+2].h = data[i].d; 
			input[3*i+2].w = max(data[i].w, data[i].h); 
			input[3*i+2].d = min(data[i].w, data[i].h); 
		}

		// sort the input by base area
		qsort(input, n*3, sizeof(input[0]), compare);

		cout << "input: ";
		for (int i = 0; i < 3*n; ++i) {
			cout << "(" << input[i].h << " " << input[i].w << " " << input[i].d << ")" << " ";
		}
		cout << endl;

		int dp[3*n];

		for (int i = 0; i < 3*n; ++i)
			dp[i] = input[i].h;

		int res = INT_MIN;
		for (int i = 1; i < 3*n; ++i) {
			for (int j = 0; j < i; ++j) {
				if (input[i].w < input[j].w && 
					input[i].d < input[j].d) {
					dp[i] = max(dp[i], dp[j] + input[i].h);
				}
				res = max(res, dp[i]);
			}
		}

		cout << "the table: ";
		for (int i = 0; i < 3*n; ++i)
			cout << dp[i] << " ";
		cout << endl;

		return res;
	}
};

int main()
{
	Solution sol;
	Box data[] = { {4,6,7}, {1,2,3}, {4,5,6}, {10,12,32} };
	int n = sizeof(data)/sizeof(data[0]);

	cout << sol.dp(data, n) << endl;

	return 0;
}
