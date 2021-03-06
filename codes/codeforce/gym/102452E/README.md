## 题意
T组数据，N（为奇数）个数字$n_i$且$1 < n_i < N$，$n_i$各不相同。
定义消除操作为连续3个数字删除最大最小的数字，留下中位数。
问：进行$\frac{N-1}{2}$次消除后，可能剩下的数字是哪几个？

## 思路
首先观察数据，显然$O(n^2)$是可以接受的。则最直观的算法是遍历每个数，O(n)判断能否留下这个数。
方便起见，对于当前数$n_i$我们把比它大的数设为1，比它小的数设为0.
经过一番思考，我们发现对于一个数而言，若此刻数组中1和0个数相同，则该数必定可以留下。（若01有相邻的位置，那么在相邻位置消除可以保证每次消除一个0和一个1，01个数依然相等。若01不相邻，则它们与$n_i$相邻，则可以在$n_i$处消除，也能保证每次消除一个0和一个1）。
因此对于0、1不相等的情况，我们需要尝试通过消去一些0或者1来使得两者相等。不难发现的是，只有诸如000、111这类排列的消去才能使得0、1相等，因此我们只需要尽可能的找到000、111的排列来消去它，至于消去000还是消去111，取决于当前0和1的数量谁更大，消去数量大的。
