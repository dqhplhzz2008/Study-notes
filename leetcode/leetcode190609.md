# Construct binary tree from preorder and inorder traversal

## 题目描述


Given preorder and inorder traversal of a tree, construct the binary tree.
Note: 
You may assume that duplicates do not exist in the tree.

## 思路

关于根据前序和中序如何得到二叉树的结构的计算方式，我就不重复了，之前的程序里面也有，这里就只说说代码里几个参数的思路。
**一定要做边界条件的判断！**
```
	root->left = build(preorder, pstart + 1, pstart + i - istart, inorder, istart, i - 1);
	root->right = build(preorder, pstart + i - istart + 1, pend, inorder, i + 1, iend);
```

对于左子树处理来说，中序遍历所要处理的位置就是根节点左侧的所有数字，所以自然起始位置就是`istart`，结束位置就是`i-1`；对于前序遍历来说表示就麻烦一些，起始位置还好，是`pstart+1`,结束位置是`pstart+(i-istart)`，其中i-istart是左子树的元素数。
对于右子树处理来说，中序遍历所要处理的位置就是根节点右侧的所有数字，所以自然起始位置就是`i+1`，结束位置就是`iend`；对于前序遍历来说，就是从左侧子树最后一个元素后面那个数字到最后一个，所以起始位置是`pstart + i - istart + 1`，结束位置是`pend`。

## 代码实现
```
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
	int presize = preorder.size();
	int insize = inorder.size();
	if (presize == 0 || insize == 0)
	{
		return NULL;
	}
	else if (presize != insize)
		return NULL;
	return build(preorder, 0, presize - 1, inorder, 0, insize - 1);
}

TreeNode* build(vector<int>&preorder, int pstart, int pend, vector<int>&inorder, int istart, int iend)
{
	if (pstart > pend || istart > iend)
		return NULL;
	int mid = preorder[pstart];
	TreeNode* root = new TreeNode(mid);
	int i = istart;
	for (; i <= iend; ++i)
	{
		if (inorder[i] == mid)
			break;
	}

	root->left = build(preorder, pstart + 1, pstart + i - istart, inorder, istart, i - 1);
	root->right = build(preorder, pstart + i - istart + 1, pend, inorder, i + 1, iend);
	return root;
}
```


# binary tree level order traversal ii

## 题目描述


Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

## 题目解析


## 代码实现

```
vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> >result;
        if(root==nullptr)
            return result;
        vector<int> temp;
        TreeNode *last=root;
        TreeNode *p;
        queue<TreeNode *>q;
        q.push(root);
        while(!q.empty())
        {
            p=q.front();
            temp.push_back(p->val);
            q.pop();
            if(p->left)
                q.push(p->left);
            if(p->right)
                q.push(p->right);
            if(p==last)
            {
                result.push_back(temp);
                temp.clear();
                last=q.back();
            }
        }
        
        reverse(result.begin(),result.end());
        return result;
    }
```

# Minimum path sum

## 题目描述


Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.Note: You can only move either down or right at any point in time.

## 题目解析


## 代码实现

```
int minPathSum(vector<vector<int> > &grid) {
	int row = grid.size();//多少行
	int col = grid[0].size();//多少列
	vector<vector<int> >dp(row, vector<int>(col, 0));
	dp[0][0] = grid[0][0];
	//第一行
	for (int i = 1; i < col; i++)
	{
		dp[0][i] = dp[0][i - 1] + grid[0][i];
	}
	//第一列
	for (int i = 1; i < row; i++)
	{
		dp[i][0] = dp[i - 1][0] + grid[i][0];
	}
	for (int i = 1; i < row; i++)
	{
		for (int j = 1; j < col; j++)
		{
			dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
		}
	}
	return dp[row-1][col-1];
}
```