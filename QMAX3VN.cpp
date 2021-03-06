/*
USER: zobayer
TASK: QMAX3VN
ALGO: treap
*/

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int MAX = 1 << 17;
const int INF = 0x7f7f7f7f;

struct Node {
	int priority, size;
	int key, best;
	Node *left, *right;

	void update() {
		size = 1 + left->size + right->size;
		best = max(key, max(left->best, right->best));
	}
};

Node buffer[MAX];
Node *R, *nil, *ptr = buffer;

void init() {
	srand(time(NULL));
	ptr->left = ptr->right = nil;
	ptr->key = ptr->best = -INF;
	ptr->size = 0, ptr->priority = -1;
	R = nil = ptr;
	ptr++;
}

Node *rotate(Node *p, Node *s) {
	if(p->left == s) { p->left = s->right; s->right = p; }
	else { p->right = s->left; s->left = p; }
	p->update(); s->update();
	return s;
}

Node *insert(Node *node, int pos, int key) {
	if(node == nil) {
		ptr->left = ptr->right = nil;
		ptr->key = ptr->best = key;
		ptr->size = 1, ptr->priority = rand();
		return ptr++;
	}
	if(node->left->size >= pos) {
		node->left = insert(node->left, pos, key);
		if(node->left->priority > node->priority) node = rotate(node, node->left);
	}
	else {
		node->right = insert(node->right, pos - node->left->size - 1, key);
		if(node->right->priority > node->priority) node = rotate(node, node->right);
	}
	node->update();
	return node;
}

int query(Node *node, int i, int j, int qi, int qj) {
	if(node == nil || i >= qj || j <= qi) return -INF;
	if(qi <= i && j <= qj) return node->best;
	int ret = -INF;
	ret = max(ret, query(node->left, i, i + node->left->size, qi, qj));
	ret = max(ret, query(node->right, i + node->left->size + 1, j, qi, qj));
	if(i + node->left->size >= qi && i + node->left->size < qj) ret = max(ret, node->key);
	return ret;
}

int main() {
	char op[2];
	int x, y, q;
	init();
	//freopen("in.txt", "r", stdin);
	scanf("%d", &q);
	while(q--) {
		scanf("%s %d %d", op, &x, &y);
		if(*op == 'Q') printf("%d\n", query(R, 0, R->size, x-1, y));
		else R = insert(R, y-1, x);
	}
	return 0;
}
