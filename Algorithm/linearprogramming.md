## 线性规划问题
遇到一个线性规划问题，该如何解决呢？
1. 确定决策变量。
2. 确定目标函数。
3. 找出约束条件。
4. 求最优解。

一般线性规划问题可以表示为如下形式。

![公式1](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/linerprogramming1.jpg)

约束条件为：

![公式2](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/linerprogramming2.jpg)


- 变量满足约束条件的一组值成为线性规划问题的一个可行解。
- 所有可行解构成的集合成为线性规划的可行区域。
- 使目标函数取得极值的可行解称为最优解。
- 在最优解处目标函数的值成**最优值**。

线性规划解的情况：
- 有唯一最优解。
- 有无数多个最优解。
- 没有最优解。

### 线性规划的标准型
标准型如下：

![公式3](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/linerprogramming3.jpg)

#### 四个要求：
1. 目标函数为最大值（即为max）；
2. 约束条件常数项b<sub>i</sub>>=0；
3. 约束条件全部为等式约束；
4. 决策变量x<sub>i</sub>非负约束。

**线性规划标准型转化方法：**

1. 一般线性规划行驶中目标函数如果求最小值，那么令z'=-z，得到最优解后，加负号即可。
2. 右端常数项小于零时，则不等式两边同乘-1，将其变成大于零；同时改变不等号的方向，保证恒等变形。
3. 约束条件为大于与等于约束条件时，则在不等式左侧减去一个新的非负变量将不等式约束改为等式约束。**例如2x<sub>1</sub>-3x<sub>2</sub>≥10，修改为：2x<sub>1</sub>-3x<sub>2</sub>-x<sub>3</sub>=10，x<sub>3</sub>>0。**
4. 约束条件为小于等于约束时，则在不等式左侧加去一个新的非负变量将不等式约束改为等式约束。
5. 无约束的决策变量x，即可正可负的变量，则引入两个新的非负变量x'和x''，令x-x'-x''，其中x'≥0，x''≥0，将x带入线性规划模型。例如：2x<sub>1</sub>-3x<sub>2</sub>+x<sub>3</sub>=10，x<sub>3</sub>无约束，则可以修改为：x<sub>3</sub>=x<sub>4</sub>-x<sub>5</sub>，x<sub>4</sub>>0,x<sub>5</sub>>0，带入方程得到**2x<sub>1</sub>-3x<sub>2</sub>+x<sub>4</sub>-x<sub>5</sub>=10，x<sub>4</sub>>0,x<sub>5</sub>>0**。
注意：引入的新的非负变量称为**松弛变量**。

### 单纯形算法图解

基本概念：
- **基本变量**：每个约束条件中的系数为正，且只出现在一个约束条件中的变量。
- **非基本变量**：除基本变量以外的变量。
- **基本可行解**：满足标准形式约束条件的可行解称为基本可行解。
- **检验数**：目标函数中非基本变量的技术。

基本定理：
- **最优解判别定理**：若目标函数中关于非基本变量的所有系数小于等于0，则当前基本可行解就是最优解。
- **无穷多最优解判别定理**：若目标函数中关于费基本变量的所有检验数小于等于0，同时存在某个非基本变量的检验数等于0，则线性规划问题有无穷多个最优解。
- **无界解定理**：如果某个检验数c<sub>j</sub>大于0，而c<sub>j</sub>所对应的列向量的各分量a<sub>1j</sub>,a<sub>2j</sub>,...,a<sub>mj</sub>都小于等于0，则该线性规划问题有无界解。

约束标准型线性规划问题单纯形算法步骤如下：

1. 建立初始单纯形表。找出基本变量和非基本变量，**将目标函数由非基本变量表示**，建立初始单纯形表。<font color="red">**注意：**</font>**如果目标函数含有基本变量，要通过约束条件方程转换为非基本变量。** 还要注意：**基本变量的系数要转化为1** ，否则不能按照下面的计算方法。基本变量做行，非基本变量做列，检验数放第一行，常数项放低1列，约束条件中非基本变量的系数作为值，构造初始单纯形表。如下所示：
![约束条件](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/lpyue1.jpg)

||b|x<sub>2</sub>|x<sub>3</sub>|x<sub>4</sub>
|--|--|--|--|--|
|c|0|-1|3|-2
|x<sub>1</sub>|7|3|-1|2
|x<sub>5</sub>|12|-2|4|0
|x<sub>6</sub>|10|-4|3|8

2. 判断是否得到最优解。判别并检查目标函数的所有系数。
    - 如果所有的c<sub>j</sub><=0，则已经获得最优解，算法结束。
    - 若在检验数c<sub>j</sub>中，有些为正数，但其中某一正的检验数所对应的列向量的各分量均小于等于0，则线性规划问题无界，算法结束。
    - 若在检验数c<sub>j</sub>中，有些为正数且它们对应的列向量中有正的分量，则转到第3步。

3. 选入基变量。选取所有正检验数中最大的一个，记为c<sub>e</sub>，其对应的非基本变量为x<sub>e</sub>，称为入基变量，x<sub>e</sub>对应的列向量[a<sub>1e</sub>,a<sub>2e</sub>,...,a<sub>me</sub>]<sup>T</sup>为入基列。在本例中，x<sub>3</sub>为入基变量，x<sub>3</sub>对应的列向量为入基列，如下所示。

||b|x<sub>2</sub>|x<sub>3</sub>|x<sub>4</sub>
|--|--|--|--|--|
|c|0|-1|**3**|-2
|x<sub>1</sub>|7|3|**-1**|2
|x<sub>5</sub>|12|-2|**4**|0
|x<sub>6</sub>|10|-4|**3**|8

