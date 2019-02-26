## 题目1  滑动窗口的最大值
### 题目描述
给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。
### 题目解析
我在做这个题的时候思路非常简单，我是用的暴力破解，所以复杂度也不理想，为O(n2)，所以仅供参考。下一步在进行第二遍做题的时候我会考虑采用复杂度更低的方法。
我的方法就是新建一个vector< int >，然后对原始数组直接进行加窗，然后对加窗的size个数进行排序，然后将最大值push进结果里面。
### 代码

    class Solution {
    public:
        vector<int> maxInWindows(const vector<int>& num, unsigned int size)
        {
            vector<int> result;//结果存放
            vector<int> temp;//加窗的数据存放
            int len = num.size();
            if(num.empty()||size>len||size<1)
                return result;
            for(int i=0;i<len-size+1;i++)
            {
                for(int j=0;j<size;j++)
                    temp.push_back(num[i+j]);//窗口里面的数据
                sort(temp.begin(),temp.end());//排序
                result.push_back(temp[size-1]);
                //直接把排序好的结果中最大的push进入到result中
                temp.clear();
            }
            return result;
        }
    };
## 题目2  对称二叉树
### 题目描述
请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
### 题目解析
既然它是镜像的话，那么就是左右对称，这个我们可以使用一个递归来解决。我们令A等于这个树，B也等于这个树，假设A树和B树都只有一个结点（空结点也看做是一个结点）其实也就是两个树中至少一个树为NULL的时候，结果只会存在三种情况：
1.A的该结点为NULL，B的该结点也为NULL，即都是空结点，那么这两个树相等，自然是镜像，返回true；
2.A的该结点为NULL，B的该结点不为NULL（或者A的该结点不是NULL，B的该结点为NULL），那么不是镜像，返回false；
3.A和B均有值，但不相等，自然不是镜像，返回false。
我们把这个结点看做是其父结点的一个子树，然后逐层向上去扩展。
判断的时候是由上向下，只要两个结点值相等就继续递归。
### 代码

        bool isSymmetrical(TreeNode* pRoot)
        {
            return isSym(pRoot, pRoot);
        }
        bool isSym(TreeNode* root1, TreeNode* root2)
        {
    
            if(root1==NULL && root2==NULL)
                return true;
            if(root1 == NULL || root2 == NULL)
            //两个均为空的情况下前面就已经返回了
            //所以既然要判断这个语句，那肯定至少其中一个不为空了
                return false;
            if(root1->val!=root2->val)
    //既然到了这一步，说明两个节点都不是空的了
    //说明是在树的中间节点。在这里就需要判断两个值是不是相等
                return false;
            return isSym(root1->left, root2->right) && isSym(root1->right, root2->left);
        }
## 题目3  删除链表中重复的结点
### 题目描述
在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5。
### 题目解析
其实就是我新建一个结点，然后令这个结点为两个重复结点（A、B）中的第二个结点（B），然后判断这个结点和A是否相等，若相等，则让这个新结点等于B的下一个结点，然后依次判断这样返回的时候就把重复的结点给删除了。
### 代码

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
      //跳过与当前结点值相同的所有结点，
      //直到找到一个值与当前不同的为止。 
                return deleteDuplication(pNode);
            }
            else
            {
                pHead->next=deleteDuplication(pHead->next);
                //保留当前结点，从下一个结点开始递归
                return pHead;
            }
    
        }

## 题目4  字符流中第一个不重复的字符
### 题目描述
请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。
### 题目解析
只要这种题，就想到用一个数组，然后字符减去'\0'（或者其他的起始位）作为数组中元素的序号，每一个元素的大小代表这个字符流中的字符出现的次数，然后判断就可以了。
Insert()函数的就是每插入一个字符，就对该字符对应的数组元素进行加1，然后看这个时候这个字符是否是第一次插入呢，如果是就送入到character这个队列里面。
那自然，随着字符流不断输入，肯定有字符个数超过一个。这个时候就要使用char FirstAppearingOnce()来进行判断了。这个函数就是判断若character没空，并且数组元素大于1，即字符出现多次，那么久把字符从队列里面删除，直到剩下的最后一个返回；如果character空了，就代表没有只出现一次的字符，返回一个“#”。
### 代码

    class Solution
    {
    public:
    	void Insert(char ch)
        {
    		++myArray[ch - '\0'];
    		if(myArray[ch - '\0'] == 1 )
    			character.push(ch);
             
        }
      //return the first appearence once char in current stringstream
        char FirstAppearingOnce()
        {
    		while(character.size()!= 0 && myArray[character.front()]>1)
    			character.pop();
    		if(character.empty())
    			return '#';
    		return character.front();
        
        }
    private:
    	unsigned char myArray[200];
    	queue<char> character;
    
    };

## 题目5  数据流中的中位数
### 题目描述
如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。我们使用Insert()方法读取数据流，使用GetMedian()方法获取当前读取数据的中位数。
### 题目解析
待弄明白更高效算法的时候再来解析。
### 代码

    class Solution {
        vector<int> numbers;
    public:
        
        void Insert(int num)
        {
            numbers.push_back(num);
        }
    
        double GetMedian()
        { 
            sort(numbers.begin(),numbers.end());
            //O(nlogn)，一般是快速排序
            int len=numbers.size();
            if(len%2==1)
                return (double)(numbers[len/2]);
            else
            {
                double a=(double)(numbers[len/2]);
                double b=(double)(numbers[len/2-1]);
                double c = (a+b)/2;
                return c;
            }  
        }
    };

## 题目6  构建乘积数组
### 题目描述
给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]。不能使用除法。
### 题目解析
将B分为两个部分，B0和B1，B0计算A[0]*A[1]*...*A[i-1]；B1计算A[i+1]*...*A[n-1]。然后将B0*B1得到结果。
### 代码

        vector<int> multiply(const vector<int>& A) {
    int n = A.size();
        vector<int> B0(n, 1);
        vector<int> B1(n, 1);
        for (int i = 1; i < n;++i)
        {
            B0[i] = B0[i - 1] * A[i - 1];
        }
        for (int i = n - 2; i >= 0;--i)
        {
            B1[i] = B1[i + 1] * A[i + 1];
        }
        vector<int> B(n, 1);
        for (int i = 0; i < n;++i)
        {
            B[i] = B0[i] * B1[i];
        }
        return B;
        }


