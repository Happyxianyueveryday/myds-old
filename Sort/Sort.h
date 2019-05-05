#include <iostream>
#include <string>
#include <vector>

using namespace std;

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