4. 选离基变量、选取“常数列元素/入基列元素”正比值最小者，所对应的基本变量x<sub>k</sub>为离基变量。x<sub>k</sub>对应的行向量为离基行。在本例中，x<sub>5</sub>为离基变量，对应的行向量为离基行。
5. 换基变换。在单纯形表上将入基变量和离基变量互换位置，即在本例中将x<sub>3</sub>和x<sub>5</sub>交换位置，换基变换后如下所示。

||b|x<sub>2</sub>|<font color="red">x<sub>5</sub></font>|x<sub>4</sub>
|--|--|--|--|--|
|c|0|-1|**3**|-2
|x<sub>1</sub>|7|3|**-1**|2
|<font color="red">**x<sub>3</sub>**</font>|12|-2|**4**|0
|x<sub>6</sub>|10|-4|**3**|8

6. 计算新的单纯形表。按照下面的方法计算新的单纯形表，然后转第2步。4个特殊位置如下：
    - **入基列**：-原值/交叉位值（不包括交叉位）。
    - **离基行**=原值/交叉位值（不包括交叉位）
    - **交叉位**=原值取倒数。
    - **c<sub>0</sub>位**：原值+同行入基列元素*同列离基行元素/交叉位值。
    - 一般位置元素=原值-同行入基列元素*同列离基行元素/交叉位值。

||b|x<sub>2</sub>|<font color="red">x<sub>5</sub></font>|x<sub>4</sub>
|--|--|--|--|--|
|c|9|0.5|**-0.75**|-2
|x<sub>1</sub>|10|2.5|**0.25**|2
|<font color="red">**x<sub>3</sub>**</font>|3|-0.5|**0.25**|0
|x<sub>6</sub>|1|-2.5|**-0.75**|8

7. 判断是否得到最优解，若没有继续第3~6步，直到找到最优解或判定无界解停止。在本例中，再次选定基列变量x<sub>2</sub>和离基变量x<sub>1</sub>，将他们互换位置，重新计算单纯形表，得到下面的表。

||b|x<sub>1</sub>|x<sub>5</sub>|x<sub>4</sub>
|--|--|--|--|--|
|c|11|-0.2|-0.8|-2.4
|x<sub>2</sub>|4|0.4|0.1|0.8
|x<sub>3</sub></font>|5|0.2|0.3|0.4
|x<sub>6</sub>|11|1|-0.5|10

可以看出目标函数的检验数全部都小于0，得到最优解。c<sub>0</sub>就是我们要的最优值（11），而最优解是由基本变量对应的常数项组成的，即x<sub>2</sub>=4，x<sub>3</sub>=5，x<sub>6</sub>=11，非基本变量全部置零。以上算法获得的是max z'，而本题要求是min z，所以答案是-11。

## 工厂最大效益——单纯形算法

### 题目描述

某食品加工厂有三个车间，第一车间用1个单位的原料N可以加工5个单位的产品A或者2个单位的产品B。产品A若直接出售，价格10元，如果第二车间继续加工，加工费5元，加工后售价19元，产品B直接出售16元，第三车间继续加工加工费4元，然后售价24元。原料N的单位购入价为5元，每工时工资为15元，第一车间加工一个单位N，需要0.05工时，第二个0.1工时，第三个0.08工时，每个月最多得到12000个N，工时最多为1000工时。如何生产，收益最大？

### 问题分析

假设变量：
x<sub>1</sub>：产品A的售出量。
x<sub>2</sub>：产品A在第二车间加工后售出量.
x<sub>3</sub>：产品B售出量。
x<sub>4</sub>：产品B在第三车间加工后售出量。
x<sub>5</sub>：第一车间所用原材料数量。

- 第一车间所有原材料费和人工费为：5x<sub>5</sub>+0.05×15x<sub>5</sub>=**5.75x<sub>5</sub>**（下面计算盈利时，均已除去第一车间的材料和人工费）

- A直接售出，盈利：**10x<sub>1</sub>**。
- A加工后售出，因为有额外加工费、人工费：5+0.1×15=6.5，售价-额外成本=19-6.5=12.5，盈利**12.5x<sub>2</sub>**。
- B直接售出，盈利**16x<sub>3</sub>**。
- B加工后售出，额外费用4+0.08×15=5.2，售价-成本=24-5.2=18.8，盈利**18.8x<sub>4</sub>**。
- 总盈利：**z=10x<sub>1</sub>+12.5x<sub>2</sub>+16x<sub>3</sub>+18.8x<sub>4</sub>-5.75x<sub>5</sub>**。
- 所以目标函数和约束条件如下：

![约束条件](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/lpyue2.jpg)

### 完美图解

转化为**标准型**，目标函数也重新表示：

![约束条件](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/lpyue3.jpg)

基本变量为：x<sub>1</sub>，x<sub>3</sub>，x<sub>6</sub>，x<sub>7</sub>。
非基本变量：x<sub>2</sub>，x<sub>4</sub>，x<sub>5</sub>。

建立单纯形表如下：
||b|x<sub>2</sub>|x<sub>4</sub>|x<sub>5</sub>|
|--|--|--|--|--|
|c|0|2.5|2.8|76.25|
|x<sub>1</sub>|0|1|0|-5|
|x<sub>3</sub>|0|0|1|-2|
|x<sub>6</sub>|12000|0|0|1|
|x<sub>7</sub>|1000|0.1|0.08|0.05|

具体图解过程不再重述。

### 代码实现

全局变量如下：

    float kernel[100][100];//存储非单纯形表
    char FJL[100] = {};//非基本变量
    char JL[100] = {};//基本变量
    int n, m, i, j;

