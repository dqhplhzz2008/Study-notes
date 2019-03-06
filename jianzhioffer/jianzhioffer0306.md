## 题目1 数组中出现次数超过一半的数字

### 题目描述
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。

### 题目解析
最简单的想法就是我们这个数组进行排序，由于数字超过了一半，那么中间的数字（**中位数**）肯定是我们所需要找的数字。代码实现如代码1所示，但是排序使用快速排序，时间复杂度为O(nlogn)，并没有达到最好的速度。因此参考《剑指offer》一书，我们还可以有两种时间复杂度为O(n)的算法。
**基于Partition函数的方法**
这种算法受快速排序算法启发。在快速排序中，我们现在数组中随机选择一个数字，然后调整数组中数字的顺序，使得比选中的数字小的数字都排在它的左边，大的都在有边。如果这个选中的数字的下表刚好是n/2，那么这个数字就是数组的**中位数**；如果它的下表大于n/2，那么中位数应该位于它左边，我们可以直接在它左边部分的数组中查找；如果它的下表小于n/2，那么中位数应该位于它的有边，我们可以在它右边部分的数组查找。
此外，我们还要考虑一些无效输入。**<font color="red">如果函数的输入参数是一个指针（数组在参数传递的时候退化为指针），就要考虑这个指针可能为nullptr。</font>**CheckInvalidArray()函数可以判断输入的数组是不是无效的。

如果输入的数组中出现频率最高的数字没有超过一半怎么办？定义一个CheckMoreThanHalf()函数来进行处理。

**根据数组特点找出时间复杂度为O(n)的算法**
数组中有一个数字出现次数超过长度一半，也就是说它出现的次数比其他所有数字出现的次数的和还要多。因此我们可以考虑在遍历数组的时候保存两个值：一个是数组中的一个数字；另一个是次数。当我们遍历到下一个数字的时候，如果下一个数字和我们之前保存的数字相同，则次数加1；如果下一个数字和我们之前保存的数字不同，则次数减1.如果次数为0，那么我们需要保存下一个数字，并把次数设为1.由于我们要找的数字出现次数比其他所有数字出现的次数之和还要多，**那么要找的数字肯定是最后一次把次数设置为1时对应的数字**。见代码3。

### 代码1

    int MoreThanHalfNum_Solution(vector<int> numbers) {
        int len = numbers.size();
        int count=0;
        if(len==0)
            return 0;
        if(len==1)
            return numbers[0];
        sort(numbers.begin(), numbers.end());
       int mid = numbers[len/2];
        for(int i=0;i<len;i++)
        {
            if(numbers[i]==mid)
                ++count;
        }
        return (count>(len/2))?mid:0;
    }
