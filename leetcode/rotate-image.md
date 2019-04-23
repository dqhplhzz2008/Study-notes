
## rotate image

### 题目描述


You are given an n x n 2D matrix representing an image.Rotate the image by 90 degrees (clockwise).Follow up:
Could you do this in-place?

### 题目解析
旋转90°，可以当做两步：第一步是关于对角线取对称；第二步是关于水平线取上下对称。
记住这个原理。


### 代码实现

```
    void rotate(vector<vector<int> > &matrix) {
        //对角线对称
        int n=matrix.size();
        for(int i=0;i<n;i++)
            for(int j=0;j<n-i;j++)
                swap(matrix[i][j],matrix[n-1-j][n-1-i]);
        //上下交换
        for(int i=0;i<n/2;i++)
            for(int j=0;j<n;j++)
                swap(matrix[i][j],matrix[n-1-i][j]);
        
    }
```