代码内容如下：

    void print()//输出单纯型表
    {
        cout<<endl;
        cout<<"----------单纯形表如下：----------"<<endl;
        cout<<"  ";
        cout<<setw(7)<<"b ";
        for(i=1;i<=m;i++)
           cout<<setw(7)<<"x"<<FJL[i];
        cout<<endl;
        cout<<"c ";
        for(i=0;i<=n;i++)
        {
            if(i>=1)
                cout<<"x"<<JL[i];
            for(j=0;j<=m;j++)
               cout<<setw(7)<<kernel[i][j]<<" ";
            cout<<endl;
        }
    }
    
    void DCXA()
    {
        float max1;  //max1用于存放最大的检验数
        float max2;  //max2用于存放最大正检验数对应的基本变量的最大系数
        int e=-1;    //记录入基列
        int k=-1;    //记录离基行
        float min;
        //循环迭代，直到找到问题的解或无解为止
        while(true)
        {
            max1=0;
            min=100000000;
            for(j=1;j<=m;j++)  //找入基列(最大正检验数对应的列)
            {
                if(max1<kernel[0][j])
                {
                    max1=kernel[0][j];
                    e=j;
                }
            }
            if(max1<=0) //最大值小于等于0，即所有检验数小于等于0，满足获得最优解的条件
            {
               cout<<endl;
               cout<<"获得最优解:"<<kernel[0][0]<< endl;
               print();
               break;
             }
            for(j=1;j<=m;j++)  //判断正检验数对应的列是否都小于等于0，如果是则无界解
            {
                max2=0;
                if(kernel[0][j]>0)
                {
                    for(i=1;i<=n;i++) //搜索正检验数对应的列
                      if(max2<kernel[i][j])
                         max2=kernel[i][j];
                    if(max2==0)
                    {
                       cout<<"解无界"<<endl;
                       return;//退出函数，不能用break，因为它只是退出当前循环
                    }
                }
            }
            for(i=1;i<=n;i++) //找离基行(常数列/入基列正比值最小对应的行)
            {
                float temp=kernel[i][0]/kernel[i][e]; //常数项在前,temp=fabs(temp);
                if(temp>0&&temp<min) //找离基变量
                {
                   min=temp;
                   k=i;
                }
            }
            cout<<"入基变量："<<"x"<<FJL[e]<<" ";
            cout<<"离基变量："<<"x"<<JL[k]<<endl;
           //换基变换(转轴变换)
            char temp=FJL[e];
            FJL[e]=JL[k];
            JL[k]=temp;
            for(i=0;i<=n;i++) //计算除入基列和出基行的所有位置的元素
            {
                if(i!=k)
                {
                    for(j=0;j<=m;j++)
                    {
                        if(j!=e)
                        {
                            if(i==0&&j==0) //计算特殊位c0,即目标函数的值
                               kernel[i][j]=kernel[i][j]+kernel[i][e]*kernel[k][j]/kernel[k][e];
                            else   //一般位置
                               kernel[i][j]=kernel[i][j]-kernel[i][e]*kernel[k][j]/kernel[k][e];
                        }
                    }
                }
            }
            for(i=0;i<=n;i++) //计算特殊位,入基列的元素
            {
                if(i!=k)
                    kernel[i][e]=-kernel[i][e]/kernel[k][e];
            }
            for(j=0;j<=m;j++) //计算特殊位,离基行的元素
            {
                if(j!=e)
                  kernel[k][j]=kernel[k][j]/kernel[k][e];
            }
            //计算特殊位,交叉位置
            kernel[k][e]=1/kernel[k][e];
            print();
        }
    }

### 复杂度分析
1. 时间复杂度：在输入基本变量和非基本变量中用了n+m循环次数，在输入单纯形表时有n*m此循环，打印最优解时有n+n*m次的时间打印结果，在寻找入基列和离基行中，最坏情况下有O(n*m)次循环，在循环迭代中最坏情况需要2<sup>n</sup>迭代，则时间复杂度为O(2<sup>n</sup>)。
2. 空间复杂度：O(1)。

## 最大网络流——最短增广路算法

### 问题描述
设有向带权图G=(V,E)，V={s,v<sub>1</sub>,v<sub>2</sub>,v<sub>3</sub>,...,t}。在G中有两个特殊的结点s和t。s称为源点，t为汇点。图中各边的方向表示允许的流向，边上的权值表示该边允许通过的最大可能流量cap，且cap≥0，称它为边的容量。而且如果边集合E含有一条边(u,v)，则比如不存在反方向的(v,u)，我们称这样的有向带权图为**网络**。
**网络是一个有向带权图，包含一个源点和一个汇点，没有反平行边。**
**网络流**：网络流即网络上的流，是定义在网络边集E上的一个非负函数flow={flow(u,v)},flow(u,v)是边上的流量。
**可行流**：满足下面两个性质的网络流flow称为可行流：
1. 容量约束。每个管道的实际流量flow不能超过该管道的最大容量cap。
2. 流量守恒。除源点s和汇点t外，所有内部结点流入量=流出量。

**网络最大流**：在满足容量约束和流量守恒前提下，在流网络中找到一个净输出最大的网络流。

### 增广路算法（Ford-Fulkerson算法）
**基本概念**
1. 实流网络：实际流量的网络。
2. 残余网络：每个网络G及其上的一个流flow，都对应一个残余网络G<sup>*</sup>。G<sup>*</sup>和G结点集相同，而网络G中的每条边对应G<sup>*</sup>中的一条边或两条边。**在残余网络中，与网络边对应的同向边是可增量（即还可以增加多少），反向边是实际流量。**
3. **可增广路**是残余网络G<sup>*</sup>中一条从源点s到汇点t的简单路径。
4. **可增广量**是指在可增广路p上每条边可以增加的流量最小值。

**可增广路增流**
增流操作分为两个过程：一是在实流网络中增流；二是在残余网络中减流。

