
## Jump Game

### 题目说明

Given an array of non-negative integers, you are initially positioned at the first index of the array.Each element in the array represents your maximum jump length at that position.Determine if you are able to reach the last index.For example:
A =[2,3,1,1,4], returntrue.A =[3,2,1,0,4], returnfalse.

### 题目解析

这个题解析起来我的想法很容易，复杂度为O(n)。就是：我记录当前A[i]的值，然后把i加上这个值，就相当于从当前这个位置往前走相应的步数。退出循环的判断条件有两个：

- 当前是第i个元素，但是i已经大于n-1了（下标从0开始，所以第n个数是第n-1）。
- A[i]为0：这里面又分两种情况，一种是如题目所给的第2种情况，在中间为0的这个位置不走了，还有一种情况是我这个数组一共1个元素，就是0。那么跳出。

交给下面的return语句后面判断。就是判断当做的位置是否是越过了最后一个位置？若越过了或者正好在最后一个位置，自然是return true；否则return false。


### 代码展示

```
bool canJump(int A[], int n) {
	int i = 0;
	while (A[i] != 0)
	{
		int jumpNum = A[i];
		i += jumpNum;
		if (i >= n-1)
			break;
	}
	return i >= n-1 ? true : false;

}
```