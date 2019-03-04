## 题目1 二叉树的镜像

### 题目描述

操作给定的二叉树，将其变换为源二叉树的镜像。

### 题目解析
一定要考虑到两种特殊情况：

- 二叉树为空
- 二叉树的左子树为空且二叉树的右子树为空

设计代码的时候一定要考虑代码的鲁棒性。所以需要设计到两个if语句，如果不在这两种特殊情况里面，再去新建一个TreeNode，然后交换进行做镜像。

### 代码

    void Mirror(TreeNode *pRoot) {
    	if(pRoot == NULL)//特殊情况1
    		return;
    	//特殊情况2
    	if((pRoot->left == NULL)&&(pRoot->right == NULL))
    		return ;
    	TreeNode *tmp;
    	tmp=pRoot->left;
    	pRoot->left=pRoot->right;
    	pRoot->right=tmp;
    	if(pRoot->left)
    		Mirror(pRoot->left);
    	if(pRoot->right)
    		Mirror(pRoot->right);
    }

## 题目2 顺时针打印矩阵

### 题目描述

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.

### 题目解析

用左上和右下的坐标定位出一次要旋转打印的数据，一次旋转打印结束后，往对角分别前进和后退一个单位。

### 代码

    vector<int> printMatrix(vector<vector<int> > matrix) {
    	vector<int> result;
    	int row=matrix.size();
    	int col=matrix[0].size();
    	if(row==0||col==0)
    		return result;
    	int left = 0,right = col-1,top=0,end =row-1;
    	while(left<=right && top<= end)
    	{
	    	//第一行从左往右
    		for(int i=left;i<=right;i++)
    			result.push_back(matrix[top][i]);
    		//最右侧从上往下
    		if(top<end)
    		{
    			for(int i=top+1;i<=end;i++)
    				result.push_back(matrix[i][right]);
    		}
    		//最下侧从右往左
    		if(top<end && left<right)
    		{
    			for(int i=right-1;i>=left;i--)
    				result.push_back(matrix[end][i]);
    		}
    		//最左侧从下往上
    		if(top+1<end && left<right)
    		{
    			for(int i=end-1;i>=top+1;i--)
    				result.push_back(matrix[i][left]);
    		}
    		left++;
    		right--;
    		top++;
    		end--;
    	}
    	return result;
    }

## 题目3 包含min函数的栈

### 题目描述

定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O（1））。

### 题目解析

我们需要一个辅助堆栈来得到我们所需要数据，因为只有一个堆栈的话，我们没办法比较得出最小值。加入我们的数据压入顺序是3,4,2,1。那么可以这样：
|步骤|操作|数据栈|辅助栈|最小值|
|--|--|--|--|--|
|1|压入3|3|3|3|
|2|压入4|3,4|3,3|3|
|3|压入2|3,4,2|3,3,2|2|
|4|压入1|3,4,2,1|3,3,2,1|1|
|5|弹出|3,4,2|3,3,2|2|
|6|弹出|3,4|3,3|3|
|7|压入0|3,4,0|3,3,0|0|

### 代码

    stack<int> stack1,stack2;
        void push(int value) {
            stack1.push(value);
            if(stack2.empty()||value<stack2.top())
                stack2.push(value);
            else
            {
                stack2.push(stack2.top());
            }
        }
         
        void pop() {
            
            stack2.pop();
            stack1.pop();
             
        }
         
        int top() {
            return stack1.top();       
        }
         
        int min() {
            return stack2.top();
        }

## 题目4 栈的压入、弹出序列

### 题目描述

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）

### 题目解析

这个程序的代码思路跟我们手工做题的思路一样，所以也许不是复杂度最低的算法，它的思路是这样的：
1. 新建一个vector数组temp；
2. 然后将pushV的最头上的元素压入temp；
3. 判断该元素是否和popV中最上面的元素（即要被弹出的元素）是否相等，若不相等正则去执行第2步，直到找到相等的，然后temp里面的元素弹出；
4. 然后开始第2个元素的比较，步骤重复2和3，直到所有的完成。

### 代码

	bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        bool result =false;
        stack<int>temp;
        int Index = 0;
		for(int i=0;i<pushV.size();i++)
		{
			temp.push(pushV[i]);
			while(!temp.empty() && temp.top()==popV[Index])
			{
				temp.pop();
				++Index;
			}
		}
        result=temp.empty();
        return result;
        
    }

## 题目5 从上往下打印二叉树

### 题目描述

从上往下打印出二叉树的每个结点，同层结点从左至右打印。

### 题目解析

这就是**层序遍历**。用层序遍历的法子，借助队列来实现。其实广度优先搜索也借鉴了层序遍历的思想。

### 代码

     vector<int> PrintFromTopToBottom(TreeNode* root) {
            vector<int> result;
            queue<TreeNode*> q;
            q.push(root);//把根结点push进去
            if(root == NULL)//稳健性
                return result;
            while(!q.empty())
            {
    	        root=q.front();//获取到队列q的头元素
    	        q.pop();
    	        result.push_back(root->val);//把头元素的值送入result
    	        if(root->left)//向左遍历
    		        q.push(root->left);
    	        if(root->right)//向右遍历
    		        q.push(root->right);
            }
            return result;
        }

