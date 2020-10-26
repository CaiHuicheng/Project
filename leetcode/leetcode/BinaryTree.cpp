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

//��������ǰ��������ǵݹ�
void prevOrederNonR(Node *_root) {
	Node * car = _root;
	stack<Node *> s;
	//s.push(car);
	//����
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

//������������������ǵݹ�
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

//���������������,�ǵݹ�
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

//���������� �ݹ�
class SulationBinaryTree1 {
public:
	void _PostorderTraversal(Node * root, vector<int> &v) {
		if (root == NULL) return ;
		_PostorderTraversal(root->left,v);//��
		_PostorderTraversal(root->right,v);//��
		v.push_back(root->_data);//��
	}
	vector<int> PostorderTraversal(Node * root) {
		vector<int> v;
		_PostorderTraversal(root, v);
		return v;
	}
};

//������ȱ���
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

//��������ĸ߶�
size_t _Depth(Node * root) {
	if (root == NULL) return 0;
	size_t leftDepth = _Depth(root->left);
	size_t rightDepth = _Depth(root->left);
	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}
size_t Depth(Node * root) {
	return _Depth(root);
}

//��Ҷ�ӽڵ�ĸ��� �ݹ�
size_t LeafSzie(Node * root) {
	if (root == NULL) return 0;
	if (root->left == NULL&&root->right) {
		return 1;
	}
	return LeafSzie(root->left) + LeafSzie(root->right);
}
//��Ҷ�ӽڵ�ĸ��� ����
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

//���������K��Ľڵ����
size_t GetKLeveSzie(Node *root,size_t k) {
	if (root == NULL) return NULL;
	if (k == 1) return 1;
	return GetKLeveSzie(root->left, k - 1) + GetKLeveSzie(root->right, k - 1);
}

//�ж�һ���ڵ��Ƿ���һ����������
size_t FindKey(Node *root, size_t key) {
	if (root == NULL) return false;
	if (root->_data == key) return true;
	if (root->left&&FindKey(root->left, key))
		return true;
	if (root->right&&FindKey(root->right, key))
		return true;
}

//�ж�һ����Ϊƽ�������
/*
1�����������߶Ȳ�ľ���ֵ<=1
2������������Ϊƽ�������
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

//���������Զ�������ڵ�ľ���
//�·����ȻҪ�����������������ĸ��ڵ㣬���Կ����õݹ��������������һ����ת��Ϊ�����������롣
size_t GetMaxPathlen(Node *root, int &maxLen) {
	if (root == NULL) {
		return 0;
	}
	int left = GetMaxPathlen(root->left, maxLen);
	int right = GetMaxPathlen(root->right, maxLen);
	if (left + right > maxLen) maxLen = left + right;
	return (left > right ? left : right) + 1;
}


//��ǰ���������������ؽ�������
class Solution {
public:
	Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (preorder.size() == 0)  //û�нڵ㣬���ؿ�
			return nullptr;
		if (preorder.size() == 1)  //����һ���ڵ㣬���ظýڵ�
		{
			Node* root = new Node(preorder[0]);
			return root;
		}
		Node* root = new TreeNode(preorder[0]);  //ǰ�������һ��Ϊ���ڵ�
		auto itr = inorder.begin();
		while (*itr != preorder[0])  //�ҵ�����������ڵ㣬�ָ���������
			++itr;
		//����������ǰ����������
		int left = itr - inorder.begin();  //�������ڵ����
		vector<int> leftpre(preorder.begin() + 1, preorder.begin() + 1 + left);  //������ǰ��
		vector<int> leftin(inorder.begin(), itr);  //����������
												   //����������ǰ����������
		vector<int> rightpre(preorder.begin() + 1 + left, preorder.end());  //������ǰ��
		vector<int> rightin(++itr, inorder.end());  //����������
													//�ݹ����
		root->left = buildTree(leftpre, leftin);
		root->right = buildTree(rightpre, rightin);

		//���ظ��ڵ�
		return root;

	}
};
int main() {

	system("pause");
	return 0;
}