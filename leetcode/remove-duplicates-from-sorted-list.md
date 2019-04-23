
## Remove duplicates from sorted list

### 题目描述

Given a sorted linked list, delete all duplicates such that each element appear only once.For example,
Given1->1->2, return1->2.
Given1->1->2->3->3, return1->2->3.（保留1个）

### 题目解析

对于当前节点和下一节点的值不相等的情况，那就一直往下走，代码中是p1移动到下一个节点的操作。代码如下：
```
            if(p1->val != p2->val) {
                p1 = p1->next;
                continue;
            }
```
当然如果当前节点和下一节点相同的情况下，我们就需要做两件事：

- 不断判断下面有几个点和当前点相等，代码如下：

```
while(p2->next != NULL && p1->val == p2->next->val) p2 = p2->next;
```

- 找到最后一个点和当前点相等的时候，直接把那个点的next赋值给当前点的next，然后那些点。即：

```
p1->next = p2->next;
delete p2;
```

### 代码实现

```
    ListNode *deleteDuplicates(ListNode *head) {
        if(head == NULL || head->next == NULL) return head;
        ListNode* p1 = head;
        while(p1 != NULL && p1->next != NULL) {
            ListNode* p2 = p1->next;
            if(p1->val != p2->val) {
                p1 = p1->next;
                continue;
            }
            while(p2->next != NULL && p1->val == p2->next->val) p2 = p2->next;
            p1->next = p2->next;
            delete p2;
            p1 = p1->next;
        }
        return head;
    }
```

## 删除链表中重复的节点（全部删除）

### 题目描述

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5

### 题目解析


### 代码实现

```
ListNode* deleteDuplication(ListNode* pHead)
    {
        if(pHead == NULL)
            return NULL;
        if(pHead->next== NULL)
            return pHead;
        if(pHead->val==pHead->next->val)
        {
            ListNode* pNode = pHead->next;
            while(pNode!=NULL && pNode->val==pHead->val)
                pNode=pNode->next;
            return deleteDuplication(pNode);
        }
        else
        {
            pHead->next=deleteDuplication(pHead->next);
            return pHead;
        }

    }
```
