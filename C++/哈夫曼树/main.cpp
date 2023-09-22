#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
#include<stack>

using namespace std;

typedef struct Node {
	int v;
	Node* lch, * rch;

	Node():v(0), lch(nullptr), rch(nullptr) {}
	Node(int n):v(n), lch(nullptr),rch(nullptr) {}
}Node, *pNode;

struct NodeCompare {
	bool operator()(const Node& x, const Node& y) {
		return x.v > y.v;
	}
};

class HTree {
private:
	priority_queue<Node, vector<Node>, NodeCompare> nodes;
	pNode root;

	void CreateTree();
	void PrintFr(pNode);
	void PrintMi(pNode);
public:
	HTree(vector<int> nums) {
		for (int n : nums)
			this->nodes.push(Node(n));
		this->root = nullptr;
		this->CreateTree();
	}
	void PrintFr() { PrintFr(this->root); cout << endl; }
	void PrintMi() { PrintMi(this->root); cout << endl; }
};
void HTree::CreateTree() {
	while (this->nodes.size()>1) {
		pNode pn1, pn2, pn3;

		pn1 = new Node(nodes.top().v);
		pn1->lch = nodes.top().lch;
		pn1->rch = nodes.top().rch;
		nodes.pop();
		pn2 = new Node(nodes.top().v);
		pn2->lch = nodes.top().lch;
		pn2->rch = nodes.top().rch;
		nodes.pop();

		pn3 = new Node(pn1->v + pn2->v);
		pn3->lch = pn1;
		pn3->rch = pn2;

		nodes.push(*pn3);
	}

	this->root = new Node(nodes.top().v);
	root->lch = nodes.top().lch;
	root->rch = nodes.top().rch;
}
void HTree::PrintFr(pNode root) {
	if (root != nullptr) {
		cout << root->v << " ";
		PrintFr(root->lch);
		PrintFr(root->rch);
	}
}
void HTree::PrintMi(pNode root) {
	if (root != nullptr) {
		PrintMi(root->lch);
		cout << root->v << " ";
		PrintMi(root->rch);
	}
}


int main() {
	//数据准备
	int n,a;
	vector<int> nums;
	cin >> n;
	while(n--) {
		cin >> a;
		nums.push_back(a);
	}

	HTree htree = HTree(nums);

	htree.PrintFr();
	htree.PrintMi();
	
	return 0;
}