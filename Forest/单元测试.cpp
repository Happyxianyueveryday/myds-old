#include "Forest.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

vector<int> levelorder(BinaryTreeNode *root)
{
	vector<int> res;
	
	if(!root)	
	return res;
	
	queue<BinaryTreeNode *> que;
	que.push(root);
	
	while(que.size())
	{
		BinaryTreeNode *now=que.front();
		que.pop();
		
		res.push_back(now->val);
		
		if(now->left)
		que.push(now->left);
		if(now->right)
		que.push(now->right);
	}
	
	return res;
}



int main(void)
{
	vector<int> preorder1={1,2,5,6,3,4,7};
	vector<int> postorder1={5,6,2,3,7,4,1};
	vector<int> preorder2={1,2,3,5,4};
	vector<int> postorder2={3,5,2,4,1};
	vector<int> preorder3={1,2,4,5,3,6,7};
	vector<int> postorder3={4,5,2,6,7,3,1};
	
	MultiTree tree1(preorder1, postorder1);
	MultiTree tree2(preorder2, postorder2);
	MultiTree tree3(preorder3, postorder3);
	
	vector<MultiTree> lis={tree1, tree2, tree3};
	Forest forest(lis);
	
	// 1. 测试森林的前序遍历序列 
	cout<<"测试森林的前序遍历序列："<<endl;
	vector<int> pre=forest.preorder();
	for(int i=0;i<pre.size();i++)
	{
		cout<<pre[i]<<" ";
	}
	cout<<endl;
	
	
	// 2. 测试森林的后序遍历序列
	cout<<"测试森林的后序遍历序列："<<endl;
	vector<int> post=forest.postorder();
	for(int i=0;i<post.size();i++)
	{
		cout<<post[i]<<" ";
	}
	cout<<endl;
	
	// 3. 测试森林转换为二叉树 
	cout<<"测试森林转换为二叉树："<<endl;
	BinaryTreeNode *root=forest.convertToBinaryTree();
	vector<int> level=levelorder(root);
	for(int i=0;i<level.size();i++)
	{
		cout<<level[i]<<" ";
	}
	cout<<endl;
	 
	
	// 4. 测试二叉树转换为森林 
	cout<<"测试二叉树转换为森林："<<endl;
	vector<TreeNode *> rootlis=Forest::convertToForest(root);
	Forest forest2(rootlis);
	
	pre=forest2.preorder();
	for(int i=0;i<pre.size();i++)
	{
		cout<<pre[i]<<" ";
	}
	cout<<endl;
	
	post=forest2.postorder();
	for(int i=0;i<post.size();i++)
	{
		cout<<post[i]<<" ";
	}
	cout<<endl;
}
