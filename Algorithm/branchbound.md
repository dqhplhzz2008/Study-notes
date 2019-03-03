## 广度优先

广度优先搜索，其实就是层次遍历，程序采用**队列**来实现。

### 算法思想
从根开始，常以BF或以最小耗费（即最大收益）优先的方式搜索问题的解空间树。首先将根结点加入活结点表，接着从活结点表中取出根结点，使其成为当前扩展结点，一次性生成其所有孩子结点，判断孩子结点是舍弃还是保留，舍弃哪些导致不可行解或导致非最优解的孩子结点，其余的被保留在活结点表中。再从活结点表中取出一个活结点作为当前扩展结点，重复上述扩展过程，直到找到所需的解或活结点表为空时为止。**每一个活结点最多只有一次机会成为扩展结点。**

### 算法步骤

算法解题步骤为：
1. 定义问题的解空间。
2. 确定问题的解空间组织结构。
3. 搜索解空间。搜索前要定义判断标准（约束函数或限界函数），如果选优优先队列式分支限界法，则必须确定优先级。


### 回溯法与分支限界法的异同
1.相同点：

- 均需要先定义问题的解空间，确定的解空间组织结构一般都是树和图；
- 在问题的解空间树上搜索问题解。
- 搜索前均需要确定判断条件，该判断条件用于判断扩展生成的结点是否为可行结点。
- 搜索过程中必须判断扩展生成的结点是否满足判断条件，如果满足则保留该扩展结点，否则舍弃。

2.不同点

- 搜索目标不同：回溯法的求解目标是找出解空间树中满足约束条件的**所有解**，而分支界限法的求解目标则是找出满足约束条件的**一个解**，或者是在满足约束条件的解中找出在某种意义下的**最优解**。
- 搜索的方式不同：回溯法以**深度优先搜索**方法搜索空间树，分支限界法采用**广度优先法**或者**最小消耗优先**搜索解空间树。
- 扩展方式不同：回溯法搜索，扩展结点一次只生成**一个孩子结点**，而分支限界法则一次生成**所有孩子结点**。

## 0-1背包问题

### 问题分析

前面有，不再重述，

|w[]|1|2|3|4
| ------ | ------ | ------ | ------| ------|
||2|5|4|2 

|v[]|1|2|3|4
| ------ | ------ | ------ | ------| ------|
||6|3|5|4 

购物车重量W=10。
商品的结构体定义为：

    struct Goods
    {
    	int weight;
    	int value;
    } goods[N];

|weight|2|5|4|2|
|--|--|--|--|--|
|value|6|3|5|4|

### 算法设计
1. 定义问题的解空间。问题解空间为{x<sub>1</sub>,x<sub>2</sub>,...,x<sub>i</sub>,...,x<sub>n</sub>}，显约束为：x<sub>i</sub>=0或者1。
2. 确定解空间的组织结构：子集树。
3. 搜索解空间：
    - 约束条件为：w<sub>i</sub>x<sub>i</sub>≤W（i=1~n）
    - 限界条件：cp+rp>bestp（cp为当前已经装入购物车的物品的总价值，rp为第t+1~第n种物品的总价值，bestp为最大价值）

4. 搜索过程：从根节点开始，以BFS方式进行搜索。根节点首先成为活结点，也是当前的扩展结点。一次性生成所有孩子结点，由于子集树中约定左分支上的值为“1”，因此沿着扩展结点的左分支扩展，则代表装入物品；右分支的值为“0”，代表不装入物品。此时判断是否满足约束条件和限界条件，如果满足，则将其加入队列中；反之舍弃。然后再从队列中取出一个元素，作为当前扩展结点，搜索过程队列为空时结束。


### 步骤解释

1. 初始化。sumw=2+5+4+2=13，sumv=6+3+5+4=18，因为**sumw>W**，所以不能装完，所以需要进行后续的操作。初始化cp=0,rp=sumv，当前剩余重量rw=W；当前处理物品序号为1；当前最优值bestp=0.解向量为x[]=(0,0,0,0)，创建一个根结点Node(cp,rp,rw,id)，标记为A，加入先进先出队列q中。cp为装入购物车的物品价值，rp为剩余物品的总价值，rw为剩余容量，id为物品号，x[]为当前解向量。