## 题目6 二叉搜索树的后序遍历序列

### 题目描述

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。假设输入的数组的任意两 个数字都互不相同。

### 题目解析

我们以后序遍历序列{5,7,6,9,11,10,8}和{7,4,6,5}为例来发现规律。在后序遍历里面，最后一个数字（8,5）一定是序列的根结点值。二叉搜索树左子树都小于根结点的值，右子树都大于根结点的值。

我们先看第一个序列。发现{5,7,6}都小于8，{9,11,10}都大于8，所以前者是左子树，后者是右子树，符合二叉搜索树的定义；再看左子树{5,7,6}，同理6是这个子树的根结点，然后5小于6，是子树的左子树，7>6，是子树的右子树，符合二叉搜索树定义；再看右子树{9,11,10}，根结点是10，9<10，符合左子树定义，11>10，符合右子树定义，符合二叉搜索树定义。所以这是一个二叉搜索树。

再看{7,4,6,5}，5是根结点，由于第一个元素7>5，所以可以肯定该树没有左子树，{7,4,6}都是右子树。然后看右子树，6是根结点，安装后序遍历来说，第一个数字应是根结点的左子树，那么{7,4}是右子树。我们再看4不仅小于右子树的根结点6，还小于整个树的根结点5，所以这个树不是二叉搜索树。

然后我们就可以根据递归来写。如果序列长度为0，那肯定不是，return false。
其它的情况我们就按照上面来，首先来寻找左子树，我们只需要一个for循环，判断到哪一位为止数字大于最后一个数字了，那么我们就默认这个数字开始的后面就是右子树了。找到左子树和右子树的之后，我们就可以分别对左子树和右子树进行递归判断了。

我们可以想一层一层递归，最后递归到一个只有根结点、左结点和右结点的小二叉树。在这个二叉树里面，我们继续判断那一个点开始是右子树，然后查找这个点后面有没有小于该树根结点的结点，如果有这样一个点，那肯定不是二叉搜索树的后序遍历，return false。**当然啦，因为每一次我们要一层一层判断下去，如果这一层不符合就不用往下递归了，所以这个判断过程要放在递归前面。**

### 代码

    bool VerifySquenceOfBST(vector<int> sequence) {
    	if(sequence.size()==0)
    		return false;
    	return IsTreeBST(sequence,0,sequence.size()-1);
    
    }
    bool IsTreeBST(vector<int> sequence, int start, int end)
    {
    	if(end < start)
    		return true;
    	int i=start;
    	for(;i<end;i++)
    	{
    		if(sequence[i]>sequence[end])
    			break;
    	}
    	for(int j=i;j<end;j++)
    	{
    		if(sequence[j]<sequence[end])
    			return false;
    	}
    	return IsTreeBST(sequence,start,i-1)&&IsTreeBST(sequence, i,end-1);
    }

## 题目7 二叉树中和为某一值的路径

### 题目描述

输入一颗二叉树的跟结点和一个整数，打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。(注意: 在返回值的list中，数组长度大的数组靠前)

### 题目解析

我们举例来考虑，加入我们输入的二叉树层序遍历的结果为{8,5,14,3,9}，整数为22。

我们要来计算，肯定要先遍历根结点，获取根结点的值，所以必须使用**前序遍历**。这样如下表所示。同时应注意，为了增强系统的鲁棒性，**要判断二叉树为空的时候的情况**。
|步骤|操作|是否叶结点|路径|路径结点值的和|
|--|--|--|--|--|
|1|访问结点8|否|结点8|8|
|2|访问结点5|否|结点8，结点5|13|
|3|访问结点3|是|结点8，结点5，结点3|16|
|4|回到结点5||结点8，结点5|13|
|5|访问结点9|是|结点8，结点5，结点9|**22**|
|6|返回结点5||结点8，结点5|13|
|7|回到结点8||结点8|8|
|8|访问结点14|是|结点8，结点14|**22**|

所以我们要做的就是新建一个
    
    vector<vector<int> > buffer

用来存放结果。然后新建一个

    vector<int> tmp;

用来存放中间值。
然后将根结点的值送入tmp，然后对左子树和右子树分别判断，即对左子树和右子树分别进行递归。

在到达一个结点的时候，我们要做两个判断：

1. 加上当前结点的值，是否等于预设值了呢？（即(expectNumber-root->val)==0）；
2. 该结点是否是叶结点了呢？（root->left==NULL && root->right==NULL）

若符合要求了，则代表找到了一条路径，直接push_back到buffer里面即可。

因为要先计算结点的值，所以就要把上面的步骤放在递归之前。
在完成一层层递归之后，需要向上返回，这个时候利用递归的特性即可，此时一定要记得删除tmp里面最上面的值。


