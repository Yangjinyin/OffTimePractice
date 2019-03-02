#include <iostream>
#define  M  4
//�������������һ��ƽ��Ķ��������ΪB������B-����B_����
namespace BTree
{

	template <class T>
	class TreeNode
	{
		int n;                          //ָʾ�ý��Ĺؼ��ָ���  
		T *keys;                      //�ý��ؼ�������(n)             [m-1,2m-1]  
		bool isLeaf;                    //�ý���Ƿ���Ҷ�ӽ��  
		TreeNode<T>  **child ;          //�ý������к��ӽ�� (n+1)         [m,2m];

		TreeNode<T>* AllocateNode()
		{ 
			TreeNode<T> *p = new TreeNode<T>;
			p->isLeaf = true;
			p->n = 0;
			p->keys = new T(2*M-1);
			p->child = new TreeNode<T>[2*M];
			for(int i = 0; i < 2*T;i++)
				p->child[i] = NULL;
			return p;

		}
	};

	template <class T>
	class BTree
	{
	private:
		TreeNode *root;
		TreeNode<T>* Search(TreeNode<T> *root,T x ,int &index);
		void BTreeInsertNonfull(TreeNode<T>*& p,T x);
		bool BTreeDeleteInNode(TreeNode<T>*& deleteNode, T x,int index);       
		bool BTreeDeleteInParentNode(TreeNode<T>*& parentNode, T x,int indexparent);
		void PrintTree(TreeNode<T>* root);
	public:
		bool Search(T x);
		void SplitChild(TreeNode<T> *&splitNode, TreeNode<T>* &parent,int indexchild);
		void BTreeInsert(T x);
		void BTreeDelete(T x);
		void PrintTree();
	};


	template <class T>
	bool BTree<T>::Search(T x)
	{
		int index;
		return Search(root,x,index);
	}

	//index ����
	template <class T>
	TreeNode<T>* BTree::Search(TreeNode<T> *root,T x ,int &index)
	{
		int i = 0;
		while(i < root->n && x > root->keys[i])
		{
			i++;
		}
		if(i < root->n && x == root->keys[i])
		{
			index = i;
			return root->keys[i];
		}
		if(root->isLeaf)
			return NULL;
		Search(root->child[i],x,index);
	}

	//indexchild �Ǵ����ѽڵ��ڸ��׽ڵ�ı������
	template <class T>
	void BTree<T>::SplitChild(TreeNode<T> *&splitNode, TreeNode<T>* &parent,int indexchild)
	{
		TreeNode<T> *p = AllocateNode();

		p->isLeaf = splitNode->isLeaf;
		p->n = M-1;

		for(int j = 0;j < p->n;j++)
			p->keys[j] = splitNode->keys[j+M];  //��splitNode�ĺ�һ�븳ֵ��p��
		
		if(splitNode->isLeaf)
		{
			for(int j = 0; j < M; j++)
				p->child[j] = splitNode->child[M+j];
		}

		splitNode->n = M-1;

		for (int j = parent->n;j>indexchild+1;j--)
		{
			parent->child[j+1] = parent->child[j];
		}

		parent->child[j] = p;

		for(int j = parent->n-1;j>indexchild;j--)
			parent->keys[j+1] = parent->keys[j];
		parent->keys[j+1] = p->keys[j];
		
		++parent->n;  
	}

	//��x����p�ڵ����Ҹýڵ㲻��
	template <class T>
	void BTree<T>::BTreeInsertNonfull(TreeNode<T>*& p,T x)
	{
		int i = p->n - 1;
		
		if(p->isLeaf)
		{
			while (i>=0 && x < p->keys[i])
			{
				p->keys[i+1] = p->keys[i];
				i = i - 1;
			}
			p->keys[i+1] = k;
			++p->n;
			
		}
		else
		{
			while(i>=0 && k < p->keys[i])
				i--;
			i++;

			if(p->child[i]->n == 2*M-1)
			{
				SplitChild(p->child[i],p,i);

				if(x > p->keys[i])
					i++;

				BTreeInsertNonfull(p->child[i],x);
			}
		}
	}

	template <class T>
	void BTree<T>::BTreeInsert(T x)
	{
		TreeNode<T> *p = root;
		if(root->n == 2*M-1)
		{
			TreeNode<T>* newRoot = AllocateNode();
			root = newRoot;
			newRoot->isLeaf = false;
			newRoot->n = 0;
			newRoot->child[0] = p;
			SplitChild(newRoot->child,newRoot,0);
			BTreeInsertNonfull(newRoot,x);
		}
		else
		{
			BTreeInsertNonfull(p,x);
		}
	}

