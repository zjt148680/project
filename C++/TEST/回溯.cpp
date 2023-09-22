#include <iostream>
#include<math.h>
#include<vector>

using namespace std;

#define N 50

/*���Ҳ�����ã��᷵������ֵ
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
	vector<int>& w, vector<int>& v, int c, int n, //����
	vector<bool>& used, int curi, int curV, //��ǰ״̬
	vector<bool>& ans, int& maxV //��¼����
) {
	//used�����е�ĳ���ʱ��ֵ��ǣ��������յĽ��
	//������Ҷ���iȡ������ֵ����Ҷ���j(j��i�ұ�)ʱ��used�ֲ�ͬ
	//����used���ս���ǿ����һ����������е�·��

	//����maxV�Ǽ�¼��ǰ����������Ҷ�ӵ����ֵ���������µĸ���ֵ�����¼��ǰ��used��curV

	if (curi > n || c == 0) {//�����棬c��СΪ0
		//curi>n�ǵ�Ҷ��
		//c==0�Ǽ�֦
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
	//curCountΪ��ǰ������Ŀ

	if (curi > n) {//����
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
		this->M = vector<int>(n+1);//��һ��ʼ���ҳ�ʼ��Ϊ0
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
	bool isBump(int k);//M[k]�Ѿ�����ֵ�������ֵ�Ƿ����
};
bool N_Queen::isBump(int k) {
	for (int i = 1; i < k; i++) {
		if (M[i] == M[k] || abs(M[i] - M[k]) == abs(i - k)) {
			//������
			return true;
		}
	}
	return false;
}
void N_Queen_F(N_Queen& nq, int k) {//����k�еķ��÷�ʽ��kһ��ʼΪ1
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
	��dfs

	ע����μ�¼����ֵ�����Ž�
	��_01BeiBao2�����ַ�ʽ�⣬�����Խ�ans,maxV��Ϊ�ⲿ����������ʹ����Ԫ����
	*/

	
	/*01��������

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
	��������������
	n������S[1...n]��ʹS[i]��S[i+1]����õ��·���S1[1...n-1]����S1��Ϊ�����εڶ���
	�������n��˵���ж��ٲ�ͬ����������ʹ�����Ÿ��Ÿ�����ͬ
	˼·
	n��Ԫ�ص���������Ԫ�ظ���Ϊ1+2+...+n=n*(n+1)/2
	��������+-����n*(n+1)/4�������Դ˺�Ϊ����ʱ�϶�����
	1	��[1][1]�ֱ�Ϊ0��1��������n=1�Ľ��
	2	�ݹ���[1][2]�ֱ�Ϊ0��1���ɴ˿��Եó�[2][1]����õ�n=2�Ľ��
	�ôζԽ��߷ָ�������Ǵ洢��������

	cout<<FuHaoSanJiaoXing(3);
	*/

	/*
	n�ʺ�����
	˼·
	��ʺ��������б��
	��һ���ʺ��ڵ�һ�У���λ��[1][1]��ʱ��
	�ھ�����Ϊ��һ�в����������ʺ����Խ���Ҳ�����������ʺ�
	�������ʾΪ����ʺ�i����ǰ��Ļʺ�����Ϊ[x_k,y_k](k:1->i-1)����yΪ������ֱ�Ӿ������ε��������ÿ��ǣ�
	�������k��x_i!=x_k����ͬ�У���abs(x_i-x_k)!=abs(y_i-y_k)��������ͬһ�Խ��ߣ�
	��Ϊy_k���ε���������ֱ����һά����M[1...n]�洢ͼ��M[j] = i��ʾλ��Ϊ(i,j)

	N_Queen nq = N_Queen(8);
	N_Queen_F(nq, 1);
	cout << nq.getNum() << endl;
	*/

	/*
	ͼ��m����ɫ����
	����
	��ͨͼ�У�ʹ���������������������в�ͬ����ɫ���ж�����ͼ�Ƿ����m����ɫ�����ɫ�����ؿ���ɫ������
	���
	������n�ʺ���������
	*/

	/*
	Բ����������
	n��ԲC[1...n]����뾶Ϊr[1...n]����Բ�������з��ھ����У�ʹ����Բ����εױ߽Ӵ���������ʹ�ܵĳ�����С
	���
	��������r��ȫ���У����жϼ���
	PS
	�ο�ȫ�����㷨�����ݿ�ʵ�֣�
	�Ż�
	��֦
	r������ͬ��ֵ������������ĿҪ����
	���жԳ�����
	�Ż���ʵ�֣�������������������������������������������������
	*/
//}


