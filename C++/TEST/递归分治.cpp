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


int ZuiDaZiDuanHe(int a[], int l, int r) {
	if (l == r) {
		return a[l] > 0 ? a[l] : 0;
	}
	int mid = (l + r) / 2;
	int leftSum = ZuiDaZiDuanHe(a, l, mid), rightSum = ZuiDaZiDuanHe(a, mid + 1, r);

	//记录从中间开始往左最大的连续子串和，从中间开始往右最大的连续子串和，最后相加
	int sum3 = 0,k,k1;
	k = k1 = 0;
	for (int i = mid; i >= l; i--) {
		k1 += a[i];
		k = k > k1 ? k : k1;
	}
	sum3 += k;
	k = k1 = 0;
	for (int i = mid+1; i <= r; i++) {
		k1 += a[i];
		k = k > k1 ? k : k1;
	}
	sum3 += k;

	int ans = leftSum > rightSum ? leftSum : rightSum;
	ans = ans > sum3 ? ans : sum3;
	return ans;
}
//int main() {
	/*
	首先明确所有数组的0下标都不用
	*/


	/*
	* 分治法的使用情况
	* 1、大问题可以分为小问题
	* 2、小问题间互斥
	* 3、小问题易于求解
	* 4、小问题结果可以合并成大问题结果
	*/

	/*
	int a[] = {1,2,3,4,5,6,7,9};
	cout << BinarySearch(a, 8, 2);
	*/

	/*
	归并排序、快速排序
	*/

	/*
	int a[] = { 1,2,3 };
	QuanPaiLie1(a, 0, 3);
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
	最大子段和
	找出整数序列中和最大的连续子段，如果段全是负数，则结果为0。
	分治分两段求。
	合并时还需要求出两段连接处的最大结果，需要遍历求。
	int a[7] = { 0,-20,11,-4,13,-5,-2 };
	int n = 6;
	cout<<ZuiDaZiDuanHe(a, 1, n);
	*/
	
	/*
	循环比赛
	对当前矩阵，子问题为一二两个矩阵，解决两个子问题后，
	再第一象限复制到第三象限，第二象限复制到第四象限。
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
		重点是证明合并过程的线性性。
	*/

	/*
	相应还有减治法，即不求解所有子问题，用其中的一个或几个子问题来求解
	比如求a^n，分治法会求两次a^(n/2)，再两个子问题结果相乘。减治法就求一次，直接平方一个子问题的结果。
	再比如折半查找。
	*/
//}