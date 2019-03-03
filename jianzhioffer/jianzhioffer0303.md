## 题目1 斐波那契数列

### 题目描述
大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）。n<=39

### 代码
递归方法：

    int Fibonacci(int n) {
        if(n==0)
            return 0;
        if(n==1||n==2)
            return 1;
        return Fibonacci(n-1)+Fibonacci(n-2);

    }
非递归方法：

    int Fibonacci(int n) {
            int first = 0;
            int second = 1;
             
            int result = n;
            for(int i = 2; i<=n; i++){
                result = first + second;
                first = second;
                second = result;
            }
            return result;
        }

## 题目2 青蛙跳台阶 

### 题目描述

一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

### 题目解析
对于这种问题我们可以这样分析。在第一次跳台阶的时候，它可以选择跳1个台阶，也可以选择跳两个台阶。对于它要跳n个台阶来说（设为f(n)），假如第一次跳了1个台阶，那么第二次跳就是f(n-1)的问题；假如第一次跳了2个台阶，那么第二次就是f(n-2)的问题。对于第二次跳也是如此，就是分别是f(n-2)和f(n-3)（对于第一次跳了1阶的情况下）、f(n-3)和f(n-4)（对于第一次跳了2阶的情况下），依次类推下去，成为一个递归。特别的，当n=1的时候，只有一种跳法（只跳一阶），当n=2的时候，有两种跳法（跳1阶跳两次，跳2阶跳一次）。实际上这就是一个斐波那契数列。

### 代码

    int jumpFloor(int number) {
            if(number==1)
                return 1;
            else if(number==2)
                return 2;
            else
                return jumpFloor(number-1)+jumpFloor(number-2);  
        }

## 题目3 变态跳台阶

### 题目描述

一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。

### 题目解析
当一个青蛙跳上n级台阶有以下的情况：
|n|情况数|情况|
|--|--|--|
|1|1|(1)|
|2|2|(1,1),(2)|
|3|4|(1,1,1),(1,2),(2,1),(3)|
|4|8|(1,1,1,1),(1,2,1),(1,1,2),(2,1,1),(2,2),(1,3),(3,1),(4)|
|……|……|……|
|n|2*f(n-1)|(1)|

通过尝试，可以发现规律，当n>1的时候，f(n)=2*f(n-1)。

### 代码

     int jumpFloorII(int number) {
    	 if(number<1)
    		 return -1;
    	 else if(number==1)
    		 return 1;
    	 else
    		 return 2*jumpFloorII(n-1);
     }

## 题目4 矩形覆盖 

### 题目描述

我们可以用2 * 1的小矩形横着或者竖着去覆盖更大的矩形。请问用n个2 * 1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？

### 题目解析
对于这种问题，我们还是需要进行分析。

|n|情况数|情况（括号中1为竖着，2为横着）|
|--|--|--|
|1|1|(1)|
|2|2|(1,1),(2,2)|

当n=3的时候，我们发现，若固定了第三块砖的放置方式，那么前两块砖有两种放置方式（f(2)）；若固定了第二块和第三块的放置方式，则前一块砖有一种放置方式（f(1)）。以此类推，可以得出f(n)=f(n-1)+f(n-2)，当n>2的时候。

### 代码

    int rectCover(int number) {
        if(number<=0)
            return 0;
        else if(number==1)
            return 1;
        else if(number==2)
            return 2;
        else
            return rectCover(number-1)+rectCover(number-2);
    }

## 题目5 二进制中1的个数 

### 题目描述
输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。

### 题目解析

思路很简单，利用与的特性：1&1=1，0&1=0就可以进行判断。

### 代码

     int  NumberOf1(int n) {
    	 int count=0;
    	 for(int i=0;i<32;i++)
    	 //32位是由int决定
    	 {
    		 if((n>>i)&1)
    			 count++;
    	 }
    	 return count;
     }

## 题目6 调整数组，使奇数位于偶数前面

### 题目描述

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，并保证奇数和奇数，偶数和偶数之间的相对位置不变。

### 题目解析
其实这个可以借助于类似于冒泡法的思想，不过这样的复杂度有O(n<sup>2</sup>)，并且空间复杂度也较高。因此可以使用下面的方法。借鉴了插入排序。
### 代码

    void reOrderArray(vector<int> &array) {
            for(int i = 0;i < array.size();i++){
                for(int j = array.size()-1; j>i;j--){
                    if(array[j]%2==1&&array[j-1]%2==0)
                        swap(array[j],array[j-1]);
                }
            }
        }

## 题目7 链表倒数第k个结点

### 题目描述

输入一个链表，输出该链表中倒数第k个结点。

### 题目解析

我们很容易可以想到，由于这是一个单向链表，所以我们可以第一遍先遍历这个链表，看有多少个结点（假设为n），然后计算出pos=n-k+1，然后我们只需要再遍历一遍这个链表，输出第n-k+1个结点的值即可。
但是要注意**鲁棒性**。我们要考虑，如果这个链表为空呢？如果这个链表的结点数不到k个呢？那就需要对代码进行补充和完善。