	template <class T>
	void BTree<T>::BTreeDelete(T x)
	{
		TreeNode<T>* p_root = root;
	
		//�ҵ��õ����ڵĽڵ�
		TreeNode<T>* parent = p_root;
		int num = 0;
		int i = 0;
		while(x > p_root->keys[i] && i < p_root->n)
		{
			i++;
		}
		if(i < p_root->n && x == root->keys[i])
		{
			BTreeDelete(p_root,x,i);            //��ɾ�������ڸ��ڵ�
			return;
		}
		p_root = p_root->child[i];

		int index = 0;
		while(p_root)
		{
			int i = 0;


			while(x > p_root->keys[i] && i < p_root->n)
			{
				i++;
			}
			if(i < p_root->n && x == root->keys[i])
			{
				BTreeDeleteInParentNode(parent,x,index);    //��ɾ�����ڷǸ��ڵ���
				return;
			}
			parent = p_root;
			p_root = p_root->child[i];
			index = i;
		}

	}

	//��ɾ�����ڽڵ��ϣ�
	template <class T>
	bool BTree<T>::BTreeDeleteInNode(TreeNode<T>*& deleteNode, T x,int index)   
	{
		if(deleteNode->isLeaf)                                        //��ɾ������Ҷ�ڵ��ϣ�
		{
			for(int i = index;i+1<deleteNode->n;i++)
				deleteNode[i] = deleteNode[i+1];
			--deleteNode->n;

			return;
		}
		else                                                         //���ڽڵ��ϣ�        
		{
			if(deleteNode->child[index]->n>=M)                       //����ǰ������������M���ؼ��֣��ҵ�ǰ�������滻��.Ȼ��ݹ�ɾ��
			{
				swap(deleteNode->keys[index],deleteNode->child[index]->key[deleteNode->child[index]->n]);
				BTreeDeleteInNode(deleteNode->child[index],x,deleteNode->child[index]->n);
			}
			else 
			{
				if(deleteNode->child[index+1]->n>=M)                 //���ĺ�������������M���ؼ��֣��ҵ���һ�����������滻��.Ȼ��ݹ�ɾ��      
				{
					swap(deleteNode->keys[index],deleteNode->child[index+1]->key[0]);
					BTreeDeleteInNode(deleteNode->child[index+1],x,0);
				}
				else                                          //ǰ����������M-1����Ȼ��ϲ�ǰ�������Լ�x��ǰ�����У�ɾ��deleteNode��x�Լ�ָ���������ָ��.Ȼ��ݹ�ɾ��x
				{
					
					deleteNode->child[index]->key[M-1] = x;
					for(int i = 0;i<M-1;i++)
					{
						deleteNode->child[index]->key[M+i] = deleteNode->child[index+1]->key[i];
						deleteNode->child[index]->n = 2*M-1;
					}	
					for(int i = index;i+1<deleteNode->n;i++)
						deleteNode[i] = deleteNode[i+1];
					--deleteNode->n;

					for(int i = index+1;i < deleteNode->n+1;i++)
						deleteNode->child[i] = deleteNode->child[i+1];

					BTreeDeleteInNode(deleteNode->child[index+1],x,M-1);
				}

			}
		}
	}

	//��ɾ�����ں��ӽڵ���
	template <class T>
	bool BTree<T>::BTreeDeleteInParentNode(TreeNode<T>*& parentNode, T x,int indexparent)
	{
		int i = 0;
		while(i<parentNode->child[indexparent]->n && x != parentNode->child[indexparent]->key[i])
			i++;
		if(parentNode->child[indexparent]->n>=M)
		{			
			BTreeDeleteInNode(parentNode->child[indexparent],x,i);
		}
		else
		{
			if(indexparent-1>=0 && parentNode->child[indexparent+1]->n>= M)        //case3.a
			{
				parentNode->child[indexparent]->key[M-1] = parentNode->keys[indexparent-1];
				parentNode->child[indexparent]->n += 1;

				parentNode->keys[indexparent-1] = parentNode->child[indexparent-1]->key[ (parentNode->child[indexparent-1]->n)-1];

				parentNode->child[indexparent+1]->n -=1;

				BTreeDeleteInNode(parentNode->child[indexparent],x,i);
			}
			else
			{
				if(indexparent+1<parentNode->n && parentNode->child[indexparent+1]->n>= M) //case 3.a
				{
					parentNode->child[indexparent]->key[M-1] = parentNode->keys[indexparent];
					parentNode->child[indexparent]->n += 1;

					parentNode->keys[indexparent] = parentNode->child[indexparent+1]->key[0];

					for(int i = 0;i+1 < parentNode->child[indexparent+1]->n;i++)
						parentNode->child[indexparent+1]->key[i] = parentNode->child[indexparent+1]->key[i+1];
					parentNode->child[indexparent+1]->n -=1;

					BTreeDeleteInNode(parentNode->child[indexparent],x,i);
				}
			}
		}
	}

	template <class T>
	void BTree<T>::PrintTree()
	{
		PrintTree(root);
	}


	template<class T>
	void BTree<T>::PrintTree(TreeNode<T>* root)
	{
		if(NULL == root)  
			return;  

		//�����ǰ�ڵ����йؼ���  
		cout << "[";  
		for(int i = 0;i < root->n;++i)  
		{  
			cout << root->keys[i];  
			if(t->n - 1 != i)  
				cout << " ";  
		}  
		cout << "]" << endl;  

		//�ݹ������������  
		for(int i = 0;i <= t->n;++i)  
			PrintTree(root->child[i]);  
	}
}

