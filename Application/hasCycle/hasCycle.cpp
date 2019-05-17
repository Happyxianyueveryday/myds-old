/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 探测给定的链表中是否存在环也是一个经典问题，使用的解法思想非常简单: 快慢指针法，初始化快指针fast和慢指针slow指向链表的首结点，快指针每次移动两步，慢指针每次移动一步，若快指针和慢指针相等则说明存在环，循环进行上述步骤，直到快指针或者慢指针指向空结点为止，这时说明不存在环

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *fast=head, *slow=head;   

        while(fast&&fast->next)
        {
            fast=fast->next->next;
            slow=slow->next;

            if(fast==slow)
            return true;
        }

        return false;
    }
};