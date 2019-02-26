## 题目1  二维数组中的查找
### 题目描述

在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

### 题目解析

其实这个题目是非常有规律的，所以才可以用复杂度更小的方法来实现。由于其每行自左向右递增，每列自上而下递增，所我们可以设置一个初始位置，让他不在(0,0)的位置，而是第一列最后一个位置，如果实际数比它大了，那就向右查找，否则向上查找。

### 代码

    bool Find(int target, vector<vector<int> > array) {
        if(array.size()!=0)
        {
            int rows=array.size();
            int cols=array[0].size();
            int i=rows-1;//最后一行
            int j=0;
            while(i>=0&&j<cols)
            {//如果target小于这个数，自然往上找
                if(target<array[i][j])
                    --i;
                //如果target大于这个数，自然往后找
                else if(target>array[i][j])
                    ++j;
                else
                    return true;
            }
        }
        return false;
    }

## 题目2  替换空格
### 题目描述
请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

### 题目解析

### 代码

    void replaceSpace(char *str,int length) {
            int count=0;
            int realen=0;
            int i=0;
            while(str[i]!='\0')
            {
                ++realen;
                if(str[i]== ' ')
                    ++count;
                ++i;
            }
            int newlen=realen+count*2;
            if(length<newlen)
                return ;
            for(int j=realen-1;j>=0;j--)
            {
                if(str[j]!=' ')
                    str[j+2*count]=str[j];
                else{
                    count--;
                    str[j+2*count]='%';
                    str[j+2*count+1]='2';
                    str[j+2*count+2]='0';
                }
            }
            str[newlen]='\0';
    
    	}


## 题目3 从尾到头打印链表

### 题目描述

输入一个链表，按链表值从尾到头的顺序返回一个ArrayList。

  

### 题目解析

其实很容易想到，可以使用FILO的堆栈来进行处理。

### 代码

    vector<int> printListFromTailToHead(ListNode* head) {
    
    vector<int> result;
    
    stack<int> arr;
    
    ListNode * p=head;
    
    //首先把链表从头到尾输入到一个堆栈
    
    //利用堆栈先入后出特性，从尾到头输出到一个vector里面
    
    while(p!=NULL)
    
    {
    
    arr.push(p->val);
    
    p=p->next;
    
    }
    
    int len= arr.size();
    
    for(int i=0;i<len;i++)
    
    {
    
    result.push_back(arr.top());
    
    arr.pop();
    
    }
    
    return result;
    
    }

  

## 题目4 重建二叉树

### 题目描述

输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。

  

### 题目解析

我们根据前序遍历的特点可以发现，前序遍历的第一个数字一定是这个二叉树的根节点；然后根据中序遍历的特点可发现，根节点左侧的数字一定是左子树，右侧一定是右子树。然后将中序遍历以根节点为中心划分成两个部分，这又是两个子树，然后这个子树又可以根据前序遍历找到各个子树的根节点……以此类推，这非常适合有递推来实现。

就拿这个例子来说。

前序遍历：
|序号|0|1|2|3|4|5|6|7
| ------ | ------| ------| ------| ------| ------| ------| ------|------|
|内容|**1**|2|4|7|3|5|6|8


中序遍历：
|序号|0|1|2|3|4|5|6|7
| ------ | ------| ------| ------| ------| ------| ------| ------|------|
|内容|4|7|2|**1**|5|3|8|6

这又就把中序遍历分为了4/7/2和5/3/8/6两个部分。然后考虑4/7/2这个部分，前序遍历的第2个数字是划分4/7/2的数字，这样，2是这个子树的根节点，4/7都位于左子树。

然后再看右子树，也就是3/5/6/8这四个数字。同理可以得出，3是右子树的根节点，然后5在左子树，8/6在右子树。再去8/6这个子树看，根据前序遍历可以看到6为子树的根节点，根据中序遍历可以看到，8为子树的左结点。

接下来考虑代码实现问题。首先肯定要判断所给的两个数组是不是空，若是空肯定是个空树，否则继续进行。我们可以使用类里面的一个私有函数来进行具体的重建功能，而这个函数的参数自然是**前序遍历结果、起始位置、结束位置、中序遍历结果、起始位置、结束位置。**

当然作为刚开始的时候，起始位置肯定是**0**，结束位置肯定是**length-1**。

**使用这个私有函数进行递归，肯定有停止递归的条件，那就是开始位置大于结束位置的时候，自然就代表迭代结束了。**

然后新建一个TreeNode，第一个节点自然是前序遍历的第一个节点，所以可以：

    TreeNode root=new TreeNode(pre[startPre]);

接下来自然要开始进行判断，寻找前序遍历和中序遍历相等值的位置，由于前序遍历里面的点都可以作为中序遍历里面的根节点，所以我们只需要在中序遍历里面找到与前序遍历中值相等的位置，就是该子树的根节点的位置，就可以根据这个点划分左子树和右子树了。而中序遍历中到的根节点的位置i左侧有几个数字就是左子树有几个元素，右边有几个数字就是右子树有几个元素