### 代码

    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
    		if (pListHead == NULL)
    			return NULL;
    		ListNode* list1 = pListHead;
    		int count=1;
    		int pos = 0;
    		while (list1)
    		{
    			++count;
    			list1 = list1->next;
    		}
    		if (count<=k)
    			return list1;
    		pos = count - k + 1;
    		int n = 1;
    		ListNode* list2 = pListHead;
    		while (list2 && n < pos - 1)
    		{
    			list2 = list2->next;
    			++n;
    		}
    		return list2;
    
    	}

## 题目8 翻转链表

### 题目描述

输入一个链表，反转链表后，输出新链表的表头。

### 题目解析

首先我们应该考虑两个问题（**鲁棒性**）：
1. 链表为空呢？返回空。
2. 链表就只有一个结点呢？返回这个结点。

其它一般情况就是多个结点了。为了正确翻转一个链表，需要调整链表中指针的方向。我们假设有下面三个结点：**a->b->c**，假设我们要翻转b的next指向a，那么指向a之后，b和c之间的联系就断了，因此我们需要把结点c的地址保存下来。也就是说，我们在调整结点b的next指针的时候，除了需要知道结点b本身，还需要知道结点b的前一个结点a，因为我们要把结点b的next指针指向a。同时，我们还需要实现保存b的一个结点c，以防止链表断开。

我们新建一个next指针，让它来保存b指针的next所指向的地址，然后把a的next指向NULL，然后令node=a，然后把lnode=b；这个时候，进入下一个循环，next指向了c，然后把b的next指向了a，然后令node=b，然后将lnode往下指向c；下一个循环，next=空了，然后把c的next指向了b，然后node=c，然后lnode=空。这个时候判断了lnode为空，结束循环，形成了**a<-b<-c**。


### 代码

    ListNode* ReverseList(ListNode* pHead) {
        if (pHead == NULL)
            return NULL;
        ListNode *node = NULL;
        ListNode *lnode = pHead;
        while(lnode!= NULL){
            ListNode *next = lnode->next;
            lnode->next = node;
            node = lnode;
            lnode = next;
             
        }
        return node;
    }

## 题目9 合并两个排序的链表 

### 题目描述

输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。

### 题目解析
一定要考虑**鲁棒性**：
1. 若第一个链表为空，则直接返回第2个；
2. 若第二个链表为空，则直接返回第1个；
3. 其实若两个链表都为空的话，在第一个if语句判断的时候返回了第二个链表，而第2个链表为空，所以正好也是返回了NULL。
4. 这个时候我们新建一个result的链表存储结果，并为空，对于头结点来说，判断第一个链表和第二个链表的值，若第一个小于第二个，则把第一个链表的头结点给result，然后继续往下进行递归调用Merge函数（Merge(pHead1->next,pHead2)）；否则，把第二个链表的头结点给result，继续往下进行递归调用Merge函数（Merge(pHead1,pHead2->next）。

### 代码

    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(pHead1==NULL)
            return pHead2;
        if(pHead2==NULL)
            return pHead1;
        ListNode* result=NULL;
        if(pHead1->val<pHead2->val)
        {
            result=pHead1;
            result->next=Merge(pHead1->next,pHead2);
        }
        else
        {
            result=pHead2;
            result->next=Merge(pHead1,pHead2->next);
        }
        return result;
    }

## 题目10 树的子结构 

### 题目描述

输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）

### 题目解析

第一步在树A中查找与根节点的值一样的结点，这实际上就是树的遍历。如HasSubtree()函数中所述。如果根值相同，则去继续比较，否则有A的左子树和B比较，如果还不行就用A的右子树和B比较。
我们一定要**注意边界条件的检查**，即检查空指针。当树A或B为空的时候，定义相应的输出。本代码里面就是if不符合之后直接返回result。
第二步是判断树A中以R为根节点的子树是不是和B具有相同的结构，这里也是用递归来实现的，如果A为空了B还不是空的，那么B肯定不是A的子树；如果B空了A还没空，那么肯定也不是；如果两个结点值不一样，那就返回false；如果值相同，则继续对左子树和右子树进行比较。
<font color="red">**一个可以提现专业的细节：**double和float表示小数的时候都有误差，所以判断两个小数的时候不能直接判断相等，而是要判断他们的误差是不是在一个很小的范围内，如果很小，就认为相等。所以可以定义下面的函数：</font>

    bool Equal(double a,double b)
    {
    	if((num1-num2>-0.0000001)&&(num1-num2<0.0000001)
    		return true;
    	else
    		return false;
    }

### 代码

    bool HasSub(TreeNode* root1, TreeNode* root2)
        {
            if(root1 ==NULL && root2 !=NULL)
                return false;
            if(root2==NULL)
                return true;
            if(root1->val != root2->val)
                return false;
            return HasSub(root1->left,root2->left)&&HasSub(root1->right,root2->right);
    
        }
        bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
        {
            bool result = false;
            if(pRoot1!=NULL && pRoot2!=NULL)
            {
                if(pRoot1->val == pRoot2->val)
                    result=HasSub(pRoot1,pRoot2);
                if(!result)
                    result=HasSubtree(pRoot1->left,pRoot2);
                if(!result)
                    result=HasSubtree(pRoot1->right,pRoot2);
            }
            
            return result;
        }

