#include "MultiTree.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/**
 * Forest: 由孩子兄弟表示法所表示的多叉树组成的森林
 * note: 由于需要具体访问多叉树类的底层指针结构，因此本类声明为多叉树的友元
 */
class Forest 
{
    public:
    // 1. constructor
    Forest();                       	  // 默认构造函数，创建空的森林
    Forest(const vector<MultiTree> &res); // 构造函数，从多叉树的列表构造森林
    Forest(const vector<TreeNode *> &res);// 构造函数，从多叉树的根结点指针列表构造森林  

    // 2. copy_controller
    Forest(const Forest &other) = delete;                 // 禁用拷贝构造函数
    Forest & operator = (const Forest &other) = delete;   // 禁用拷贝赋值运算符

    // 3. methods
    BinaryTreeNode *convertToBinaryTree();                			 // 将当前的森林转化为二叉树
    static vector<TreeNode *> convertToForest(BinaryTreeNode *root); // 将给定的二叉树转换为森林
    vector<int> preorder();  // 生成当前森林的前序遍历序列
    vector<int> postorder(); // 生成当前森林的后序遍历序列

    // 4. destructor
    ~Forest();

    private:
    // 5. domains
    vector<MultiTree> treeroot;
    
    // 6. private functions
    static TreeNode *convertMultiToBinaryTree(BinaryTreeNode *root);     // 将二叉树逆向变换为多叉树 
};

/**
 * Forest: 默认构造函数，构造一个空的森林
 */
Forest::Forest()
{
}

/**
 * Forest: 构造函数，从多叉树的列表构造森林
 */   
Forest::Forest(const vector<MultiTree> &res)
{
    for(int i=0;i<res.size();i++)
    {
        treeroot.push_back(res[i]);
    }
}

/**
 * Forest: 构造函数，从多叉树的根结点指针列表构造森林 
 */   
Forest::Forest(const vector<TreeNode *> &res)
{
	for(int i=0;i<res.size();i++)
	{
		treeroot.push_back(MultiTree(res[i]));
	}
}

/**
 * convertToBinaryTree: 将当前的森林转化为二叉树
 * return: 由当前森林转化得到的二叉树
 * note:  将森林转换成二叉树的基本步骤如下所示：
 		(1) 将森林中的每棵多叉树转换为二叉树 
 		(2) 从多叉树转换为二叉树的算法中，得到的每棵二叉树的根结点的right指针均为空（回顾一下，因为多叉树转二叉树的算法是，令right指针等于当前结点的兄弟指针brother，令left指针等于当前结点的儿子指针child） 
 		(3) 因此只需要将森林中第一棵树根结点的right指针指向第二棵树，第二棵树根结点的right指针指向第三棵树，...，第n-1棵树根结点的right指针指向第n棵树即可
 */
BinaryTreeNode *Forest::convertToBinaryTree()
{
	// 1. 将当前森林中的每一棵树由多叉树转换为二叉树 
	vector<BinaryTreeNode *> res;
	for(int i=0;i<treeroot.size();i++)
	{
		res.push_back(treeroot[i].convertToBinaryTree());	
	}  
	
	// 2. 依次将第i棵树的根结点的right指针指向第i+1棵树
	for(int i=0;i<treeroot.size()-1;i++)
	{
		res[i]->right=res[i+1];
	} 
	
	return res[0];
}

/**
 * convertToForest: 将给定的二叉树转换为森林
 * return: 由给定的二叉树转化得到的森林
 * note 1: 根据上述的森林转换为二叉树的算法，很容易得到将二叉树转换为森林的算法
 * note 2: 在森林转换为二叉树的算法中，是首先将森林中的每一棵多叉树转化为二叉树，然后令第i棵二叉树根结点的right指针指向第i+1棵二叉树 
 * note 3: 因此将二叉树转换为森林实际上就是上述过程的逆过程，核心步骤简述如下：
 			(1) 从根结点开始，沿着right指针也即右子结点的方向，沿途遇到的每一个结点都记录下来作为森林中一个二叉树的根结点，同时将各个根结点的right指针置为空 
 			(2) 将上述步骤中得到的二叉树逆向转化为多叉树，转换方法非常简单：多叉树中结点的child指针等于二叉树中对应结点的left指针，多叉树中结点的brother指针等于二叉树中对应结点的right指针 
 */
vector<TreeNode *> Forest::convertToForest(BinaryTreeNode *root)
{
	// 1. 首先分离各个二叉树
	vector<BinaryTreeNode *> lis;
	BinaryTreeNode *now=root;
	
	while(now)
	{
		lis.push_back(now);
		BinaryTreeNode *temp=now->right;
		now->right=NULL;
		now=temp;
	}
	
	// 2. 然后将各个二叉树逆向转换为多叉树
	vector<TreeNode *> res;
	for(int i=0;i<lis.size();i++)
	{
		res.push_back(Forest::convertMultiToBinaryTree(lis[i]));
	} 
	
	return res;
}

TreeNode *Forest::convertMultiToBinaryTree(BinaryTreeNode *root)
{
	if(!root)
	return NULL;
	else
	{
		TreeNode *res=new TreeNode(root->val);
		res->child=convertMultiToBinaryTree(root->left);
		res->brother=convertMultiToBinaryTree(root->right);
		
		return res;
	}
} 

/**
 * preorder: 生成当前森林的前序遍历序列
 * return: 当前森林的前序遍历序列
 * note: 森林的前序遍历算法的主要步骤可以概括为: 依次取出森林中的每一棵树，对每棵树依次进行前序遍历即可
 */
vector<int> Forest::preorder()
{
    vector<int> res;

    for(int i=0;i<treeroot.size();i++)
    {
        vector<int> temp=treeroot[i].preorder();
        for(int i=0;i<temp.size();i++)
        {
            res.push_back(temp[i]);
        }
    }

    return res;
}

/**
 * postorder: 生成当前森林的后序遍历序列
 * return: 当前森林的后序遍历序列
 * note: 森林的后序遍历算法的主要步骤可以概括为: 依次取出森林中的每一棵树，对每棵树依次进行后序遍历即可
 */
vector<int> Forest::postorder()
{
    vector<int> res;

    for(int i=0;i<treeroot.size();i++)
    {
        vector<int> temp=treeroot[i].postorder();
        for(int i=0;i<temp.size();i++)
        {
            res.push_back(temp[i]);
        }
    }

    return res;
}

/**
 * Forest: 森林的析构函数
 * note: 森林的析构函数实际上不需要做任何的额外操作，因为vector的析构过程中会自动调用MultiTree的析构函数 
 */
Forest::~Forest()
{
}