//定义结点。每个节点来记录当前的解。
struct Node

    {
        int cp, rp; //cp背包的物品总价值，rp剩余物品的总价值
        int rw; //剩余容量
        int id; //物品号
        bool x[N];//解向量
        Node() {}
        Node(int _cp, int _rp, int _rw, int _id){
            cp = _cp;
            rp = _rp;
            rw = _rw;
            id = _id;
            memset(x, 0, sizeof(x));//解向量初始化为0
        }
    };

2. 扩展A结点。队头元素A出队，该结点的cp+rp≥bestp，满足限界条件，可以扩展。rw=10>goods[1].weight=2，剩余容量大于1号物品，满足约束条件，可以放入购物车，cp=0+6=6。rp=18-6=12，rw=10-2=8，t=2，x[1]=1，解向量更新为x[]=(1,0,0,0)，生成左孩子B，加入q队列，更新bestp=6。**再扩展右分支**，cp=0,rp=18-6=12,cp+rp>=bestp=6，满足限界条件，不放入1号物品，cp=0,rp=12,rw=10,t=2,x[1]=0，解向量为x[]=(0,0,0,0)，创建新结点C，加入q队列。如下表所示，**X表示为空**。

|B|X|X|X|
|--|--|--|--|

|B|C|X|X|
|--|--|--|--|

3. 扩展B结点。队头元素B出队，该结点cp+rp>=bestp，满足限界条件，可以扩展。rw=8>goods[2].weight=5，剩余容量大于2号物品重量，满足约束条件，可以放入购物车，cp=6+3=9。rp=12-3=9，rw=8-5=3，t=3，x[2]=1，解向量更新为x[]=(1,1,0,0)，生成左孩子D，加入q队列，更新bestp=9。**再扩展右分支**，cp=6,rp=12-3=9,cp+rp>=bestp=9，满足限界条件，不放入2号物品，cp=6,rp=9,rw=8,t=3,x[2]=0，解向量为x[]=(1,0,0,0)，创建新结点E，加入q队列。如下表所示。

|C|D|E|X|
|--|--|--|--|

4. 扩展C结点。队头元素C出队，该结点cp+rp>=bestp，满足限界条件，可以扩展。rw=10>goods[2].weight=5，剩余容量大于2号物品重量，满足约束条件，可以放入购物车，cp=0+3=3。rp=12-3=9，rw=10-5=5，t=3，x[2]=1，解向量更新为x[]=(0,1,0,0)，生成左孩子F，加入q队列。**再扩展右分支**，cp=0,rp=12-3=9,cp+rp>=bestp=9，满足限界条件，不放入2号物品，cp=6,rp=9,rw=10,t=3,x[2]=0，解向量为x[]=(0,0,0,0)，创建新结点G，加入q队列。如下表所示。

|D|E|F|G
|--|--|--|--|

5. 扩展D结点。队头元素D出队，该结点cp+rp>=bestp，满足限界条件，可以扩展。但是rw=3>goods[3].weight=4，所以不满足约束条件，舍弃左分支。**扩展右分支**，cp=9,rp=9-5=4,cp+rp>=bestp=9，满足限界条件，不放入3号物品，cp=9,rp=4,rw=3,t=4,x[3]=0，解向量为x[]=(1,1,0,0)，创建新结点H，加入q队列。如下表所示。

|E|F|G|H|
|--|--|--|--|

