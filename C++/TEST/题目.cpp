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
		//合数
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

class QuanPaiLie {
public:
	QuanPaiLie(int n) {
		this->n = n;
		this->a = new int[n + 1]();
		this->visit = new bool[n + 1]();
		this->ans = new int[n + 1]();

		for (int i = 1; i <= n; i++)
			this->a[i] = i;
	}
	QuanPaiLie(int n, int* a) {
		this->n = n;
		this->a = a;
		this->visit = new bool[n + 1]();
		this->ans = new int[n + 1]();
	}

	void F1(int);//dfs求不含重复元素的全排列
	void F2(int);//另一种实现，见内部注释

	int cmp(void const* a, void const* b) {
		return *(int*)a - *(int*)b;
	}
	void F3(int);//有重复元素的

private:
	int* a;
	int n;

	bool* visit;
	int* ans;
};
void QuanPaiLie::F1(int k) {
	if (k > n) {
		for (int i = 1; i <= n; i++)
			cout << ans[i]<< " ";
		cout << endl;
	}
	for (int i = 1; i <= n; i++) {
		
		if (!visit[i]) {
			visit[i] = true;
			ans[k] = a[i];
			QuanPaiLie::F1(k + 1);
			visit[i] = false;
		}
	}
}
void QuanPaiLie::F2(int k) {
	/*
	a分为两段一段已排好，一段待选择
	每次在未排好的段中选择一元素加入排好的段
	至全部排好

	k为新位置，即当前a[1...k-1]已经排好，对a[k]，依次将a[k...n]放入a[k]，进入下一次选择
	*/
	if (k == n) {
		for (int i = 1; i <= n; i++)
			cout << a[i] << " ";
		cout << endl;
	}
	for (int i = k; i <= n; i++) {
		//a[k], a[i]交换位置，最后再换回来。即相当于做了一次选择，最后输出a
		int r = a[k];
		a[k] = a[i];
		a[i] = r;
		QuanPaiLie::F2(k + 1);
		r = a[k];
		a[k] = a[i];
		a[i] = r;
	}
}
void QuanPaiLie::F3(int k) {
	//先排序
	//qsort(a, n, sizeof(int), cmp);
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
	//QuanPaiLie(3, new int[] {-1, 3, 4, 5}).F2(1);
//}


