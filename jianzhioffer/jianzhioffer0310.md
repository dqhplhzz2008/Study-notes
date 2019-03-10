## 题目1 序列化二叉树

### 题目描述
请实现两个函数，分别用来序列化和反序列化二叉树

### 题目解析
序列化二叉树可以使用前序遍历来进行，这样的话响应的反序列化在根节点的数值读出来的时候就可以开始了。如果二叉树读的时候遇到NULL，就输出一个“\$”。我们以字符串“1,,2,4,$,$,$,3,5,\$,\$,6,\$,\$”为例来分析如何反序列化。第一个读出来的数字是1，所以这肯定是根节点的值，接下来读出来的肯定是根节点左子结点上的值，然后接下来再读到的肯定是其左子结点上的值。接着我们读出了两个“\$”，这表明4的左右子结点都是空，因此它是一个叶结点，然后返回到上面的结点，也就是2，建立它的右节点，由于下一个字符是“\$”，所以肯定右节点也是空，然后继续返回上一层结点，如此而来。

### 代码

    void Serialize(BinaryTreeNode* pRoot, ostream& stream)
    {
    	if(pRoot==NULL)
    	{
    		stream<<"$";
    		return;
    	}
    	stream<<pRoot->val<<',';
    	Serialize(pRoot->left,stream);
    	Serialize(pRoot->right,stream);
    }
    
    void Deserialize(BinaryTreeNode* pRoot, istream& stream)
    {
    	int number;
    	if(ReadStream(stream,&number))
    	{
    		*pRoot=new BinaryTreeNode();
    		(*pRoot)->val=number;
    		(*pRoot)->left=NULL;
    		(*pRoot)->right=NULL;
    		
    		Deserialize(&((*pRoot)->left),stream);
    		Deserialize(&((*pRoot)->right),stream);
    		
    	}
    }

## 题目2 平衡二叉树

### 题目描述

输入一棵二叉树，判断该二叉树是否是平衡二叉树。

### 题目解析
一个最容易想到的办法就是在每一层结点都分别判断这个子树是不是平衡二叉树，若都是那么就返回true，如果看到一个不是平衡二叉树，立马返回false。如代码1，其核心就是计算树的深度，这可以借鉴前面“二叉树的高度”的代码来执行。
但是这个方法每一次都有往下遍历到叶结点，纯粹浪费时间和空间。如果我们用后序遍历的方式遍历二叉树的每个结点，那么在遍历到一个结点之前我们就已经遍历了它的左、右子树。只要在遍历每个结点的时候记录它的深度，我们就可以一遍遍历一边判断每个结点是不是平衡的了。如代码2。

### 代码1

    class Solution {
    public:
        bool IsBalanced_Solution(TreeNode* pRoot) {
            if(pRoot == NULL)
                return true;
            int leftDepth = getDepth(pRoot -> left);
            int rightDepth = getDepth(pRoot -> right);
            if(leftDepth > rightDepth + 1 || leftDepth + 1 < rightDepth)
                return false;
            else
                return IsBalanced_Solution(pRoot -> left) && IsBalanced_Solution(pRoot -> right);
        }
         
        int getDepth(TreeNode* pRoot){
            if(pRoot == NULL)
                return 0;
            int leftDepth = getDepth(pRoot -> left);
            int rightDepth = getDepth(pRoot -> right);
            return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
        }
    };