6. 扩展E结点。同理可得cp=11,rp=4,rw=4,t=4,x[3]=1，更新解向量为x[]=(1,0,1,0)，生成左孩子I，加入q队列，更新bestp=11。**扩展右分支**，cp=6,rp=9-5=4,cp+rp=10<bestp=11，所以不满足限界条件，舍弃。
7. 扩展F结点。同理得到左分支，cp=8,rp=4,rw=1,t=4,x[3]=1，解向量为x[]=(0,1,1,0)，生成左孩子J，加入q队列。**扩展右分支**，cp+rp<11，舍弃。
8. 扩展G结点。该结点cp+rp<bestp=11，不满足限界条件，不再扩展。
9. 扩展H结点。队头H结点出队，该结点cp+rp>=bestp，满足限界条件，rw=3>goods[4].weight=2，满足约束条件，令cp=9+4=13,rp=4-4=0,rw=3-2=1,t=5,x[4]=1，解向量更新为x[]=(1,1,0,1)，生成孩子K，加入q队列，更新bestp=13。右分支不满足限界条件舍弃。
10. 扩展I结点。 队头I结点出队，该结点cp+rp>=bestp，满足限界条件，rw=4>goods[4].weight=2，满足约束条件，令cp=11+4=15,rp=4-4=0,rw=4-2=2,t=5,x[4]=1，解向量更新为x[]=(1,0,1,1)，生成孩子L，加入q队列，更新bestp=15。右分支不满足限界条件舍弃。
11. 队头元素J出队，该结点cp+rp=12<15，不满足限界条件，不再扩展。
12. 队头元素K出队，扩展K结点：t=5，已经处理完毕，cp<bestp，不是最优解。
13. 队头元素K出队，扩展K结点：t=5，已经处理完毕，cp=bestp，是最优解，输出该向量(1,0,1,1)。
14. 队列为空，算法结束。

### 代码实现

    int bestp, W, n, sumw, sumv;
    /*
    bestp 用来记录最优解。
    W为购物车最大容量。
    n为物品的个数。
    sumw 为所有物品的总重量。
    sumv 为所有物品的总价值。
    */
    //bfs 来进行子集树的搜索。
    int bfs()
    {
    	int t, tcp, trp, trw;
    	queue<Node> q; //创建一个普通队列(先进先出)
    	q.push(Node(0, sumv, W, 1)); //压入一个初始结点
    	while (!q.empty()) //如果队列不空
    	{
    		Node livenode, lchild, rchild;//定义三个结点型变量
    		livenode = q.front();//取出队头元素作为当前扩展结点livenode
    		q.pop(); //队头元素出队
    				 //cp+rp>bestp当前装入的价值+剩余物品价值小于当前最优值时，不再扩展。
    		cout << "当前结点的id值:" << livenode.id << "当前结点的cp值:" << livenode.cp << endl;
    		cout << "当前结点的解向量:";
    		for (int i = 1; i <= n; i++)
    		{
    			cout << livenode.x[i];
    		}
    		cout << endl;
    		t = livenode.id;//当前处理的物品序号
    						// 搜到最后一个物品的时候不需要往下搜索。
    						// 如果当前的购物车没有剩余容量(已经装满)了，不再扩展。
    		if (t>n || livenode.rw == 0)
    		{
    			if (livenode.cp >= bestp)//更新最优解和最优值
    			{
    				for (int i = 1; i <= n; i++)
    				{
    					bestx[i] = livenode.x[i];
    				}
    				bestp = livenode.cp;
    			}
    			continue;
    		}
    		if (livenode.cp + livenode.rp<bestp)//判断当前结点是否满足限界条件，如果不满足不再扩展
    			continue;
    		//扩展左孩子
    		tcp = livenode.cp; //当前购物车中的价值
    		trp = livenode.rp - goods[t].value; //不管当前物品装入与否，剩余价值都会减少。
    		trw = livenode.rw; //购物车剩余容量
    		if (trw >= goods[t].weight) //满足约束条件，可以放入购物车
    		{
    			lchild.rw = trw - goods[t].weight;
    			lchild.cp = tcp + goods[t].value;
    			lchild = Node(lchild.cp, trp, lchild.rw, t + 1);//传递参数
    			for (int i = 1; i<t; i++)
    			{
    				lchild.x[i] = livenode.x[i];//复制以前的解向量
    			}
    			lchild.x[t] = true;
    			if (lchild.cp>bestp)//比最优值大才更新
    				bestp = lchild.cp;
    			q.push(lchild);//左孩子入队
    		}
    		//扩展右孩子
    		if (tcp + trp >= bestp)//满足限界条件，不放入购物车
    		{
    			rchild = Node(tcp, trp, trw, t + 1);//传递参数
    			for (int i = 1; i<t; i++)
    			{
    				rchild.x[i] = livenode.x[i];//复制以前的解向量
    			}
    			rchild.x[t] = false;
    			q.push(rchild);//右孩子入队
    		}
    	}
    	return bestp;//返回最优值。
    }

### 算法分析

时间复杂度为O(2<sup>n+1</sup>)，空间复杂度O(n*2<sup>n+1</sup>)。

