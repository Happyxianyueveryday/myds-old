/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 很经典的链表习题，本题的算法步骤非常简单，主要难点在于如何简化代码，将实现写的简单明晰

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *res=new ListNode(0);   // 结果链表

        ListNode *pos1=l1;   // 遍历链表l1的游标指针
        ListNode *pos2=l2;   // 遍历链表l2的游标指针
        ListNode *respos=res;// 遍历结果链表的游标指针

        int carrier=0;       // 加法进位值

        while(l1||l2||carrier)
        {
            int val=(((l1)?l1->val:0)+((l2)?l2->val:0)+carrier)%10;    // 计算本位上的结果
            carrier=(((l1)?l1->val:0)+((l2)?l2->val:0)+carrier)/10;    // 计算新的进位值

            respos->next=new ListNode(val);

            l1=(l1)?l1->next:l1;
            l2=(l2)?l2->next:l2;
            respos=respos->next;
        }

        ListNode *temp=res;
        res=res->next;
        
        return res;
    }
};