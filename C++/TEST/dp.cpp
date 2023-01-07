#include <iostream>
#include<math.h>

#define N 100

using namespace std;


template <typename T>
void Print2DWithShapeOfMNAndFrom1(T a[][N], int m, int n) {
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}



int JuZhengLianChengZhongLeiShu(int count) {
	//count表示矩阵个数
	//分治法
	if (count == 1) {
		return 1;
	}
	int ans = 0;
	for (int i = 1; i < count; i++) {
		ans += JuZhengLianChengZhongLeiShu(i) * JuZhengLianChengZhongLeiShu(count - i);
	}
	return ans;
}

void DpJuZhengLianCheng(int* a, int n, int ans[][N], int R[][N]) {
	// a为矩阵形状（1+n+1个元素，首元素不用;a[i,i+1]表示第i个矩阵形状）
	// n为矩阵个数，ans为结果，R记录如何分配
	// 都从1开始

	//设置ans[i][i]=0，单个矩阵不用算
	for (int i = 1; i <= n; i++)
		ans[i][i] = 0;

	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++)
			ans[i][j] = 0x7fffffff;

	//画图知，求解顺序应该是主对角线逐步上移而经过的各元素
	for (int r = 1; r <= n - 1; r++) {
		for (int i = 1, j = i + r; j <= n; i++, j++) {
			for (int k = i; k + 1 <= j; k++) {
				//A[i...j]在k处分割
				if (ans[i][j] > (ans[i][k] + ans[k + 1][j] + a[i] * a[k + 1] * a[j + 1])) {
					ans[i][j] = ans[i][k] + ans[k + 1][j] + a[i] * a[k + 1] * a[j + 1];
					R[i][j] = k;
				}
			}
		}
	}
}
void PrintR(int R[][N], int a, int b) {
	if (a == b) {
		cout << a;
		return;
	}
	else {
		cout << "(";
		PrintR(R, a, R[a][b]);
		PrintR(R, R[a][b] + 1, b);
		cout << ")";
	}
}

int DiGui(int* a, int n, int ans[][N], int R[][N], int x, int y) {
	//外部初始化ans主对角全为0，上三角为0x7fffffff
	if (x == y) {
		return 0;
	}
	int curans;
	for (int k = x; k < y; k++) {
		//这里会重复计算多次同样的问题
		curans = DiGui(a, n, ans, R, x, k) + DiGui(a, n, ans, R, k + 1, y) + a[x] * a[k + 1] * a[y + 1];
		if (curans < ans[x][y]) {
			ans[x][y] = curans;
			R[x][y] = k;
		}
	}
	return ans[x][y];
}
int BeiWangLu(int* a, int n, int ans[][N], int R[][N], int x, int y, int M[][N]) {
	//用M存储已经算过的问题，遇到直接返回即可,M初始化为全0
	if (M[x][y] > 0) {
		//已经计算过的子问题，直接返回
		return M[x][y];
	}

	//接下来和递归差不多，但是多了一个记录每次的结果
	if (x == y) {
		return 0;
	}
	int curans;
	for (int k = x; k < y; k++) {
		//这里会重复计算多次同样的问题
		curans = DiGui(a, n, ans, R, x, k) + DiGui(a, n, ans, R, k + 1, y) + a[x] * a[k + 1] * a[y + 1];
		if (curans < ans[x][y]) {
			ans[x][y] = curans;
			R[x][y] = k;
		}
	}
	M[x][y] = ans[x][y];//当前子问题的结果

	return ans[x][y];
}

void ZuiChangGongGongZiXuLie(int* a, int m, int* b, int n, int ans[][N]) {
	//ans使用[m][n]
	// a b均从1开始
	//初始化
	for (int i = 0; i <= m; i++)
		ans[i][0] = 0;
	for (int i = 0; i <= n; i++)
		ans[0][i] = 0;
	//画图得到循环写法
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (a[i] == b[j]) {
				ans[i][j] = ans[i - 1][j - 1] + 1;
			}
			else {
				ans[i][j] = ans[i][j - 1] > ans[i - 1][j] ? ans[i][j - 1] : ans[i - 1][j];
			}
		}
	}
}