**增广路算法**
增广路定理：设flow是网络G的一个可行流，如果不存在从源点s到汇点t关于flow的可增广路，则flow是G的一个最大流。
增广路算法基本思想是在残余网络中找到可增广路，然后在实流网络中沿可增广路增流，在残余网络中沿可增广路减流；继续在残余网络中找可增广路，直到不存在可增广路为止。

**最短增广路算法**
Edmonds-Karp算法是以**广度优先**的增广路算法，又称为最短增广路算法（Shortest Augment Path, SAP）。算法步骤如下：
采用队列q来存放已访问未检查的结点。bool数组vis[]标注结点是否被访问过，pre[]数组记录可增广路上结点的前驱。pre[v]=u表示可增广路上v结点的前驱是u，最大流值maxflow=0。

1. 初始化可行流flow为零流，即实流网络中全是零流边，残余网络中全是最大容量边。初始化vis[]=false，pre[]数组为-1。
2. 令vis[s]=true，s加入队列q。
3. 如果队列不空，继续下一步，否则算法结束，找不到可增广路。当前的实流网络就是最大流网络，返回最大流值maxflow。
4. 队头元素new出队，在残余网络中检查new的所有邻接结点i。如果未被访问，则访问它，令vis[i]=true，pre[i]=new；如果i=t，说明已经到达汇点，找到一条可增广路，转向第5步；否则结点i加入队列q，，转向第3步。
5. 从汇点开始，通过前驱数据pre[]，逆向找可增广路上每条边值的最小值，即可增量d。
6. 在实流网络中增流，在残余网络中减流，maxflow+=d，转向第2步。

### 算法设计
在求解的时候需要先初始化一个可行流，然后在可行流上不断找可增广路增流即可。初始化为任何一个可行流都可以，但需要满足容量约束和平衡约束。通常初始化可行流为0流。

![网络G](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/wangluog.jpg)

1. 数据结构。网络G邻接矩阵为g[][]。

|∞|12|10|∞|∞|∞|
|--|--|--|--|--|--|
|∞|∞|∞|8|∞|∞|
|∞|2|∞|∞|13|∞|
|∞|∞|5|∞|∞|18|
|∞|∞|∞|6|∞|4|
|∞|∞|∞|∞|∞|∞|

2. 初始化。初始化可行流flow为零流，即实流网络中全是零流边，残余网络全是最大容量边，初始化vis[]=false，pre[]数组为-1。

|vis[i]|1|2|3|4|5|6|
|--|--|--|--|--|--|--|
||0|0|0|0|0|0|0

|pre[i]|1|2|3|4|5|6|
|--|--|--|--|--|--|--|
||-1|-1|-1|-1|-1|-1|

3. 令vis[1]=true，1加入队列q。
4. 队头元素1出队。在残余网络G<sup>*</sup>中依次检查1的所有邻接结点2和3，两个结点都未被访问，令vis[2]=true，pre[2]=1，结点2加入队列q；vis[3]=true,pre[3]=1，结点3加入队列q。此时vis[i]、pre[i]和q如下所示。

|vis[i]|1|2|3|4|5|6|
|--|--|--|--|--|--|--|
||1|1|1|0|0|0|0

|pre[i]|1|2|3|4|5|6|
|--|--|--|--|--|--|--|
||-1|1|1|-1|-1|-1|

|序号|0|1|2|3|
|--|--|--|--|--|
|q|2|3|||

5. 队头元素2出队。在残余网络中依次检查2的所有邻接结点4，4未被访问，令vis[4]=1,pre[4]=2，结点4加入队列q。
6. 队头元素3出队。在残余网络中依次检查3的所有邻接结点2和5。2已经被访问，5未被访问，令vis[5]=1,pre[5]=3，结点5加入队列q。此时vis[i]、pre[i]和q如下所示。

|vis[i]|1|2|3|4|5|6|
|--|--|--|--|--|--|--|
||1|1|1|1|1|0|0

|pre[i]|1|2|3|4|5|6|
|--|--|--|--|--|--|--|
||-1|1|1|2|3|-1|

|序号|0|1|2|3|
|--|--|--|--|--|
|q|4|5|||

7. 队头元素4出队。在残余网络中依次检查4的所有邻接结点3和6。3已经被访问，6未被访问，令vis[6]=1,pre[6]=4。结点6就是汇点，找到一条增广路。此时vis[i]、pre[i]和q如下所示。

|vis[i]|1|2|3|4|5|6|
|--|--|--|--|--|--|--|
||1|1|1|1|1|1|1

|pre[i]|1|2|3|4|5|6|
|--|--|--|--|--|--|--|
||-1|1|1|2|3|4|

|序号|0|1|2|3|
|--|--|--|--|--|
|q|5||||

8. 读取钱取数组，得到1-2-4-6，找到该路径上的最小边值为8，即可增量d=8。
9. 实流网络增流，残余网络减流。可增广路通向的边增流d，反向边减流d。
10. 重复2~8步，找到第2条可增广路1-3-5-6，找到最小边值，即可增量=4，进行第9步。 
11. 重复2~8步，找到第3条可增广路1-3-5-4-6，找到最小边值，即可增量=6，进行第9步。 
12. 重复2~8步，找不到可增广路，算法结束，最大流值为所有的增量之和18。

**为什么要采用残余网络+实流网络？**
在网络G及可行流直接找可增广路，有可能得不到最大流。

**为什么要用实流网络？**
从残余网络中无法判断哪些是实流边，哪些是可增量边，如果想知道实际的网络流量，就需要借助于实流网络。

整个过程是采用：**在残余网络找可增广路，在实流网络中增流相结合的方式**，求解最大流。

### 代码实现

