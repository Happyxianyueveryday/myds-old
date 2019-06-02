package com.pzh.threadtree;
import com.pzh.threadnode.ThreadNode;
import java.util.*;

public class ThreadTree
{
	// 1. domains
	private ThreadNode treeroot;
	
	// 2. constructor
	/**
	 * @ThreadTree: 从前序遍历和中序遍历构造二叉线索树
	 * @param preorder: 前序遍历序列
	 * @param inorder: 中序遍历序列
	 * @param _nullflag: 用于区分函数重载的哑元，可以传入一个任意值
	 */
	public ThreadTree(ArrayList<Integer> preorder, ArrayList<Integer> inorder, int _nullflag)
	{
		// 1. 构造二叉树
		this.treeroot=this.__buildTree1(preorder, inorder);
		
		// 2. 将构造出的二叉树进行中序线索化
		Stack<ThreadNode> sta=new Stack<ThreadNode>();
		
		ThreadNode temp=this.treeroot;
		ThreadNode nowprev=null; 
		
		while(temp!=null)
		{
			sta.push(temp);
			temp=temp.left;
		}
		
		while(!sta.empty())
		{
			ThreadNode now=sta.pop();
			
			temp=now.right;
			while(temp!=null)
			{
				sta.push(temp);
				temp=temp.left;
			}
			
			if(now.left==null)
			{
				now.lflag=1;
				now.left=nowprev;
			}
			if(now.right==null)
			{
				now.rflag=1;
				if(!sta.empty())
					now.right=sta.peek();
			}
			
			nowprev=now;
		}
		
		return;
	}
	
	private ThreadNode __buildTree1(ArrayList<Integer> preorder, ArrayList<Integer> inorder)
	{
		if(preorder.size()==0||inorder.size()==0)
			return null;
		
		ThreadNode root=new ThreadNode(preorder.get(0));
		
		int index=-1;
		for(int i=0;i<inorder.size();i++)
		{
			if(inorder.get(i)==preorder.get(0))
			{
				index=i;
				break;
			}
		}
		
		ArrayList<Integer> left=new ArrayList<Integer>();
		ArrayList<Integer> right=new ArrayList<Integer>();
		
		for(int i=0;i<inorder.size();i++)
		{
			if(i<index)
				left.add(inorder.get(i));
			else if(i>index)
				right.add(inorder.get(i));
		}
		
		preorder.remove(0);
		root.left=this.__buildTree1(preorder, left);
		root.right=this.__buildTree1(preorder, right);
		
		return root;
	}
	
	/**
	 * @ThreadTree: 从后序遍历和中序遍历构造二叉树
	 * @param postorder: 后序遍历序列
	 * @param inorder: 中序遍历序列
	 */
	public ThreadTree(ArrayList<Integer> postorder, ArrayList<Integer> inorder)
	{
		// 1. 构造二叉树
		this.treeroot=this.__buildTree2(postorder, inorder);
				
		// 2. 将构造出的二叉树进行中序线索化
		// 2. 将构造出的二叉树进行中序线索化
		Stack<ThreadNode> sta=new Stack<ThreadNode>();
				
		ThreadNode temp=this.treeroot;
		ThreadNode nowprev=null; 
				
		while(temp!=null)
		{
			sta.push(temp);
			temp=temp.left;
		}
				
		while(!sta.empty())
		{
			ThreadNode now=sta.pop();
					
			temp=now.right;
			while(temp!=null)
			{
				sta.push(temp);
				temp=temp.left;
			}
					
			if(now.left==null)
			{
				now.lflag=1;
				now.left=nowprev;
			}
			if(now.right==null)
			{
				now.rflag=1;
				if(!sta.empty())
					now.right=sta.peek();
			}
					
			nowprev=now;
		}
		
		return;
	}
	
	private ThreadNode __buildTree2(ArrayList<Integer> postorder, ArrayList<Integer> inorder)
	{
		if(inorder.size()==0||postorder.size()==0)
			return null;
		
		ThreadNode root=new ThreadNode(postorder.get(postorder.size()-1));
		
		int index=-1;
		for(int i=0;i<inorder.size();i++)
		{
			if(inorder.get(i)==postorder.get(postorder.size()-1))
			{
				index=i;
				break;
			}
		}
		
		ArrayList<Integer> left=new ArrayList<Integer>();
		ArrayList<Integer> right=new ArrayList<Integer>();
		
		for(int i=0;i<inorder.size();i++)
		{
			if(i<index)
				left.add(inorder.get(i)); 
			else if(i>index)
				right.add(inorder.get(i));
		}
		
		postorder.remove(postorder.size()-1);
		root.right=this.__buildTree2(postorder, right);   // 易错点：需要特别注意，使用后序遍历序列和中序遍历狗啊早序列时，需要首先构造右子树，因为后序遍历是按左子树->右子树->根节点进行遍历的，而我们的构造过程是反向进行的
		root.left=this.__buildTree2(postorder, left);
		
		return root;
	}
	