对于左子树来说，左子树的起始位置自然是startPre的下一个位置，而结束是startPre+i-startIn（startPre是位置，i-startIn是从中序遍历中看左子树有几个元素），而中序遍历的开始位置自然是startIn，结束位置是i-1。

对于右子树来说，中序遍历的起始位置自然是i+1，结束位置是endIn；而对于前序遍历来说，自然是startPre+左子树的元素数+1，而左子树我们知道是i-startIn了，所以起始位置是startPre+i-startIn+1，结束位置自然是endPre。

于是，完成了这个程序的编写。

  

### 代码

    public TreeNode reConstructBinaryTree(int [] pre,int [] in) {
        TreeNode root=reConstructBinaryTree(pre,0,pre.length-1,in,0,in.length-1);
        return root;
    }
    //前序遍历{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}
    private TreeNode reConstructBinaryTree(int [] pre,int startPre,int endPre,int [] in,int startIn,int endIn) {
         
        if(startPre>endPre||startIn>endIn)
            return null;
        TreeNode root=new TreeNode(pre[startPre]);
         
        for(int i=startIn;i<=endIn;i++)
            if(in[i]==pre[startPre]){
                root.left=reConstructBinaryTree(pre,startPre+1,startPre+i-startIn,in,startIn,i-1);
                root.right=reConstructBinaryTree(pre,i-startIn+startPre+1,endPre,in,i+1,endIn);
                      break;
            }
                 
        return root;
    }

  

## 题目5 用两个栈实现队列

### 题目描述

用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。


### 题目解析

  思路很简单，就是用两个堆栈，push直接push进去就可以。由于队列是FIFO，而堆栈是FILO，所以只要使用push后的堆栈再push到另一个堆栈里面，这个时候pop出来的顺序总体上来说就是FIFO了。

### 代码

    public:
    
    void push(int node) {
    
    stack1.push(node);
    
    }
    
    int pop() {
    
    int tmp;
    
    if(stack2.empty())
    
    while(!stack1.empty())
    
    {
    
    tmp=stack1.top();
    
    stack2.push(tmp);
    
    stack1.pop();
    
    }
    
    int res=stack2.top();
    
    stack2.pop();
    
    return res;
    
    }
    
      
    
    private:
    
    stack<int> stack1;
    
    stack<int> stack2;

  

## 题目6 旋转数组的最小数字

### 题目描述

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。 输入一个非减排序的数组的一个旋转，输出旋转数组的最小元素。 例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

  

### 题目解析

 最傻瓜的方式就是直接进行比较了，但是这样的时间复杂度为O(n)，我们可以考虑降低复杂度。考虑到这个旋转数组本质上是一个基本有序的数组，所以我们可以考虑借鉴二分查找的思想。
 令low=0，high=len-1，即两个指针分别指向数组的开头和结尾。我们令mid=(low+high)/2。
 - 若a[mid]>a[high]，则代表最小的元素一定在后面(因为这两块都是递增的），所以low=mid+1
 - 若a[mid]==a[high]，这种情况比较复杂，需要一个一个的试，所以high=high-1，一点点缩小范围。
 - a[mid]<a[high]，则代表最小数字一定就是array[mid]或者在mid的左边。因为右边必然都是递增的，所以直接high=mid（一定不能为mid-1）。

### 代码

    int minNumberInRotateArray(vector<int> rotateArray) {
        int low=0;int high=rotateArray.size()-1;
    	while(low<high){
    		int mid = low+(high-low)/2;
    		if(rotateArray[mid]>rotateArray[high])
    			low= mid+1;
    		else if(rotateArray[mid]==rotateArray[high])
    			high=high-1;
    		else
    			high=mid;
    	}
    	return rotateArray[low];
    }

## 题目7 数值的整数次方

### 题目描述

给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。

### 题目解析

假如我们要计算3<sup>13</sup>，我们既可以直接乘（复杂度为O(n)），也可以用快速算法降低复杂度。方法是怎样的呢？
我们关注指数部分，13=(1101)<sub>2</sub>所以3<sup>13</sup>=3<sup>(1000)<sub>2</sub></sup> * 3<sup>(0100)<sub>2</sub></sup> * 3<sup>(0001)<sub>2</sub></sup>。
这样的话，我们可以将exponent&1操作，如最低位为1，那么就是做ans=ans*base，否则不做。然后对exponent进行右移，每右移1位，base=base*base，这样若为1，则ans=base；若为101，则为ans=base*(base*base)。然后就可以得到结果了，代码如下。
  
### 代码

    double Power(double base, int exponent)
    {
    	long long exp=abs((long long)exponent);
    	double ans =1.0;
    	while(exp)
    	{
    		if(exp&1)
    			ans*=base;
    		base*=base;
    		exp>>=1;
    	}
    	return exponent<0?(1/ans):ans;
    }

