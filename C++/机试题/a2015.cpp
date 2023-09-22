#include "a2015.h"

using namespace std;

void _2015f1(
	vector<int>& person,
	int &ans, 
	int curi, int curCount
) {
	//person被初始化为0，表示未分配礼物
	//curi表示当前的人,初始为0
	//curCount表示当前已经出现的礼物数目,初始化为1
	//ans初始足够大
	if (person.size() == 0) {
		//没人，所以答案为0
		ans=0;
		return;
	}

	if (curi == person.size()) {
		//分配已完成
		if (ans > curCount)
			ans = curCount;
		return;
	}

	if (curCount > ans) {
		//剪枝
		return;
	}

	bool success = false;
	for (int i = 1; i <= curCount; i++) {
		//看第curi个人可以得到哪个礼物
		int pre = (curi - 1 + person.size()) % person.size(), af = (curi + 1) % person.size();
		if ((person[pre] == 0 || person[pre] != i) && (person[af] == 0 || person[af] != i)) {
			//可以得到礼物i
			person[curi] = i;
			success = true;
			_2015f1(person, ans, curi + 1, curCount);

			person[curi] = 0;
		}
	}
	if (!success) {
		//不能分配，只能新加礼物用以分配
		++curCount;
		person[curi] = curCount;
		_2015f1(person, ans, curi + 1, curCount);
	}
}