1.找可增广路。采用普通队列实现对残余网络的广度搜索，从源点u开始，s搜索邻接点v。如果v被访问，则标记已访问，且记录v结点的前驱为u；如果u结点不是汇点则入队；如果u结点恰好是汇点，则返回，找到汇点时则找到一条可增广路。如果队列为空，则说明已经找不到可增广路。

    bool bfs(int s,int t)
    {
        memset(pre,-1,sizeof(pre));
        memset(vis,false,sizeof(vis));
        queue<int>q;
        vis[s]=true;
        q.push(s);
        while(!q.empty())
        {
            int now=q.front();
            q.pop();
            for(int i=1;i<=n; i++)//寻找可增广路
            {
                if(!vis[i]&&g[now][i]>0)//未被访问且有边相连
                {
                    vis[i] = true;
                    pre[i] = now;
                    if(i==t)  return true;//找到一条可增广路
                    q.push(i);
                }
            }
        }
        return false;//找不到可增广路
    }

2.沿可增广路增流。根据钱取数组，从汇点向前，一直到源点，找到可增广路上所有边的最小值，即为可增量d。然后从汇点向前，一直到源点，残余网络中同向边减流，反向边增流，实流网络中如果是反向边，则减流，否则正向边增流。

    int EK(int s, int t)
    {
        int v,w,d,maxflow;
        maxflow = 0;
        while(bfs(s,t))//可以增广
        {
            v=t;
            d=INF;
            while(v!=s)//找可增量d
            {
                w=pre[v];//w记录v的前驱
                if(d>g[w][v])
                    d=g[w][v];
                v=w;
            }
            maxflow+=d;
            v=t;
            while(v!=s)//沿可增广路增流
            {
                w=pre[v];
                g[w][v]-=d;  //残余网络中正向边减流
                g[v][w]+=d;  //残余网络中反向边增流
                if(f[v][w]>0) //实流网络中如果是反向边,则减流,否则正向边增流
                    f[v][w]-=d;
                else
                    f[w][v]+=d;
                v=w;
             }
        }
        return maxflow;
    }
    
3.输出实流网络

    void print()//输出实流网络
    {
        cout<<endl;
        cout<<"----------实流网络如下：----------"<<endl;
        cout<<"  ";
        for(int i=1;i<=n;i++)
           cout<<setw(7)<<"v"<<i;
        cout<<endl;
        for(int i=1;i<=n;i++)
        {
            cout<<"v"<<i;
            for(int j=1;j<=n;j++)
               cout<<setw(7)<<f[i][j]<<" ";
            cout<<endl;
        }
    }

### 算法复杂度分析
1. 时间复杂度：找到一条可增广路时间是O(E)，最多会执行O(VE)此，因此关键边总数为O(VE)，因此总的时间复杂度为O(VE<sup>2</sup>)。其中V为结点个数，E为边的数量。
2. 空间复杂度：使用了一个二维数组，所以复杂度为O(V<sup>2</sup>)。

### 优化扩展——重贴标签算法ISAP

首先对所有的结点标记到汇点的最短距离，称之为高度。标高从汇点开始，用BFS方式，汇点的邻接点高度为1，继续访问的结点高度是2，一直到源点结束。

贴好标签之后，就可以从源点开始，沿着高度h(u)=h(v)+1且具有可行邻接边（cap>flow)的方向前进。我们找到了1-2-4-6。

我们再次从源点开始搜索，沿着高度h(u)=h(v)+1且具有可行邻接边（cap>flow)的方向前进，h(1)=3,h(2)=2，走到这里无法走到4号结点，因为没有邻接边，3号结点不近没有邻接边，而且高度也不满足条件，也不能走到1号结点，怎么办呢？

可以用**重贴标签**的方法。当前结点无法前进时，令当前结点的高度=所有邻接点高度的最小值+1；如果没有邻接边，则令当前结点的高度=结点数；退回一步，重新搜索。

**算法设计**

1. 确定合适的数据结构。采用邻接表存储网络。
2. 对网络结点贴标签，即标高操作。
3. 如果源点的高度≥结点数，则转向第6步；否则从源点开始，沿着高度h(u)=h(v)+1且具有可行邻接边（cap>flow)的方向前进，如果到达汇点，则转向第4步；如果无法进行，则第5步。
4. 增流操作：沿着找到的可增广路同向边增流，反向边减流。**注意：在原网络上操作**。
5. 重贴标签：如果拥有当前结点高度的结点只有一个，转向第6步；令当前结点的高度=所有邻接点高度的最小值+1；如果没有邻接边，则令当前结点的高度=结点数；退回一步；转向第3步。
6. 算法结束，已经找到最大流。

