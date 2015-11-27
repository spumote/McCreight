#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <set>
#include <vector>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define f first
#define s second
#define pb push_back
#define mp make_pair

const int Alphabet_size = 27;

const int MAX_MEM = 1e8;
int mpos = 0;
char mem[MAX_MEM];

inline void * operator new ( size_t n ) {
	char *res = mem + mpos;
	mpos += n;
	assert(mpos <= MAX_MEM);
	return (void *)res;
}

inline void operator delete ( void * ) { }

struct Node {
	Node* parent;
	int left, right;
	int depth;
	Node* suffLink;
	vector<Node*> children;

	Node() {
		parent = NULL;
		suffLink = NULL;
		children.resize(Alphabet_size);
	}
	Node(Node* _parent, int _left, int _right, int _depth) {
		children.resize(Alphabet_size);
		suffLink = NULL;
		parent = _parent;
		left = _left;
		right = _right;
		depth = _depth;
	}
	~Node() {
	}
};

class SuffixTree {
private:
	Node* root;
	Node* head;
	int diffStr;
	string s;
		
	Node* AddSuffix(Node* head, int i);
	Node* Split(Node* cur, int len);
	void GetSuffLink(Node* cur);

public:
	void go(Node* cur, int dp);
	int getdiffStr();
	SuffixTree() {}
	SuffixTree(const string& Str, int l, int r, int k);
	~SuffixTree() {}
	void delet(Node* cur) {
		if (cur == NULL)
			return;
		for (int i = 0; i < Alphabet_size; i++)
			delet(cur->children[i]);
		delete cur;
	}	
};

void SuffixTree::go(Node* cur, int dp) {
	if (cur == NULL)
		return;
	for (int i = 0; i < dp; i++)
		cout << ' ';
	if (cur == root)
		cout << "root" << endl;
	else
		cout << cur->left << ' ' << cur->right << ' ' << cur->depth << endl;
	for (int i = 0; i < Alphabet_size; i++)
		go(cur->children[i], dp + 1);
}

SuffixTree::SuffixTree(const string& Str, int l, int r, int k) {
	s.resize(k + 1);
	int t = 0;
	if (l <= r)
		for (int i = l; i <= r; i++)
			s[t++] = Str[i];
	else {
		for (int i = l; i < (int)Str.size(); i++)
			s[t++] = Str[i];
		for (int i = 0; i <= r; i++)
			s[t++] = Str[i];
	}
	s[t] = 'a' - 1;
	int n = s.size();

	root = new Node(NULL, 0, -1, 0);
	root->suffLink = root;
	head = root;
	diffStr = 0;

	for (int i = 0; i < n; i++) {
		head = AddSuffix(head, i);
	}	
	delet(root);
}

Node* SuffixTree::Split(Node* cur, int len) {
	Node* newNode = new Node(cur->parent, cur->left, cur->left + len - 1, cur->parent->depth + len);
	cur->parent->children[s[cur->left] - 'a' + 1] = newNode;
	newNode->children[s[cur->left + len] - 'a' + 1] = cur;
	cur->left += len;
	cur->parent = newNode;
	return newNode;
}

Node* SuffixTree::AddSuffix(Node* head, int i) {
	if (head->suffLink == NULL) {
		GetSuffLink(head);
	}
	head = head->suffLink;
	int left = i + head->depth;
	while (head->children[s[left] - 'a' + 1] != NULL) {
		Node* child = head->children[s[left] - 'a' + 1];
		bool bl = false;
		for (int i = child->left; i <= child->right; i++)
			if (s[i] != s[left]) {
				head = Split(child, i - child->left);
				bl = true;
				break;
			}
			else
				left++;
		if (bl)
			break;
		head = child;
	}
	if (left < (int)s.size()) {
		head->children[s[left] - 'a' + 1] = new Node(head, left, s.size() - 1, head->depth + s.size() - left);
		diffStr += s.size() - left;
	}
	return head;
}

void SuffixTree::GetSuffLink(Node* node) {
	int len = node->right - node->left + 1;
	int left = node->left;
	Node* cur = node->parent->suffLink;
	if (node->parent == root) {
		len--;
		left++;
	}
	while (len > 0) {
		Node* child = cur->children[s[left] - 'a' + 1];
		if (child->right - child->left + 1 > len)
			break;
		left += child->right - child->left + 1;
		len -= child->right - child->left + 1;
		cur = child;		
	}
	if (len > 0) 
		cur = Split(cur->children[s[left] - 'a' + 1], len);
	node->suffLink = cur;
}

int SuffixTree::getdiffStr() {
	return diffStr - s.size();
}

int main() {
	int k;
	scanf("%d\n", &k);
	string str;
	cin >> str;


	for (int i = 0; i < (int)str.size(); i++) {
		mpos = 0;
		SuffixTree tree(str, i, (i + k - 1) % (int)str.size(), k);
		cout << tree.getdiffStr() << ' ';
	}
	cout << endl;                                   
		

	return 0;
}                                                    