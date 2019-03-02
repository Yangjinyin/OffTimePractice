#include <iostream>
#include <fstream>

using namespace std;

template <class T>

/*��������ÿ��ѡ��һ��Ԫ��K���뵽֮ǰ���ź���Ĳ���A[1��i]�У�
���������K�����ɺ���ǰ��A[1��i]�е�Ԫ�ؽ��бȽϡ������ַ���A[x]>=K,
��K���뵽A[x]�ĺ��棬����ǰ��Ҫ�ƶ�Ԫ��,��С�����ȶ������� o(n*n)
�ռ临�Ӷ�o(1);
*/
void InsertSort(T R[],int n)
{
	int i,j;
	for(i = 1;i < n;i++)
	{
		T tmp = R[i];
		j = i-1;
		while(j>=0&&R[j]>tmp)
		{
			R[j+1] = R[j];
			j--;
		}

		R[j+1] = tmp;
	}
}

template <class T>

/*��ͨ�������������ڼ�¼�ؼ��ּ�ıȽϺ�λ�õĽ���,
ʹ�ؼ�����С�ļ�¼������һ�������ϡ�Ư����ֱ����ˮ�桱�� 
*/
void SwapSort(T R[],int n)//ð������
{
	for(int i = 0;i < n ;i++)
	{
		for(int j = n-1; j >i ;j--)
		{
			if(R[j] < R[j-1])
			{
				T tmp = R[j-1];
				R[j-1] = R[j];
				R[j] = tmp;
			}
		}
	}
}

template <class T>

void SelectSort(T R[],int n)
{
	for(int i = 0;i < n;i++)
	{
		int k = i;
		T min= R[i];
		for(int j = i+1;j < n;j++)
		{
			if(R[j] < min)
			{
				min = R[j];
				k = j;
			}
		}
		T tmp;
		tmp = R[i];
		R[i]= min;
		R[k] = tmp;
	}
}

template <class T>
/*�ڴ������n����¼����ȡһ����¼(ͨ��ȡ��һ����¼),�Ѹü�¼�����ʵ�λ�ú�,
	�������б��˼�¼���ֳ������֡����йؼ��ֱȸü�¼�ؼ���С�ļ�¼������ǰһ����,
	���б�����ļ�¼�����ں�һ����,���Ѹü�¼�����������ֵ��м�(��Ϊ�ü�¼��λ),
	������̳���һ�˿�������
	*/
void QuickSort(T R[],int start ,int end)
{
	if(start > end)
		return;
	int i = start;
	int j = end;

	T basepoint = R[i];
	while(i <j)
	{

		while(j>i&&R[j]>=basepoint)
			j--;
		R[i] = R[j];
		while(i<j&&R[i]<=basepoint)
			i++;
		R[j] = R[i];		
	}
	R[i] = basepoint;
	QuickSort(R,start,i-1);
	QuickSort(R,j+1,end);
}

template <class T>

void Merge(T r[],int start,int middle,int end,T rf[])
{
	int i,j,k;
	i = start;
	j = middle+1;
	k = 0;
	while(i<=middle&&j<=end)
	{
		if(r[i]<r[j])
			rf[k++] = r[i++];
		else
			rf[k++] = r[j++];
	}
	while(i<=middle)
		rf[k++] = r[i++];
	while(j<=end)
		rf[k++] = r[j++];

	for(int i = 0;i < k;i++)
	{
		r[start+i] = rf[i];
	}
}

template <class T>

void MergeSort(T R[],int low ,int high,T tmp[])
{
	if(low<high)
	{
		MergeSort(R,low,(low+high)/2,tmp);
		MergeSort(R,(low+high)/2+1,high,tmp);

		Merge(R,low,(low+high)/2,high,tmp);
	}
}
bool MergeSort(int a[], int n) 
{
	int *p = new int[n];

	if(p == NULL)
		return false;
	else
	{
		MergeSort(a,0,n-1,p);
		
		delete[] p;
		return true;
	}
	
}

//��������
void CountSort(int A[],int n)
{
	int *B,*C;
	int max=0;
	for(int i = 0;i<n;i++)
	{
		if(A[i]>max)
			max = A[i];
	}
	C = new int[max+1];
	for(int i = 0;i<=max;i++)
	{
		C[i] = 0;
	}
	B = new int[n+1];
	for(int i = 0;i<=n;i++)
	{
		B[i] = 0;
	}
	for(int i = 0;i < n;i++)
		C[A[i]] = C[A[i]]+1;
	for(int j = 1;j<=max;j++)
		C[j] = C[j-1]+C[j];
	for(int s=n-1;s>=0;s--)
	{
		B[C[A[s]]] = A[s];
		C[A[s]] = C[A[s]] - 1;
	}
	for(int i = 1;i<=n;i++)
	{
		A[i-1] = B[i];
	}
}


//������
template<class T>
void BuildHeap(T *R,int size)//�����ѣ�
{
	for(int i = (size-1)/2;i>=0;i--)//��Ҷ�ӽڵ�������Ϊsize-1/2���������һ��Ԫ�صĸ��ڵ㡣
	{
		MinHeapAdjust(R,i,size);
	}
}

template<class T>
void MinHeapAdjust(T R[],int i, int size)
{
	int j;
	T tmp;

	tmp = R[i];
	j = 2*i+1;
	while(j<size)
	{
		if(j+1<size&&R[j+1]<R[j])  //�����Һ������ҵ���С��
			j++;
		if(R[j]>=tmp)
			break;
		R[i] = R[j];  //����С�������ƶ����滻���ĸ��ڵ�
		i = j;
		j = 2*i +1;
	}
	R[i] = tmp;
}
template<class T>
void MinHeapSort(T R[],int size)
{
	BuildHeap(R,size);
	for(int i = size -1;i>=1;i--)
	{
		swap(R[i],R[0]);
		cout<<R[0];
		MinHeapAdjust(R,0,i);
	}
}

void Maxheepadjust(int a[],int i,int size)
{
	int j = i*2+1; //right child
	int tmp = a[i];
	while(j<size)
	{
		if(j+1<size && a[j+1]>a[j])
			j++;
		if(tmp>a[j])
			break;
		a[i] = a[j];
		i = j;
		j = i*2+1;
	}
	a[i] = tmp;
}


