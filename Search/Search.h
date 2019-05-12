#include <iostream> 

using namespace std;

class Search
{
	public:
	int seq_search(int lis[], int size, int target);        // 顺序查找算法  
	int binary_search(int lis[], int size, int target);     // 二分查找算法 
};

/*
 * seq_search: 顺序查找算法
 * param lis: 输入的有序数组 
 * param size: 输入的数组的大小 
 * param target: 要查找的目标值 
 * note: 最基本的查找方法，几乎每天都在使用，算法的基本思想是: 依次遍历访问数组中的每一个元素，若当前元素的值和目标值相等，就立即返回其下标 
*/
int Search::seq_search(int lis[], int size, int target)
{
	// 1. 遍历整个数组来查找目标值的下标，查找到则立即返回 
	for(int i=0;i<size;i++)
	{
		if(lis[i]==target)
		return i;
	}
	
	// 2. 若查找不到等于目标值的元素，则返回-1表示查找不到对应的元素 
	return -1;
}


/*
 * binary_search: 二分查找算法 
 * param lis: 输入的有序数组 
 * param size: 输入的数组的大小 
 * param target: 要查找的目标值 
 * note 1: 二分查找是查找算法中最重要的查找算法，虽然思想很简单，但是一次就写出完全正确的代码却并不容易，绝不可以轻视，其中的下标变换稍微改动都可能导致很隐蔽的错误，务必做到非常熟练的程度 
 * note 2: 二分查找算法的基本思想是: 首先比较数组的中间元素和目标值的大小，若相等，则直接返回中间元素的下标；若目标值大于中间元素，则在左半部分数组查找（下标范围为0~mid-1）；若目标值小于中间元素，则在右半部分数组查找（下标范围为mid+1~size-1） 
 * note 3: 关于使用(begin+end)/2可能导致溢出的情况，请参见: https://zhuanlan.zhihu.com/p/32719708
*/
int Search::binary_search(int lis[], int size, int target)
{
	int begin=0;       // 待查找的数组片段的起始元素下标  
	int end=size-1;    // 待查找的数组片段的终止元素下标  
	
	while(begin<=end)
	{
		int mid=begin+(end-begin)/2;    // 待查找的数组片段的中间元素下标，为什么这里使用减法，而非(begin+end)/2呢，因为(begin+end)/2当数组较大时存在溢出风险 
		
		if(target>lis[mid])         // 若目标值大于数组中间位置，则在数组的后半部分查找 
		begin=mid+1;                // 注意，改变范围时begin=mid+1，而不能包括mid，因为mid已经比较过了，即begin=mid是错误的 
		else if(target<lis[mid])    // 若目标值小于数组中间位置，则在数组的前半部分查找 
		end=mid-1;  
		else
		return mid;
	}
	
	return -1;
}