**算法实现**

    const int inf = 0x3fffffff;
    const int N=100;
    const int M=10000;
    int top;
    int h[N], pre[N], g[N];
    
    struct Vertex
    {
       int first;
    }V[N];
    struct Edge
    {
       int v, next;
       int cap, flow;
    }E[M];
    void init()
    {
        memset(V, -1, sizeof(V));
        top = 0;
    }
    void add_edge(int u, int v, int c)
    {
        E[top].v = v;
        E[top].cap = c;
        E[top].flow = 0;
        E[top].next = V[u].first;
        V[u].first = top++;
    }
    void add(int u,int v, int c)
    {
        add_edge(u,v,c);
        add_edge(v,u,0);
    }
    void set_h(int t,int n)
    {
        queue<int> Q;
        memset(h, -1, sizeof(h));
        memset(g, 0, sizeof(g));
        h[t] = 0;
        Q.push(t);
        while(!Q.empty())
        {
           int v = Q.front(); Q.pop();
           ++g[h[v]];
           for(int i = V[v].first; ~i; i = E[i].next)
           {
              int u = E[i].v;
              if(h[u] == -1)
              {
                 h[u] = h[v] + 1;
                 Q.push(u);
               }
            }
        }
        cout<<"初始化高度"<<endl;
        cout<<"h[ ]=";
        for(int i=1;i<=n;i++)
           cout<<"  "<<h[i];
        cout<<endl;
    }
    int Isap(int s, int t,int n)
    {
        set_h(t,n);
        int ans=0, u=s;
        int d;
        while(h[s]<n)
        {
            int i=V[u].first;
            if(u==s)
               d=inf;
            for(; ~i; i=E[i].next)
            {
               int v=E[i].v;
               if(E[i].cap>E[i].flow && h[u]==h[v]+1)
               {
                    u=v;
                    pre[v]=i;
                    d=min(d, E[i].cap-E[i].flow);
                    if(u==t)
                    {
                       cout<<endl;
                       cout<<"增广路径："<<t;
                       while(u!=s)
                       {
                           int j=pre[u];
                           E[j].flow+=d;
                           E[j^1].flow-=d;
                           u=E[j^1].v;
                           cout<<"--"<<u;
                       }
                       cout<<"增流："<<d<<endl;
                       ans+=d;
                       d=inf;
                    }
                    break;
                }
            }
            if(i==-1)
            {
               if(--g[h[u]]==0)
                  break;
               int hmin=n-1;
               //cur[u]=V[u].first;
               for(int j=V[u].first; ~j; j=E[j].next)
                  if(E[j].cap>E[j].flow)
                     hmin=min(hmin, h[E[j].v]);
               h[u]=hmin+1;
               cout<<"重贴标签后高度"<<endl;
               cout<<"h[ ]=";
               for(int i=1;i<=n;i++)
                  cout<<"  "<<h[i];
               cout<<endl;
               ++g[h[u]];
               if(u!=s)
                  u=E[pre[u]^1].v;
            }
        }
        return ans;
    }
    void printg(int n)//输出网络邻接表
    {
       cout<<"----------网络邻接表如下：----------"<<endl;
       for(int i=1;i<=n;i++)
       {
           cout<<"v"<<i<<"  ["<<V[i].first;
           for(int j=V[i].first;~j;j=E[j].next)
               cout<<"]--["<<E[j].v<<"   "<<E[j].cap<<"   "<<E[j].flow<<"   "<<E[j].next;
           cout<<"]"<<endl;
    
       }
    
    }
    void printflow(int n)//输出实流边
    {
       cout<<"----------实流边如下：----------"<<endl;
       for(int i=1;i<=n;i++)
         for(int j=V[i].first;~j;j=E[j].next)
            if(E[j].flow>0)
            {
               cout<<"v"<<i<<"--"<<"v"<<E[j].v<<"   "<<E[j].flow;
               cout<<endl;
            }
    }

**算法复杂度分析**
时间复杂度：找到一条可增广路时间为O(V)，最多会执行O(VE)次，因为关键边的总数为O(VE)，因此总的时间复杂度为O(V<sup>2</sup>E)，其中V为结点个数，E为边的数量。

空间复杂度O(V)。

## 最小费用路算法——最小费用最大流

### 问题分析
除了流量之外，还定义了一个单位流量的费用。对于网络上的一个流flow，其费用为

$\cos t(flow)=\sum\limits_{<x,y>\in E}{\cos t(x,y)*flow(x,y)}$

网络流的费用=单位流量费用*每条边的流量

### 算法设计

有两种思路：
1. 先找最小费用路，在该路径上增流，增加到最大流，称为**最小费用路算法**。
2. 先找最大流，然后找负费用圈，消减费用，减少到最小费用，称为**消圈算法**。
最小费用路算法，是在残余网络上寻找从源点到汇点的最小费用路，即从源点到汇点的以单位费用为权的最短路，然后沿着最小费用路增流，直到找不到最小费用路为止。

### 算法解释

1. 创建混合网络。先初始化为零流，零流对应混合网络中，正向边容量为cap，流量为0，费用为cost，反向边容量为0，流量为0，费用为-cost。
2. 找最小费用路。先初始化每个结点的距离为无穷大，然后令源点的距离dist[v<sub>1</sub>]=0。在混合网络中，从源点出发，沿可行边（E[i].cap>E[i].flow）广度搜索每个邻接点，如果当前距离dist[v]>dist[u]+E[i].cost，则更新为最短距离：dist[v]=dist[u]+E[i].cost，并记录前驱。***根据前驱数组，找到一条最短费用路，增广路经：1-2-5-6***。
3. 然后沿着增广路经正向增流d，反向减流d。从汇点逆向找最小可增流量d=min(d,E[i].cap-E[i].flow)，增流量d=3，产生费用为mincost+=dist[v<sub>6</sub>]*d=8*3=24。
4. 找最小费用路。先初始化每个结点距离为无穷大，然后令源点的距离dist[v<sub>1</sub>]=0。在混合网络中，从源点出发，沿可行边（E[i].cap>E[i].flow）广度搜索每个邻接点，如果当前距离dist[v]>dist[u]+E[i].cost，则更新为最短距离：dist[v]=dist[u]+E[i].cost，并记录前驱。***根据前驱数组，找到一条最短费用路，增广路经：1-3-4-6***。
5. 然后沿着增广路经正向增流d，反向减流d。从汇点逆向找最小可增流量d=min(d,E[i].cap-E[i].flow)，增流量d=4，产生费用为mincost+=24+dist[v<sub>6</sub>]*d=24+16*4=88。
6. 找最小费用路。先初始化每个结点距离为无穷大，然后令源点的距离dist[v<sub>1</sub>]=0。在混合网络中，从源点出发，沿可行边（E[i].cap>E[i].flow）广度搜索每个邻接点，发现从源点出发已经没有可行边，结束，得到的网络流就是最小费用最大流。把混合网络中flow>0的边输出，就是我们要的实流网络。