### 算法优化拓展——优先队列式分支限界法
优先队列优化，简单来说就是以当前结点的上界为优先值，把普通队列改成优先队列。
1. 算法设计。约束条件没有改变。优先级定义为活结点代表的部分解锁描述的装入物品价值的上界，该价值上界越大，优先级越高。活结点的价值上界up=活结点的cp+剩余物品装满购物车剩余容量的最大价值rp'。限界条件变为**up=cp+rp'>=bestp**。
2. 解题步骤（简略版）
    - 初始化。sumw和sumv分别用来统计所有物品的总重量和总价值。sumw=13,sumv=18,sumw>W，所以不能全部装完，需要搜索求解。
    - **按价值重量比非递增排序**。排序结果如下表所示。
    - 后续不再详细叙述。

|weight|2|2|4|5|
|--|--|--|--|--|
|value|6|4|5|3|

3.代码实现

    //定义辅助物品结构体，包含物品序号和单位重量价值,用于按单位重量价值(价值/重量比)排序、
    struct Object
     {
            int id; //物品序号
            double d;//单位重量价值
        }S[N];
        
    //定义排序优先级按照物品单位重量价值由大到小排序
    bool cmp(Object a1,Object a2)
    {
        return a1.d>a2.d;
    }
    
    //定义队列的优先级。 以up为优先，up值越大，也就越优先
    bool operator <(const Node &a, const Node &b)
    {
        return a.up<b.up;
    }
    
    int bestp,W,n,sumw,sumv;
    /*
      bestv 用来记录最优解。
      W为背包的最大容量。
      n为物品的个数。
      sumw 为所有物品的总重量。
      sumv 为所有物品的总价值。
    */
    
    double Bound(Node tnode)
    {
        double maxvalue=tnode.cp;//已装入购物车物品价值
        int t=tnode.id;//排序后序号
        //cout<<"t="<<t<<endl;
        double left=tnode.rw;//剩余容量
        while(t<=n&&w[t]<=left)
        {
            maxvalue+=v[t];
           // cout<<"malvalue="<<maxvalue<<endl;
            left-=w[t];
            t++;
        }
        if(t<=n)
            maxvalue+=double(v[t])/w[t]*left;
        //cout<<"malvalue="<<maxvalue<<endl;
        return maxvalue;
    }
    //priorbfs 为优先队列式分支限界法搜索。
    int priorbfs()
    {
         int t,tcp,trw;
         double tup; //当前处理的物品序号t，当前装入购物车物品价值tcp，
        //当前装入购物车物品价值上界tup，当前剩余容量trw
        priority_queue<Node> q; //创建一个优先队列,优先级为装入购物车的物品价值上界up
        q.push(Node(0, sumv, W, 1));//初始化,根结点加入优先队列
        while(!q.empty())
        {
            Node livenode, lchild, rchild;//定义三个结点型变量
            livenode=q.top();//取出队头元素作为当前扩展结点livenode
            q.pop(); //队头元素出队
            cout<<"当前结点的id值:"<<livenode.id<<"当前结点的up值:"<<livenode.up<<endl;
            cout<<"当前结点的解向量:";
            for(int i=1; i<=n; i++)
            {
                cout<<livenode.x[i];
            }
            cout<<endl;
            t=livenode.id;//当前处理的物品序号
            // 搜到最后一个物品的时候不需要往下搜索。
            // 如果当前的购物车没有剩余容量(已经装满)了，不再扩展。
            if(t>n||livenode.rw==0)
            {
                if(livenode.cp>=bestp)//更新最优解和最优值
                {
                  cout<<"更新最优解向量:";
                  for(int i=1; i<=n; i++)
                  {
                    bestx[i]=livenode.x[i];
                    cout<<bestx[i];
                  }
                  cout<<endl;
                  bestp=livenode.cp;
                }
                continue;
            }
            //判断当前结点是否满足限界条件，如果不满足不再扩展
            if(livenode.up<bestp)
              continue;
            //扩展左孩子
            tcp=livenode.cp; //当前购物车中的价值
            trw=livenode.rw; //购物车剩余容量
            if(trw>=w[t]) //满足约束条件，可以放入购物车
            {
                lchild.cp=tcp+v[t];
                lchild.rw=trw-w[t];
                lchild.id=t+1;
                tup=Bound(lchild); //计算左孩子上界
                lchild=Node(lchild.cp,tup,lchild.rw,lchild.id);//传递参数
                for(int i=1;i<=n;i++)
                {
                  lchild.x[i]=livenode.x[i];//复制以前的解向量
                }
                lchild.x[t]=true;
                if(lchild.cp>bestp)//比最优值大才更新
                   bestp=lchild.cp;
                q.push(lchild);//左孩子入队
            }
            //扩展右孩子
             rchild.cp=tcp;
             rchild.rw=trw;
             rchild.id=t+1;
             tup=Bound(rchild); //右孩子计算上界
             if(tup>=bestp)//满足限界条件，不放入购物车
             {
                rchild=Node(tcp,tup,trw,t+1);//传递参数
                for(int i=1;i<=n;i++)
                {
                  rchild.x[i]=livenode.x[i];//复制以前的解向量
                }
                rchild.x[t]=false;
                q.push(rchild);//右孩子入队
              }
        }
        return bestp;//返回最优值。
    }


