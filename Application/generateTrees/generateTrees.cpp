/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<TreeNode *> generateTrees(int n) 
    {
        if(n==0)
        {
            vector<TreeNode *> res;
            return res;
        }
        else
        return __realGenerate(1, n);
    }

    vector<TreeNode *> __realGenerate(int begin, int end)
    {
        vector<TreeNode *> res;

        if(begin>end)
        {
            res.push_back(NULL);
            return res;
        }
        else if(begin==end)
        {
            TreeNode *root=new TreeNode(begin);
            res.push_back(root);
            return res;
        }
        else
        {
            for(int i=begin;i<=end;i++)
            {
                vector<TreeNode *> left=__realGenerate(begin, i-1);
                vector<TreeNode *> right=__realGenerate(i+1, end);

                for(int m=0;m<left.size();m++)
                {
                    for(int n=0;n<right.size();n++)
                    {
                        TreeNode *root=new TreeNode(i);  // 注意为每种树生成一个新的根结点
                        root->left=left[m];
                        root->right=right[n];

                        res.push_back(root);
                    }
                }
            }
            return res;
        }
    }
};