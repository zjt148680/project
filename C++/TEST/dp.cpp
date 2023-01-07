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
	//count��ʾ�������
	//���η�
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
	// aΪ������״��1+n+1��Ԫ�أ���Ԫ�ز���;a[i,i+1]��ʾ��i��������״��
	// nΪ���������ansΪ�����R��¼��η���
	// ����1��ʼ

	//����ans[i][i]=0��������������
	for (int i = 1; i <= n; i++)
		ans[i][i] = 0;

	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++)
			ans[i][j] = 0x7fffffff;

	//��ͼ֪�����˳��Ӧ�������Խ��������ƶ������ĸ�Ԫ��
	for (int r = 1; r <= n - 1; r++) {
		for (int i = 1, j = i + r; j <= n; i++, j++) {
			for (int k = i; k + 1 <= j; k++) {
				//A[i...j]��k���ָ�
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
	//�ⲿ��ʼ��ans���Խ�ȫΪ0��������Ϊ0x7fffffff
	if (x == y) {
		return 0;
	}
	int curans;
	for (int k = x; k < y; k++) {
		//������ظ�������ͬ��������
		curans = DiGui(a, n, ans, R, x, k) + DiGui(a, n, ans, R, k + 1, y) + a[x] * a[k + 1] * a[y + 1];
		if (curans < ans[x][y]) {
			ans[x][y] = curans;
			R[x][y] = k;
		}
	}
	return ans[x][y];
}
int BeiWangLu(int* a, int n, int ans[][N], int R[][N], int x, int y, int M[][N]) {
	//��M�洢�Ѿ���������⣬����ֱ�ӷ��ؼ���,M��ʼ��Ϊȫ0
	if (M[x][y] > 0) {
		//�Ѿ�������������⣬ֱ�ӷ���
		return M[x][y];
	}

	//�������͵ݹ��࣬���Ƕ���һ����¼ÿ�εĽ��
	if (x == y) {
		return 0;
	}
	int curans;
	for (int k = x; k < y; k++) {
		//������ظ�������ͬ��������
		curans = DiGui(a, n, ans, R, x, k) + DiGui(a, n, ans, R, k + 1, y) + a[x] * a[k + 1] * a[y + 1];
		if (curans < ans[x][y]) {
			ans[x][y] = curans;
			R[x][y] = k;
		}
	}
	M[x][y] = ans[x][y];//��ǰ������Ľ��

	return ans[x][y];
}

void ZuiChangGongGongZiXuLie(int* a, int m, int* b, int n, int ans[][N]) {
	//ansʹ��[m][n]
	// a b����1��ʼ
	//��ʼ��
	for (int i = 0; i <= m; i++)
		ans[i][0] = 0;
	for (int i = 0; i <= n; i++)
		ans[0][i] = 0;
	//��ͼ�õ�ѭ��д��
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
	//w������v��ֵ��c���أ�n��Ʒ��Ŀ
	//��1��ʼ

	//�������
	for (int i = 1; i <= c; i++) {
		if (i < w[n])//��Ʒn���ܷ�
			ans[n][i] = 0;
		else
			ans[n][i] = v[n];
	}

	//ѭ����
	for (int i = n - 1; i >= 1; i--) {
		for (int j = 1; j <= c; j++) {
			if (j < w[i]) {//i���ܷ�
				ans[i][j] = ans[i + 1][j];
			}
			else
				ans[i][j] = ans[i + 1][j] > ans[i + 1][j - w[i]] + v[i] ? ans[i + 1][j] : ans[i + 1][j - w[i]] + v[i];
		}
	}

	//�����ֻѡ��һ�֣�
	int cc = c;
	for (int i = 1; i < n; i++) {
		if (ans[i][cc] == ans[i + 1][cc])
			R[i] = 0;
		else {
			R[i] = 1;
			cc -= w[i];
		}
	}
	//�����һ��
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
	//p��n����1��ʼ��n��Ϊ��������Ϊֻ�ж�0�Ͷ�2���
	//k%2==1ʱ��ʾҶ��㣬��������

	float M[N][N] = {0};//��¼������Ȩ�������ʡȥ������ѭ��

	//���Խǳ�ʼ��Ϊ��ӦԪ�ظ���
	for (int i = 1; i <= n; i++) {
		ans[i][i] = p[i];
		M[i][i] = p[i];
	}

	//��ͼ��ѭ����
	for (int r = 2; r + 1 <= n; r += 2) {
		for (int i = 1, j = i + r; j <= n; i += 2, j += 2) {

			//�ɼ���˳��(1,3)(3,5)(1,5)
			//�����˼����ÿ������[i...j]��p֮��M[i][j]
			M[i][j] = M[i][j - 2] + p[j - 1] + p[j];

			float curMin = 1e8;
			int curK = 0;
			for (int k = i+1; k <= j; k += 2) {
				//kΪ[i...j]�ָ�㣬������
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
	1	���������Ž�
	2	���η�Ҳ���ԣ����ǿ��ܻ�ʹ��ͬ�������ⱻ�ظ�����
	3	dp�Ǳ�����ÿ���Ѿ�������������������쵱ǰ��ʱ����õ���Щ��
	����
	1	��ʵ����������������ʱ��״̬�����Ƴ���ʱ��Ӧ�����������ⶼ�����ŵ�
		����ֻҪ������ܳ��ֵ���������������Ž⣬�ٽ�����ϲ���ѡ�񣬱�Ȼ��һ��ʹ������������
		�����������ʱ����ʱk�ָ�㹹�ɵ������������ŵģ�
		���Խ���ͬk��Ӧ������������ȫ����Ⲣ�ϲ���ѡ�������ž���ԭ���������
	*/

	/*
	������������
	����
	A(i,j)B(j,k)��Ҫ�������Ϊi*j*k�����Զ���������Ҫ��Ƽ������
	�ⷨ
	1	���η�
		n��������˵ļ�����������JuZhengLianChengZhongLeiShu(n);
		���ǿ����������Ƚϴ���������ȫ�������Ļ��������ܴ�
	2	dp
		1	��"���Ž�ʱ"ʽ����k���Ͽ�����A[1...n]��Ϊ��A[1...k]��a[k+1...n]
			��ans[1,n] = ans[1,k]+ans[k+1,n]+A[1]*A[k]*A[n]
		2	��A[1...k]��a[k+1...n]�ڲ���Ȼ���������е����Ž�
			��������ʱA[1...k]�ڻ����и��õĽⷨ����A[1...n]Ҳ�϶��и��õĽⷨ(��ans[1,k]��С)
			����������ӽṹ����
		3	�г�ʽ��
			1	�����A[i...j]������Ľ�������ڶ�ά����ans[i][j]�У���Ȼi<=j�������ǣ�
			2	��Ŀ������A[1][n]��ֵ
			3	����������
				i==jʱ��ans[i][j]==0;//���ü���
				i<jʱ����������� ans[i][j] = min{ans[i][k]+ans[k+1][j]+A[i]*A[k]*A[j]|i<=k<=j}
		4	����
			1	���Եݹ飬���ܶ�������ᱻ�ظ�����
			2	����ֱ���ö�ά���鱣�������ڼ���ans[1][n]ʱ����������Ľ���ᱻ���棬�´�ֱ���ü���
				���д��ѭ���壿
				��Ϊans[1][n]��Ҫans[1][k]��ans[k+1][n]�Ľ�������Կ϶�������Ƚϼ򵥵�����
				��ͼ������ǰ��֪����Ϣ���������Щ�½������ĳһ�����Ҫ֪����Щ��Ϣ
			3	�ָʽ���棺�����ڸ��������㷨
	//dp�㷨
	int a[] = { -1,30,35,15,5,10,20,25 };
	int n = 6;
	int ans[N][N] = { 0 }, R[N][N] = {0};
	DpJuZhengLianCheng(a, n, ans, R);
	Print2DWithShapeOfMNAndFrom1(ans,n,n);
	Print2DWithShapeOfMNAndFrom1(R,n,n);
	PrintR(R,1,n);

	3	����¼�㷨
		����
		1	dpʱ�Ե����ϣ������������𲽺ϳ�������
		2	����¼���Զ����£��ڵݹ�����б����������������ٴεݹ鵽��������ʱ��ɲ��
		3	�������м�¼�ݹ�������Ѽ������������
	//��ͨ�ݹ��㷨�ͱ���¼�㷨
	int a[] = { -1,30,35,15,5,10,20,25 };
	int n = 6;
	int ans[N][N] = { 0 }, R[N][N] = { 0 }, M[N][N] = { 0 };
	for (int i = 1; i < n; i++)
		for (int j = i+1; j <= n; j++)
			ans[i][j] = 0x7fffffff;
	//��ͨ�ݹ�
	DiGui(a, n, ans, R, 1, n);
	//����¼
	BeiWangLu(a, n, ans, R, 1, n, M);


	4	dp�ͱ���¼
		1	dp�Ե����ϣ��Ƚ������⡣����¼�Զ����£��ݹ���Ҽ�¼�����������ٵ�������ʱֱ�ӷ���
		2	dp�������������⣬����¼�����㲻��Ҫ��������
	*/

	/*
	�����������
	1	A[1...n]���������е��±��ǵ����ģ�����A[1,4,7,10,50]
	2	��A[1...n]��B[1...m]�������������Z[1...k]
	˼·���ɴ�����ת��С���⣩
	1	�������ս�
	2	��A[n]==B[m]����Z[k]==A[n]==B[m]������Z[1...k-1]��A[1...n-1]��B[1...m-1]�������������
		��A[n]!=B[m],Z[k]==B[m]����Z[1...k]��A[1...n-1]��B[1...m]�������������
		��A[n]!=B[m],Z[k]==A[n]����Z[1...k]��A[1...n]��B[1...m-1]�������������
		��A[n]��B[m]��Z[k]����ͬ����Z[1...k]��A[1...n-1]��B[1...m-1]�������������
	3	��ͼ������ans[n][m]��Ҫ��Щ�⣻��֪��ǰ����������Щ��
	4	���Ǽ��������һ����Ϊ0����𰸶���0
	5	������δ洢���
		1	��������
		2	��ΪansԪ�ؼ���ֱ�ӵ��ڵģ���û������������㣬���Կ�����ͼ�����ҵ�ǰֵ�����ĸ�ֵ�õ��ģ�
			�ɴ˿����ҵ����У�ע��ֵͬ�����������

	int a[12] = { -1,1,1,2,4,5,6,8,9,11,20,0 };
	int b[8] = { -1,1,1,2,5,6,0,0 };
	int m = 11, n = 7;//������ֵ����
	int ans[N][N] = { 0 };
	ZuiChangGongGongZiXuLie(a, m, b, n, ans);
	cout << ans[m][n] << endl;
	*/

	/*
	����Ӷκ�
	���壺�������������������еĺ���󣬵���������Ϊ����ʱ�������Ϊ0
	1	���η�
		������
		������֮�䣬��������Ӵ�����׺���ֵ�������Ӵ�����׺���ֵ���������ɣ����Ը��Ӷ�ΪO(n)
		�����ܸ��Ӷ�O(nlogn)
	2	dp
		˼·����С����ת�������⣩
		�������ӽṹ���ʣ�����������������������������������
	*/

	/*
	͹������������Ƿָ�����
	����
	͹n���ο��Ի���Ϊ�����غϵ������Σ����һ��f(x)���Ա����������εĸ��ߣ�Ӧ������һ������
	����������ε��ܳ����򻮷�Ŀ����ʹ���������ܳ�����С
	͹n���ζ���Ϊ����˳ʱ��˳��Ϊ{v0,v1,v2,...vn-1,vn}������vn=v0
	˼·
	��;���������������ƣ����������γɶ�����
	���������Խ��߿���Ҷ�ڵ㣬ÿ���ָ��߶����������ĸ��ڵ㣬��;���������ͬ��������
	*/

	/*
	01����
	����
	n����Ʒk����ֵΪv[1...n]������Ϊw[1...n]���������Ϊc�Ĵ����У�����뷽ʽʹ��ֵ���
	˼·
	1	������ʱ�ķ��뷽ʽΪy[1...n]��y[i]=1��ʾi��Ʒ���룬y[i]=0��ʾi��Ʒ������
	2	��y[2...n]��c1=c-w[1]*y[1]ʱ�����Ž�
		֤����
		�������⻹���ڸ��Ž�z[2...n]
		��sum(z[i]*v[i])>sum(y[i]*v[i])��sum(z[i]*w[i])<=c-w[1]*y[1]������i>=2
		��{y[1],z[2],z[3]...z[n]}��ԭ����ĸ��Ž⣬ì��
	����ʽ
	1	ԭ������k[1...n],c����������k[2...n],c-w[1]*y[1]
		������״̬����m[i][j]����ʾk[i...n]�������Ϊj�Ĵ��ӵ�����ֵ
	2	���Ǽ��������ֻ��һ����Ʒ����w[1]>c�������Ʒ�޷����룬��Ȼ���Է���
	3	�ɼ������
		m[n][j] = v[n]	j>=w[n]
				= 0		j<w[n]
		�ձ����
		m[i][j] = max(m[i+1][j],m[i+1][j-w[i]]+v[i]) //����i�򲻷���
				= m[i+1][j]	//i�޷����룬��j<w[i]
	4	��ͼдѭ��
	�Ż�
	1	��������������������������С������
	2	���ǵ�M[i]����M[i+1]�ǽ����ͣ��ɼ�¼���ݵı�־�����������С��
	3	ʵ�֣���������������������������������������������������������������������������

	//δ�Ż�01����
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
	���Ŷ���������
	����
	1	����������Ҷ�ڵ�Ϊʧ�ܽڵ�
	2	���������������������ΪA[1...n](��{(-inf,0),0,(0,1),1,(1,2),2,(2,inf)})�����нڵ���Ҹ�������ΪP[1...n]
	3	������ʹƽ�����ҳ�����С
	˼·
	���Ż��֣�ע��Ԫ�ؽ��ſ������ն˽��
	�Ż�
	ע�⵽�ϲ�ʱ����[i...j]��[j+2...k]ʱ�����������ӵ�һ���£�
	��������ֵ=ֵ[i][j]+sum(p[i...j])+ֵ[j+2][k]+sum(p[j+2][k])+p[j+1]
				=ֵ[i][j]+ֵ[j+2][k]+sum(p[i...k])
	���Կ��Ǽ��������sum(p[r1...r2])����
	������Լ���������M�Ĵ���

	int n = 11;
	float p[] = { -1,0.05,0.15,0.1,0.1,0.05,0.05,0.05,0.1,0.05,0.2,0.1 };
	float ans[N][N] = { 0 };
	int R[N][N] = { 0 };
	ZuiYouErChaShu(p, n, ans, R);
	Print2DWithShapeOfMNAndFrom1(ans, n, n);
	Print2DWithShapeOfMNAndFrom1(R, n, n);
	*/

}