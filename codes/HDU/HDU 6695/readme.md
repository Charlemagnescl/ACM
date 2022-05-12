
# HDU 6695

- [HDU 6695](#hdu-6695)
  - [题意](#题意)
  - [题解](#题解)
    - [贪心策略](#贪心策略)
    - [贪心策略证明](#贪心策略证明)
  - [题解来源](#题解来源)

## 题意
有n个人，两种节目，每个人都要且只能表演一种节目，每种节目至少要一个人来演。用$x_i$和$y_i$表示第$i(1 \leq i \leq n)$个人的表演两种节目的能力值。要求表演第一种节目的人中的能力最大值和表演第二种节目的能力最大值之差最小，求该最小值。

## 题解

### 贪心策略
维护两个集合$s_1$和$s_2$。（这两个集合都只存储y）

按$x$从大到小枚举。相当于我们取当前$x_i$为第一种节目最大值，大于$x_i$的部分自然全部扔到$s_2$集合作为表演第二种节目的人，对于这一部分，我们找到$y_z$最大的人$z$。对于$x_j \leq x_i$的部分，我们挑选$y_j$与$x_i$最接近的第$j$个人$j$。$ans = min(ans,abs(x_i-max(y_j,y_z)))$，维护最小ans即可

### 贪心策略证明
由于这种贪心策略枚举了每个$x_i$作为答案，因此如果该贪心策略错误，意味着在某个正确的$x_i$下，该贪心策略选择了错误的$y_j$。但是集合$s_1$保证了能够取到$x_i$作为答案，因此对于上述的$y_z$选择是唯一的。对于$s_2$，我们选择了最接近$x_i$的$y_j$作为答案，也符合最优解的性质，因此不可能有其他的最优解。因此贪心策略正确。

## 题解来源
https://wutao18.github.io/2019/08/23/HDU-6695-Welcome-Party-%E8%B4%AA%E5%BF%83/
在这位dalao的基础上又加上了贪心策略的证明（希望是对的，当然是错的也请务必指出）。