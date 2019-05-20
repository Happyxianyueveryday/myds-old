/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

// 验证一个二叉树是否为二叉搜索树的最直接方法就是使用中序遍历，若中序遍历得到递增序列，则原树为二叉搜索树，否则原树不为二叉搜索树

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(!root)
        return true;

        stack<TreeNode *> sta;
        vector<int> res;

        TreeNode *temp=root;

        while(temp)
        {
            sta.push(temp);
            temp=temp->left;        
        }

        while(sta.size())
        {
            TreeNode *now=sta.top();

            sta.pop();
            res.push_back(now->val);

            temp=now->right;

            while(temp)
            {
                sta.push(temp);
                temp=temp->left;
            }
        }

        int val=res[0];
        for(int i=1;i<res.size();i++)
        {
            if(res[i]<=val)
            return false;
            else
            val=res[i];
        }

        return true;  
    }
};