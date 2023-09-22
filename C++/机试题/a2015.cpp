#include "a2015.h"

using namespace std;

void _2015f1(
	vector<int>& person,
	int &ans, 
	int curi, int curCount
) {
	//person����ʼ��Ϊ0����ʾδ��������
	//curi��ʾ��ǰ����,��ʼΪ0
	//curCount��ʾ��ǰ�Ѿ����ֵ�������Ŀ,��ʼ��Ϊ1
	//ans��ʼ�㹻��
	if (person.size() == 0) {
		//û�ˣ����Դ�Ϊ0
		ans=0;
		return;
	}

	if (curi == person.size()) {
		//���������
		if (ans > curCount)
			ans = curCount;
		return;
	}

	if (curCount > ans) {
		//��֦
		return;
	}

	bool success = false;
	for (int i = 1; i <= curCount; i++) {
		//����curi���˿��Եõ��ĸ�����
		int pre = (curi - 1 + person.size()) % person.size(), af = (curi + 1) % person.size();
		if ((person[pre] == 0 || person[pre] != i) && (person[af] == 0 || person[af] != i)) {
			//���Եõ�����i
			person[curi] = i;
			success = true;
			_2015f1(person, ans, curi + 1, curCount);

			person[curi] = 0;
		}
	}
	if (!success) {
		//���ܷ��䣬ֻ���¼��������Է���
		++curCount;
		person[curi] = curCount;
		_2015f1(person, ans, curi + 1, curCount);
	}
}