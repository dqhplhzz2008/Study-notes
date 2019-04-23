
## unique path

### 题目描述


A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).How many possible unique paths are there?
![](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/leetcode/assets/unique-path1.png)

Above is a 3 x 7 grid. How many possible unique paths are there?Note: m and n will be at most 100.


### 题目解析

自己就是想不出来动态规划里面的问题如何来划分为合适的子问题（也就是写不出递推公式）。每次都是看了答案恍然大悟。其实这个题的递推公式非常之简单。就是：
当前点的路径=上面一个点的路径+左边一个点的路径。
也就是

```
path[i][j]=path[i-1][j]+path[i][j-1];
```

### 代码实现

```
    int uniquePaths(int m, int n) {
        vector<vector<int> >path(m,vector<int >(n,1));
        for(int i=1;i<m;i++)
            for(int j=1;j<n;j++)
            {
                path[i][j]=path[i-1][j]+path[i][j-1];
            }
        return path[m-1][n-1];
    }
```