## 旅行商问题

### 问题分析
带权邻接矩阵g[][]如下所示，空表示为无穷，即没有路径。

|  |15|30|5|
|--|--|--|--|
|15|  |6|12|
|30|6|  |3|
|5|12|3|  |

### 算法设计
可以使用优先队列分支限界法，加快搜索速度。
设置优先级：当前已走过的城市所有的路径长度cl。cl越小，优先级越高。
从根节点开始，以广度优先的方式进行搜索。根节点首先成为活结点，也是当前的扩展结点。一次性生成所有的孩子结点，判断孩子结点是否满足约束条件和限界条件，如果满足，将其加入到队列中，反之，舍弃。然后再从队列中取出一个元素，作为当前扩展结点，搜索过程队列为空时为止。

### 代码实现

    struct Node//定义结点,记录当前结点的解信息
    {
        double cl; //当前已走过的路径长度
        int id; //景点序号
        int x[N];//记录当前路径
        Node() {}
        Node(double _cl,int _id)
        {
            cl = _cl;
            id = _id;
        }
    };
    
    //定义队列的优先级。 以cl为优先级，cl值越小，越优先
    bool operator <(const Node &a, const Node &b)
    {
        return a.cl>b.cl;
    }
    
    //Travelingbfs 为优先队列式分支限界法搜索
    double Travelingbfs()
    {
        int t; //当前处理的景点序号t
        Node livenode,newnode;//定义当前扩展结点livenode,生成新结点newnode
        priority_queue<Node> q; //创建一个优先队列,优先级为已经走过的路径长度cl,cl值越小，越优先
        newnode=Node(0,2);//创建根节点
        for(int i=1;i<=n;i++)
        {
           newnode.x[i]=i;//初时化根结点的解向量
        }
        q.push(newnode);//根结点加入优先队列
        cout<<"按优先级出队顺序："<<endl;//用于调试
        while(!q.empty())
        {
            livenode=q.top();//取出队头元素作为当前扩展结点livenode
            q.pop(); //队头元素出队
            //用于调试
            cout<<"当前结点的id值:"<<livenode.id<<"当前结点的cl值:"<<livenode.cl<<endl;
            cout<<"当前结点的解向量:";
            for(int i=1; i<=n; i++)
            {
                cout<<livenode.x[i];
            }
            cout<<endl;
            t=livenode.id;//当前处理的景点序号
            // 搜到倒数第2个结点时个景点的时候不需要往下搜索
            if(t==n)  //立即判断是否更新最优解，
                //例如当前找到一个路径(1243)，到达4号结点时，立即判断g[4][3]和g[3][1]是否有边相连，
                //如果有边则判断当前路径长度cl+g[4][3]+g[3][1]<bestl，满足则更新最优值和最优解
            {
               //说明找到了一条更好的路径，记录相关信息
               if(g[livenode.x[n-1]][livenode.x[n]]!=INF&&g[livenode.x[n]][1]!=INF)
                 if(livenode.cl+g[livenode.x[n-1]][livenode.x[n]]+g[livenode.x[n]][1]<bestl)
                 {
                    bestl=livenode.cl+g[livenode.x[n-1]][livenode.x[n]]+g[livenode.x[n]][1];
                    cout<<endl;
                    cout<<"当前最优的解向量:";
                    for(int i=1;i<=n;i++)
                    {
                      bestx[i]=livenode.x[i];
                      cout<<bestx[i];
                    }
                    cout<<endl;
                    cout<<endl;
                  }
                continue;
            }
            //判断当前结点是否满足限界条件，如果不满足不再扩展
           if(livenode.cl>=bestl)
              continue;
            //扩展
            //没有到达叶子结点
            for(int j=t; j<=n; j++)//搜索扩展结点的所有分支
            {
                if(g[livenode.x[t-1]][livenode.x[j]]!=INF)//如果x[t-1]景点与x[j]景点有边相连
                {
                    double cl=livenode.cl+g[livenode.x[t-1]][livenode.x[j]];
                    if(cl<bestl)//有可能得到更短的路线
                    {
                        newnode=Node(cl,t+1);
                        for(int i=1;i<=n;i++)
                        {
                          newnode.x[i]=livenode.x[i];//复制以前的解向量
                        }
                        swap(newnode.x[t], newnode.x[j]);//交换x[t]、x[j]两个元素的值
                        q.push(newnode);//新结点入队
                    }
                }
            }
        }
        return bestl;//返回最优值。
    }
