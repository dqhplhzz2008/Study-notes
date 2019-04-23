
## merge sorted array

### 题目描述


Given two sorted integer arrays A and B, merge B into A as one sorted array.Note: 
You may assume that A has enough space to hold additional elements from B. The number of elements initialized in A and B are mand n respectively.

### 题目解析

由于数组A的空间足够，为了不使用额外空间，我们很容易想到从后往前进行。该题目分为两步完成。
第一步：从后往前进行插入，也就是说比较的时候从A和B已有元素的最后一个元素开始比较，大的插入到A的未插入的最后一个位置。
完成上述操作的前提是，A和B的待排元素都还有，所以判断条件就是下面的
```
x1>=0 && x2>=0
```
对于上述操作的实现如下：
```
A[index--] = A[x1] > B[x2] ? A[x1--] : B[x2--];
```
这句话其实就是下面这段话的意思：
```
if(A[x1]>B[x2])
{
	A[index]=A[x1];
	--index;
	--x1;
}
else
{
	A[index]=B[x2];
	--index;
	--x2;
}
```
第二步：在第一步完成情况下存在两种情况：

- 原来的A和B都已经完整插入到A中，即x1=-1且x2=-1。
- 原来B已经插入完毕了但是A还没有，即x2=-1且x1>=0，此时A剩下的数字都在正确的位置，不需要再排序了。
- 原来的A插入完毕了，B还没有，即x1=-1且x2>=0，那就直接把B插入到剩下的位置即可。


### 代码实现

```
void merge(int A[], int m, int B[], int n) {
	int total = m + n;
	int x1 = m - 1;
	int x2 = n - 1;
	int index = total - 1;
	while (x1 >= 0 && x2 >= 0)
	{
		A[index--] = A[x1] > B[x2] ? A[x1--] : B[x2--];
	}
	while (x2 >= 0)
		A[index--] = B[x2--];
  }
```