### 代码2

    bool IsBalanced(BinaryTreeNode* pRoot, int *pDepth)
    {
    	if(pRoot==NULL)
    	{
    		*pDepth=0;
    		return true;
    	}
    	
    	int left,right;
    	if(IsBalanced(pRoot->left,&left
    	&& IsBalanced(pRoot->right,&right))
    	{
    		int diff=left-right;
    		if(diff<=1 &&diff>=-1)
    		{
    			*pDepth=1+(left>right?left:right);
    			return true;
    		}
    	}
    	return false;
    }


## 题目3 和为S的连续正数序列

### 题目描述

小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。但是他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。没多久,他就得到另一组连续正数和为100的序列:18,19,20,21,22。现在把问题交给你,你能不能也很快的找出所有和为S的连续正数序列? Good Luck!

### 题目解析
这个题其实可以这样思考：由于这个序列肯定至少是从1开始（0的话没什么用处），所以先把l和r（也就是left和right）都设置为1。然后就判断在l<=r条件下，对r不断右移位置，看他们这个时候的和是多少，如果这个时候这个和等于给定值并且l不等于r的话，那就把这个序列直接push进二维vector里面去。如果这个时候和大于给定值了，那就尝试把序列最左端（也就是最小的值）逐一减去试试，看何时到达给定值。这个时候如果到达了，又push进去。最后直到l>r，也就是找不到了为止。

### 代码

    vector<vector<int> > FindContinuousSequence(int sum) {
        int l = 1,r = 1,sumx = 1;
        vector<vector<int> > ans;
        while(l <= r){
            r ++;
            sumx += r;
            while(sumx > sum){
                sumx -= l;
                l ++;
            }
            if(sumx == sum && l != r){
                vector<int> tmp;
                for(int i = l;i <= r;i ++)  tmp.push_back(i);
                ans.push_back(tmp);
            }
        }
        return ans;
    }

## 题目4 孩子们的游戏（约瑟夫环问题）

### 题目描述

每年六一儿童节,牛客都会准备一些小礼物去看望孤儿院的小朋友,今年亦是如此。HF作为牛客的资深元老,自然也准备了一些小游戏。其中,有个游戏是这样的:首先,让小朋友们围成一个大圈。然后,他随机指定一个数m,让编号为0的小朋友开始报数。每次喊到m-1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,并且不再回到圈中,从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到剩下最后一个小朋友,可以不用表演,并且拿到牛客名贵的“名侦探柯南”典藏版(名额有限哦!!^_^)。请你试着想下,哪个小朋友会得到这份礼品呢？(注：小朋友的编号是从0到n-1)

### 题目解析

这实际上是一个约瑟夫环的问题。首先定义最初的n个数字（0,1,…,n-1）中最后剩下的数字是关于n和m的方程为f(n,m)。

在这n个数字中，第一个被删除的数字是(m-1)%n，为简单起见记为k。那么删除k之后的剩下n-1的数字为0,1,…,k-1,k+1,…,n-1，并且下一个开始计数的数字是k+1。相当于在剩下的序列中，k+1排到最前面，从而形成序列k+1,…,n-1,0,…k-1。该序列最后剩下的数字也应该是关于n和m的函数。由于这个序列的规律和前面最初的序列不一样（最初的序列是从0开始的连续序列），因此该函数不同于前面函数，记为f’(n-1,m)。最初序列最后剩下的数字f(n,m)一定是剩下序列的最后剩下数字f’(n-1,m)，所以f(n,m)=f’(n-1,m)。

接下来我们把剩下的的这n-1个数字的序列k+1,…,n-1,0,…k-1作一个映射，映射的结果是形成一个从0到n-2的序列：

> k+1  ->  0   
> k+2  ->  1  
>  …   
>  n-1  ->  n-k-2  
>   0  ->  n-k-1   
>   …   
>   k-1 
> ->  n-2

把映射定义为p，则p(x)= (x-k-1)%n，即如果映射前的数字是x，则映射后的数字是(x-k-1)%n。对应的逆映射是p-1(x)=(x+k+1)%n。

由于映射之后的序列和最初的序列有同样的形式，都是从0开始的连续序列，因此仍然可以用函数f来表示，记为f(n-1,m)。根据我们的映射规则，映射之前的序列最后剩下的数字f’(n-1,m)= p-1  [f(n-1,m)]=[f(n-1,m)+k+1]%n。把k=(m-1)%n代入得到f(n,m)=f’(n-1,m)=[f(n-1,m)+m]%n。

经过上面复杂的分析，我们终于找到一个递归的公式。要得到n个数字的序列的最后剩下的数字，只需要得到n-1个数字的序列的最后剩下的数字，并可以依此类推。当n=1时，也就是序列中开始只有一个数字0，那么很显然最后剩下的数字就是0。我们把这种关系表示为：

0  n=1  
f(n,m)={  
[f(n-1,m)+m]%n  n>1

尽管得到这个公式的分析过程非常复杂，但它用递归或者循环都很容易实现。最重要的是，这是一种时间复杂度为O(n)，空间复杂度为O(1)的方法，

### 代码

    int LastRemaining_Solution(int n, int m)
    {
        if(n==0)
            return -1;
        int s = 0;
        for(int i = 2;i <= n; i++)
        {
            s = (s+m) % i;
        }
        return s;
    }