（1）时间复杂度：O(n!)。空间复杂度：O(n*n!)。

### 算法优化拓展
1. 算法开始时创建一个用于表示活结点优先队列。每个结点的费用下界zl=cl+rl值作为优先级。cl表示已经走过的路径长度，rl表示剩余路径长度的下界，rl用剩余每个结点的最小出边之和来计算。初始时先计算图中每个顶点i的最小出边，并用minout[i]数组记录，minsum记录所有结点的最小出边之和。如果所给的有向图中某个顶点没有出边，则该图不可能有回路，算法立即结束。
    - 限界条件：zl<bestl，zl<cl+rl。
2. 优先级：zl指已经走过的路径长度+剩余路径长度的下界。zl越小，优先级越高。

### 算法优化代码实现
1.定义节点结构体


    //定义结点,记录当前结点的解信息
    struct Node
    {
        double cl; //当前已走过的路径长度
        double rl; //剩余路径长度的下界
        double zl; //当前路径长度的下界zl=rl+cl
        int id; //景点序号
        int x[N];//记录当前解向量
        Node() {}
        Node(double _cl,double _rl,double _zl,int _id)
        {
            cl = _cl;
            rl = _rl;
            zl = _zl;
            id = _id;
        }
    };

2.定义队列优先级

    bool operator <(const Node &a, const Node &b)
    {
        return a.zl>b.zl;
    }

3.计算下界

    bool Bound()//计算下界（即每个景点最小出边权值之和）
    {
        for(int i=1;i<=n;i++)
        {
           double minl=INF;//初时化景点点出边最小值
           for(int j=1;j<=n;j++)//找每个景点的最小出边
             if(g[i][j]!=INF&&g[i][j]<minl)
                minl=g[i][j];
           if(minl==INF)
              return false;//表示无回路
           minout[i]=minl;//记录每个景点的最少出边
           cout<<"第"<<i<<"个景点的最少出边:"<<minout[i]<<" "<<endl;
           minsum+=minl;//记录所有景点的最少出边之和
        }
        cout<<"每个景点的最少出边之和:""minsum= "<<minsum<<endl;
        return true;
    }

