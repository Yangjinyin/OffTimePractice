#include <iostream>
#include <stack>
using namespace std;

struct BinaryTree
{
	int m_element;
	BinaryTree * leftNode;
	BinaryTree * rightNode;
	BinaryTree(int e,BinaryTree* p1,BinaryTree* p2)
	{
		m_element = e;
		leftNode = p1;
		rightNode= p2;
	}
	BinaryTree(BinaryTree* p)
	{
		m_element = p->m_element;
		leftNode = p->leftNode;
		rightNode = p->rightNode;
	}
};
//����������������������
class BinarySearchTree  
{
public:
	BinaryTree* m_rootNode;

	BinarySearchTree(){m_rootNode = NULL;};
	BinarySearchTree(BinaryTree* p); //���캯��
	~BinarySearchTree();
	bool Search(const int& x);
	bool Insert(const int& x);                     //�������
	void Remove(const int& x);
	void Makeempty();
	void printTree(int flag);

private:
	void Makempty(BinaryTree* root);
	BinaryTree* Search(const int&x,BinaryTree* root);
	void insert(const int& x,BinaryTree *&root);       //����һ������ָ�����ã���Ϊδ���ҵ����˰���
	void remove(const int& x,BinaryTree *&root);        //ͬ��
	void printTreePre(BinaryTree *root);
	void printTreeMid(BinaryTree* root);
	void printTreePost(BinaryTree* root);
	
};

BinarySearchTree::BinarySearchTree(BinaryTree* p)
{
	m_rootNode = p;
}

BinarySearchTree::~BinarySearchTree()
{
	Makeempty();
}

void BinarySearchTree::Makeempty()
{
	Makempty(m_rootNode);
}


void BinarySearchTree::Makempty(BinaryTree *p)
{
	if(p==NULL)
	{
		return;
	}
	else
	{
		Makempty(p->leftNode);
		Makempty(p->rightNode);
		delete p;
	}
}

bool BinarySearchTree::Search(const int& x)
{
	return Search(x,m_rootNode);
}


BinaryTree* BinarySearchTree::Search(const int& x,BinaryTree* p)
{
	if((p->m_element == x) || p == NULL)
	{
		return p;
	}
	if(x<(p->m_element))
		return Search(x,p->leftNode);
	else
		return Search(x,p->rightNode);
	
}

bool BinarySearchTree::Insert(const int& x)
{	
		insert(x,m_rootNode);
		return true;
}

void BinarySearchTree::insert(const int& x,BinaryTree * &root)
{
	if(root == NULL)
	{
		BinaryTree* node = new BinaryTree(x,NULL,NULL);
		root = node;
		return ;
	}
	else
	{
		if(x>root->m_element)
			insert(x,root->rightNode);
		if(x<root->m_element)
			insert(x,root->leftNode);
	}
}

void BinarySearchTree::Remove(const int&x)
{
	remove(x,m_rootNode);
}

void BinarySearchTree::remove(const int& x,BinaryTree *&root)
{
	if(root == NULL)
		return;
	else
	{
		if (root->m_element == x)
		{
			if (root->leftNode&&root->rightNode) //����õ�ĺ��Ӷ���Ϊ�գ����ҳ���������������Сֵ�滻��.
			{
				BinaryTree * tmp;
				tmp = root->rightNode;
				while(tmp->leftNode)
					tmp = tmp->leftNode;
				root->m_element = tmp->m_element;
				root->rightNode = tmp->rightNode;

				remove(tmp->m_element,root->rightNode);
			}
			else                    //�������һ����0�����ӡ�
			{
				BinaryTree* tmp = root;
				if(root->rightNode == NULL)
					root = root->leftNode;
				else if(root->leftNode == NULL)
					root = root->rightNode;
				delete(tmp);
			}

			return;
		}
		else 
		{
			if(root->m_element > x)
				remove(x,root->leftNode);
			else 
				remove(x,root->rightNode);
		}
	}

}

void BinarySearchTree::printTree(int flag)
{
	if(flag == 1)
		printTreePre(m_rootNode);
	else if (flag == 2)
	{
		printTreeMid(m_rootNode);
	}
	else
		printTreePost(m_rootNode);

}
void BinarySearchTree::printTreePre(BinaryTree *root)
{
	if(root == NULL)
		return;
	else
	{
		cout<<root->m_element<<"  ";
		printTreePre(root->leftNode);
		
		printTreePre(root->rightNode);
	}
}

//void BinarySearchTree::printTreeMid(BinaryTree *root)
//{
//	if(root == NULL)
//		return;
//	else
//	{
//		
//		printTreeMid(root->leftNode);
//		cout<<root->m_element<<"  ";
//		printTreeMid(root->rightNode);
//	}
//}
void BinarySearchTree::printTreePost(BinaryTree *root)
{
	if(root == NULL)
		return;
	else
	{
		printTreeMid(root->leftNode);
		printTreeMid(root->rightNode);
		cout<<root->m_element<<"  ";		
	}
}
// �����Լ���дһ��
void BinarySearchTree::printTreeMid(BinaryTree *root)
{
	stack<BinaryTree*> s;
	BinaryTree* tmp;
	if(root == NULL)
		return;
	while(root || !s.empty())
	{
		while(root)
		{
			s.push(root);
			root = root->leftNode;
		}

		tmp = s.top();
		s.pop();
		cout<<tmp->m_element<<"  ";
		root = tmp->rightNode;
	}
}

