# Edit distance(dynamic programing)

## 题目描述

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)You have the following 3 operations permitted on a word:a) Insert a character
b) Delete a character
c) Replace a character

## 题目解析

## 代码实现

```
int min3(int a, int b, int c)
{
	return (a < b) ? (a < c ? a : c) : (b < c ? b : c);
}
int minDistance(string word1, string word2) {
	//准备工作：获取字符串长度
	int strlen1 = word1.size();
	int strlen2 = word2.size();
	//准备工作：新建dp矩阵
	vector<vector<int> >dp(strlen1 + 1, vector<int>(strlen2 + 1, 0));
	//第一步：第一行，第一列分别置i
	for (int i = 1; i <= strlen1; i++)
		dp[i][0] = i;
	for (int i = 1; i <= strlen2; i++)
		dp[0][i] = i;
	//第二步：双层for循环进行递推
	for (int i = 1; i <= strlen1; i++)
	{
		for (int j = 1; j <= strlen2; j++)
		{
			int diff;
			if (word1[i - 1] == word2[j - 1])
				diff = 0;
			else
				diff = 1;
			dp[i][j] = min3(dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + diff);

		}
	}
	return dp[strlen1][strlen2];
}
```

# Add two numbers

## 题目描述

You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8

## 题目分析

链表版的两个数相加的题，题目是从个位到十位到百位……因此还是比较简单。

## 代码实现

```
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
	if (l1 == NULL)
		return l2;
	if (l2 == NULL)
		return l1;
	ListNode *result=new ListNode(-1);
	ListNode *p1 = l1;
	ListNode *p2 = l2;
	ListNode *p = result;
	int v = 0;
	int jin = 0;
	while (p1 != NULL || p2 != NULL||jin)
	{
		v = (p1 ? p1->val : 0) + (p2 ? p2->val : 0) + jin;
		jin = v / 10;
		v %= 10;
		ListNode *newnode = new ListNode(v);
		p->next = newnode;
		p = p->next;
		if (p1)
			p1 = p1->next;
		if (p2)
			p2 = p2->next;
	}
	return result->next;
}
```

# partition list

## 题目描述


Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.You should preserve the original relative order of the nodes in each of the two partitions.For example,
Given1->4->3->2->5->2and x = 3,
return1->2->2->4->3->5.

## 题目解析

最简单的方法，新建两个链表l1和l2，l1存放小于指定数字的链表部分，l2存放大于等于指定数字的链表部分。然后把他们拼接起来。

## 代码实现

```
ListNode *partition(ListNode *head, int x)
{
	ListNode *plist1 = new ListNode(0);
	ListNode *plist2 = new ListNode(0);
	ListNode *list1 = plist1;
	ListNode *list2 = plist2;
	while (head != NULL)
	{
		if (head->val < x)
		{
			ListNode *newnode = new ListNode(0);
			newnode->val = head->val;
			newnode->next = NULL;
			list1->next = newnode;
			list1 = list1->next;
		}
		else if (head->val >= x)
		{
			ListNode *bignode = new ListNode(0);
			bignode->val = head->val;
			bignode->next = NULL;
			list2->next = bignode;
			list2 = list2->next;
		}
		head = head->next;
	}
	list1->next = plist2->next;
	plist2->next = NULL;
	return plist1->next;
}
```