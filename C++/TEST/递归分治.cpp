#include <iostream>
#include<math.h>

using namespace std;

int BinarySearch(int* a, int n, int x) {
	//������������x��Ӧ�±�
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
	//��1��ʼ;kΪ��ǰ���̴�С;x,yΪ�����Ѿ�����˵Ŀ�
	if (k == 0) {
		//�����꣬����
		return;
	}
	int t = pow(2, k - 1);
	//�µ��Ŀ�����Ϊ
	int left1 = left + t, right1 = right, up1 = up, down1 = down - t;//��һ����
	int left2 = left, right2 = right - t, up2 = up, down2 = down - t;//�ڶ�����
	int left3 = left, right3 = right - t, up3 = up + t, down3 = down;//��������
	int left4 = left + t, right4 = right, up4 = up + t, down4 = down;//��������
	if (left1 <= x && down1 >= y) {
		//�����ڵ�һ����
		qiPan[right2][down2] = 1;
		qiPan[right3][up3] = 1;
		qiPan[left4][up4] = 1;
		FuGaiQiPan(qiPan, k - 1, left1, right1, up1, down1, x, y);
		FuGaiQiPan(qiPan, k - 1, left2, right2, up2, down2, right2, down2);
		FuGaiQiPan(qiPan, k - 1, left3, right3, up3, down3, right3, up3);
		FuGaiQiPan(qiPan, k - 1, left4, right4, up4, down4, left4, up4);
	}
	else if (right2 >= x && down2 >= y) {
		//�ڵڶ�����
		qiPan[left1][down1] = 2;
		qiPan[right3][up3] = 2;
		qiPan[left4][up4] = 2;
		FuGaiQiPan(qiPan, k - 1, left1, right1, up1, down1, left1, down1);
		FuGaiQiPan(qiPan, k - 1, left2, right2,  up2, down2, x, y);
		FuGaiQiPan(qiPan, k - 1, left3, right3, up3, down3, right3, up3);
		FuGaiQiPan(qiPan, k - 1, left4, right4, up4, down4, left4, up4);
	}
	else if (right3 >= x && up3 <= y) {
		//�ڵ�������
		qiPan[left1][down1] = 3;
		qiPan[right2][down2] = 3;
		qiPan[left4][up4] = 3;
		FuGaiQiPan(qiPan, k - 1, left1, right1, up1, down1, left1, down1);
		FuGaiQiPan(qiPan, k - 1, left2, right2, up2, down2, right2, down2);
		FuGaiQiPan(qiPan, k - 1, left3, right3, up3, down3, x, y);
		FuGaiQiPan(qiPan, k - 1, left4, right4, up4, down4, left4, up4);
	}
	else {
		//�ڵ�������
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

	//��¼���м俪ʼ�������������Ӵ��ͣ����м俪ʼ�������������Ӵ��ͣ�������
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
	������ȷ���������0�±궼����
	*/


	/*
	* ���η���ʹ�����
	* 1����������Է�ΪС����
	* 2��С����以��
	* 3��С�����������
	* 4��С���������Ժϲ��ɴ�������
	*/

	/*
	int a[] = {1,2,3,4,5,6,7,9};
	cout << BinarySearch(a, 8, 2);
	*/

	/*
	�鲢���򡢿�������
	*/

	/*
	int a[] = { 1,2,3 };
	QuanPaiLie1(a, 0, 3);
	*/

	/*
	�������˷�
	˼·
	1	A��Ϊ(a1,a2)�ȳ����Σ�BҲ�����
	2	��A = a1*10^(n/2)+a2,B = b1*10^(m/2)+b2
	3	A*B = a1*b1*10^((n+m)/2)+a1*b2**10^(n/2)+a2*b1*10^(m/2)+a2*b2
	4	������÷��η�
	5	�������ٻ�����ٳ˷����������տ���ʵ������������
	6	�����Է�����
	*/

	/*
	����˷�
	1	�ֿ��㲢���ܽ��͸��Ӷ�
	2	���Ǽ��ٳ˷��������У���һЩ���ɿ��Լ��ٳ˷�����
	*/

	/*
	���̸���
	����
	2^k*2^k��������һ����������Ϊ3��ֱ���ͷ�����������
	˼·
	��Ϊ�Ŀ飬��һֱ���ͷ���������ģ�ʹ�串������û�а����������ӿ飬����Է��ν��
	
	int qiPan[100][100] = { 0 };
	int k = 4;
	int x = 10, y = 10;//��ʼ���ǿ�λ��
	qiPan[x][y] = 5;
	
	FuGaiQiPan(qiPan, k, 1, pow(2, k), 1, pow(2, k), x, y);

	for (int i = 1; i <= pow(2, k); i++) {
		for (int j = 1; j <= pow(2, k); j++)
			cout << qiPan[i][j] << " ";
		cout << endl;
	}
	*/

	/*
	�ҵ�kСԪ��
	1	������
	2	���ÿ����л�Ԫ�ط������λ�ú��ǰ�涼�󣬱Ⱥ��涼С��Ҳ�����ҵ�
	*/
	
	/*
	����Ӷκ�
	�ҳ����������к����������ӶΣ������ȫ�Ǹ���������Ϊ0��
	���η�������
	�ϲ�ʱ����Ҫ����������Ӵ������������Ҫ������
	int a[7] = { 0,-20,11,-4,13,-5,-2 };
	int n = 6;
	cout<<ZuiDaZiDuanHe(a, 1, n);
	*/
	
	/*
	ѭ������
	�Ե�ǰ����������Ϊһ���������󣬽�������������
	�ٵ�һ���޸��Ƶ��������ޣ��ڶ����޸��Ƶ��������ޡ�
	*/

	/*
	һά����������
	1	��֤���½縴�Ӷ�ΪO(nlogn)�����Ƿ��η�
	2	����O(nlogn)
		ѡ����ʵĵ�ָΪ��ƽ�⣬ѡ������λ������ĵ㡣
		�����ӵ㼯�ڲ���С������Է��εó����������ܳ�������������ֱ��������ӵ㼯��
		�����������������������ֵ������Сֵ����
		�ۺϱȽϿɵó����
		ƽ�⻮�ֵĸ��Ӷ�Ҳ��O(nlogn)�����ϲ�����ĸ��ӶȲ����ڴˣ������ۺ�ΪO(nlogn)
	����˼·�����ƹ���ƽ��������
		�ص���֤���ϲ����̵������ԡ�
	*/

	/*
	��Ӧ���м��η�������������������⣬�����е�һ���򼸸������������
	������a^n�����η���������a^(n/2)������������������ˡ����η�����һ�Σ�ֱ��ƽ��һ��������Ľ����
	�ٱ����۰���ҡ�
	*/
//}