#include <iostream>
#include<math.h>

using namespace std;

void F1(int* a, int n, int k) {
	//找最接近所查数的两个下标，相同则返回找到的下标
	//a升序
	int left = 0, right = n - 1, mid;
	int ans;
	bool find = false;
	while (left <= right) {
		mid = (left + right) / 2;
		if (a[mid] == k) {
			ans = mid;
			find = true;
			break;
		}
		else if (a[mid] < k) {
			left = mid + 1;
			ans = mid;
		}
		else {
			right = mid - 1;
			ans = mid-1;
		}
	}
	if (find) {
		cout << ans << endl;
	}
	else {
		if(ans==n-1)
			cout << ans << endl;
		else
			cout << ans << "," << ans + 1 << endl;
	}
}

bool IsPrim(unsigned int x) {
	if (x == 1)
		return false;
	for (int i = 2; i <= sqrt(x); i++)
		if (x % i == 0)
			return false;
	return true;
}
int F2(int x) {
	//返回x的分解式个数
	//比如12=2*6=6*2=3*4=4*3=2*2*3=2*3*2=3*2*2，共8个
	if (x==1 || IsPrim(x)) {
		return 1;
	}
	else {
		//和数
		int count = 1;//x*1
		for (int i = 2; i <= sqrt(x); i++) {
			if (x % i == 0) {
				if (i == x / i) count += F2(i);
				else count += F2(i) + F2(x / i);
			}
		}
		return count;
	}
}

int F3(int count) {
	//集合划分数目
	if (count == 0 || count == 1) {
		return 1;
	}
	else {
		int ans=1;//本身和空集的划分
		for (int i = 1; i < count; i++)
			ans += F3(i) * F3(count - i);
		return ans;
	}
}

//int main() {
	/*
	int a[5] = { 1,3,6,8,10 };
	F1(a, 5, 11);
	*/

	/*
	int n;
	while (1) {
		cin >> n;
		cout << F2(n) << endl;
	}
	*/

	/*
	int n;
	while (1) {
		cin >> n;
		cout << F3(n) << endl;
	}
	*/
//}