void _01BeiBao(int* w, int* v, int c, int n, int ans[][N], int* R) {
	//w重量，v价值，c承重，n物品数目
	//从1开始

	//极端情况
	for (int i = 1; i <= c; i++) {
		if (i < w[n])//物品n不能放
			ans[n][i] = 0;
		else
			ans[n][i] = v[n];
	}

	//循环体
	for (int i = n - 1; i >= 1; i--) {
		for (int j = 1; j <= c; j++) {
			if (j < w[i]) {//i不能放
				ans[i][j] = ans[i + 1][j];
			}
			else
				ans[i][j] = ans[i + 1][j] > ans[i + 1][j - w[i]] + v[i] ? ans[i + 1][j] : ans[i + 1][j - w[i]] + v[i];
		}
	}

	//结果（只选择一种）
	int cc = c;
	for (int i = 1; i < n; i++) {
		if (ans[i][cc] == ans[i + 1][cc])
			R[i] = 0;
		else {
			R[i] = 1;
			cc -= w[i];
		}
	}
	//看最后一个
	if (cc == 0) {
		R[n] = 0;
	}
	else {
		if (ans[n][cc] == 0)
			R[n] = 0;
		else
			R[n] = 1;
	}
}

void ZuiYouErChaShu(float* p, int n, float ans[][N], int R[][N]) {
	//p长n，从1开始；n必为奇数，因为只有度0和度2结点
	//k%2==1时表示叶结点，否则根结点

	float M[N][N] = {0};//记录各子树权，则可以省去第四重循环

	//主对角初始化为对应元素概率
	for (int i = 1; i <= n; i++) {
		ans[i][i] = p[i];
		M[i][i] = p[i];
	}

	//画图得循环体
	for (int r = 2; r + 1 <= n; r += 2) {
		for (int i = 1, j = i + r; j <= n; i += 2, j += 2) {

			//由计算顺序(1,3)(3,5)(1,5)
			//可依此计算出每棵子树[i...j]的p之和M[i][j]
			M[i][j] = M[i][j - 2] + p[j - 1] + p[j];

			float curMin = 1e8;
			int curK = 0;
			for (int k = i+1; k <= j; k += 2) {
				//k为[i...j]分割点，即树根
				if (curMin > M[i][j] + ans[i][k - 1] + ans[k + 1][j]) {
					curMin = M[i][j] + ans[i][k - 1] + ans[k + 1][j];
					curK = k;
				}
			}
			ans[i][j] = curMin;
			R[i][j] = curK;
		}
	}
}