### 代码2

    bool g_bInputInvaild = false;
    bool CheckInvalidArray(int* numbers, int length)
    {
    	g_bInputInvalid = false;
    	if (numbers == nullptr && length <= 0)
    		g_bInputInvalid = true;
    	return g_bInputInvalid;
    }
    bool CheckMoreThanHalf(int* numbers, int length, int number)
    {
    	int times = 0;
    	for (int i = 0; i < length; ++i)
    	{
    		if (numbers[i] == number)
    			times++;
    	}
    	bool isMoreThanHalf = true;
    	if (times * 2 <= length)
    	{
    		g_bInputInvalid = true;
    		isMoreThanHalf = false;
    	}
    	return isMoreThanHalf;
    }
    int Partition(int data[],int length,int start,int end)
{
    if(data==NULL || length<=0||start<0 || end>=length)
    {
        cout<<"error1!"<<endl;
        exit(0);
    }
    int index=RandomInRange(start,end);
 
    swap_element(&data[index],&data[end]);
    int small=start-1;
    for(index=start;index<end;index++)
    {
       if(data[index]<data[end])
        {
                 ++small;
            if(small != index)
            {
                swap_element(&data[index],&data[small]);
            }
        }
    }
    ++small;
    swap_element(&data[small],&data[end]);
    return small;
}
  

      int MoreThanHalfNum_Solution(vector<int> numbers) {
        	if(CheckInvalidArray(numbers,length)
        		return 0;
        	int middle=length>>1;
        	int start=0;
        	int end=length-1;
        	int index=Partition(numbers,length,start,end);
        	while(index!=middle)
        	{
        		if(index>middle)
        		{
        			end=index-1;
        			index=Partition(numbers,length,start,end);
        		}
        		else{
        			start=index+1;
        			index=Partition(numbers,length,start,end);
        		}
        	}
    	
    	int result=numbers[middle];
    	if(!CheckMoreThanHalf(numbers,length,result))
    		result=0;
    	return result;
    }
    
### 代码3

    int MoreThanHalfNum_Solution2(int* numbers, int length)
    {
    	if (CheckInvalidArray(numbers, length))
    		return 0;
    	int result = numbers[0];
    	int times = 1;
    	for (int i = 1; i < length; ++i)
    	{
    		if (times == 0)
    		{
    			result = numbers[i];
    			times = 1;
    		}
    		else if (numbers[i] == result)
    			times++;
    		else
    			times--;
    	}
    	if (!CheckMoreThanHalf(numbers, length, result))
    		result = 0;
    	return result;
    }
    

## 题目2 最小的k个数

### 题目描述

输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。

### 题目解析
最简单的方法莫过于对这个数组进行排序，然后输出前k个数，但是这样复杂度是O(nlogn)，当数字很大的时候，还是复杂度高了些。

但是我们可以考虑借鉴题目1中的方法，也就是借鉴快速排序进行处理，复杂度有O(n)，当然这种方法只有当我们可以修改输入的数组的时候才可以用。如果基于数组的第k个数字来调整，那么比第k个数字小的所有数字位于数组的左边，比第k个数字大的数字都位于数字有边。这样调整以后，位于数组中左边的k个数字就是最小的k个数字（这k个数字不一定有序）。代码如代码1所示。

### 代码

    void GetLeastNumbers(int* input, int n, int* output, int k)
    {
    	if(input==nullptr||output==nullptr||k>n||n<=0||k<=0)
    		return;
    	int start=0;
    	int end=n-1;
    	int index=Partition(intput,n,start,end);
    	while(index!=k-1)
    	{
    		if(index>k-1)
    		{
    			end=index-1;
    			index=Partition(input,n,start,end);
    		}
    		else
    		{
    			start=index+1;
    			index=Partition(intput,n,start,end);
    		}
    	}
    	for(int i=0;i<k;++i)
    		output[i]=input[i];
    }

## 题目3 连续子数组的最大和

### 题目描述

HZ偶尔会拿些专业问题来忽悠那些非计算机专业的同学。今天测试组开完会后,他又发话了:在古老的一维模式识别中,常常需要计算连续子向量的最大和,当向量全为正数的时候,问题很好解决。但是,如果向量中包含负数,是否应该包含某个负数,并期望旁边的正数会弥补它呢？例如:{6,-3,-2,7,-15,1,2,2},连续子向量的最大和为8(从第0个开始,到第3个为止)。给一个数组，返回它的最大连续子序列的和，你会不会被他忽悠住？(子向量的长度至少是1)

### 题目解析

使用在线规划，复杂度为O(n)。在线规划的思想就是定义一个当前和（ThisSum）和一个最大和（MaxSum）。就是从第一个数开始加，赋值给ThisSum，然后如果ThisSum比MaxSum大的话，那就把ThisSum给MaxSum，否则的话不给。如果ThisSum加着加着都小于0了，那么这几个数字的和就没必要保留，直接舍弃就好了。**由于题目说了长度至少是1，所以无需判断长度为0的情况，但是脑子里应该要想着这件事。**

### 代码

    int FindGreatestSumOfSubArray(vector<int> array) {
		int ThisSum =0;
		int MaxSum = array[0];
		int N = array.size();
		int i;
		for(i=0;i<N;i++)
		{
			ThisSum += array[i];
			if(ThisSum>MaxSum)
				MaxSum=ThisSum;
			else if(ThisSum<0)
				ThisSum=0;
		}
		return MaxSum;
    
    }

## 题目4 整数中出现1的次数

### 题目描述
求出1-13的整数中1出现的次数,并算出100-1300的整数中1出现的次数？为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数（从1 到 n 中1出现的次数）。

### 题目解析

可以直接判断，用数字%10的出来的余数看是不是等于1即可。复杂度为O(n)。

### 代码

    int NumberOf1Between1AndN_Solution(int n)
    {
        int count = 0;
        if(n==0)
            return count;
        for(int i=1;i<=n;i++)
        {
            int tmp=i;
            while(tmp)
            {
                if(tmp%10==1)
                    ++count;
                tmp /=10;
            }
        }
    return count;
    }

## 题目5 把数组排成最小的数字

### 题目描述
输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。

### 题目解析
我们应该考虑怎么去拼接数字。要注意，m和n在int型能表达范围之内，但是mn或者nm可就不一定了。所以我们可以**把数字转换成字符串**进行处理。
根据题目要求，若mn<nm，则输出mn；若nm<mn，则输出nm。然后我们可以通过证明得到以下结论（证明省略）：

> 若ab > ba 则 a > b，即排序为ba；
> 若ab < ba 则 a < b，即排序为ab；
> 若ab = ba 则 a = b，即排序为ab。

### 代码

        static bool cmp(int a, int b)
    {
    //意思是若ab<ba，则返回(a,b)；若ab>ba，则返回(b,a)。
    	string A = to_string(a) + to_string(b);
    	string B = to_string(b) + to_string(a);
    	return A < B;
    }
        string PrintMinNumber(vector<int> numbers) {
            int len =numbers.size();
            if(len==0)
                return "";
            string result;
            sort(numbers.begin(),numbers.end(),cmp);
            for(int i=0;i<len;i++)
                result += to_string(numbers[i]);
            return result;
            
        }

## 题目6 第一次只出现一次的字符

### 题目描述
在一个字符串(0<=字符串长度<=10000，全部由字母组成)中找到第一个只出现一次的字符,并返回它的位置, 如果没有则返回 -1（需要区分大小写）。

### 题目解析

只要这种问题，就可以想到HashTable，但是由于这个问题很简单，而且字符串全部由字母组成，那么每个字母的ASCII码肯定不一样，我们就可以用一个长度为52的数组来记录他们出现的次数，对于字母每出现一次，就对它加1。
当然我们这里为了通用性，可以使用对任意字符进行判断，那么我们就可以考虑实现一个简单的哈希表。字符是一个长度为8的数据类型，所以有256种可能，于是可以创建一个长度为256的数组，每个字符根据其ASCII码值作为数组的下表对应数组的一个数字，而数组中存储的是每个字符出现的次数。

第一次扫描时，在河西表中更新一个字符出现的次数的时间是O(1)。如果字符串长度为n，那么第一次扫描的时间复杂度是O(n)。第二次扫描时，同样在O(1)时间内能独处一个字符出现的次数，所以时间复杂度仍然是O(n)。这样算起来，总的时间复杂度是O(n)。同时，我们需要一个包含256个字符的辅助数组，它的代销为1kb。由于这个数组的大小是一个常数，因此可以认为空间复杂度为O(1)。

### 代码

    int FirstNotRepeatingChar(string str) {
        int asc[256]={0};
        int len=str.size();
        if(len==0)
            return -1;
        for(int i=0;i<len;i++)
            asc[str[i]]++;
        for(int i=0;i<len;i++)
        {
            if(asc[str[i]]==1)
                return i;
        }
        return -1;
    }

## 题目7 丑数

### 题目描述

把只包含质因子2、3和5的数称作丑数（Ugly Number）。例如6、8都是丑数，但14不是，因为它包含质因子7。 习惯上我们把1当做是第一个丑数。求按从小到大的顺序的第N个丑数。

### 题目解析
代码1中所述是最简单的判断方法，很直观，但是效率不够高。

### 代码1

    bool isUgly(int number)
    {
    	while(number%2==0)
    		number/=2;
    	while(number%3==0)
    		number/=3;
    	while(number%/5==0)
    		number/=5;
    	return (number==1)?true:false;
    }
    
    int GetUglyNumber(int index)
    {
    	if(index<=0)
    		return 0;
    	int number=0;
    	int uglyFound=0;
    	while(uglyFound<index)
    	{
    		++number;
    		if(isUgly(number))
    		{
    			uglyFound++;
    		}
    	}
    	return number;
    }


## 题目8 数字在排序数组中出现的次数


### 题目描述

统计一个数字在排序数组中出现的次数。

### 题目解析
最简单的方法就是直接for循环，这个复杂度是O(n)。

### 代码

    int GetNumberOfK(vector<int> data ,int k) {
        int len = data.size();
        int count=0;
        for(int i=0;i<len;i++)
        {
            if(data[i]==k)
                ++count;
        }
        return count;
    }
    

## 题目9 两个链表的第一个公共节点

### 题目描述

输入两个链表，找出它们的第一个公共结点。

### 代码
  
```
 ListNode* FindFirstCommonNode( ListNode *pHead1, ListNode *pHead2) {
        int len1 = findListLenth(pHead1);
        int len2 = findListLenth(pHead2);
        //如果两个长度不相等，就把长的那个链表上的指针从开头往后移动|len1-len2|个位置，这样就相当于两个链表同一起跑线开始。
        if(len1 > len2){
            pHead1 = walkStep(pHead1,len1 - len2);
        }else{
            pHead2 = walkStep(pHead2,len2 - len1);
        }
        //由于这个时候两个链表从指针所在位置往后长度肯定一致，所以这里指定pHead1和pHead2判断是否到尾部都可以
        while(pHead1 != NULL){
            //如果两个结点相等，自然就是第一个公共节点了，否则往后继续找
            if(pHead1 == pHead2) return pHead1;
            pHead1 = pHead1->next;
            pHead2 = pHead2->next;
        }
        return NULL;
    }
     
    int findListLenth(ListNode *pHead1){
        if(pHead1 == NULL) return 0;
        int sum = 1;
        while(pHead1 = pHead1->next) sum++;
        return sum;
    }
     
    ListNode* walkStep(ListNode *pHead1, int step){
        while(step--){
            pHead1 = pHead1->next;
        }
        return pHead1;
    }
```


## 题目10 数组中的逆序对

### 题目描述

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组,求出这个数组中的逆序对的总数P。并将P对1000000007取模的结果输出。 即输出P%1000000007

### 题目解析

我们以数组{7,5,6,4}为例来分析统计逆序对的过程。每次扫描到一个数字的时候，我们不拿ta和后面的每一个数字作比较，否则时间复杂度就是O(n^2)，因此我们可以考虑先比较两个相邻的数字。

![图示](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/jianzhioffer/images/nixudui.jpg)

(a) 把长度为4的数组分解成两个长度为2的子数组；
(b) 把长度为2的数组分解成两个成都为1的子数组；
(c ) 把长度为1的子数组 合并、排序并统计逆序对 ；
(d) 把长度为2的子数组合并、排序，并统计逆序对。

在上图（a）和（b）中，我们先把数组分解成两个长度为2的子数组，再把这两个子数组分别拆成两个长度为1的子数组。接下来一边合并相邻的子数组，一边统计逆序对的数目。在第一对长度为1的子数组{7}、{5}中7大于5，因此（7,5）组成一个逆序对。同样在第二对长度为1的子数组{6}、{4}中也有逆序对（6,4）。由于我们已经统计了这两对子数组内部的逆序对，因此需要把这两对子数组 排序 如上图（c）所示， 以免在以后的统计过程中再重复统计。
接下来我们统计两个长度为2的子数组子数组之间的逆序对。合并子数组并统计逆序对的过程如下图如下图所示。
我们先用两个指针分别指向两个子数组的末尾，并每次比较两个指针指向的数字。如果第一个子数组中的数字大于第二个数组中的数字，则构成逆序对，并且逆序对的数目等于第二个子数组中剩余数字的个数，如下图（a）和（c）所示。如果第一个数组的数字小于或等于第二个数组中的数字，则不构成逆序对，如图b所示。每一次比较的时候，我们都把较大的数字从后面往前复制到一个辅助数组中，确保 辅助数组（记为copy） 中的数字是递增排序的。在把较大的数字复制到辅助数组之后，把对应的指针向前移动一位，接下来进行下一轮比较。

过程：先把数组分割成子数组，先统计出子数组内部的逆序对的数目，然后再统计出两个相邻子数组之间的逆序对的数目。在统计逆序对的过程中，还需要对数组进行排序。如果对排序算法很熟悉，我们不难发现这个过程实际上就是归并排序。

### 代码

```
int InversePairs(int* data, int length)
{
	if(data==nullptr||length<0)
		return 0;
	int* copy=new int[length];
	for(int i=0;i<length;++i)
		copy[i]=data[i];
	int count=InversePairsCore(data,copy,0,length-1);
	delete[] copy;
	return count;
}

int InversePairsCore(int*data,int*copy,int start,int end)
{
	if(start==end)
	{
		copy[start]=data[start];
		return 0;
	}
	
	int length=(end-start)/2;
	
	int left=InversePairsCore(copy,data,start,start+length);
	int right=InversePairsCore(copy,data,start+length+1,end);
	
	//i初始化为前半段最后一个数字的下标
	int i=start+length;
	//j初始化为后半段最后一个数字的下标
	int j=end;
	int indexCopy=end;
	int count=0;
	while(i>=start&&j>=start+length+1)
	{
		if(data[i]>data[j])
		{
			copy[indexCopy--]=data[i--];
			count+=j-start-length;
		}
		else
		{
			copy[indexCopy--]=data[j--];
		}
	}
	for(;i>=start;--i)
		copy[indexCopy--]=data[i];
	for(;j>=start+length+1;--j)
		copy[indexCopy--]=data[j];
	
	return left+right+count;
}
```
