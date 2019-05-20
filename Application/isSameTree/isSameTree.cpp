/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 判断给定的两个树是否相同非常简单，仍然是一个递归问题，只需要两个树的根结点的值相同，左子树和右子树对应分别相同，则两个树就是相同的

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p&&!q)
        return true;
        else if(p&&!q||!p&&q)
        return false;
        else
        {
            if(p->val==q->val&&isSameTree(p->left, q->left)&&isSameTree(p->right, q->right))
            return true;
            else
            return false;
        }
    }
};