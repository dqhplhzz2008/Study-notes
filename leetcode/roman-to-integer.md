## Roman to Integer

### 题目描述

Given a roman numeral, convert it to an integer.Input is guaranteed to be within the range from 1 to 3999.

### 题目解析

罗马数字的规律如下：

| 罗马数字 |阿拉伯数字 |
| --- | --- |
|I| 1 |
| V |5  |
|X | 10 |
|L | 50 |
| C |100  |
|D  |500  |
| M |1000  |

另外还要注意的是：
- 相同的数字连写、所表示的数等于这些数字相加得到的数、如：Ⅲ=3；
- 小的数字在大的数字的右边、所表示的数等于这些数字相加得到的数、 如：Ⅷ=8、Ⅻ=12；
- 小的数字、（限于 Ⅰ、X 和 C）在大的数字的左边、所表示的数等于大数减小数得到的数、如：Ⅳ=4、Ⅸ=9；
- 正常使用时、连写的数字重复不得超过三次；
- 在一个数的上面画一条横线、表示这个数扩大 1000 倍。

由于这个题的范围限制到了3999，所以用不上最后一条主要事项。另外，由于本题是给定的罗马数字，所以不要考虑连写的数字重复超过三次的情况。
假设一个罗马数字是由A和B组成，我们可以发现以下的现象：

- A=B：结果为int(A)+int(B)；
- A>B：结果为int(A)+int(B)；
- A<B：结果为-int(A)+int(B)。

注意：在这里int()不是强制类型转换的意思，而是我自己定义的将罗马数字转换成整型数字的一个标志而已。

所以我们可以这样想：使用一个for循环遍历从0~len-1（字符串长度-1），如果当前位置i的数字小于下一位置i+1的数字的时候，则直接从sum里面减去第i个数字（加1个数字再减一个数字等同于减一个数字再加一个数字）；否则就加上i。这样，字符串的最后一个元素所代表的数字没有加，在循环结束之后加上即可。
代码实现如下。

### 代码实现

```
int strToint(char c)

{

       switch (c)

       {

       case 'I':

              return 1;

       case 'V':

              return 5;

       case 'X':

              return 10;

       case 'L':

              return 50;

       case 'C':

              return 100;

       case 'D':

              return 500;

       case 'M':

              return 1000;

       default:

              return 0;

       }

}



int romanToInt(string s) {

       int len = s.size();

       int sum=0;

       for (int i = 0; i < len-1; ++i)

       {

              int tem1 = strToint(s[i]);

              int tem2 = strToint(s[i + 1]);

              if (tem1 < tem2) 

                     sum -= tem1;

              else

                     sum += tem1;//若大于则直接相加，若等于也相加。

              //因为已经是罗马数字，所以不用考虑相同的会超过3个

       }

       sum += strToint(s[len - 1]);

       return sum;
       }
```






