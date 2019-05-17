/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 非常基础的链表问题，同样使用双指针法进行求解: 
// (1) 创建一个快指针fast和慢指针slow指向链表头结点head
// (2) 将快指针向前移动k步
// (3) 同时循环移动快指针和慢指针一步，直到快指针指向NULL，这时慢指针指向链表的倒数第k个结点

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *fast=head;
        ListNode *slow=head;
        ListNode *slowprev=NULL;

        for(int i=0;i<n;i++)
        {
            fast=fast->next;
        }

        while(fast)
        {
            slowprev=slow;
            fast=fast->next;
            slow=slow->next;
        }

        if(slowprev)
        slowprev->next=slow->next;
        else
        head=head->next;
        
        delete slow;  
        
        return head;
    }
};