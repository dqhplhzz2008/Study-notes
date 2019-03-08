## 题目1 二叉树的深度

### 题目描述

输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。

### 题目解析

如果一棵树只有一个结点，那么深度为1.如果根节点只有左子树而没有右子树，那么深度就是左子树深度+1；同理，对于右子树也是如此。如果既有左子树，也有右子树，那么该树的深度就是左右子树深度的最大值+1。所以可以利用递归的方式实现该题目。

### 代码

```
int TreeDepth(TreeNode* pRoot)
{
	int Hl, Hr, MaxH;
	if(pRoot)
	{
		Hl=TreeDepth(pRoot->left);
		Hr=TreeDepth(pRoot->right);
		MaxH=(Hl>Hr)?Hl:Hr;
		return MaxH + 1;
	}
	else
		return 0;
}
```

## 题目2 数组中只出现一次的数字 

### 题目描述

一个整型数组里除了两个数字之外，其他的数字都出现了偶数次。请写程序找出这两个只出现一次的数字。

### 题目解析

这一题我们来对这个数组进行分析。我的想法是首先对其排序，这样这部分复杂度是O(nlogn)，然后我们再来考虑排好序的数组中，这两个特殊的数字会有什么特点呢？

1. 假如有一个单独的数字在开头，那么它一定与第二个数字不相等。例如（1/2/2/3/3/4）
2. 假如有一个单独的数字在末尾，那么它一定与倒数第二个数字不相等。例如(1/2/2/3/3/4)
3. 假如有一个数字在中间（从第2位到最后一位），那么它一定与左边和右边的两个数字不相等。例如(1/2/3/3/4/4)或者(1/2/2/3/4/4)。
4. 剩余一个数字肯定也符合上面3种情况中两种情况之一（第一个数字占据了之外的那种情况）。

所以这样，我们就可以把代码写出来了。

### 代码

```
	void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
		sort(data.begin(),data.end());
		int len=data.size();
		vector<int> temp;
		if(data[0]!=data[1])//第一种情况
			temp.push_back(data[0]);
		for(int i=1;i<len-1;++i)//第二种情况
			if(data[i]!=data[i-1] && data[i]!=data[i+1])
				temp.push_back(data[i]);
		if(data[len-1]!=data[len-2])//第三种情况
			temp.push_back(data[len-1]);
		
		*num1=temp[0];
		*num2=temp[1];
		
    }
```

## 题目3 数组中重复的数字

### 题目描述

在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中任意一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。

### 题目解析
借鉴前面数组中只出现一次的数字的思想，同样使用数组，利用hash的思想来做。

### 代码
```
    bool duplicate(int numbers[], int length, int* duplication) {
        if(numbers==NULL||length==0) return 0;
        int isused[255]={0};
        for(int i=0;i<length;i++)
        {
            isused[numbers[i]]++;
        }
        int count=0;
        for(int i=0;i<length;i++)
        {
            if(isused[numbers[i]]>1)
            {
                duplication[count++]=numbers[i];
                return true;
            }
        }
        return false;
    }
```


## 题目4 和为S的两个数字

### 题目描述


输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。

### 题目解析
我们知道，两个数字，距离越远，乘积越小，距离越近乘积越大。所以我们可以设置两个指针，一个指向开头，一个指向末尾，然后他们不断移动，同时相加看是不是等于所制定的值。移动的条件是：

1. 若和大于指定值，则将右指针左移；
2. 若和小于指定值，则将左指针右移；
3. 若到最后左指针和有指针位于一个位置，那么直接返回。

### 代码

```
    vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        int length = array.size();
        int start=0;
        int end=length-1;
        vector<int> result;
        while(start<end)
        {
            if(array[start]+array[end]==sum)
            {
                result.push_back(array[start]);
                result.push_back(array[end]);
                break;
            }
            else if(array[start]+array[end]<sum)
                ++start;
            else
                --end;
        }
        return result;
    }
```

## 题目5 左旋转字符串

### 题目描述

汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。是不是很简单？OK，搞定它！

### 题目解析

这里我们可以使用一个C++里面的函数：
```
string substr (size_t pos = 0, size_t len = npos) const;
```
解释如下：
- pos：要复制的第一个字符作为子字符串的位置。  如果这等于字符串长度，则该函数返回一个**空字符串**；如果这大于字符串长度，则抛出**out_of_range**。
- len：要包含在子字符串中的字符数。若为npos，代表所有的字符。

该函数返回一个string类型的对象。

```
 string& erase (size_t pos = 0, size_t len = npos);
```

这个函数的意思是：删除从字符位置pos开始并跨越len个字符的字符串值的部分。

所以我们可以考虑利用substr将所要移动的字符复制出来，放到一个临时的字符串中，然后用erase将这几个字母从原字符串中删除，再将临时字符串加到原来字符串的后面即可。

当然一定不要忘记考虑n若为0或者小于零怎么办。

### 代码

```
    string LeftRotateString(string str, int n) {
        if(n<0)
            return NULL;
        if(n==0)
            return str;
        string temp=str.substr(0,n);
        str.erase(0,n);
        str+=temp;
        return str;
    }
```

## 题目6 不用加减乘除做加法

### 题目描述


写一个函数，求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。

### 题目解析

这个题目就是让我们思考加法的原理。
首先看十进制是如何做的： 5+7=12，三步走   
第一步：相加各位的值，不算进位，得到2。   
第二步：计算进位值，得到10. 如果这一步的进位值为0，那么第一步得到的值就是最终结果。   
第三步：重复上述两步，只是相加的值变成上述两步的得到的结果2和10，得到12。   
同样我们可以用三步走的方式计算二进制值相加： 5-101，7-111   
第一步：相加各位的值，不算进位，得到010，二进制每位相加就相当于各位做异或操作，101^111。   
第二步：计算进位值，得到1010，相当于各位做与操作得到101，再向左移一位得到1010，(101&111)<<1。   
第三步重复上述两步， 各位相加 010^1010=1000，进位值为100=(010&1010)<<1。   
继续重复上述两步：1000^100 = 1100，进位值为0，跳出循环，1100为最终结果。  

### 代码
```
 public int Add(int num1,int num2) {
        while(num2!=0){
            int temp = num1^num2;
            num2 = (num1&num2)<<1;
            num1 = temp;
        }
        return num1;
    }
```


## 题目7 二叉树的下一个结点

### 题目描述

给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。

### 题目解析

三种情况：

1. 是该点若有右子树，则继续往右子树中序遍历；
2. 是该点无右子树，且是父节点的左孩子，则下一节点就是其父节点；
3. 是该点无右子树，且是父节点的右孩子，则寻找其父节点的父节点的父节点的……，直到当前节点是寻找到的那个点的左孩子为止。

所以总体来说是四种情况（除以上三种，还有二叉树为空的情况）

### 代码

```
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        //空二叉树
        if (pNode == NULL)
            return NULL;
        //第一种情况
        if(pNode->right!=NULL)
        {
            pNode=pNode->right;
            while(pNode->left!=NULL)
                pNode=pNode->left;
            return pNode;
        }
        //第二三种情况本质上是可以合并的，就是寻找当前节点是寻找到的那个点的左孩子
        while(pNode->next!=NULL)
        {
            TreeLinkNode *paren = pNode->next;
            if(paren->left==pNode)
                return paren;
            pNode=pNode->next;
        }
        //最后一个节点的情况
        return NULL;
    }
```


