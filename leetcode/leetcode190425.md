
## Remove Duplicates from sorted Array II

### 题目描述


Follow up for "Remove Duplicates":
What if duplicates are allowed at most twice?For example,
Given sorted array A =[1,1,1,2,2,3],Your function should return length =5, and A is now[1,1,2,2,3].

### 题目解析

类似于Remove Duplicates from sorted Array，但是这个题目要求重复的数字要保留两位。所以做适当修改即可。


### 代码实现

```
    int removeDuplicates(int A[], int n) {
        if(n<=2)
            return n;
        int count=2;
        for(int i=2;i<n;i++)
        {
            if(A[i]!=A[count-2])
                A[count++]=A[i];
        }
        return count;
    }
```

## Sqrx

### 题目说明
求一个数字的平方根

### 题目解析
利用牛顿逼近法。

### 代码实现

```
    int sqrt(int x) {
        long r=x;
		while(r*r>x)
			r=(r+x/r)/2;
		return r;
    }
```

## Length of last word

### 题目描述


Given a string s consists of upper/lower-case alphabets and empty space characters' ', return the length of last word in the string.If the last word does not exist, return 0.Note: A word is defined as a character sequence consists of non-space characters only.For example, 
Given s ="Hello World",
return5.

### 题目解析
这个题的关键就是抓住最后一个单词有什么特征，最后一个单词一定是它的前面有一个单词和空格，而后面没有单词（本题允许最后有空格），所以我们可以根据这个特点，很容易想到两种复杂度为O(n)的解题方法。第一种是最容易想到的，也就是从前往后走的方法，这个方法我们可以走这样的路子：判断当前字符不是空格，就对计数加1，如果是空格，就把计数重新置0，然后再开始计数。如果最后一个字符是空格怎么办呢？那我们就可以考虑空格是最后一个字符与不是一个字符时的区别：

| 情况 |是最后一个字符  |不是最后一个字符  |
| --- | --- | --- |
| s[i] |‘ ’  |‘ ’  |
| s[i+1 | '\0' |某个字符  |

所以可以基于上面这两个条件来进行判断，即若s[i]=' '且s[i+1]!='\0'的时候，那就是中间的空格符，所以可以计数置零。具体见代码1。

还有一种思路就是从后往前走，因为题目要求的是最后一个单词，所以在一般情况下，这种方法的时间都要快于第一种方法，特别是语句中单词特别多的时候。这种思路就是直接寻找除了最后一个字符位置之外第一个空字符的位置，得到这个位置后直接break即可。所以这个方法的步骤就是：

- 不断对计数加1，直到遇到第1个空格。
- 然后判断此时count是否为0，若为0，说明空格是最后一个字符，所以循环不跳出，继续进行；若count不为零，说明第一个单词已经结束，直接break跳出，返回count。


### 代码实现1

```
int lengthOfLastWord(const char *s) {

       if (s == nullptr)
              return 0;
       int count = 0;
       int len = strlen(s);
       for (int i = 0; i < len; i++)
       {
              if (s[i] != ' ')
                     ++count;
              else if (s[i] == ' '&&s[i + 1] != '\0')
                     count = 0;
              else
                     break;
       }
       return count;
}
```



### 代码实现2

```
    int lengthOfLastWord(const char *s) {
	if (s == nullptr)
		return 0;
	int count = 0;
	int len = strlen(s);
	for (int i = len - 1; i >= 0; i--)
	{
		if (s[i] != ' ')
			++count;
		else
			if(count)
				break;
	}
	return count;
    }
```