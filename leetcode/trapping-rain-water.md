
## Trapping Rain Water

### 题目描述

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.For example, 
Given[0,1,0,2,1,0,1,3,2,1,2,1], return6.

![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/leetcode/assets/nqueensii.png)


The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. Thanks Marcosfor contributing this image!


### 题目分析

这个题目的想法，最容易想到的就是将它以最高的地方为基准分为左右两列进行相加计算，因为相加不可能跨过最高的那个地方。
对于左侧，我们从0向最高值靠拢，首先判断当前位置的值是否小于left（left刚开始是第0个，判断从第0个开始判断没问题），如果小于，那么就将suml累加上left-A[i]即可，如果不是小于，那么代表着从这一点开始，又要重新计算一个容量，所以令left=A[i]。如下所示：

```
if (A[i] < left)
			suml += left - A[i];
		else
			left = A[i];
```

对于右侧同理，从最右侧n-1开始往左判断，过程与上面相同，不再重复。代码如下：

```
		if (A[i] < right)
			sumr += right - A[i];
		else
			right = A[i];
```


### 代码实现

```
int trap(int A[], int n) {
	int maxHeight = 0;
	int left = 0;//由左往最大值计算
	int right = 0;//由右往最大值计算
	int suml = 0;
	int sumr = 0;
	//寻找到高度的最大值，将区间分为左侧和右侧两部分进行分别处理
	for (int i = 0; i < n; i++)
		if (A[i] > A[maxHeight])
			maxHeight = i;
	//先计算左侧的容量
	for (int i = 0; i < maxHeight; i++)
	{
		if (A[i] < left)
			suml += left - A[i];
		else
			left = A[i];
	}
	for (int i = n-1; i > maxHeight; i--)
	{
		if (A[i] < right)
			sumr += right - A[i];
		else
			right = A[i];
	}
	return suml + sumr;

}
```