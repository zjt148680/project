#include "a2013.h"

using namespace std;

bool _2013f1(string& s) {
	int a = 0, b = 0;
	for (int i = s.length() - 1; i >= 0; i -= 2) {
		a += s[i] - '0';
	}

	cout << s.length()<<" "<<(s.length() <= 6) << "-----" << endl;

	if (s.length() - 2 >= 0)
		b += s[s.length() - 2] - '0';
	if (s.length() - 4 >= 0)
		b += s[s.length() - 4] - '0';
	if (s.length() - 6 >= 0)
		//b += s[s.length() - 6] - '0'; 
	b *= 2;
	b = (b >= 10 && b < 100) ? (b - 9) : b;
	
	return ((a + b) % 10 == 0);
}

bool _2013f2(
	vector<int>& nums,int targetSum,
	int curi, int curSum, 
	vector<int>& choice //存储结果,1:+,2:-,3:*10。直接传入一个空vector即可
) {
	//surSum为当前结果，初始为0
	//curi为当前数字的下标，对应的符号下标就是curi-1.初始为0，0时特殊操作

	if (curi == 0) {//第一个数字直接赋给curSum
		return _2013f2(nums, targetSum, curi+1, curSum + nums[curi], choice);
	}
	else if (curi == nums.size()) {//结束时
		if (curSum == targetSum) {
			cout << nums[0];
			for (int i = 1; i < curi; i++) {
				if (choice[i - 1] == 1) {
					cout << "+";
				}
				else if (choice[i - 1] == 2) {
					cout << "-";
				}
				else {
					;
				}
				cout << nums[i];
			}
			cout << endl;

			return true;
		}
		else {
			return false;
		}
	}
	else {//递归部分
		bool m1,m2,m3;
		//+
		choice.push_back(1);
		m1 = _2013f2(nums, targetSum, curi + 1, curSum + nums[curi], choice);
		choice.pop_back();
		choice.push_back(2);
		m2 = _2013f2(nums, targetSum, curi + 1, curSum - nums[curi], choice);
		choice.pop_back();
		choice.push_back(3);
		m3 = _2013f2(nums, targetSum, curi + 1, curSum*10 + nums[curi], choice);
		choice.pop_back();
		return m1 || m2 || m3;
	}
}




