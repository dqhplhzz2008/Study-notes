## Same Tree

### 题目描述

Given two binary trees, write a function to check if they are equal or not.Two binary trees are considered equal if they are structurally identical and the nodes have the same value.

### 思路说明

其实这个题非常简单，算是判断一个树是不是另一个树子树的基础版，不需要调用另一个子程序，直接递归自己这个程序即可。就是判断树上每一个结点当前的情况：

- p当前节点为空且q当前节点为空，true；
- p为空q不为空，或q为空p不为空，false；
- p->val==q->val，那么就判断它的左右子树；
- p->val!q->val，false。

判断完成后，逐层向上返回bool结果。

### 代码实现

```
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if(p==nullptr && q==nullptr)
            return true;
        if(p==nullptr || q==nullptr)
            return false;
        if(p->val==q->val)
            return isSameTree(p->left,q->left)&&isSameTree(p->right,q->right);
        else
            return false;
    }
```
