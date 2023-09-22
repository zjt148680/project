#include <iostream>
#include<math.h>

using namespace std;

#define N 50

//int main() {
	/*
	目的是为了求出可行解，并在一定程度上最优化

	就是广搜

	剪枝
	1	剪去不符合题意的分支
	2	最小化时，剪去已超出当前已计算出的最小值（即前面到达叶子时的值）的分支
	*/
//}