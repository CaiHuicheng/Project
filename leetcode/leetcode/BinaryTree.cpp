#include<iostream>
#include<stack>
#include<vector>
#include<queue>


using namespace std;


typedef struct Node {
	int _data;
	struct Node *left, *right;
}Node;


/*
struct BinaryTreeNode
{
BinaryTreeNode(char data)
:_pLeft(NULL)
, _pRight(NULL)
, _data(data)
{}
BinaryTreeNode *_pLeft;
BinaryTreeNode *_pRight;
char _data;
};
*/

//二叉树，前序遍历，非递归
void prevOrederNonR(Node *_root) {
	Node * car = _root;
	stack<Node *> s;
	//s.push(car);
	//中左
	while (car || !s.empty()) {
		while (car) {
			cout << car->_data << " ";
			s.push(car);
			car = car->left;
		}
		Node * top = s.top();
		s.pop();
		car = top->right;
	}
	cout << endl;
}

//二叉树，中序遍历，非递归
void InOrderNonR(Node * _root) {
	Node * root = _root;
	stack<Node *> s;
	while (root || !s.empty()) {
		while (root) {
			s.push(root);
			root = root->left;
		}
		Node * top = s.top();
		cout << root->_data << " ";
		s.pop();
		root = top->right;
	}
	cout << endl;
}

//二叉树，后序遍历,非递归
void PostOrderNonR(Node * _root) {
	Node * root = _root;
	stack<Node *> s;
	Node * prev = NULL;
	while (root || !s.empty()) {
		while (root) {
			s.push(root);
			root = root->left;
		}
		Node * top = s.top();
		s.pop();
		if (top->right == NULL || top->right == prev) {
			cout << top->_data << " ";
			s.pop();
			top = prev;
		}
		else {
			root = top->right;
		}
	}
	cout << endl;
}

//二叉树遍历 递归
class SulationBinaryTree1 {
public:
	void _PostorderTraversal(Node * root, vector<int> &v) {
		if (root == NULL) return ;
		_PostorderTraversal(root->left,v);//左
		_PostorderTraversal(root->right,v);//中
		v.push_back(root->_data);//右
	}
	vector<int> PostorderTraversal(Node * root) {
		vector<int> v;
		_PostorderTraversal(root, v);
		return v;
	}
};

//广度优先遍历
void leveOreder(Node * root) {
	queue<Node *> q;
	if (root ) q.push(root);
	while (q.empty()) {
		Node * front = q.front();
		cout << front->_data << " ";
		q.pop();
		if(front->left) q.push(front->left);
		if(front->right) q.push(front->right);
	}
	cout << endl;
}

//求二叉树的高度
size_t _Depth(Node * root) {
	if (root == NULL) return 0;
	size_t leftDepth = _Depth(root->left);
	size_t rightDepth = _Depth(root->left);
	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}
size_t Depth(Node * root) {
	return _Depth(root);
}

//求叶子节点的个数 递归
size_t LeafSzie(Node * root) {
	if (root == NULL) return 0;
	if (root->left == NULL&&root->right) {
		return 1;
	}
	return LeafSzie(root->left) + LeafSzie(root->right);
}
//求叶子节点的个数 遍历
size_t _leafSize(Node * root) {
	size_t size;
	if (root == NULL) return 0;
	if (root->left == NULL && root->right == NULL) {
		++size;
	}
	_leafSize(root->left);
	_leafSize(root->right);
	return size;
}

//求二叉树第K层的节点个数
size_t GetKLeveSzie(Node *root,size_t k) {
	if (root == NULL) return NULL;
	if (k == 1) return 1;
	return GetKLeveSzie(root->left, k - 1) + GetKLeveSzie(root->right, k - 1);
}

//判断一个节点是否在一个二叉树中
size_t FindKey(Node *root, size_t key) {
	if (root == NULL) return false;
	if (root->_data == key) return true;
	if (root->left&&FindKey(root->left, key))
		return true;
	if (root->right&&FindKey(root->right, key))
		return true;
}

//判断一个数为平衡二叉树
/*
1、左右子树高度差的绝对值<=1
2、左右子树均为平衡二叉树
*/
class SolutionBalanced {
public:
	bool IsBalanced(Node * root, int &depth) {
		if(root == NULL) return false;
		int leftDepth = 0;
		int rigthDepth = 0;
		if (IsBalanced(root->left, leftDepth) && IsBalanced(root->right, rigthDepth)) {
			if (abs(leftDepth - rigthDepth) > 1) {
				return false;
			}
			else {
				depth = (leftDepth > rigthDepth ? leftDepth : rigthDepth) + 1;
				return true;
			}
		}
		return false;
	}
};

//求二叉树最远的两个节点的距离
//最长路径必然要经过树或者其子树的根节点，所以可以用递归来解决，即把这一问题转化为子树的最大距离。
size_t GetMaxPathlen(Node *root, int &maxLen) {
	if (root == NULL) {
		return 0;
	}
	int left = GetMaxPathlen(root->left, maxLen);
	int right = GetMaxPathlen(root->right, maxLen);
	if (left + right > maxLen) maxLen = left + right;
	return (left > right ? left : right) + 1;
}


//由前序遍历和中序遍历重建二叉树
class Solution {
public:
	Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.size() == 0)  //没有节点，返回空
			return nullptr;
		if (preorder.size() == 1)  //仅有一个节点，返回该节点
		{
			Node* root = new Node(preorder[0]);
			return root;
		}
		Node* root = new TreeNode(preorder[0]);  //前序遍历第一个为根节点
		auto itr = inorder.begin();
		while (*itr != preorder[0])  //找到中序遍历根节点，分割左右子树
			++itr;
		//构造左子树前序中序序列
		int left = itr - inorder.begin();  //左子树节点个数
		vector<int> leftpre(preorder.begin() + 1, preorder.begin() + 1 + left);  //左子树前序
		vector<int> leftin(inorder.begin(), itr);  //左子树中序
												   //构造右子树前序中序序列
		vector<int> rightpre(preorder.begin() + 1 + left, preorder.end());  //右子树前序
		vector<int> rightin(++itr, inorder.end());  //右子树中序
													//递归调用
		root->left = buildTree(leftpre, leftin);
		root->right = buildTree(rightpre, rightin);

		//返回根节点
		return root;

	}
};
int main() {

	system("pause");
	return 0;
}