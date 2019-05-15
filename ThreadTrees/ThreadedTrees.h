#include <iostream> 
#include <string>
#include <stack>
#include "tree.h"

using namespace std; 


struct ThreadNode
{
    ThreadNode(int ival=0):val(ival),left(NULL),right(NULL),lflag(0),rflag(0)
    {
    }

    int val;
    ThreadNode *left;
    ThreadNode *right;
    int lflag;
    int rflag;
};


/*
 * ThreadTree: 中序遍历的二叉搜索线索树
 * note 1: 在普通二叉树中，可能存在许多的结点只有左子结点或者右子结点，或者是叶子结点，这时该结点中left和right成员就处于空置状态
 * note 2: 为了在左子结点/右子结点为空的情况下利用left和right成员，规定: 当左子结点为空时，使用left字段记录当前结点在中序遍历时的前驱结点；当右子结点为空时，使用right字段记录当前结点在中序遍历时的后继结点，并额外新增lflag和rflag表明left字段和right字段指向的是前后驱结点还是左右子结点，这就构成了二叉线索树 
*/
class ThreadTree
{
	public:  
	// 1. 构造函数 
	ThreadTree();                                                      // 默认构造函数 
	ThreadTree(const Tree &other);                                     // 从普通二叉搜索树生成对应的线索树
	
	// 2. 拷贝控制 
	ThreadTree(const ThreadTree &other);                               // 拷贝构造函数  
	ThreadTree & operator = (const ThreadTree &other) = delete;        // 禁止拷贝赋值运算符的使用 
	
	// 3. 功能函数: 重点注意线索树的两种基本操作getFirstNode和getNextNode 
	vector<int> inorder();                                              // 获取当前线索树的中序遍历序列，该算法应用上述两个基本操作进行实现 
	
	// 4. 析构函数
	~ThreadTree();
	
	private:
	ThreadNode *treeroot;     // 线索树的根结点 
	
	ThreadNode *__copyTree(TreeNode *root);                              // 从二叉搜索树拷贝一个线索树的底层递归实现
	
	// 5. 二叉线索树的两种基本操作：获取线索树的中序遍历首结点，获取输入结点的下一个结点 
	ThreadNode *getFirstNode(ThreadNode *root);               // 线索树基本操作1: 获取给定的线索树中序遍历序列中的第一个结点 
	ThreadNode *getNextNode(ThreadNode *pos);                // 线索树基本操作2: 获取在中序遍历中当前结点的下一个结点
};


/*
 * ThreadTree: 默认构造函数 
*/
ThreadTree::ThreadTree()
{
	treeroot=NULL;
}


/*
 * ThreadTree: 根据普通二叉搜索树生成对应的线索树
 * note: 从普通二叉搜索树生成线索树的算法步骤可以划分为简单两步：
 *       (1) 第一步，从原始二叉搜索树进行深拷贝；
 *       (2) 第二步，在拷贝结果上通过进行依次中序遍历进行线索化：若当前结点的left为NULL，则令left指向当前结点在中序遍历中的前驱结点；若当前结点的right为NULL，则令right指向当前结点在中序遍历中的后继结点；并修改对应的状态标记变量 
*/ 
ThreadTree::ThreadTree(const Tree &other)
{
	// 1. 首先从输入的源二叉搜索树进行深拷贝，得到一个二叉搜索树 
	treeroot=__copyTree(other.getroot());    
	
	// 2. 然后进行该二叉搜索树的线索化，通过一次中序遍历进行实现，这里使用非递归方法进行实现（关于普通二叉树的中序遍历请参见二叉搜索树的部分，本处不再重复介绍） 
	// note: 使用中序遍历每次访问一个结点，将正在访问的结点进行线索化 
	stack<ThreadNode *> sta;
	
	ThreadNode *temp=treeroot;     // 用于遍历的临时指针 
	ThreadNode *nowprev=NULL;      // 当前结点now的前驱结点指针 
	
	while(temp)
	{
		sta.push(temp);
		temp=temp->left;
	}
	
	while(sta.size())
	{
		// 2.1 进行中序遍历所需要的常规步骤 
		ThreadNode *now=sta.top();    // 当前正在访问的和准备进行线索化的结点 
		sta.pop();
		
		temp=now->right;
		
		while(temp)
		{
			sta.push(temp); 
			temp=temp->left;
		}
		
		// 2.2 对当前结点now进行线索化，线索化规则按照线索树的定义: 若now->left==NULL，则将now->left指向当前结点now的前驱结点nowprev；若now->right==NULL，则将now->right指向当前结点的后继结点（当前结点now后下一个访问的结点就是当前的栈顶结点）；并设置对应的标志变量 
		if(!now->left)
		{
			now->left=nowprev;
			now->lflag=1;
		}
		if(!now->right)
		{
			// 注意首先判断栈是否为空，若访问当前结点后栈为空，说明当前结点是中序遍历中的最后一个结点，没有后继结点 
			if(sta.size())
			now->right=sta.top();
			else
			now->right=NULL;
			
			now->rflag=1;
		}
		
		// 2.3 更新当前结点now的前驱结点nowprev
		nowprev=now; 
	}
}

