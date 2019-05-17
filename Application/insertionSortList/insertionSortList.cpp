/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 对链表进行插入排序是典型的习题: 首先增加头部哑结点，然后直接使用一个游标指针now遍历整个链表中的每一个结点，从原链表的第二个结点开始，对每一个结点，将该结点插入到该结点前的合适位置上

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        // 0. 若链表为空或者只有单结点，则无需进行排序，直接返回即可
        if(!head||!head->next)        
        return head;

        // 1. 为原始链表增加头部哑结点
        ListNode *now=head->next, *nowprev=head;  // 当前需要进行插入的结点now和前驱结点nowprev

        ListNode *newhead=new ListNode(0);
        newhead->next=head;
        head=newhead;

        // 2. 遍历链表中的每一个结点，将当前结点插入到当前结点之前的合适位置上
        while(now)
        {
            ListNode *pos=head->next, *posprev=head;    // 插入点指针pos和插入点的前驱结点posprev
            while(pos&&pos->val<now->val)
            {
                posprev=pos;
                pos=pos->next;
            }

            if(pos!=now)      
            {
                // 将当前结点now从原位置删除，并插入到结点pos之前
                nowprev->next=now->next;
                now->next=pos;
                posprev->next=now;

                // 更新游标指针now和nowprev
                nowprev=nowprev;
                now=nowprev->next;
            }
            else    // 若pos==now，则位置不需要变换，无需进行插入
            {
                nowprev=now;
                now=now->next;
            }
        }

        ListNode *temp=head;
        head=head->next;
        delete temp;

        return head;
    }
};