	/**
	 * @getFirstNode: 获取到二叉线索树的中序遍历的第一个结点
	 * @param root: 输入的二叉线索树
	 * @return: 二叉线索树的中序遍历的第一个结点
	 * @note: 二叉线索树的中序遍历的第一个结点必定是整个二叉线索树中最左侧的结点，直接返回该结点即可
	 */
	private ThreadNode getFirstNode(ThreadNode root)
	{
		ThreadNode now=root;
		
		while(now.lflag!=1)
		{
			now=now.left;
		}
		
		return now;
	}
	
	/**
	 * @getNextNode: 获取到二叉线索树的中序遍历的下一个结点
	 * @param now: 二叉线索树中序遍历中的当前结点
	 * @return: 二叉线索树的中序遍历的下一个结点
	 * @note: 假设二叉线索树中的当前结点为now，则:(1)若当前结点的右子树存在，即now.rflag==0，则下一个结点是右子树的中序遍历的第一个结点，即this.getFirstNode(root.right)
	 *                                  (2)若当前结点的右子树不存在，即now.rflag==1，则这时now.right就指向中序遍历的下一个结点，即now.right
	 */
	private ThreadNode getNextNode(ThreadNode now)
	{
		if(now.rflag==0)
			return this.getFirstNode(now.right);
		else 
			return now.right;
	}
	
	/**
	 * @getLastNode: 获取到二叉线索树的中序遍历的最后一个结点
	 * @return: 二叉线索树的中序遍历的最后一个结点
	 * @note: 二叉线索树的中序遍历的最后一个结点一定是整个二叉树中最右侧的结点，直接返回该结点即可
	 */
	private ThreadNode getLastNode(ThreadNode root)
	{
		ThreadNode now=root;
		
		while(now.rflag!=1)
		{
			now=now.right;
		}
		
		return now;
	}
	
	/**
	 * @getPrevNode: 获取到二叉线索树的中序遍历的上一个结点
	 * @param now: 二叉线索树中序遍历中的当前结点
	 * @return: 二叉线索树中序遍历中的上一个结点
	 * @note: 假设二叉线索树中的当前结点为now，则:(1)若当前结点的左子树存在，即now.lflag==0，则当前结点的上一个结点就是左子树now.left的中序遍历的最后一个结点，即this.getLastNode(root.left)
	 *                                  (2)若当前结点的左子树不存在，即now.lflag==1，则now.left就指向当前结点在中序遍历中的上一个结点
	 */
	private ThreadNode getPrevNode(ThreadNode now)
	{
		if(now.lflag==0)
			return this.getLastNode(now.left);
		else
			return now.left;
	}
	
	/**
	 * @getInorder: 得到二叉线索树的中序遍历序列
	 * @return: 当前二叉线索树的中序遍历序列
	 */
	public String getInorder()
	{
		ThreadNode now=this.getFirstNode(this.treeroot);
		String res=new String("");
		
		while(now!=null)
		{
			res=res+String.valueOf(now.val)+" ";
			now=this.getNextNode(now);
		}
		
		return res;
	}
	
	/**
	 * @getReverseInorder: 得到二叉线索树的反向中序遍历序列
	 * @return: 当前二叉线索树的反向中序遍历序列
	 */
	public String getReverseInorder()
	{
		ThreadNode now=this.getLastNode(this.treeroot);
		String res=new String("");
		
		while(now!=null)
		{
			res=res+String.valueOf(now.val)+" ";
			now=this.getPrevNode(now);
		}
		
		return res;
	}
	
	/**
	 * @main: 单元测试
	 */
	public static void main(String [] args)
	{
		Integer [] in= {2,5,9,12,15,16,17,18,19};
		Integer [] pre= {12,5,2,9,18,15,17,16,19};
		Integer [] post= {2,9,5,16,17,15,19,18,12};
		
		ArrayList<Integer> inorder = new ArrayList<Integer>(Arrays.asList(in));
		ArrayList<Integer> preorder = new ArrayList<Integer>(Arrays.asList(pre));
		ArrayList<Integer> postorder = new ArrayList<Integer>(Arrays.asList(post));
		
		ThreadTree tree1=new ThreadTree(preorder, inorder, 1);
		ThreadTree tree2=new ThreadTree(postorder, inorder);
		
		System.out.println(tree1.getInorder());
		System.out.println(tree1.getReverseInorder());
		System.out.println(tree2.getInorder());
		System.out.println(tree2.getReverseInorder());
	}
}