int main() {
	/*
	dp
	1	适于求最优解
	2	分治法也可以，但是可能会使相同的子问题被重复计算
	3	dp是保存了每个已经解出的子问题结果，构造当前解时便可用到这些解
	理解
	1	其实就是由主问题最优时的状态可以推出此时对应的所有子问题都是最优的
		所以只要求出可能出现的所有子问题的最优解，再将结果合并后选择，必然有一个使得主问题最优
		比如矩阵连乘时最优时k分割点构成的子问题是最优的，
		所以将不同k对应的最优子问题全部求解并合并后选出的最优就是原问题的最优
	*/

	/*
	矩阵连乘问题
	介绍
	A(i,j)B(j,k)需要计算次数为i*j*k，所以多个矩阵相乘要设计计算次序
	解法
	1	分治法
		n个矩阵相乘的计算次序个数：JuZhengLianChengZhongLeiShu(n);
		这是卡特兰数，比较大，所以若是全部遍历的话数量级很大
	2	dp
		1	设"最优解时"式子在k处断开，即A[1...n]分为了A[1...k]、a[k+1...n]
			则ans[1,n] = ans[1,k]+ans[k+1,n]+A[1]*A[k]*A[n]
		2	则A[1...k]、a[k+1...n]内部必然是其子序列的最优解
			否则若此时A[1...k]内还能有更好的解法，则A[1...n]也肯定有更好的解法(即ans[1,k]更小)
			这就是最优子结构性质
		3	列出式子
			1	上面的A[i...j]子问题的结果保存在二维矩阵ans[i][j]中（显然i<=j，上三角）
			2	则目标是求A[1][n]的值
			3	考虑最简情况
				i==j时，ans[i][j]==0;//不用计算
				i<j时，由上面分析 ans[i][j] = min{ans[i][k]+ans[k+1][j]+A[i]*A[k]*A[j]|i<=k<=j}
		4	程序
			1	可以递归，但很多子问题会被重复计算
			2	所以直接用二维数组保存结果，在计算ans[1][n]时计算子问题的结果会被保存，下次直接用即可
				如何写出循环体？
				因为ans[1][n]需要ans[1][k]、ans[k+1][n]的结果，所以肯定是先求比较简单的问题
				画图，看当前已知的信息可以求出哪些新结果；看某一结果需要知道哪些信息
			3	分割方式保存：类似于弗洛伊德算法
	//dp算法
	int a[] = { -1,30,35,15,5,10,20,25 };
	int n = 6;
	int ans[N][N] = { 0 }, R[N][N] = {0};
	DpJuZhengLianCheng(a, n, ans, R);
	Print2DWithShapeOfMNAndFrom1(ans,n,n);
	Print2DWithShapeOfMNAndFrom1(R,n,n);
	PrintR(R,1,n);

	3	备忘录算法
		介绍
		1	dp时自底向上，即由子问题逐步合成主问题
		2	备忘录是自顶向下，在递归过程中保存子问题结果，当再次递归到此子问题时便可查表
		3	就是自行记录递归过程中已计算过的子问题
	//普通递归算法和备忘录算法
	int a[] = { -1,30,35,15,5,10,20,25 };
	int n = 6;
	int ans[N][N] = { 0 }, R[N][N] = { 0 }, M[N][N] = { 0 };
	for (int i = 1; i < n; i++)
		for (int j = i+1; j <= n; j++)
			ans[i][j] = 0x7fffffff;
	//普通递归
	DiGui(a, n, ans, R, 1, n);
	//备忘录
	BeiWangLu(a, n, ans, R, 1, n, M);


	4	dp和备忘录
		1	dp自底向上，先解子问题。备忘录自顶向下，递归而且记录子问题结果，再到子问题时直接返回
		2	dp会解出所有子问题，备忘录不计算不需要的子问题
	*/

	/*
	最长公共子序列
	1	A[1...n]的子序列中的下标是递增的，比如A[1,4,7,10,50]
	2	求A[1...n]和B[1...m]的最长公共子序列Z[1...k]
	思路（由大问题转到小问题）
	1	考虑最终解
	2	若A[n]==B[m]，则Z[k]==A[n]==B[m]，所以Z[1...k-1]是A[1...n-1]和B[1...m-1]的最长公共子序列
		若A[n]!=B[m],Z[k]==B[m]，则Z[1...k]是A[1...n-1]和B[1...m]的最长公共子序列
		若A[n]!=B[m],Z[k]==A[n]，则Z[1...k]是A[1...n]和B[1...m-1]的最长公共子序列
		若A[n]、B[m]、Z[k]都不同，则Z[1...k]是A[1...n-1]和B[1...m-1]的最长公共子序列
	3	画图，看求ans[n][m]需要哪些解；已知当前解可以求出哪些解
	4	考虑极端情况，一个长为0，则答案都是0
	5	考虑如何存储结果
		1	弗洛伊德
		2	因为ans元素间是直接等于的，而没有作额外的运算，所以可以由图反向找当前值是由哪个值得到的，
			由此可以找到序列，注意同值产生多个序列

	int a[12] = { -1,1,1,2,4,5,6,8,9,11,20,0 };
	int b[8] = { -1,1,1,2,5,6,0,0 };
	int m = 11, n = 7;//有意义值个数
	int ans[N][N] = { 0 };
	ZuiChangGongGongZiXuLie(a, m, b, n, ans);
	cout << ans[m][n] << endl;
	*/

	/*
	最大子段和
	定义：整数序列中连续子序列的和最大，当所有数都为负数时结果定义为0
	1	分治法
		两个串
		若是在之间，则求出左子串的右缀最大值加上右子串的左缀最大值，遍历即可，所以复杂度为O(n)
		所以总复杂度O(nlogn)
	2	dp
		思路（由小问题转到大问题）
		有最优子结构性质？？？？？？？？？？？？？？？？？？
	*/

	/*
	凸多边形最优三角分割问题
	定义
	凸n边形可以划分为各不重合的三角形，设计一个f(x)，自变量是三角形的各边，应变量是一个数。
	比如各三角形的周长。则划分目标是使各三角形周长和最小
	凸n边形定义为各点顺时针顺序为{v0,v1,v2,...vn-1,vn}，其中vn=v0
	思路
	其和矩阵连乘问题很相似，矩阵连乘形成二叉树
	这个问题可以将边看作叶节点，每个分割线都是两个结点的父节点，则和矩阵连乘是同样的问题
	*/

	/*
	01背包
	介绍
	n个物品k，价值为v[1...n]，重量为w[1...n]，放入承重为c的袋子中，求放入方式使价值最高
	思路
	1	设最优时的放入方式为y[1...n]，y[i]=1表示i物品放入，y[i]=0表示i物品不放入
	2	则y[2...n]是c1=c-w[1]*y[1]时的最优解
		证明：
		若新问题还存在更优解z[2...n]
		则sum(z[i]*v[i])>sum(y[i]*v[i])，sum(z[i]*w[i])<=c-w[1]*y[1]。其中i>=2
		即{y[1],z[2],z[3]...z[n]}是原问题的更优解，矛盾
	递推式
	1	原问题是k[1...n],c；子问题是k[2...n],c-w[1]*y[1]
		所以设状态矩阵m[i][j]，表示k[i...n]放入承重为j的袋子的最大价值
	2	考虑极端情况：只有一个物品。若w[1]>c，则此物品无法放入，不然可以放入
	3	由极端情况
		m[n][j] = v[n]	j>=w[n]
				= 0		j<w[n]
		普遍情况
		m[i][j] = max(m[i+1][j],m[i+1][j-w[i]]+v[i]) //放入i或不放入
				= m[i+1][j]	//i无法放入，即j<w[i]
	4	画图写循环
	优化
	1	上面重量必须是整数，重量是小数则不行
	2	考虑到M[i]关于M[i+1]是阶梯型，可记录阶梯的标志，则可适用于小数
	3	实现？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？？

	//未优化01背包
	int n = 5, c = 7;
	int w[] = { -1,1,2,7,4,6 };
	int v[] = { -1,80,100,20,30,70 };
	int ans[N][N] = {0};
	int *R = new int[n+1];
	_01BeiBao(w, v, c, n, ans, R);
	cout << ans[1][c] << endl;
	for (int i = 1; i <= n; i++)
		cout << R[i] << " ";
	cout << endl;
	*/

	/*
	最优二叉搜索树
	问题
	1	搜索树中设叶节点为失败节点
	2	设整棵树按中序遍历序列为A[1...n](如{(-inf,0),0,(0,1),1,(1,2),2,(2,inf)})，其中节点查找概率序列为P[1...n]
	3	求树，使平均查找长度最小
	思路
	最优划分，注意元素结点才可做非终端结点
	优化
	注意到合并时子树[i...j]、[j+2...k]时，将他们连接到一根下，
	则新树的值=值[i][j]+sum(p[i...j])+值[j+2][k]+sum(p[j+2][k])+p[j+1]
				=值[i][j]+值[j+2][k]+sum(p[i...k])
	所以考虑计算出所有sum(p[r1...r2])保存
	具体策略见函数体内M的处理

	int n = 11;
	float p[] = { -1,0.05,0.15,0.1,0.1,0.05,0.05,0.05,0.1,0.05,0.2,0.1 };
	float ans[N][N] = { 0 };
	int R[N][N] = { 0 };
	ZuiYouErChaShu(p, n, ans, R);
	Print2DWithShapeOfMNAndFrom1(ans, n, n);
	Print2DWithShapeOfMNAndFrom1(R, n, n);
	*/

}