4.Travelingbfsopt 为优化的优先队列式分支限界法

    double Travelingbfsopt()
    {
        if(!Bound())
            return -1;//表示无回路
        Node livenode,newnode;//定义当前扩展结点livenode,生成新结点newnode
        priority_queue<Node> q; //创建一个优先队列,优先级为当前路径长度的下界zl=rl+cl,zl值越小，越优先
        newnode=Node(0,minsum,minsum,2);//创建根节点
        for(int i=1;i<=n;i++)
        {
           newnode.x[i]=i;//初时化根结点的解向量
        }
        q.push(newnode);//根结点加入优先队列
        while(!q.empty())
        {
            livenode=q.top();//取出队头元素作为当前扩展结点livenode
            q.pop(); //队头元素出队
            cout<<"当前结点的id值:"<<livenode.id<<"当前结点的zl值:"<<livenode.zl<<endl;
            cout<<"当前结点的解向量:";
            for(int i=1; i<=n; i++)
            {
                cout<<livenode.x[i];
            }
            cout<<endl;
            int t=livenode.id;//当前处理的景点序号
            // 搜到倒数第2个结点时个景点的时候不需要往下搜索
            if(t==n)  //立即判断是否更新最优解，
                //例如当前找到一个路径(1243)，到达4号结点时，立即判断g[4][3]和g[3][1]是否有边相连，
                //如果有边则判断当前路径长度cl+g[4][3]+g[3][1]<bestl，满足则更新最优值和最优解
            {
               //说明找到了一条更好的路径，记录相关信息
               if(g[livenode.x[n-1]][livenode.x[n]]!=INF&&g[livenode.x[n]][1]!=INF)
                 if(livenode.cl+g[livenode.x[n-1]][livenode.x[n]]+g[livenode.x[n]][1]<bestl)
                 {
                    bestl=livenode.cl+g[livenode.x[n-1]][livenode.x[n]]+g[livenode.x[n]][1];
                    cout<<endl;
                    cout<<"当前最优的解向量:";
                    for(int i=1;i<=n;i++)
                    {
                      bestx[i]=livenode.x[i];
                      cout<<bestx[i];
                    }
                    cout<<endl;
                    cout<<endl;
                  }
                continue;
            }
            //判断当前结点是否满足限界条件，如果不满足不再扩展
           if(livenode.cl>=bestl)
              continue;
            //扩展
            //没有到达叶子结点
            for(int j=t; j<=n; j++)//搜索扩展结点的所有分支
            {
                if(g[livenode.x[t-1]][livenode.x[j]]!=INF)//如果x[t-1]景点与x[j]景点有边相连
                {
                    double cl=livenode.cl+g[livenode.x[t-1]][livenode.x[j]];
                    double rl=livenode.rl-minout[livenode.x[j]];
                    double zl=cl+rl;
                    if(zl<bestl)//有可能得到更短的路线
                    {
                        newnode=Node(cl,rl,zl,t+1);
                        for(int i=1;i<=n;i++)
                        {
                          newnode.x[i]=livenode.x[i];//复制以前的解向量
                        }
                        swap(newnode.x[t], newnode.x[j]);//交换两个元素的值
                        q.push(newnode);//新结点入队
                    }
                }
            }
        }
        return bestl;//返回最优值。
    }
### 算法复杂度分析
时间复杂度最坏为O(nn!)，空间复杂度为O(n<sup>2</sup>*(n+1)!)。


## 最优工程布线问题

### 问题描述
在3×3的方格阵列，灰色表示封锁，不能通过。将每个方格抽象为一个结点，方格和相邻4个方向（上下左右）中能通过的方格用一条线连接起来，不能通过的方格不连线。这样，可以把问题的解空间定义为**一个图**，如下图所示。

