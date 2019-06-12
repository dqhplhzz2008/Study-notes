
## Search for a range

### 题目描述


Given a sorted array of integers, find the starting and ending position of a given target value.Your algorithm's runtime complexity must be in the order of O(log n).If the target is not found in the array, return[-1, -1].For example,
Given[5, 7, 7, 8, 8, 10]and target value 8,
return[3, 4].

### 题目解析

关键词：**有序数组**、**复杂度O(logn)**。这就很明显说明了一件事，题目想让我们使用二分查找的方法来实现。在C++的STL里面，已经由现成的函数帮我们实现返回第一个位置和最后一个位置的函数，也就是low_bound()和upper_bound()。

low_bound()和upper_bound()都是使用二分查找实现查找工作，两者都是返回一个迭代器（iterator），但是不同的是，low_bound()返回的是第一个大于或等于num的数字，找到返回该数字的地址，（若数组中没有该元素，则返回end），upper_bound()返回第一个大于num的数字的位置（如果数组没有该元素，同理）。因此，如果我们对low_bound()返回的地址减去起始地址，就得到了第一次出现目标数字的位置，对upper_bound()减去起始地址，就得到了目标数字下一个位置，再减1，得到最后一次出现目标数字的位置。代码实现见代码实现1。

这是一种取巧的方法，使用了STL中的Algorithm。但是，这样除了展示你会使用STL中的algorithm之外没有任何用处，所以还是需要去实现这个寻找过程。这个过程就是实现二分查找。

其实现具体过程很基础，不再重述。


### 代码实现1
```
#include<iostream>
#include<algorithm>
#include<vector>
//故意把所需要包含的头文件注明了
using namespace std;

vector<int> searchRange(int A[], int n, int target) {
	vector<int> result(2,-1);//默认2个值，均为-1
	//若传递过来的参数不合理，直接返回result
	if(A==nullptr || n<=0)
		return result;
	//数组不是STL标准的容器，其没有真正的iterator，所以退化为了指针，用指针来表示
	auto low=lower_bound(A,A+n,target)-A;//auto类型应该为int
	if(low==n||A[low]!=target)
		return result;
	//以上是说若在数组内没有找到target，那么high也不用找，直接返回result
	auto high=upper_bound(A,A+n,target)-A-1;
	result[0]=low;
	result[1]=high;
	return result;
}
```

### 代码实现2

```
vector<int> searchRange(int A[], int n, int target) {
	vector<int>result(2, -1);
	if (A == nullptr || n <= 0)
		return result;
	int low = 0, high = n - 1;
	while (low <= high)
	{
		int mid = (low + high) >>1;
		if (A[mid] < target)
			low = mid + 1;
		else
			high = mid - 1;
	}
	int low2 = 0; 
	int high2 = n - 1;
	while (low2 <= high2)
	{
		int mid2 = (low2 + high2) >> 1;
		if (A[mid2] <= target)
			low2 = mid2 + 1;
		else
			high2 = mid2 - 1;
	}
	if (low <= high2)
	{
		result[0] = low;
		result[1] = high2;
	}
	return result;
}


```

## Validate Binary Search Tree

### 题目描述


Given a binary tree, determine if it is a valid binary search tree (BST).Assume a BST is defined as follows:The left subtree of a node contains only nodes with keys less than the node's key.The right subtree of a node contains only nodes with keys greater than the node's key.Both the left and right subtrees must also be binary search trees.

### 题目解析


### 代码实现

```
    bool isValidBST(TreeNode *root) {
        if(root==nullptr)
            return true;
        if(root->left)
            if(toRight(root->left)->val>=root->val)
                return false;
        if(root->right)
            if(toLeft(root->right)->val<=root->val)
                return false;
        return isValidBST(root->left)&&isValidBST(root->right);
    }
    TreeNode* toLeft(TreeNode* root){
        while(root->left)
            root=root->left;
        return root;
    }
    TreeNode* toRight(TreeNode *root){
        while(root->right)
            root=root->right;
        return root;
    }
```