ThreadNode *ThreadTree::__copyTree(TreeNode *root)
{
	if(!root)
	return NULL;
	else
	{
		ThreadNode *now=new ThreadNode(root->val);
		now->left=__copyTree(root->left);
		now->right=__copyTree(root->right);
		
		return now;
	}
}


/*
 * getFirstNode: 线索树基本操作1: 获取给定的线索树中序遍历序列中的第一个结点，该操作的算法思想（见note）非常重要，务必非常熟练地理解和掌握 
 * param root: 输入的给定线索树的根结点 
 * return: 给定的线索树的中序遍历的首结点 
 * note: 给定一个线索树，其中序遍历的首结点必然是最左侧的结点，因此一直沿着左子结点的方向直到整个树最左侧的结点，返回该结点即可 
*/
ThreadNode *ThreadTree::getFirstNode(ThreadNode *root)
{
	// 1. 初始化游标指针now指向输入的线索树的根结点 
	ThreadNode *now=root;
	
	// 2. 移动游标指针now到线索树最左侧的结点: 直接从根结点开始一直向左移动到最后一个结点即可，判断最后一个结点只需根据标志变量lflag即可 
	while(now&&!now->lflag)   // lflag==1表明当前结点没有左子结点，这时当前结点就是最左侧的结点，直接退出循环并返回即可 
	{
		now=now->left;
	}
	
	return now;
}


/*
 * getNextNode: 线索树基本操作2: 获取在中序遍历中当前结点的下一个结点，该操作的算法思想（见note）非常重要，务必非常熟练地理解和掌握 
 * param pos: 输入的线索树结点 
 * return: 给定的结点在中序遍历中的下一个结点 
 * note: 给定一个线索树中的某个结点，要获得该结点在中序遍历中的下一个结点，站在中序遍历的角度上思考，其思路非常简单：
 *       (1) 若输入结点pos的rflag==1，根据二叉线索树结点的定义，这时沿着right必定能够达到后继结点，故直接返回pos->right；
 *       (2) 若输入结点pos的rflag==0，这时当前结点存在右子树，因为当前结点pos已经输出，因此中序遍历中的后继结点是当前结点的右子树pos->right中的中序遍历首结点，故直接返回getFirstNode(pos->right) （为什么不用处理左子树？因为左子树由getFirstNode方法处理了，可以使用一个示例来附辅助理解） 
*/          
ThreadNode *ThreadTree::getNextNode(ThreadNode *pos)
{
	if(pos->rflag)	
	return pos->right;
	else
	return getFirstNode(pos->right);
}


/* 
 * inorder: 对当前的线索树进行中序遍历，返回中序遍历结果
 * note: 本算法直接使用上述的线索树的两种基本操作进行完成，首先使用getFirstNode方法获取整个线索树中序遍历的首结点，然后不断使用getNextNode方法获取中序遍历中的后继结点，直到遇到空结点NULL为止 
*/
vector<int> ThreadTree::inorder()
{
	vector<int> res;
	
	ThreadNode *now=getFirstNode(treeroot);
	
	while(now)
	{
		res.push_back(now->val);
		now=getNextNode(now);
	}
	
	return res;
}


/*
 * ~ThreadTree: 析构函数 
 * note: 同样可以按照中序遍历的顺序来进行析构，使用getFirstNode和getNextNode两个方法进行遍历的同时进行删除即可 
*/
ThreadTree::~ThreadTree()
{
	ThreadNode *now=getFirstNode(treeroot);
	
	while(now)
	{
		ThreadNode *temp=now;
		now=getNextNode(now);
		delete now;
	} 
}
