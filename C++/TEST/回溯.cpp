#include <iostream>
#include<math.h>
#include<vector>

using namespace std;

#define N 50

/*这个也可以用，会返回最大价值
int _01BeiBao2(
	int* w, int* v, int c, int n,
	bool* used, int curi, int curV,
	bool* ans, int &maxV
) {
	if (curi > n || c == 0) {
		if (curV > maxV) {
			maxV = curV;
			for (int i = 1; i <= n; i++)
				ans[i] = used[i];
		}
		return maxV;
	}
	else {
		if (c >= w[curi]) {
			int a, b;
			used[curi] = true;
			a = _01BeiBao2(w, v, c - w[curi], n, used, curi + 1, curV+v[curi], ans, maxV);
			used[curi] = false;
			b = _01BeiBao2(w, v, c, n, used, curi + 1, curV, ans, maxV);
			if (a > b) {
				used[curi] = true;
				return a;
			}
			else {
				used[curi] = false;
				return b;
			}
		}
		else {
			used[curi] = false;
			return _01BeiBao2(w, v, c, n, used, curi + 1, curV, ans, maxV);
		}
	}
}*/
void _01BeiBao2(
	vector<int>& w, vector<int>& v, int c, int n, //问题
	vector<bool>& used, int curi, int curV, //当前状态
	vector<bool>& ans, int& maxV //记录最优
) {
	//used是运行到某结点时的值标记，不是最终的结果
	//比如在叶结点i取得最优值，在叶结点j(j在i右边)时的used又不同
	//所以used最终结果是看最后一个结点在树中的路径

	//所以maxV是记录当前所有遇到的叶子的最大值，若发现新的更大值，则记录当前的used和curV

	if (curi > n || c == 0) {//看下面，c最小为0
		//curi>n是到叶子
		//c==0是剪枝
		if (curV > maxV) {
			maxV = curV;
			for (int i = 1; i <= n; i++)
				ans[i] = used[i];
		}
		//return;
	}
	else {
		if (c >= w[curi]) {
			int a, b;
			used[curi] = true;
			_01BeiBao2(w, v, c - w[curi], n, used, curi + 1, curV + v[curi], ans, maxV);
			a = maxV;
			used[curi] = false;
			_01BeiBao2(w, v, c, n, used, curi + 1, curV, ans, maxV);
			b = maxV;
			if (a > b) {
				used[curi] = true;
				//return;
			}
			else {
				used[curi] = false;
				//return;
			}
		}
		else {
			used[curi] = false;
			_01BeiBao2(w, v, c, n, used, curi + 1, curV, ans, maxV);
			//return;
		}
	}
}

void FuHaoSanJiaoXing_F1(
	int curi, int curCount,
	vector<vector<int>>& M, int n,
	int& ans
) {
	//curCount为当前正号数目

	if (curi > n) {//最终
		if (curCount == n * (n + 1) / 4) {
			ans++;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++)
					cout << M[i][j] << " ";
				cout << endl;
			}
		}
		cout << endl;
		return;
	}
	else {
		int K = curi + 1;
		int i, j;
		int count;

		for (int sign = 0; sign <= 1; sign++) {
			count = curCount;

			M[1][curi] = sign;
			count += sign;
			for (i = 2; i <= curi; i++) {
				j = K - i;
				M[i][j] = M[i - 1][j] == M[i - 1][j + 1] ? 1 : 0;
				count += M[i][j];
			}
			FuHaoSanJiaoXing_F1(curi + 1, count, M, n, ans);
		}
	}
}
int FuHaoSanJiaoXing(int n) {
	if (n * (n + 1) / 2 % 2 == 1) {
		return 0;
	}
	else {
		vector<vector<int>> M(n+1, vector<int>(n+1));
		int ans = 0;
		FuHaoSanJiaoXing_F1(1, 0, M, n, ans);
		return ans;
	}
}

