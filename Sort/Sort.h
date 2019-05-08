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
	void adjust(int lis[], int begin, int end);          // 对给定大顶堆的单次调整操作实现 
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
 * note: 插入排序的思路也较为简单: 插入排序第i轮循环将第i个元素依次和第i-1个，第i-2个，...，第1个元素比较，将其插入在前(i-1)个元素中合适的位置上即可 
 * note: 插入排序的思想非常简单，但是在数组中的插入过程的实现非常容易出错，要思路清晰，经常练习和回顾，见下面关于插入过程的核心思想 
*/
void Sort::insert_sort(int lis[], int size)
{
	for(int i=0;i<size;i++)
	{
		// 将lis[i]和lis[i-1],...,lis[0]依次比较，从而将lis[i]插入到前i-1个元素中的正确位置上 
		
		int tar=lis[i];   
		int ins=i-1;
		
		// 插入的核心思想是: 从要插入的元素的前一个元素(即下标为(i-1)的位置)开始，从后向前查找直到第一个满足lis[ins]<tar的元素，则lis[ins+1]就是插入点，从后往前找的目的是为了减少开销，从前向后也可以，但是开销较大 		
		while(ins>=0&&lis[ins]>tar)    
		{
			lis[ins+1]=lis[ins];
			ins--;
		}
		
		lis[ins+1]=tar;              // 数组的插入移动需要仔细思考，这里一开始写成了lis[k]=tar，出现了错误，因为lis[k]<tar，因此插入点应该是lis[k+1] 
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


/*
 * shell_sort: 希尔排序
 * link: 参考链接: https://blog.csdn.net/qq_39207948/article/details/80006224, https://www.cnblogs.com/yonghao/p/5151641.html 
 * note: 希尔排序的基本思想为: 首先以一个初始整数值作为步长(注释1)，将原始数组分为多个组(注释2)，然后使用普通插入排序对每个组内的元素进行排序，接着减小步长，重复上述步骤，即划分为多个组然后分别对每个组进行插入排序，直到步长减小到1为止 
 * 注释1: 关于步长序列的选择可以是任意的，只要能够逐步减小到1，一般所使用的步长序列是: size/2, size/4, size/8, ..., 1
 * 注释2: 关于希尔排序中如何根据步长来分组，下面举一个例子，存在数组{1,2,3,4,5,6,7,8}，假设步长为step=4，则该数组被分为4组: {1,5}, {2,6}, {3,7}, {4,8}；假设步长为2，则该数组被分为2组: {1,3,5,7}, {2,4,6,8} 
 * note: 希尔排序重点掌握其分组排序思想，即要能回答两个基本问题: (a) 步长序列如何选择？ (b)如何根据步长将原数组划分为多个分组（每个分组的首元素下标如何计算，每个分组中的所有元素下标如何计算），剩下的关于如何在一个组内进行插入排序的问题，请参见插入排序部分 
*/
void Sort::shell_sort(int lis[], int size)
{
	int step=size/2;   // 初始化步长为size/2 
	
	while(step>=1)
	{ 
		for(int i=0;i<step;i++)          // 第一层循环用于遍历各个分组，假设步长为step，则各个分组的首元素下标就是0,1,..., step-1
		{
			for(int k=i;k<size;k+=step)  // 第二层循环用于遍历一个分组中的各个元素，假设步长为step，当前分组的首元素下标为i，则各个分组的首元素下标就是i,i+step,i+2*step,... 
			{
				// 下面对组中的每个元素进行插入排序，这部分代码和普通插入排序类似，请参考普通插入排序算法的实现部分 
				// 插入的核心思想和过程是: 从要插入的元素tar的前一个元素开始，从后向前查找第一个满足lis[ins]<tar的元素lis[ins]，则该元素的下一个位置lis[ins+step]就是插入点 
				int ins=k-step;     // 从后向前第一个小于tar的数组元素的下标 
				int tar=lis[k];     // 要插入的值 
				
				while(ins>=0&&lis[ins]>tar) 
				{
					lis[ins+step]=lis[ins];
					ins-=step;
				}
				
				lis[ins+step]=tar;
			}
		}
		
		step/=2;       // 将步长减半，重复上述步骤 
	}
}


/*
 * heap_sort: 堆排序
 * note 1: 堆的基本定义: 堆是一种完全二叉树，且对于每个结点而言，满足当前结点大于当前结点的子结点的值，这就是大顶堆，若满足当前结点小于当前结点的子结点的值，则就是小顶堆 
 *		   一个大顶堆的左右子树都是大顶堆，一个小顶堆和左右子树都是小顶堆 
 * note 2: 堆排序的基本步骤: 首先由原始数组建立大顶堆，然后循环进行以下步骤：将堆顶元素与倒数第一个叶子结点的值进行交换，交换后重新调整堆为大顶堆 
 * note 3: 提供一个参考说明网址: https://www.jianshu.com/p/21bef3fc3030，写的非常详细，并且含有配图，显然比我的纯文字说明要清晰 
 * note 4: 堆的建立和堆的调整操作: 
 *         (1) 堆的建立: 从最后一个非叶子结点开始(最后一个非叶子结点的下标为(size/2-1)，重要结论需要记清)，倒序对每个非叶子结点作为根结点的大顶堆进行调整操作（调整操作请参见下面的"堆的调整"部分)） 
 *         (2) 堆的调整: 每次移出堆顶元素(即将堆顶元素与倒数第一个叶子结点交换)后都需要进行堆的调整
 *						 给定一个堆的调整过程为: 记堆顶的元素为val，需要追踪每轮循环后堆顶元素val所在的结点位置。循环进行以下步骤，直到值val所在结点是叶子结点或者值val所在的结点大于其左右子结点时停止：将值val所在的结点和其左右子结点的值比较，将值val所在的结点和左右子结点中的较大值结点交换值 
 * note 5: 堆排序相对于前面的几种排序难度较大，主要需要掌握好堆的建立和调整两种操作（其中堆的建立也是基于调整操作的），然后就是堆排序如何综合上述两种操作
 * note 6: 堆排序的算法还是要多进行训练，从而最后达到熟练 
*/ 
void Sort::heap_sort(int lis[], int size)
{
	// 1. 首先从原始数组构造堆，构造堆的算法为: 从最后一个非叶子结点(下标为size/2-1)开始，倒序对每个非叶子结点作为根结点的堆进行调整
	for(int i=size/2-1;i>=0;i--)
	{
		adjust(lis, i, size);
	}
	 
	// 2. 然后循环进行以下步骤，直到堆中的元素个数为0为止: 将整个大顶堆的堆顶元素(lis[0])和整个堆的最后一个叶子结点交换，然后从堆中移出最后一个叶子结点
	for(int i=size-1;i>=0;i--)   // i为堆的最后一个叶子结点的下标 
	{
		// 2.1 交换堆顶元素(lis[0])和堆的最后一个叶子结点(lis[i])的值 
		swap(&lis[0], &lis[i]);
		
		// 2.2 对整个大顶堆进行一次调整(和创建堆时对每个非叶子结点都需要调整不同，经过上述交换步骤中只有整个堆的根结点的值发生变化，因此只需要对整个堆的根结点进行一次调整) 
		adjust(lis, 0, i-1);       // 注意i-1为这时堆的最后一个叶子结点的下标 
	}
	
	return;
}

/*
 * adjust: 对由下标begin和end范围划定的子堆lis[begin, end]进行单次调整 
 * param begin: 需要调整的堆的根结点下标 
 * param end: 需要调整的堆的最后一个叶子结点的下标 
*/
void Sort::adjust(int lis[], int begin, int end)
{
	int pos=begin;   // 根结点的初始值所在的结点的下标，调整过程需要全程追踪堆的根结点的值所在的结点下标
	int flag=0;
	
	// 对给定堆的调整过程可以简记为: 记调整前堆顶的元素为val，需要追踪每轮循环后堆顶元素val所在的结点位置。循环进行以下步骤，直到值val所在结点是叶子结点或者值val所在的结点大于其左右子结点时停止：将值val所在的结点和其左右子结点的值比较，将值val所在的结点和左右子结点中的较大值结点交换值    
	while(!flag)
	{
		if(pos*2+1>end&&pos*2+2>end)               // 若值val到达叶子结点，无需再进行调整，直接退出循环 
		flag=1;
		else 
		{
			// 需要特别注意: 在比较当前结点和左右子结点的值之前，首先需要判断左右子结点是否存在 
			int left=(pos*2+1>end)?INT_MIN:lis[pos*2+1];    // 左子结点的值: 若不存在则设为INT_MIN 
			int right=(pos*2+2>end)?INT_MIN:lis[pos*2+2];   // 右子结点的值: 若不存在则设为INT_MIN
			
			if(left>lis[pos]&&left>right)          // 若值val所在结点的左子结点大于当前结点，并且大于右子结点，则将val所在的当前结点和左子结点的值交换，并利用下标pos继续追踪val所在的位置(交换后val到了左子结点) 
			{
				swap(&lis[pos], &lis[2*pos+1]);
				pos=2*pos+1;
			}
			else if(right>lis[pos]&&right>left)    // 若值val所在结点的右子结点大于当前结点，并且大于左子结点，则将val所在的当前结点和右子结点的值交换，并利用下标pos继续追踪val所在的位置(交换后val到了右子结点) 
			{
				swap(&lis[pos], &lis[2*pos+2]);
				pos=2*pos+2;
			}
			else                                  // 若值val所在的结点值大于其左右结点的值，这时说明值val已经调整到位，因此退出循环 
			flag=1;
		}
	}
	
	return;
	
	return;
}


