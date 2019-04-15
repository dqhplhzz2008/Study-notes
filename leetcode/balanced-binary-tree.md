## Balanced Binary Tree

###  题目描述


Given a binary tree, determine if it is height-balanced.For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

### 题目解析

见剑指offer题解（平衡二叉树）

### 代码实现

```
    int getDepth(TreeNode *root)
    {
        if(root == NULL)
            return 0;
        int leftDepth=getDepth(root -> left);
        int rightDepth=getDepth(root->right);
        return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    }
    bool isBalanced(TreeNode *root) {
        if(root == NULL)
            return true;
        int leftDepth = getDepth(root -> left);
        int rightDepth = getDepth(root -> right);
        if(leftDepth > rightDepth + 1 || leftDepth + 1 < rightDepth)
            return false;
        else
            return isBalanced(root->left)&&isBalanced(root->right);
    }
```