class N_Queen {
public:
	N_Queen(int n) {
		this->n = n;
		this->M = vector<int>(n+1);//从一开始，且初始化为0
		this->num = 0;
	}
	int getNum() {
		return this->num;
	}
	friend void N_Queen_F(N_Queen&,int);
private:
	vector<int> M;
	int n;
	int num;
	bool isBump(int k);//M[k]已经有了值，看这个值是否合理
};
bool N_Queen::isBump(int k) {
	for (int i = 1; i < k; i++) {
		if (M[i] == M[k] || abs(M[i] - M[k]) == abs(i - k)) {
			//不符合
			return true;
		}
	}
	return false;
}
void N_Queen_F(N_Queen& nq, int k) {//考虑k列的放置方式，k一开始为1
	if (k > nq.n) {
		nq.num++;
		for (int i = 1; i <= nq.n; i++)
			cout << nq.M[i] << " ";
		cout << endl;
		return;
	}
	for (int i = 1; i <= nq.n; i++) {
		nq.M[k] = i;
		if (!nq.isBump(k)) {
			N_Queen_F(nq, k + 1);
		}
	}
}


//int main() {
	/*
	如dfs

	注意如何记录最优值，最优解
	除_01BeiBao2的两种方式外，还可以将ans,maxV设为外部变量，或是使用友元函数
	*/

	
	/*01背包问题

	vector<int> w = { -1,1,2,7,4,6 };
	vector<int> v = { -1,80,100,20,30,70 };
	int c = 7;

	int maxV = -1;
	vector<bool> used(w.size());
	vector<bool> ans(w.size());
	_01BeiBao2(w, v, c, w.size()-1, used, 1, 0, ans, maxV);
	cout << maxV << endl;
	for (int i = 1; i <= w.size() - 1; i++)
		cout << ans[i] << " ";
	cout << endl;
	*/
	
	/*
	符号三角形问题
	n个符号S[1...n]，使S[i]和S[i+1]运算得到新符号S1[1...n-1]，将S1作为三角形第二行
	计算对于n来说，有多少不同符号三角形使得正号负号个数相同
	思路
	n个元素的三角形总元素个数为1+2+...+n=n*(n+1)/2
	所以最终+-各有n*(n+1)/4个，所以此和为奇数时肯定不行
	1	设[1][1]分别为0，1。则计算出n=1的结果
	2	递归设[1][2]分别为0，1；由此可以得出[2][1]。则得到n=2的结果
	用次对角线分割的上三角存储此三角形

	cout<<FuHaoSanJiaoXing(3);
	*/

	/*
	n皇后问题
	思路
	设皇后以所在列编号
	第一个皇后在第一行（即位置[1][1]）时，
	在矩阵中为第一行不能有其他皇后；主对角线也不能有其他皇后
	对坐标表示为任意皇后i，其前面的皇后坐标为[x_k,y_k](k:1->i-1)，（y为列数，直接就是依次递增，不用考虑）
	则对任意k，x_i!=x_k（不同行）且abs(x_i-x_k)!=abs(y_i-y_k)（不处在同一对角线）
	因为y_k依次递增，所以直接用一维数组M[1...n]存储图，M[j] = i表示位置为(i,j)

	N_Queen nq = N_Queen(8);
	N_Queen_F(nq, 1);
	cout << nq.getNum() << endl;
	*/

	/*
	图的m可着色问题
	介绍
	连通图中，使任意边所连的两个顶点具有不同的颜色，判断整个图是否可用m种颜色完成着色，返回可着色方案数
	解决
	与上面n皇后问题类似
	*/

	/*
	圆的排列问题
	n个圆C[1...n]，其半径为r[1...n]，将圆依次排列放在矩形中，使所有圆与矩形底边接触，求排列使总的长度最小
	解决
	就是生成r的全排列，再判断即可
	PS
	参考全排列算法（回溯可实现）
	优化
	剪枝
	r中有相同的值，所以排列数目要减少
	还有对称问题
	优化的实现？？？？？？？？？？？？？？？？？？？？？？？？？
	*/
//}


