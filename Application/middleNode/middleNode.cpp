/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// 非常经典的快慢双指针题目，需要特别注意
// 本题的基本算法思路是: 创建一个快指针fast和慢指针slow，快指针fast和慢指针slow初始化为指向头结点，然后循环进行以下步骤: 将快指针一次移动两步，慢指针一次移动一步，直到快指针指向空结点或者快指针的下一个指针指向空结点时停止，退出循环并返回慢指针，这时慢指针slow就指向链表的中间结点

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode *slow=head, *fast=head;

        while(fast&&fast->next)
        {
            fast=fast->next->next;
            slow=slow->next;
        }

        return slow;
    }
};