![](https://dqhplhzz2008-1251830035.cos.ap-guangzhou.myqcloud.com/wp-content/uploads/2019/03/zuiyougongcheng1.jpg) ![](https://dqhplhzz2008-1251830035.cos.ap-guangzhou.myqcloud.com/wp-content/uploads/2019/03/zuiyougongcheng2.jpg)

该问题是特殊的最短路径问题，特殊之处在于用布线走过的方格数代表布线的长度，布线时每一个方格，布线长度累加1.我们可以看出，从a到b有多种布线方案，最短的布线长度即从a到b的最短路径长度为4。
既然只能朝四个方向布线，也就是说如果从树型搜索的角度来看，我们可以把它看做为m叉树，那么问题的解空间就变成了一颗m叉树。

### 算法设计
（1）定义问题的解空间。可以把最优工程布线问题解的形式为n元组{x<sub>1</sub>,x<sub>2</sub>,...,x<sub>i</sub>,...,x<sub>n</sub>}，分量x<sub>i</sub>表示最优布线方案经过的第i个方格，而方格也可以用(x,y)表示第x行第y列。因为方格不可重复布线，所以在确定x<sub>i</sub>的时候，前面走过的方格{x<sub>1</sub>,x<sub>2</sub>,...,x<sub>i-1</sub>}都不可以再走，x<sub>i</sub>的取值范围为**S-{x<sub>1</sub>,x<sub>2</sub>,...,x<sub>i-1</sub>}**。
<font color="red">**注意：和前面问题不同，因为不知道最优布线长度，所以n是未知的。**</font>

（2）解空间的组织结构：一颗m叉树，m=4，树的深度n未知。

（3）搜索解空间。搜索从起始结点a开始，到目标节点b结束。
- 约束条件：非障碍物或边界未曾布线。
- 限界条件：最先碰到的一定是距离最短的，因此无限界条件。
- 搜索过程：从a开始将其作为第一个扩展结点，沿a的右、下、左、上4个方向的相邻结点扩展。判断约束条件是否成立，若成立，则放入活结点中，并将这个方格标记为1。接着从活结点队列中取出队首结点作为下一个扩展结点，并沿当前扩展结点的右、下、左、上四个方向的相邻结点扩展，将满足约束条件的方格记为2，依此类推，一直继续搜索到目标方格或活结点为空为止，目标方格里的数据就是最优的布线长度。

构造最优解过程从目标节点开始，沿着右、下、左、上四个方向。判断如果某个方向方格里的数据比扩展结点方格的数据小1，则进入该方向方格，使其成为当前的扩展结点。以此类推，搜索过程一直持续到起始结点结束。

### 算法实现

    //定义结构体position
    typedef struct
    {
    	int x;
    	int y;
    } Position;//位置
    int grid[100][100];//地图
    bool findpath(Position s, Position e, Position *&path, int &PathLen)
    {
    	if ((s.x == e.x) && (s.y == e.y))//开始位置就是结束位置
    	{
    		PathLen = 0;
    		return true;
    	}
    	Position DIR[4], here, next;
    	//定义方向数组DIR[4]，当前位置here，下一个位置next
    	DIR[0].x = 0;
    	DIR[0].y = 1;
    	DIR[1].x = 1;
    	DIR[1].y = 0;
    	DIR[2].x = 0;
    	DIR[2].y = -1;
    	DIR[3].x = -1;
    	DIR[3].y = 0;
    	here = s;
    	grid[s.x][s.y] = 0;//标记初始为0，未布线为-1，墙壁为-2
    	queue<Position> Q;//所使用队列
    	//按四个方向进行搜索
    	for (;;)
    	{
    		for (int i = 0; i < 4; i++)//四个方向前进，右下左上
    		{
    			next.x = here.x + DIR[i].x;
    			next.y = here.y + DIR[i].y;
    			if (grid[next.x][next.y] == -1)//未布线
    			{
    				grid[next.x][next.y] = grid[here.x][here.y] + 1;
    				Q.push(next);
    			}
    			if ((next.x == e.x) && (next.y == e.y))
    				break;//找到了我们需要的目标
    		}
    		if ((next.x == e.x) && (next.y == e.y))
    			break;//找到了我们需要的目标
    		if (Q.empty())
    			return false;
    		else
    		{
    			here = Q.front();
    			Q.pop();//把Q队头的元素弹出
    		}
    	}
    	//逆向找回最短布线方案
    	PathLen = grid[e.x][e.y];//最短的长度
    	path = new Position[PathLen];
    	here = e;
    	for (int j = PathLen - 1; j >= 0; j--)
    	{
    		path[j] = here;
    		//沿着四个方向寻找，右下左上
    		for (int i = 0; i < 4; i++)
    		{
    			next.x = here.x + DIR[i].x;
    			next.y = here.y + DIR[i].y;
    			if (grid[next.x][next.y] == j)
    				break;
    		}
    		here = next;
    	}
    	return true;
    }
    //初始化地图，标记大于0表示已经布线，-1未布线，-2墙壁
    void init(int m, int n)
    {
    	for (int i = 1; i <= m; i++)
    		for (int j = 1; j <= n; j++)
    			grid[i][j] = -1;
    	//上面是先将所有的格子都初始化为-1
    	//然后把本问题为了方便加上的第0行和第0列都设置为墙
    	for (int i = 0; i <= n + 1; i++)
    		grid[0][i] = grid[m + 1][i] = -2;
    	for (int i = 0; i <= m + 1; i++)
    		grid[i][0] = grid[i][n + 1] = -2;
    }

### 复杂度分析
时间复杂度O(nm)，构造最短布线需要O(L)，空间复杂度O(n)。




