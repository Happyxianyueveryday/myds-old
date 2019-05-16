  # ThreadTrees: 线索树

  ## 1. 线索树的基本概念和定义
  线索树是基于二叉树（或者二叉搜索树）上进行改进的一种数据结构。对于普通二叉树中的结点，在左右子结点中存在空结点时，该结点的left和right字段被置为NULL，这时left和right字段的所占用的内存空间被浪费了。    
  
  因此线索树的基本定义为: 线索树规定在左子结点/右子结点为空时，将left指向当前结点在中序遍历中的前驱结点，将right指向当前结点在中序遍历中的后继结点。  
  
  根据上述定义，线索树中的结点可以定义如下：  

  ```
  struct ThreadNode
  {
      ThreadNode(int ival=0):val(ival),left(NULL),right(NULL),lflag(0),rflag(0)
      {
      }

      int val;
      ThreadNode *left;        // 指向当前结点的左子结点或者是中序遍历中的前驱结点的指针
      ThreadNode *right;       // 指向当前结点的右子结点或者是中序遍历中的后继结点的指针
      int lflag;               // 标志变量，lflag==0表示left指向左子结点，lflag==1表示left指向中序遍历中的前驱结点
      int rflag;               // 标志变量，rflag==0表示right指向右子结点，rflag==1表示right指向中序遍历中的后继结点
  };
  ```


## 2. 线索树的构建——二叉树的线索化算法


## 3. 线索树的两种基本操作
#### 3.1. 获取中序遍历首结点——getFirstNode操作

#### 3.2 获取中序遍历下一个结点——getNextNode操作
