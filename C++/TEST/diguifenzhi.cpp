#include <iostream>
#include<math.h>

using namespace std;

int BinarySearch(int* a, int n, int x) {
	//升序数组中找x对应下标
	int left = 0, right = n - 1, mid;
	while (left <= right) {
		mid = (left + right) / 2;
		if (a[mid] == x) return mid;
		else if (a[mid] > x) right = mid - 1;
		else left = mid + 1;
	}
	return -1;
}


void  swap(int& a, int& b) {
	int c = a;
	a = b;
	b = c;
}
void QuanPaiLie1(int* a, int n, int m) {
	if (n == m) {
		for (int i = 0; i < m; i++)
			cout << a[i] << " ";
		cout << endl;
	}
	else {
		for (int i = n; i < m; i++) {
			swap(a[n], a[i]);
			QuanPaiLie1(a, n + 1, m);
			swap(a[n], a[i]);
		}
	}
}


void FuGaiQiPan(int qiPan[][100], int k, int left, int right, int up,int down,int x, int y) {
	//从1开始;k为当前子盘大小;x,y为此盘已经填充了的块
	if (k == 0) {
		//处理完，结束
		return;
	}
	int t = pow(2, k - 1);
	//新的四块棋盘为
	int left1 = left + t, right1 = right, up1 = up, down1 = down - t;//第一象限
	int left2 = left, right2 = right - t, up2 = up, down2 = down - t;//第二象限
	int left3 = left, right3 = right - t, up3 = up + t, down3 = down;//第三象限
	int left4 = left + t, right4 = right, up4 = up + t, down4 = down;//第四象限
	if (left1 <= x && down1 >= y) {
		//填充块在第一象限
		qiPan[right2][down2] = 1;
		qiPan[right3][up3] = 1;
		qiPan[left4][up4] = 1;
		FuGaiQiPan(qiPan, k - 1, left1, right1, up1, down1, x, y);
		FuGaiQiPan(qiPan, k - 1, left2, right2, up2, down2, right2, down2);
		FuGaiQiPan(qiPan, k - 1, left3, right3, up3, down3, right3, up3);
		FuGaiQiPan(qiPan, k - 1, left4, right4, up4, down4, left4, up4);
	}
	else if (right2 >= x && down2 >= y) {
		//在第二象限
		qiPan[left1][down1] = 2;
		qiPan[right3][up3] = 2;
		qiPan[left4][up4] = 2;
		FuGaiQiPan(qiPan, k - 1, left1, right1, up1, down1, left1, down1);
		FuGaiQiPan(qiPan, k - 1, left2, right2,  up2, down2, x, y);
		FuGaiQiPan(qiPan, k - 1, left3, right3, up3, down3, right3, up3);
		FuGaiQiPan(qiPan, k - 1, left4, right4, up4, down4, left4, up4);
	}
	else if (right3 >= x && up3 <= y) {
		//在第三象限
		qiPan[left1][down1] = 3;
		qiPan[right2][down2] = 3;
		qiPan[left4][up4] = 3;
		FuGaiQiPan(qiPan, k - 1, left1, right1, up1, down1, left1, down1);
		FuGaiQiPan(qiPan, k - 1, left2, right2, up2, down2, right2, down2);
		FuGaiQiPan(qiPan, k - 1, left3, right3, up3, down3, x, y);
		FuGaiQiPan(qiPan, k - 1, left4, right4, up4, down4, left4, up4);
	}
	else {
		//在第四象限
		qiPan[left1][down1] = 4;
		qiPan[right2][down2] = 4;
		qiPan[right3][up3] = 4;
		FuGaiQiPan(qiPan, k - 1, left1, right1, up1, down1, left1, down1);
		FuGaiQiPan(qiPan, k - 1, left2, right2, up2, down2, right2, down2);
		FuGaiQiPan(qiPan, k - 1, left3, right3, up3, down3, right3, up3);
		FuGaiQiPan(qiPan, k - 1, left4, right4, up4, down4, x, y);
	}

}

//int main() {
	/*
	int a[] = {1,2,3,4,5,6,7,9};
	cout << BinarySearch(a, 8, 2);
	*/

	//复杂的递归需要列出关系式，即P(m,n)用P(m-i,n-j)表示，即降级；再考虑最简单的情况
	/*
	int a[] = { 1,2,3 };
	QuanPaiLie1(a, 0, 3);
	*/



	//分治法
	/*
	理解：将大问题分解为小问题的结果的组合运算，小问题运算方式与大问题一样

	1	算法复杂度一般是O(nlogn),遇到的话考虑分治法
	2	如何分使子问题相同形式、如何合并子问题结果
	3	合理划分使整个问题可以为T(n)=T(n/2)+K
		合理地合并子问题结果可以使K为O(n)
		由此得到O(nlogn )
	*/

	/*
	大整数乘法
	思路
	1	A分为(a1,a2)等长两段，B也是如此
	2	则A = a1*10^(n/2)+a2,B = b1*10^(m/2)+b2
	3	A*B = a1*b1*10^((n+m)/2)+a1*b2**10^(n/2)+a2*b1*10^(m/2)+a2*b2
	4	则可以用分治法
	5	还可以再化简减少乘法次数，最终可以实现数量级减少
	6	还可以分三段
	*/

	/*
	矩阵乘法
	1	分块算并不能降低复杂度
	2	考虑减少乘法次数才行，用一些技巧可以减少乘法次数
	*/

	/*
	棋盘覆盖
	介绍
	2^k*2^k的棋盘由一特殊格，用面积为3的直角型方块填满棋盘
	思路
	分为四块，将一直角型方块放入中心，使其覆盖三个没有包含特殊块的子块，则可以分治解决
	
	int qiPan[100][100] = { 0 };
	int k = 4;
	int x = 10, y = 10;//初始覆盖块位置
	qiPan[x][y] = 5;
	
	FuGaiQiPan(qiPan, k, 1, pow(2, k), 1, pow(2, k), x, y);

	for (int i = 1; i <= pow(2, k); i++) {
		for (int j = 1; j <= pow(2, k); j++)
			cout << qiPan[i][j] << " ";
		cout << endl;
	}
	*/

	/*
	找第k小元素
	1	堆排序
	2	利用快排中基元素放在最后位置后比前面都大，比后面都小，也可以找到
	*/

	/*
	一维数组最近点对
	1	可证明下界复杂度为O(nlogn)。考虑分治法
	2	排序O(nlogn)
		选择合适的点分割，为了平衡，选择离中位数最近的点。
		两个子点集内部最小距离可以分治得出，但还可能出现最近点对两点分别在两个子点集中
		如果上述情况成立，找左最大值，右最小值即可
		综合比较可得出结果
		平衡划分的复杂度也是O(nlogn)，而合并结果的复杂度不高于此，所以综合为O(nlogn)
	上述思路可以推广至平面最近点对
		重点是证明合并过程的线性性，即K为O(n)
	*/
//}