### 代码实现

（1）定义结构体。结构体的定义与ISAP中结构体相同，边只是多了一个cost域，fisrt指向第一个邻接边，next是吓一跳邻接边，该结构体用于创建邻接表。

       struct Vertex
    {
       int first;
    }V[N];
    struct Edge
    {
       int v, next;
       int cap, flow,cost;
    }E[M];

（2）创建残余网络边。正向边的容量为cap，流量为0，费用为cost，反向边容量为0，流量为0，费用为-cost。

    void add_edge(int u, int v, int c,int cost)
    {
        E[top].v = v;
        E[top].cap = c;
        E[top].flow = 0;
        E[top].cost = cost;
        E[top].next = V[u].first;
        V[u].first = top++;
    }
    void add(int u,int v, int c,int cost)
    {
        add_edge(u,v,c,cost);
        add_edge(v,u,0,-cost);
    }

（3）求最小费用路。先初始化每个结点距离无穷大，然后令源点的距离dist[v<sub>1</sub>]=0。在混合网络中，从源点出发，沿可行边（E[i].cap>E[i].flow）广度搜索每个邻接点，如果当前距离dist[v]>dist[u]+E[i].cost，则更新为最短距离：dist[v]=dist[u]+E[i].cost，并记录前驱。

    bool SPFA(int s, int t, int n)//求最短费用路的SPFA
    {
        int i, u, v;
        queue <int> qu; // 队列，STL实现
        memset(vis,false,sizeof(vis));//访问标记初始化
        memset(c,0,sizeof(c));   //入队次数初始化
        memset(pre,-1,sizeof(pre)); //前驱初始化
        for(i=1;i<=n;i++)
        {
            dist[i]=INF; //距离初始化
        }
        vis[s]=true; //顶点入队vis要做标记
        c[s]++;     //要统计顶点的入队次数
        dist[s]=0;
        qu.push(s);
        while(!qu.empty())
        {
            u=qu.front();
            qu.pop();
            vis[u]=false;
            //队头元素出队，并且消除标记
            for(i=V[u].first; i!=-1; i=E[i].next)//遍历顶点u的邻接表
            {
                v=E[i].v;
                if(E[i].cap>E[i].flow && dist[v]>dist[u]+E[i].cost)//松弛操作
                {
                    dist[v]=dist[u]+E[i].cost;
                    pre[v]=i; //记录前驱
                    if(!vis[v]) //顶点v不在队内
                    {
                        c[v]++;
                        qu.push(v);   //入队
                        vis[v]=true; //标记
                        if(c[v]>n) //超过入队上限，说明有负环
                            return false;
                    }
                }
            }
        }
        cout<<"最短路数组"<<endl;
        cout<<"dist[ ]=";
        for(int i=1;i<=n;i++)
           cout<<"  "<<dist[i];
        cout<<endl;
        if(dist[t]==INF)
            return false; //如果距离为INF，说明无法到达，返回false
        return true;
    }

（4）沿着最小费用路增流。从汇点逆向找最小可增流量d=min(d,E[i].cap-E[i].flow)。沿着增广路径正向边增流d，反向边减流d，产生费用为mincost+=dist[t]*d。

    int MCMF(int s,int t,int n) //minCostMaxFlow
    {
        int d; //可增流量
        int i,mincost;//maxflow 当前最大流量，mincost当前最小费用
        mincost=0;
        while(SPFA(s,t,n))//表示找到了从s到t的最短路
        {
            d=INF;
            cout<<endl;
            cout<<"增广路径："<<t;
            for(i=pre[t]; i!=-1; i=pre[E[i^1].v])
            {
                d=min(d, E[i].cap-E[i].flow); //找最小可增流量
                cout<<"--"<<E[i^1].v;
            }
            cout<<"增流："<<d<<endl;
            cout<<endl;
            maxflow+=d; //更新最大流
            for(i=pre[t]; i!=-1; i=pre[E[i^1].v])//修改残余网络，增加增广路上相应弧的容量，并减少其反向边容量
            {
                E[i].flow+=d;
                E[i^1].flow-=d;
            }
            mincost+=dist[t]*d; //dist[t]为该路径上单位流量费用之和 ，最小费用更新
       }
        return mincost;
    }

### 复杂度分析

1. 时间复杂度：找到一条可增广路时间为O(E)，最多会执行O(VE)次，因为关键边的总数为O(VE)，因此总的时间复杂度为O(VE<sup>2</sup>)，其中V为结点个数，E为边的数量。
2. 空间复杂度：O(V)。

### 消圈算法

**算法设计**
三个过程：

1. 找给定网络的最大流。
2. 在最大流对应的混合网络找负费用圈。
3. 消负费用圈：负费用圈同方向的边流量加d，反方向的边流量减d。d为负费用圈所有边的最小可增量cap-flow。

算法的核心是**在残余网络中找负费用圈。**

**算法解释**

1. 求最大流。用最大流求解算法求解最大流。
2. 在最大流对应的混合网络中找负费用圈。在最大流的混合网络中，沿着cap>flow的边找负费用圈，就是各边费用之和为负的圈。
3. 负费用圈同方向的边流量加d，反方向的边流量减d。沿找到的负费用全增流，其增量为组成负费用圈的所有边的最小可增量cap-flow。负费用圈说明费用较高，可以对费用为负的边减流，因为该残余网络为特殊的残余网络，负费用的边流量也是负值，减流实际上需要加上增流量d，为了维持平衡性，负费用圈同方向的边流量加d，反方向的边流量减d。
4. 在混合网络中继续找负费用圈。在混合网络中，沿着cap>flow的边找负费用圈，已经找不到负费用圈，算法结束。把混合网络中flow>0的边输出，就是我们需要的实流网络。