### 代码


    vector<vector<int> > buffer;
    vector<int> tmp;
    vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
        if(root==NULL)//鲁棒性
            return buffer;
        tmp.push_back(root->val);
        if((expectNumber-root->val)==0 && root->left==NULL && root->right==NULL)
        {
            buffer.push_back(tmp);
        }
        FindPath(root->left,expectNumber-root->val);
        FindPath(root->right,expectNumber-root->val);
        if(tmp.size()!=0)
            tmp.pop_back();
        return buffer;
    }

## 题目8 复杂链表的复制

### 题目描述

输入一个复杂链表（每个结点中有结点值，以及两个指针，一个指向下一个结点，另一个特殊指针指向任意一个结点），返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的结点引用，否则判题程序会直接返回空）

### 题目解析

第一步，仍然是根据原始链表的每个结点N创建对应的N'。这一次，我们把N'链接在N的后面。

    void nodeClone(RandomListNode *head)
    {
        RandomListNode *pNode = head;
        while (pNode != NULL)
        {
            RandomListNode *pClone = new RandomListNode(pNode->label);
            pClone->next = pNode->next;
            pNode->next = pClone;
            pNode = pClone->next;
        }
    }

第二步，设置复制出来的结点的random。假设原来上的N的random指向结点S，那么对应复制出来的N'是N的next指向的结点，同样S'也是S的next指向的结点。

    void connectRandom(RandomListNode *head)
    {
        RandomListNode *pNode = head;
         
        while (pNode != NULL)
        {
            RandomListNode *pClone = pNode->next;
            if (pNode->random)
            {
                pClone->random = pNode->random->next;
            }
            pNode = pClone->next;
        }
    }

第三步把这个厂链拆分成两个链表，把技术位置的结点用next链接起来的就是原始链表，把偶数位置的结点用next链接起来的就是复制出来的链表。

    RandomListNode *reconnect(RandomListNode *head)
    {
        RandomListNode *pNode = head;
        RandomListNode *result = head->next;
        while (pNode != NULL)
        {
            RandomListNode *pClone = pNode->next;
            pNode->next = pClone->next;
            pNode = pNode->next;
            if (pNode != NULL)
                pClone->next = pNode->next;
             
        }
        return result;
    }


## 题目9 二叉搜索树与双向链表

### 题目描述

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。

### 题目解析
![示意图](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/jianzhioffer/images/timu03041.jpg)

由于要求转换之后的链表是排好序的，所以我们可以用一个中序遍历，这样就可以从小到大遍历二叉树的每个结点。当遍历到根节点的时候，我们把树看成3部分：值为10的结点；根结点为6的左子树；根结点为14的右子树。根据排序链表的定义，值为10的结点将和它左子树的最大一个结点链接起来，同时还将和右子树最小结点连接起来。

按照中序遍历顺序，我们遍历到根结点的时候，左子树已经变成一个排序的链表了，并且处在链表中的最后一个结点就是当前最大的结点，我们把值为8的结点和根结点链接起来，此时链表中最后一个结点就是10。然后我们去遍历转换右子树，然后把根节点和右子树最小结点链接起来。以此递归下去。

### 代码

    TreeNode* Convert(TreeNode* pRootOfTree)
        {
            if (pRootOfTree == NULL)return NULL;
            TreeNode *pointer = NULL;
            convert2List(pRootOfTree, pointer);
            while (pointer->left!=NULL)
            {
                pointer = pointer->left;
            }
            return pointer;
        }
        void convert2List(TreeNode* pRoot,TreeNode *&pointer)
        {
            if (pRoot == NULL)
            {
                return;
            }
            {
                if (pRoot->left != NULL)
                {
                    convert2List(pRoot->left,pointer);
                }
     
                pRoot->left = pointer;
                if (pointer != NULL)
                {
                    pointer->right = pRoot;
                }
                 
                pointer = pRoot;
                if (pRoot->right!=NULL)
                {
                    convert2List(pRoot->right, pointer);
                }
            }
        }

## 题目10 字符串的排列

### 题目描述

输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。

### 题目解析

我们求整个字符串的排列，可以分成两步。第一步，把字符串分为第一个字符和后面若干个字符，那么第一个位置上有哪些可能呢？就把第一个位置上原来的字符和后面的字符进行交换，加上原来的情况。第二步，就是固定第一个字符，求剩下的，对于剩下的字符来说，又可以分解为第一个字符和后面字符串的关系，然后把这个子字符串按照第一步来求解即可。这样很明显是一个递归。

当然啦，字符串为空的情况也要考虑到。

### 代码

    vector<string> result;
    vector<string> Permutation(string str) {
        if(str.length()==0){
            return result;
        }
        Permutation1(str,0);
        sort(result.begin(),result.end());
        return result;
    }
    void Permutation1(string str,int begin){
        if(begin == str.length()){
            result.push_back(str);
            return ;
        }
        for(int i = begin; str[i]!='\0';i++){
             
            if(i!=begin&&str[begin]==str[i])
                continue;
            swap(str[begin],str[i]);
            Permutation1(str,begin+1);
            swap(str[begin],str[i]);
        }         
    }

