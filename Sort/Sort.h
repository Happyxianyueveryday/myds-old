#include <iostream>
#include <string>
#include <vector>

using namespace std;

void swap(int *a, int *b)
{
	int temp=*a;
	*a=*b;
	*b=temp;
}

class Sort
{
	public:
	void bubble_sort(int lis[], int size);      // 冒泡排序 
	void insert_sort(int lis[], int size);      // 插入排序 
	void select_sort(int lis[], int size);      // 选择排序 
	void merge_sort(int lis[], int size);		// 归并排序 
	void quick_sort(int lis[], int size);       // 快速排序 
	void shell_sort(int lis[], int size);       // 希尔排序 
	void heap_sort(int lis[], int size);        // 堆排序 
	
	private:
	void real_merge(int lis[], int begin, int end);      // 归并排序底层递归实现
	void real_quick(int lis[], int begin, int end);      // 快速排序底层递归实现 
};


/*
 * bubble_sort: 冒泡排序算法实现
 * note: 冒泡排序的思路较为简单: 冒泡排序每轮交换只排序数组中的一位，即通过相邻元素的两两交换，将第i大的值移动到倒数第i个位置上，经过size轮后即完成任务 
*/
void Sort::bubble_sort(int lis[], int size)
{
	for(int i=size-1;i>=0;i--)	  // 冒泡排序每轮排序数组中的一位，依次将第m大的值移动到倒数第m个位置上	
	{
		for(int k=0;k<i;k++)      // 通过对前(size-i)个元素的相邻两两交换，将前(size-i)个元素的最大值移动到第i位 
		{
			if(lis[k]>lis[k+1])   // 若lis[k]>lis[k+1]，则交换lis[k]和lis[k+1] 
			{
				int temp=lis[k];
				lis[k]=lis[k+1];
				lis[k+1]=temp;
			}
		}
	}
	
	return;
}


/*
 * insert_sort: 插入排序 
 * note: 插入排序的思路也较为简单: 插入排序第i轮循环将第i个元素，将其依次和第1个，第2个，...，第i-1个元素比较，将其插入在前(i-1)个元素中合适的位置上即可 
*/
void Sort::insert_sort(int lis[], int size)
{
	for(int i=0;i<size;i++)
	{
		// 将lis[i]插入到前i-1个元素中的正确位置上 
		int tar=lis[i];
		
		int ins=-1;     // 插入点 
		
		for(int k=0;k<i;k++)  // 从前往后查找lis[0]~lis[i-1]，查找到其中第一个大于lis[i]的元素的位置 
		{
			if(lis[k]>tar)
			{
				ins=k;
				break;
			}
		}
		
		if(ins==-1)          // 若遍历结束后ins==-1，则lis[0]~lis[i-1]中不存在大于lis[i]的元素，这时lis[i]的位置正确，无需进行插入 
		continue;
		else                 // 需要进行插入的情况，lis[i]就插入到位置下标ins上 
		{
			for(int k=i;k>ins;k--)
			{
				lis[k]=lis[k-1];
			}
			lis[ins]=tar;
		}
	}
	
	return;
} 


/*
 * select_sort: 选择排序
 * note: 选择排序的思想和冒泡排序的思想恰好相反: 冒泡排序第i轮冒泡选出第i大的数，放在倒数第i位上，而选择排序第i轮选出第i小的数，通过和第i位的数交换，从而放在第i位上 
*/
void Sort::select_sort(int lis[], int size)
{
	for(int i=0;i<size;i++)   // 选择排序每次选出数组lis[i]~lis[size-1]中最小的一位，和lis[i]交换位置
	{
		int min=lis[i];       // 数组元素lis[i]~lis[size-1]中的最小值 
		int ind=i;            // 最小值所出现位置的下标 
		
		// 查找数组元素lis[i]~lis[size-1]中的最小值 
		for(int k=i;k<size;k++)
		{
			if(lis[k]<min)
			{
				min=lis[k];
				ind=k;
			}
		}
		
		// 将最小值和数组元素lis[i]交换位置
		int temp=lis[i];
		lis[i]=lis[ind];
		lis[ind]=temp;
	}
	
	return;
}


/*
 * merge_sort: 归并排序
 * note: 归并排序的思想是一种递归思想: 对一个数组进行排序，首先对该数组的前半部分和后半部分分别进行排序，然后再将有序的前半部分和后半部分合并，即完成排序过程 （关于两个有序数组的合并较为简单，请参见其他相关资料） 
*/
void Sort::merge_sort(int lis[], int size) 
{
	real_merge(lis, 0, size-1);
	return;
}

void Sort::real_merge(int lis[], int begin, int end)
{
	// 1. 递归中止条件: 当数组中没有元素或者仅有一个元素时，该数组本身就是有序的，无需进行排序 
	if(begin>=end)
	return;
	
	int mid=(begin+end)/2;
	
	// 2. 分别对数组的前半部分和后半部分进行递归排序
	real_merge(lis, begin, mid);
	real_merge(lis, mid+1, end);
	
	// 3. 将已经排好序的前半部分数组和后半部分数组进行合并 
	vector<int> temp;
	
	int pos1=begin;
	int pos2=mid+1;
	
	while(pos1<=mid&&pos2<=end)
	{
		if(lis[pos1]<lis[pos2])	
		{
			temp.push_back(lis[pos1]);
			pos1+=1;
		}
		else
		{
			temp.push_back(lis[pos2]);
			pos2+=1;
		}
	}
	
	while(pos1<=mid)
	{
		temp.push_back(lis[pos1]);
		pos1+=1;
	}
	
	while(pos2<=end)
	{
		temp.push_back(lis[pos2]);
		pos2+=1;
	}
	
	for(int i=begin,k=0;i<=end;i++,k++)
	{
		lis[i]=temp[k]; 
	}
	
	return;
}


/*
 * quick_sort: 快速排序
 * note: 快速排序的基本思想是: 首先在数组中选取一个主元，然后根据该主元对数组进行划分，大于该主元的放在主元后，小于该主元的放在主元前，然后以该主元为界将数组划分为两个部分，分别对这两个部分进行递归排序即可 
*/ 
void Sort::quick_sort(int lis[], int size)
{
	real_quick(lis, 0, size-1);
	return;
}

void Sort::real_quick(int lis[], int begin, int end)
{
	// 1. 递归中止条件: 当数组片段中仅含有一个元素或者没有元素时，无需进行排序，直接返回即可
	if(begin>=end)
	return;
	
	// 2. 进行划分过程，将数组中所有小于主元的元素放在主元之前，将数组中所有大于等于主元的元素放在主元之后 
	// 2.1 选择数组片段的首元素作为主元
	int pivot=lis[begin];  
	
	int lastpos=begin;     // 最后一个小于主元的元素的位置
	
	// 2.2 从下标begin+1开始遍历，每当在数组中遇到一个小于主元的值lis[i]，就先将最后一个小于主元的元素的位置lastpos加1，然后交换lis[i]和lis[lastpos] 
	for(int i=begin+1;i<=end;i++) 
	{
		if(lis[i]<pivot)   
		{
			lastpos+=1;
			swap(&lis[lastpos], &lis[i]);
		}
	}
	
	// 2.3 最后交换主元lis[begin]和最后一个小于主元的位置lis[lastpos]，从而将小于主元的放在主元前，大于等于主元的放在主元后 
	swap(&lis[begin], &lis[lastpos]);
	
	// 3. 以主元为界将数组片段划分为前后两段，对前后两段分别进行递归排序
	real_quick(lis, begin, lastpos-1);
	real_quick(lis, lastpos+1, end);
	
	return;
}