**复杂度分析**

1. 时间复杂度：最大流方法为O(V<sup>2</sup>E)，如果每次消去负费用圈至少使费用下降一个单位，最多执行ECM此找负费用圈和增减流操作（C为每条边费用上界，M为每条边容量上界）。该算法时间复杂度为O(V<sup>2</sup>E<sup>2</sup>CM)。
2. 空间复杂度O(V)。

## 配对方案问题

### 问题分析
先了解几个概念。
**二分图**：又称二部图。设G=(V,E)是一个无向图，如果结点集V客分割为两个互不相交的子集（V1,V2），并且图中的每条边（i,j）所关联的两个结点i和j分别属于这两个不同的结点集（i∈V1，j∈V2），则称图G是一个二分图。
**匹配**：在图论中，一个匹配是一个边的集合，其中任意两条边都没有公共结点。
**最大匹配**：一个图所有匹配中，边数最多的匹配，成为这个图的**最大匹配**。

最佳推销员配对方案要求两个推销员男女搭配，相当于男女推销员形成了两个不相交的集合，可以配合工作的男女推销员有连线，求最大配对数，实际上这就是一个简单的**二分图最大匹配**问题。可以借助最大流算法，通过下面的变换，把二分图转化成网络，求最大流即可。

将二分图左边添加1个源点，右边添加一个汇点，将左边的点全部与源点相连，有边的点和汇点相连，所有边容量均为1.前面为女推销员编号，后面为男推销员编号，有连线表示两个人可以配合，男男之间、女女之间没有连线，构成网络。然后求**网络最大流**即可。

### 算法设计

1. 构建网络：根据输入的数据，增加源点和汇点，每条边的容量设置为1，创建混合网络。
2. 求网络最大流。
3. 输出最大流值就是最大的配对数。
4. 搜索女推销员结点的邻接表，流量为1的边对应的邻接点就是该女推销员的配对方案。

### 算法解释

如图1所示的关系。

![图1](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/peiduifangan1.jpg)

图1

1. 构建网络。构建网络如图所示。

![图2](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/peiduifangan2.jpg)

图2

2. 求网络最大流。使用优化的ISAP算法求网络最大流，找到5条可增广路径。分别是：
    - 13-10-5-0，增流：1。
    - 13-9-4-0，增流：1。
    - 13-7-3-0，增流：1。
    - 13-11-2-0，增流：1。
    - 13-8-1-0，增流：1。
增流后的实流网络如图3所示。


3. 输出最大流值就是最多的配对数。搜索女推销员结点的邻接表，流量为1的边对应的邻接点就是该女推销员的配对方案。最大配对数5。配对方案：1-8,2-11,3-7,4-9，5-10。

![图2](https://raw.githubusercontent.com/dqhplhzz2008/Study-notes/master/Algorithm/images/peiduifangan3.jpg)

图3

### 代码实现

（1）创建混合网络邻接表

       for(int i=1;i<=m;i++)
            add(0, i, 1);//源点到女推销员的边
        for(int j=m+1;j<=total;j++)
            add(j, total+1, 1);//男推销员到汇点的边
        cout<<"请输入可以配合的女推销员编号u和男推销员编号v(两个都为-1结束):"<<endl;
        while(cin>>u>>v,u+v!=-2)
            add(u,v,1);

（2） 求网络最大流。

    int Isap(int s, int t,int n)
    {
        set_h(t,n);
        int ans=0, u=s;
        int d;
        while(h[s]<n)
        {
            int i=V[u].first;
            if(u==s)
               d=inf;
            for(; ~i; i=E[i].next)
            {
               int v=E[i].v;
               if(E[i].cap>E[i].flow && h[u]==h[v]+1)
               {
                    u=v;
                    pre[v]=i;
                    d=min(d, E[i].cap-E[i].flow);
                    if(u==t)
                    {
                       cout<<endl;
                       cout<<"增广路径："<<t;
                       while(u!=s)
                       {
                           int j=pre[u];
                           E[j].flow+=d;
                           E[j^1].flow-=d;
                           u=E[j^1].v;
                           cout<<"--"<<u;
                       }
                       cout<<"增流："<<d<<endl;
                       ans+=d;
                       d=inf;
                    }
                    break;
                }
            }
            if(i==-1)
            {
               if(--g[h[u]]==0)
                  break;
               int hmin=n-1;
               //cur[u]=V[u].first;
               for(int j=V[u].first; ~j; j=E[j].next)
                  if(E[j].cap>E[j].flow)
                     hmin=min(hmin, h[E[j].v]);
               h[u]=hmin+1;
               cout<<"重贴标签后高度"<<endl;
               cout<<"h[ ]=";
               for(int i=1;i<=n;i++)
                  cout<<"  "<<h[i];
               cout<<endl;
               ++g[h[u]];
               if(u!=s)
                  u=E[pre[u]^1].v;
            }
        }
        return ans;
    }

（3）输出最佳配对数

    cout<<"最大配对数:"<<Isap(0,total+1,total+2)<<endl;
    cout<<endl;

（4）输出最佳配对方案如下：

    void printflow(int n)//输出配对方案
    {
       cout<<"----------配对方案如下：----------"<<endl;
       for(int i=1;i<=n;i++)
         for(int j=V[i].first;~j;j=E[j].next)
            if(E[j].flow>0)
            {
               cout<<i<<"--"<<E[j].v<<endl;
               break;
            }
    }

### 算法复杂度分析

（1）时间复杂度：O(V<sup>2</sup>E)。
（2）空间复杂度：O(V)。

### 算法优化拓展——匈牙利算法


